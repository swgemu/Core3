#include "Checks.h"

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/CreaturePosture.h"
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

template <> bool CheckFollowDead::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();
	
    return followCreo != NULL && followCreo->isDead();
}

template <> bool CheckFollowIncapped::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	CreatureObject* followCreo = followCopy->asCreatureObject();
	
    return followCreo != NULL && followCreo->isDead();
}

template <> bool CheckFollowDestroyed::check(AiAgent* agent) const {
	ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	if (followCopy == NULL) return false;
	
	TangibleObject* followTano = followCopy->asTangibleObject();
	
    return followTano != NULL && followTano->isDestroyed();
}

template <> bool CheckRandomLevel::check(AiAgent* agent) const {
    return System::random(agent->getLevel()) < checkVar;
}

template <> bool CheckLastCommand::check(AiAgent* agent) const {
    return false; // TODO: pet check like agent->getLastCommand() == checkVar;
}