#include "Checks.h"

#include "templates/params/creature/CreaturePosture.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/frs/FrsManager.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::creature::ai::bt::leaf;

template<> bool CheckPosture::check(AiAgent* agent) const {
	return agent->getPosture() == checkVar;
}

template<> bool CheckDestination::check(AiAgent* agent) const {
	return agent->setDestination() > checkVar;
}

template<> bool CheckFollowState::check(AiAgent* agent) const {
	return agent->getFollowState() == checkVar;
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
		int radius = agent->getAggroRadius();
		if (radius == 0)
			radius = AiAgent::DEFAULTAGGRORADIUS;

		return agent->isInRange(tar, radius * aggroMod);
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

	if (tar == nullptr)
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	return tarCreo != nullptr && agent->isAggressiveTo(tarCreo);
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

	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
		int maxRange = 0;

		if (weao != nullptr)
			maxRange = weao->getMaxRange();

		agent->info("CheckFollowInWeaponRange: dist: " + String::valueOf(dist) + " maxRange: " + String::valueOf(maxRange));
	}

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

	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
		agent->info("CheckFollowClosestIdealRange: dist: " + String::valueOf(dist) + " weao: " + String::valueOf(weao->getMaxRange()) + " otherWeao: " + String::valueOf(otherWeao->getMaxRange()));

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

	if (queueCommand == nullptr || followCopy == nullptr)
		return false;

	float templatePadding = agent->getTemplateRadius() + followCopy->getTemplateRadius();
	if ((queueCommand->getMaxRange() > 0 && !followCopy->isInRange(agent, queueCommand->getMaxRange() + templatePadding))
			|| (queueCommand->getMaxRange() <= 0 && !followCopy->isInRange(agent, agent->getWeapon()->getMaxRange() + templatePadding))) {
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
		return tar->isCreatureObject() && !tar->isCreature();
	case TANGIBLE:
		return tar->isTangibleObject();
	case AGENT:
		return tar->isAiAgent();
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
