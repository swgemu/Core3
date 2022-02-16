#ifndef LOOKFORALLIES_H_
#define LOOKFORALLIES_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "templates/params/OptionBitmask.h"
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

class LookForAllies : public Decorator {
public:
	LookForAllies(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	LookForAllies(const LookForAllies& b) : Decorator(b) {
	}

	LookForAllies& operator=(const LookForAllies& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if ((agent->getOptionsBitmask() & OptionBitmask::AIENABLED) == 0 || agent->isDead())
			return FAILURE;

		assert(child != nullptr);

		if (agent->peekBlackboard("allyTarget")) {
			ManagedReference<SceneObject*> currAlly = agent->readBlackboard("allyProspect").get<ManagedReference<SceneObject*> >().get();
			if (currAlly != nullptr && currAlly->isCreatureObject()) {
				if (isInvalidTarget(currAlly->asCreatureObject(), agent)) {
					agent->eraseBlackboard("allyProspect");
					return FAILURE;
				} else {
					return child->doAction(agent);
				}
			}
		}

		// Get allied targets we want to apply our child tree to
		CloseObjectsVector* vec = (CloseObjectsVector*) agent->getCloseObjects();
		if (vec == nullptr)
			return FAILURE;

		SortedVector<QuadTreeEntry* > closeObjects;
		vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

		for (int i = 0; i < closeObjects.size(); ++i) {
			ManagedReference<SceneObject*> sceneTarget = static_cast<SceneObject*>(closeObjects.get(i));
			if (isInvalidTarget(sceneTarget->asCreatureObject(), agent)) {
				continue;
			}

			agent->writeBlackboard("allyProspect", sceneTarget);

			Behavior::Status result = child->doAction(agent);
			if (result != FAILURE) {
				return result;
			}
		}

		return FAILURE;
	}

	bool isInvalidTarget(CreatureObject* target, AiAgent* agent) const {
		if (target == nullptr || target->isDead() || target == agent || !target->isAiAgent() || !(target->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE) ||
			!(target->getOptionsBitmask() & OptionBitmask::AIENABLED) || target->isInCombat())
			return true;

		AiAgent* tarAgent = target->asAiAgent();

		if (tarAgent == nullptr)
			return true;

		uint32 socialGroup = agent->getSocialGroup().toLowerCase().hashCode();
		uint32 targetSocialGroup = tarAgent->getSocialGroup().toLowerCase().hashCode();

		if (socialGroup != targetSocialGroup)
			return true;

		SceneObject* agentParent = agent->getParent().get();
		SceneObject* targetParent = target->getParent().get();

		uint64 agentParentID = agentParent != nullptr ? agentParent->getObjectID() : 0;
		uint64 targetParentID = targetParent != nullptr ? targetParent->getObjectID() : 0;

		if (agentParentID == targetParentID && (agent->getPosition().squaredDistanceTo(target->getPosition()) > 50 * 50))
			return true;

		if (!CollisionManager::checkLineOfSight(agent, target))
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

#endif // LOOKFORALLIES_H_