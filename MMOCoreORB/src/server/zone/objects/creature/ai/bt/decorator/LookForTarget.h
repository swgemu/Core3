#ifndef LOOKFORTARGET_H_
#define LOOKFORTARGET_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "templates/params/OptionBitmask.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class LookForTarget : public Decorator {
public:
	LookForTarget(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	LookForTarget(const LookForTarget& b) : Decorator(b) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if ((agent->getOptionsBitmask() & OptionBitmask::AIENABLED) == 0 || agent->isDead() || agent->isIncapacitated()
				|| (agent->getPvpStatusBitmask() == CreatureFlag::NONE && !(agent->isDroidObject() && agent->isPet()))
				|| agent->getNumberOfPlayersInRange() <= 0 || agent->isRetreating() || agent->isFleeing() || agent->isInCombat())
			return FAILURE;

		assert(child != nullptr);

		// If we have a follow object, check if it is still valid then set as prospect
		ManagedReference<SceneObject*> currObj = agent->getFollowObject().get();
		if (currObj != nullptr) {
			if (currObj->isCreatureObject() && isInvalidTarget(currObj->asCreatureObject(), agent)) {
				if (~agent->getCreatureBitmask() & CreatureFlag::FOLLOW) {
					agent->setFollowObject(nullptr);
					agent->setMovementState(AiAgent::PATHING_HOME);
				}
				return FAILURE;
			} else {
				agent->writeBlackboard("targetProspect", currObj);
				return child->doAction(agent);
			}
		}

		// get targets we want to apply our child tree to
		// TODO: might have to fix numberOfPlayersInRange here
		CloseObjectsVector* vec = (CloseObjectsVector*) agent->getCloseObjects();
		if (vec == nullptr)
			return FAILURE;

		SortedVector<QuadTreeEntry* > closeObjects;
		vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

		// Shuffle closeobjects to randomize target checks
		std::shuffle(closeObjects.begin(), closeObjects.end(), *System::getMTRand());
		/*QuadTreeEntry* temp;
		int index;
		for (int i = 0; i < closeObjects.size(); i++) {
			index = (int) System::random(closeObjects.size() - 1 - i) + i;
			temp = closeObjects.set(i, closeObjects.get(index));
			closeObjects.set(index, temp);
		}*/

		for (int i = 0; i < closeObjects.size(); ++i) {
			ManagedReference<SceneObject*> scene = static_cast<SceneObject*>(closeObjects.get(i));
			if (isInvalidTarget(scene->asCreatureObject(), agent))
				continue;

			agent->writeBlackboard("targetProspect", scene);

			Behavior::Status result = child->doAction(agent);
			if (result != FAILURE) {
				return result;
			}
		}

		return FAILURE;
	}

	bool isInvalidTarget(CreatureObject* target, AiAgent* agent) const {
		if (target == nullptr || target == agent || target->getPvpStatusBitmask() == CreatureFlag::NONE)
			return true;

		if (target->isDead() || target->isFeigningDeath() || (!agent->isKiller() && target->isIncapacitated()) || target->isInvulnerable() || target->isInvisible() || !target->isAttackableBy(agent) || !agent->isAttackableBy(target))
			return true;

		if (target->isVehicleObject() || target->hasRidingCreature())
			return true;

		SceneObject* agentRoot = agent->getRootParent();
		SceneObject* targetRoot = target->getRootParent();

		uint64 agentParentID = agentRoot != nullptr && agentRoot->isBuildingObject() ? agentRoot->getObjectID() : 0;
		uint64 targetParentID = targetRoot != nullptr && targetRoot->isBuildingObject() ? targetRoot->getObjectID() : 0;

		if (agentParentID != targetParentID && !CollisionManager::checkLineOfSight(agent, target))
			return true;

		return false;
	}
};

}
}
}
}
}
}
}

#endif // LOOKFORTARGET_H_
