#include "Checks.h"

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/creature/PetManager.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::creature::ai::bt::leaf;

template <> bool CheckPosture::check(AiAgent* agent) const {
    return agent->getPosture();
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

template <> bool CheckFollowInRange::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	
    return followCopy != NULL && agent->isInRange(followCopy, checkVar);
}

template <> bool CheckFollowAttackable::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	TangibleObject* followTano = followCopy->asTangibleObject();
	
    return followTano != NULL && followTano->isAttackableBy(agent);
}

template <> bool CheckFollowAggression::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();
	
    return followCreo != NULL && agent->isAggressiveTo(followCreo);
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
    if (checkVar != AiAgent::WEAPONDEFAULT)
        weao = agent->getReadyWeapon();
    if (checkVar == AiAgent::WEAPONDEFAULT || weao == NULL)
        weao = agent->getSlottedObject("default_weapon").castTo<WeaponObject*>();

    return weao->getMaxRange() <= dist;
}

template <> bool CheckFollowClosestIdealRange::check(AiAgent* agent) const {
    if (!agent->peekBlackboard("followRange"))
        return false;

    float dist = agent->readBlackboard("followRange").get<float>();

    // TODO: this logic will change when we allow for multiple weapons
    WeaponObject* weao = NULL;
    WeaponObject* otherWeao = NULL;
    if (checkVar != AiAgent::WEAPONDEFAULT) {
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

    return fabs(weao->getIdealRange() - dist) <= fabs(otherWeao->getIdealRange() - dist);
}

template <> bool CheckRandomLevel::check(AiAgent* agent) const {
    return System::random(agent->getLevel()) < checkVar;
}

template <> bool CheckLastCommand::check(AiAgent* agent) const {
    return false; // TODO: pet check like agent->getLastCommand() == checkVar;
}
