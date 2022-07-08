#include "Checks.h"

#include "templates/params/creature/CreaturePosture.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::creature::ai::bt::leaf;

template<> bool CheckPosture::check(AiAgent* agent) const {
	return agent->getPosture() == checkVar;
}

template<> bool CheckDestination::check(AiAgent* agent) const {
	return agent->setDestination() > checkVar;
}

template<> bool CheckMovementState::check(AiAgent* agent) const {
	return agent->getMovementState() == checkVar;
}

template<> bool CheckHasFollow::check(AiAgent* agent) const {
	return agent->getFollowObject() != nullptr;
}

template<> bool CheckAggroDelayPast::check(AiAgent* agent) const {
	Time* delay = agent->getAggroDelay();

	return delay != nullptr && delay->isPast();
}

template<> bool CheckFollowHasState::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == nullptr)
		return false;

	CreatureObject* followCreo = followCopy->asCreatureObject();

	return followCreo != nullptr && followCreo->hasState(checkVar);
}

template<> bool CheckProspectInRange::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (checkVar > 0.f) {
		return tar != nullptr && agent->isInRange(tar, checkVar);
	} else if (tar != nullptr && agent->peekBlackboard("aggroMod")) {
		float aggroMod = agent->readBlackboard("aggroMod").get<float>();
		float radius = agent->getAggroRadius();

		if (radius == 0)
			radius = AiAgent::DEFAULTAGGRORADIUS;

		radius = Math::min(96.f, radius * aggroMod);

		return agent->isInRange(tar, radius);
	}

	return false;
}

template<> bool CheckFollowAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == nullptr)
		return false;

	CreatureObject* followCreo = followCopy->asCreatureObject();

	return followCreo != nullptr && agent->isAggressiveTo(followCreo);
}

template<> bool CheckProspectAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr || !tar->isCreatureObject())
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	return tarCreo != nullptr && agent->isAggressiveTo(tarCreo);
}

template<> bool CheckIsCamouflaged::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> target = nullptr;

	if (agent->peekBlackboard("targetProspect"))
		target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (target == nullptr || !target->isCreatureObject())
		return false;

	CreatureObject* tarCreo = target->asCreatureObject();

	return tarCreo != nullptr && !agent->isCamouflaged(tarCreo);
}

template<> bool CheckFollowPosture::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == nullptr)
		return false;

	CreatureObject* followCreo = followCopy->asCreatureObject();

	if (followCreo == nullptr) {
		// special check for TANO's. If the btree designer asks if the follow
		// is dead, then return true if the TANO is destroyed, but only if it
		// is not a CREO
		TangibleObject* followTano = followCopy->asTangibleObject();
		return followTano != nullptr && checkVar == CreaturePosture::DEAD && followTano->isDestroyed();
	}

	return followCreo->getPosture() == checkVar;
}

template<> bool CheckFollowInWeaponRange::check(AiAgent* agent) const {
	if (!agent->peekBlackboard("followRange"))
		return false;

	float dist = agent->readBlackboard("followRange").get<float>();

	WeaponObject* weao = nullptr;
	if (checkVar == DataVal::PRIMARYWEAPON)
		weao = agent->getPrimaryWeapon();
	else if (checkVar == DataVal::SECONDARYWEAPON)
		weao = agent->getSecondaryWeapon();

#ifdef DEBUG_AI
	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
		int maxRange = 0;

		if (weao != nullptr)
			maxRange = weao->getMaxRange();

		agent->info("CheckFollowInWeaponRange: dist: " + String::valueOf(dist) + " maxRange: " + String::valueOf(maxRange));
	}
#endif // DEBUG_AI

	return weao != nullptr && weao->getMaxRange() >= dist;
}

template<> bool CheckFollowClosestIdealRange::check(AiAgent* agent) const {
	if (!agent->peekBlackboard("followRange"))
		return false;

	float dist = agent->readBlackboard("followRange").get<float>();

	WeaponObject* weao = nullptr;
	WeaponObject* otherWeao = nullptr;
	if (checkVar == DataVal::PRIMARYWEAPON) {
		weao = agent->getPrimaryWeapon();
		otherWeao = agent->getSecondaryWeapon();
	} else if (checkVar == DataVal::SECONDARYWEAPON) {
		weao = agent->getSecondaryWeapon();
		otherWeao = agent->getPrimaryWeapon();
	}

	if (otherWeao == nullptr)
		return true;
	else if (weao == nullptr)
		return false;

#ifdef DEBUG_AI
	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
		agent->info("CheckFollowClosestIdealRange: dist: " + String::valueOf(dist) + " weao: " + String::valueOf(weao->getMaxRange()) + " otherWeao: " + String::valueOf(otherWeao->getMaxRange()));
#endif // DEBUG_AI

	if (otherWeao->getMaxRange() < dist)
		return true;

	return fabs(weao->getIdealRange() - dist) <= fabs(otherWeao->getIdealRange() - dist + 1.f);
}

template<> bool CheckRandomLevel::check(AiAgent* agent) const {
	return System::random(agent->getLevel()) < checkVar;
}

template<> bool CheckAttackInRange::check(AiAgent* agent) const {
	const QueueCommand* queueCommand = agent->getNextAction();
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();

	if (queueCommand == nullptr || followCopy == nullptr || !queueCommand->isCombatCommand()) {
		return false;
	}

	const CombatQueueCommand* combatCommand = cast<const CombatQueueCommand*>(queueCommand);

	float templatePadding = agent->getTemplateRadius() + followCopy->getTemplateRadius();
	float maxRange = combatCommand->getRange();

	if ((maxRange > 0 && !followCopy->isInRange(agent, maxRange)) || (maxRange <= 0 && !followCopy->isInRange(agent, agent->getWeapon()->getMaxRange() + templatePadding))) {
		return false;
	}

	return true;
}

template<> bool CheckAttackIsValid::check(AiAgent* agent) const {
	return agent->validateStateAttack();
}

template<> bool CheckTargetIsValid::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	return agent->validateTarget(tar);
}

template<> bool CheckRetreat::check(AiAgent* agent) const {
	if (agent->isRetreating())
		return false;

	PatrolPoint* homeLocation = agent->getHomeLocation();
	if (homeLocation == nullptr)
		return false;

	SceneObject* target = agent->getFollowObject().get();

	if (target != nullptr)
		return !homeLocation->isInRange(target, checkVar);

	return !homeLocation->isInRange(agent, checkVar);
}

template<> bool CheckFlee::check(AiAgent* agent) const {
	if (agent == nullptr || agent->getParent().get() != nullptr || agent->getParentID() > 0)
		return false;

	Time* fleeDelay = agent->getFleeDelay();
	int fleeChance = 30;

	if (agent->getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
		fleeChance = 15;

	if (fleeDelay == nullptr || !fleeDelay->isPast() || System::random(100) > fleeChance)
		return false;

	if ((agent->getHAM(CreatureAttribute::HEALTH) < agent->getMaxHAM(CreatureAttribute::HEALTH) * checkVar)
		|| (agent->getHAM(CreatureAttribute::ACTION) < agent->getMaxHAM(CreatureAttribute::ACTION) * checkVar)
		|| (agent->getHAM(CreatureAttribute::MIND) < agent->getMaxHAM(CreatureAttribute::MIND) * checkVar)) {

		return true;
	}

	return false;
}

template<> bool CheckSpeed::check(AiAgent* agent) const {
	return agent->getCurrentSpeed() > checkVar;
}

template<> bool CheckProspectSpeed::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr || !tar->isCreatureObject())
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	return CreaturePosture::instance()->getSpeed(tarCreo->getPosture(), tarCreo->getLocomotion()) == checkVar;
}

template<> bool CheckProspectLOS::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	Locker locker(tar, agent);

	return agent->checkLineOfSight(tar);
}

template<> bool CheckOutdoors::check(AiAgent* agent) const {
	return agent->getParent() == nullptr;
}

template<> bool CheckProspectLevel::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr || !tar->isCreatureObject())
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	float aggroMod = 1.f;
	if (agent->peekBlackboard("aggroMod"))
		aggroMod = agent->readBlackboard("aggroMod").get<float>();

	return agent->getLevel() * aggroMod < tarCreo->getLevel();
}

template<> bool CheckProspectBackAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	if (tar->isPlayerCreature())
		return true;

	if (!tar->isAiAgent())
		return false;

	AiAgent* tarAgent = tar->asAiAgent();
	return tarAgent->isAggressiveTo(agent);
}

template<> bool CheckProspectFacing::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	return tar->isFacingObject(agent);
}

template<> bool CheckPetCommand::check(AiAgent* agent) const {
	if (!agent->isPet())
		return false;

	Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
	if (cd == nullptr)
		return false;

	return cd->getLastCommand() == checkVar;
}

template<> bool CheckProspectIsCommand::check(AiAgent* agent) const {
	if (!agent->isPet())
		return false;

	Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
	if (cd == nullptr)
		return false;

	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	return cd->getLastCommandTarget().get() == tar;
}

template<> bool CheckIsInCombat::check(AiAgent* agent) const {
	return agent->isInCombat();
}

template<> bool CheckHasPatrol::check(AiAgent* agent) const {
	return agent->getPatrolPointSize() > 0;
}

template<> bool CheckProspectIsType::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	switch (checkVar) {
	case PLAYER:
		return tar->isPlayerCreature();
	case CREATURE:
		return tar->isCreature();
	case NPC:
		return tar->isCreatureObject() && tar->asCreatureObject()->isNonPlayerCreatureObject();
	case TANGIBLE:
		return tar->isTangibleObject();
	case AGENT:
		return tar->isAiAgent();
	default:
		return false;
	};

	return false;
}

template<> bool CheckIsType::check(AiAgent* agent) const {
	if (agent == nullptr)
		return false;

	switch (checkVar) {
	case NPC:
		return agent->isNpc();
	case MONSTER:
		return agent->isMonster();
	case DROID:
		return agent->isDroid();
	case ANDROID:
		return agent->isAndroid();
	case HUMANOID:
		return agent->isHumanoid();
	default:
		return false;
	};

	return false;
}

template<> bool CheckProspectJediTrial::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr || !tar->isCreatureObject())
		return false;

	PlayerObject* ghost = tar->asCreatureObject()->getPlayerObject();
	if (ghost == nullptr)
		return false;

	int councilType = ghost->getFrsData()->getCouncilType();
	String objName = agent->getObjectNameStringIdName().toCharArray();

	return (councilType == FrsManager::COUNCIL_DARK && objName != "dark_jedi_sentinel")
		|| (councilType == FrsManager::COUNCIL_LIGHT && objName != "light_jedi_sentinel");
}

template<> bool CheckProspectIsIncapacitated::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr || !tar->isCreatureObject())
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	if (tarCreo == nullptr)
		return false;

	return tarCreo->isIncapacitated();
}

template<> bool CheckIsKiller::check(AiAgent* agent) const {
	return agent->isKiller();
}

template<> bool CheckIsStalker::check(AiAgent* agent) const {
	return agent->isStalker();
}

template<> bool CheckOwnerInRange::check(AiAgent* agent) const {
	if (agent == nullptr || !agent->isPet())
		return false;

	Reference<PetControlDevice*> controlDevice = agent->getControlDevice().castTo<PetControlDevice*>();

	if (controlDevice == nullptr)
		return false;

	ManagedReference<SceneObject*> commander = controlDevice->getLastCommander();

	if (checkVar > 0.f) {
		return commander != nullptr && agent->isInRange(commander, checkVar);
	}

	return false;
}

template<> bool CheckTargetInOwnerRange::check(AiAgent* agent) const {
	if (agent == nullptr || !agent->isPet())
		return false;

	ManagedReference<SceneObject*> tar = nullptr;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == nullptr)
		return false;

	Reference<PetControlDevice*> controlDevice = agent->getControlDevice().castTo<PetControlDevice*>();

	if (controlDevice == nullptr)
		return false;

	ManagedReference<SceneObject*> commander = controlDevice->getLastCommander();

	if (checkVar > 0.f) {
		return commander != nullptr && tar->isInRange(commander, checkVar);
	}

	return false;
}

template<> bool CheckUseRanged::check(AiAgent* agent) const {
	return agent->getUseRanged();
}

template<> bool CheckWeaponIsRanged::check(AiAgent* agent) const {
	if (checkVar == PRIMARYWEAPON) {
		WeaponObject* primaryWeapon = agent->getPrimaryWeapon();

		if (primaryWeapon != nullptr && primaryWeapon->isRangedWeapon()) {
			return true;
		}
	} else if (checkVar == SECONDARYWEAPON) {
		WeaponObject* secondaryWeapon = agent->getPrimaryWeapon();

		if (secondaryWeapon != nullptr && secondaryWeapon->isRangedWeapon()) {
			return true;
		}
	}

	return false;
}

template<> bool CheckIsDroid::check(AiAgent* agent) const {
	return agent->isDroid();
}

template<> bool CheckCrackdownScanner::check(AiAgent* agent) const {
	return agent->getCreatureBitmask() & CreatureFlag::SCANNING_FOR_CONTRABAND;
}

template<> bool CheckCrackdownFollowTarget::check(AiAgent* agent) const {
	if (!(agent->getCreatureBitmask() & CreatureFlag::FOLLOW))
		return false;

	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == nullptr || !followCopy->isCreatureObject())
		return false;

	CreatureObject* followCreo = followCopy->asCreatureObject();

	if (followCreo != nullptr && !followCreo->isDead()) {
		return true;
	}

	return false;
}

template<> bool CheckIsStationary::check(AiAgent* agent) const {
	return agent->getCreatureBitmask() & CreatureFlag::STATIONARY;
}

template<> bool CheckIsHealer::check(AiAgent* agent) const {
	return agent->isHealer();
}

template<> bool CheckHealChance::check(AiAgent* agent) const {
	Time* healDelay = agent->getHealDelay();

	if (healDelay == nullptr || !healDelay->isPast()) {
		return false;
	}

	if (System::random(100) < 98)
		return false;

	return true;
}

template<> bool CheckIsHome::check(AiAgent* agent) const {
	PatrolPoint* homeLocation = agent->getHomeLocation();

	return homeLocation != nullptr && homeLocation->isReached() ? true : false;
}

template<> bool CheckHomeIsCell::check(AiAgent* agent) const {
	PatrolPoint* homeLocation = agent->getHomeLocation();

	return homeLocation != nullptr && homeLocation->getCell() != nullptr ? true : false;
}

template<> bool CheckChatDelay::check(AiAgent* agent) const {
	return agent->getCooldownTimerMap()->isPast("reaction_chat") ? true : false;
}

template<> bool CheckCallForHelp::check(AiAgent* agent) const {
	if (agent == nullptr || agent->isDead())
		return false;

	Time* packNotify = agent->getLastPackNotify();

	if (packNotify == nullptr || !packNotify->isPast()) {
		agent->eraseBlackboard("allyProspect");
		return false;
	}

	if (agent->peekBlackboard("allyProspect")) {
		return true;
	}

	Time* callForHelp = agent->getLastCallForHelp();

	if (callForHelp != nullptr) {
		if (!callForHelp->isPast())
			return false;

		if (System::random(100) < 75) {
			callForHelp->updateToCurrentTime();
			callForHelp->addMiliTime(60 * 1000);
			return false;
		}
	}

	return true;
}

template<> bool CheckIsHarvester::check(AiAgent* agent) const {
	if (agent == nullptr || !agent->isDroid())
		return false;

	ManagedReference<DroidObject*> droid = cast<DroidObject*>(agent);

	if (droid == nullptr)
		return false;

	auto module = droid->getModule("harvest_module").castTo<DroidHarvestModuleDataComponent*>();

	return module != nullptr ? true : false;
}

template<> bool CheckHasHarvestTargets::check(AiAgent* agent) const {
	if (agent == nullptr || !agent->isDroid())
		return false;

	if (agent->peekBlackboard("harvestTarget"))
		return true;

	ManagedReference<DroidObject*> droid = cast<DroidObject*>(agent);

	if (droid == nullptr)
		return false;

	auto module = droid->getModule("harvest_module").castTo<DroidHarvestModuleDataComponent*>();

	return module != nullptr && module->hasMoreTargets() ? true : false;
}

template<> bool CheckShouldRest::check(AiAgent* agent) const {
	if (agent == nullptr)
		return false;

	if (!agent->isNeutral())
		return false;

	if (agent->getFollowObject() != nullptr)
		return false;

	Time* restDelay = agent->getRestDelay();

	if (restDelay == nullptr || !restDelay->isPast())
		return false;

	int restChance = 40; // % chance out of 100
	int restRoll = System::random(100);

	// Chance is less than the roll, fail and add time to check again
	if (restChance < restRoll) {
		int delay = 45 * 1000; // Time in ms to delay checking again or resting again

		restDelay->updateToCurrentTime();
		restDelay->addMiliTime(delay);

		return false;
	}

	return true;
}

template<> bool CheckStopResting::check(AiAgent* agent) const {
	if (agent == nullptr)
		return false;

	if (agent->isInCombat() || agent->getFollowObject() != nullptr)
		return true;

	Time* restDelay = agent->getRestDelay();

	if (restDelay == nullptr)
		return true;

	// Default time to rest is 45s less the 5min set on the delay when set Resting in ms
	int resting = 255 * 1000;

	if (agent->peekBlackboard("restingTime"))
		resting = agent->readBlackboard("restingTime").get<int>();

	int restedTime = restDelay->miliDifference() * -1;

	if (resting < restedTime)
		return false;

	agent->eraseBlackboard("restingTime");

	return true;
}