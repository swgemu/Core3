#ifndef LOOKFORTARGET_H_
#define LOOKFORTARGET_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "templates/params/OptionBitmask.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"
#include "server/zone/managers/collision/CollisionManager.h"

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
#ifdef DEBUG_AI
		bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_AI
		bool alwaysActive = false;
#endif // DEBUG_AI


		if ((agent->getOptionsBitmask() & OptionBitmask::AIENABLED) == 0 || agent->isDead() || agent->isIncapacitated() || (agent->getPvpStatusBitmask() == CreatureFlag::NONE && !(agent->isDroidObject() && agent->isPet())))
			return FAILURE;

		if ((!alwaysActive && agent->getNumberOfPlayersInRange() <= 0) || agent->isRetreating() || agent->isFleeing() || agent->isInCombat())
			return FAILURE;

		assert(child != nullptr);

		// If we have a follow object, check if it is still valid then set as prospect
		ManagedReference<SceneObject*> currObj = agent->getFollowObject().get();
		if (currObj != nullptr) {
			if (currObj->isCreatureObject() && isInvalidTarget(currObj->asCreatureObject(), agent)) {
				if (!(agent->getCreatureBitmask() & CreatureFlag::FOLLOW)) {
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

		if (target->isDead() || target->isFeigningDeath() || (!agent->isKiller() && target->isIncapacitated()) || target->isInvisible() || !target->isAttackableBy(agent))
			return true;

		if (target->isVehicleObject() && !target->hasRidingCreature())
			return true;

		SceneObject* agentParent = agent->getParent().get();
		SceneObject* targetParent = target->getParent().get();

		uint64 agentParentID = agentParent != nullptr ? agentParent->getObjectID() : 0;
		uint64 targetParentID = targetParent != nullptr ? targetParent->getObjectID() : 0;

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
