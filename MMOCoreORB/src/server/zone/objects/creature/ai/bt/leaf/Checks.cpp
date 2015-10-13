#include "Checks.h"

#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::creature::ai::bt::leaf;

template <> bool CheckPosture::check(AiAgent* agent) const {
    return agent->getPosture() == checkVar;
}

template <> bool CheckDestination::check(AiAgent* agent) const {
    return agent->setDestination() > checkVar;
}

template <> bool CheckFollowState::check(AiAgent* agent) const {
    return agent->getFollowState() == checkVar;
}

template <> bool CheckHasFollow::check(AiAgent* agent) const {
    return agent->getFollowObject() != NULL;
}

template <> bool CheckFollowHasState::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();
	
    return followCreo != NULL && followCreo->hasState(checkVar);
}

template <> bool CheckProspectInRange::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (checkVar > 0.f)
		return tar != NULL && agent->isInRange(tar, checkVar);
	else if (tar != NULL && agent->peekBlackboard("aggroMod")) {
		float aggroMod = agent->readBlackboard("aggroMod").get<float>();
		int radius = agent->getAggroRadius();
		if (radius == 0) radius = AiAgent::DEFAULTAGGRORADIUS;

		return agent->isInRange(tar, radius*aggroMod);
	}

	return false;
}

template <> bool CheckFollowAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();
	
    return followCreo != NULL && agent->isAggressiveTo(followCreo);
}


template <> bool CheckProspectAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL) return false;
	
	CreatureObject* tarCreo = tar->asCreatureObject();
	
    return tarCreo != NULL && agent->isAggressiveTo(tarCreo);
}

template <> bool CheckFollowPosture::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();

    if (followCreo == NULL) {
        // special check for TANO's. If the btree designer asks if the follow
        // is dead, then return true if the TANO is destroyed, but only if it
        // is not a CREO
    	TangibleObject* followTano = followCopy->asTangibleObject();
        return followTano != NULL &&
               checkVar == CreaturePosture::DEAD &&
               followTano->isDestroyed();
    }
	
    return followCreo->getPosture() == checkVar;
}

template <> bool CheckFollowInWeaponRange::check(AiAgent* agent) const {
    if (!agent->peekBlackboard("followRange"))
        return false;

    float dist = agent->readBlackboard("followRange").get<float>();

    // TODO: this logic will change when we allow for multiple weapons
    WeaponObject* weao = NULL;
    if (checkVar != DataVal::DEFAULT)
        weao = agent->getReadyWeapon();
    if (checkVar == DataVal::DEFAULT || weao == NULL)
        weao = agent->getSlottedObject("default_weapon").castTo<WeaponObject*>();

    return weao->getMaxRange() >= dist;
}

template <> bool CheckFollowClosestIdealRange::check(AiAgent* agent) const {
    if (!agent->peekBlackboard("followRange"))
        return false;

    float dist = agent->readBlackboard("followRange").get<float>();

    // TODO: this logic will change when we allow for multiple weapons
    WeaponObject* weao = NULL;
    WeaponObject* otherWeao = NULL;
    if (checkVar != DataVal::DEFAULT) {
        weao = agent->getReadyWeapon();
        otherWeao = agent->getSlottedObject("default_weapon").castTo<WeaponObject*>();
    } else {
        weao = agent->getSlottedObject("default_weapon").castTo<WeaponObject*>();
        otherWeao = agent->getReadyWeapon();
    }

    if (otherWeao == NULL)
        return true;
    else if (weao == NULL)
        return false;

    return fabs(weao->getIdealRange() - dist) <= fabs(otherWeao->getIdealRange() - dist + 1.f);
}

template <> bool CheckRandomLevel::check(AiAgent* agent) const {
    return System::random(agent->getLevel()) < checkVar;
}

template <> bool CheckAttackInRange::check(AiAgent* agent) const {
    QueueCommand* queueCommand = agent->getNextAction();
    ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
    float templatePadding = agent->getTemplateRadius() + followCopy->getTemplateRadius();
    if (queueCommand == NULL || followCopy == NULL ||
            (queueCommand->getMaxRange() > 0 && !followCopy->isInRange(agent, queueCommand->getMaxRange() + templatePadding)) ||
            (queueCommand->getMaxRange() <= 0 && !followCopy->isInRange(agent, agent->getWeapon()->getMaxRange() + templatePadding))) {
        return false;
    }

    return true;
}

template <> bool CheckAttackIsValid::check(AiAgent* agent) const {
    return agent->validateStateAttack();
}

template <> bool CheckTargetIsValid::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

    return agent->validateTarget(tar);
}

template <> bool CheckRetreat::check(AiAgent* agent) const {
	if (agent->isRetreating())
		return false;

	PatrolPoint* homeLocation = agent->getHomeLocation();
    if (homeLocation == NULL)
        return false;

	SceneObject* target = agent->getFollowObject().get();

	if (target != NULL)
		return !homeLocation->isInRange(target, checkVar);

	return !homeLocation->isInRange(agent, checkVar);
}

template <> bool CheckSpeed::check(AiAgent* agent) const {
    return agent->getCurrentSpeed() > checkVar;
}

template <> bool CheckProspectSpeed::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL || !tar->isCreatureObject())
		return false;
	
	CreatureObject* tarCreo = tar->asCreatureObject();

    return CreaturePosture::instance()->getSpeed(tarCreo->getPosture(), tarCreo->getLocomotion()) == checkVar;
}

template <> bool CheckProspectLOS::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL) return false;

	Locker locker(tar, agent);

	return agent->checkLineOfSight(tar);
}

template <> bool CheckOutdoors::check(AiAgent* agent) const {
	return agent->getParent() == NULL;
}

template <> bool CheckProspectLevel::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL || !tar->isCreatureObject())
		return false;

	CreatureObject* tarCreo = tar->asCreatureObject();

	float aggroMod = 1.f;
	if (agent->peekBlackboard("aggroMod"))
		aggroMod = agent->readBlackboard("aggroMod").get<float>();

	return agent->getLevel() * aggroMod < tarCreo->getLevel();
}

template <> bool CheckProspectBackAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL)
		return false;
	
	if (tar->isPlayerCreature())
		return true;

	if (!tar->isAiAgent())
		return false;

	AiAgent* tarAgent = tar->asAiAgent();
	return tarAgent->isAggressiveTo(agent);
}

template <> bool CheckProspectFacing::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	if (tar == NULL)
		return false;

	return tar->isFacingObject(agent);
}

template<> bool CheckPetCommand::check(AiAgent* agent) const {
	if (!agent->isPet())
		return false;

	Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
	if (cd == NULL)
		return false;

	return cd->getLastCommand() == checkVar;
}

template<> bool CheckProspectIsCommand::check(AiAgent* agent) const {
	if (!agent->isPet())
		return false;

	Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
	if (cd == NULL)
		return false;

	ManagedReference<SceneObject*> tar = NULL;
	if (agent->peekBlackboard("targetProspect"))
		tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

	return cd->getLastCommandTarget().get() == tar;
}
