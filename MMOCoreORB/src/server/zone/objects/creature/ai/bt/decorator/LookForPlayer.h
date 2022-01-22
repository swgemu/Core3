#ifndef LOOKFORPLAYER_H_
#define LOOKFORPLAYER_H_

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

class LookForPlayer : public Decorator {
public:
	LookForPlayer(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	LookForPlayer(const LookForPlayer& b) : Decorator(b) {
	}

	LookForPlayer& operator=(const LookForPlayer& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if ((agent->getOptionsBitmask() & OptionBitmask::AIENABLED) == 0 || agent->isDead() || agent->isIncapacitated())
			return FAILURE;

		assert(child != nullptr);

		// Get player targets we want to apply our child tree to
		CloseObjectsVector* vec = (CloseObjectsVector*) agent->getCloseObjects();
		if (vec == nullptr)
			return FAILURE;

		SortedVector<QuadTreeEntry* > closeObjects;
		vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

		// Shuffle closeobjects to randomize target checks
		std::shuffle(closeObjects.begin(), closeObjects.end(), *System::getMTRand());

		for (int i = 0; i < closeObjects.size(); ++i) {
			ManagedReference<SceneObject*> sceneTarget = static_cast<SceneObject*>(closeObjects.get(i));
			if (isInvalidTarget(sceneTarget->asCreatureObject(), agent))
				continue;

			agent->writeBlackboard("targetProspect", sceneTarget);

			Behavior::Status result = child->doAction(agent);
			if (result != FAILURE) {
				return result;
			}
		}

		return FAILURE;
	}

	bool isInvalidTarget(CreatureObject* target, AiAgent* agent) const {
		if (target == nullptr || target->isDead() || target->isFeigningDeath() || target->isInvulnerable() || target->isInvisible())
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

#endif // LOOKFORPLAYER_H_