#ifndef LOOKFORTARGETSPACE_H_
#define LOOKFORTARGETSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class LookForTargetSpace : public DecoratorSpace {
public:
	LookForTargetSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	LookForTargetSpace(const LookForTargetSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
#ifdef DEBUG_SHIP_AI
		bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else  // DEBUG_SHIP_AI
		bool alwaysActive = false;
#endif // DEBUG_SHIP_AI

	if (!(agent->getOptionsBitmask() & OptionBitmask::AIENABLED) || (agent->getPvpStatusBitmask() & ShipFlag::NONE))
		return FAILURE;

	if ((!alwaysActive && agent->getNumberOfPlayersInRange() <= 0) /*|| agent->isInCombat()*/)
		return FAILURE;

		assert(child != nullptr);

		// If we have a follow object, check if it is still valid then set as prospect
		ManagedReference<SceneObject*> currObj = agent->getFollowObject().get();

		if (currObj != nullptr) {
			if (currObj->isShipObject() && isInvalidTarget(currObj->asShipObject(), agent)) {
				// Target is invalid, only clear follow if Ship is not following a friendly
				if (!(agent->getShipBitmask() & ShipFlag::FOLLOW)) {
					agent->setFollowObject(nullptr);
					agent->setMovementState(ShipAiAgent::PATHING_HOME);
				}

				return FAILURE;
			} else {
				agent->writeBlackboard("targetProspect", currObj);
				return child->doAction(agent);
			}
		}

		auto targetVector = agent->getTargetVector();

		if (targetVector == nullptr) {
			return FAILURE;
		}

		SortedVector<ManagedReference<ShipObject*>> targetVectorCopy;
		targetVector->safeCopyTo(targetVectorCopy);

		// Shuffle closeobjects to randomize target checks
		std::shuffle(targetVectorCopy.begin(), targetVectorCopy.end(), *System::getMTRand());

		for (int i = 0; i < targetVectorCopy.size(); ++i) {
			auto target = targetVectorCopy.get(i).castTo<ShipObject*>();

			if (isInvalidTarget(target, agent)) {
				continue;
			}

			agent->writeBlackboard("targetProspect", target);

			BehaviorSpace::Status result = child->doAction(agent);

			if (result != FAILURE) {
				return result;
			}
		}

		return FAILURE;
	}

	bool isInvalidTarget(ShipObject* target, ShipAiAgent* agent) const {
		if (target == nullptr || target->getObjectID() == agent->getObjectID())
			return true;

		if (!target->isAttackableBy(agent))
			return true;

		return false;
	}
};

} // namespace decoratorspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // LOOKFORTARGETSPACE_H_
