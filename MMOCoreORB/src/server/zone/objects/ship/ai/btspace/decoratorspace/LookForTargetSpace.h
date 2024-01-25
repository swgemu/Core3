#ifndef LOOKFORTARGETSPACE_H_
#define LOOKFORTARGETSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"
#include "templates/params/creature/ObjectFlag.h"

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
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - called";

		bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else  // DEBUG_SHIP_AI
		bool alwaysActive = false;
#endif // DEBUG_SHIP_AI

		if (!(agent->getOptionsBitmask() & OptionBitmask::AIENABLED) || (agent->getPvpStatusBitmask() & ObjectFlag::NONE)) {
#ifdef DEBUG_SHIP_AI
			if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
				agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - FAILURE at 1";
#endif // DEBUG_SHIP_AI
			return FAILURE;
		}

		if ((!alwaysActive && agent->getNumberOfPlayersInRange() <= 0)) {
#ifdef DEBUG_SHIP_AI
			if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
				agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - FAILURE at 2";
#endif // DEBUG_SHIP_AI
			return FAILURE;
		}

		assert(child != nullptr);

		// If we have a follow object, check if it is still valid then set as prospect
		ManagedReference<ShipObject*> currShipObj = agent->getFollowShipObject().get();

		if (currShipObj != nullptr) {
			if (isInvalidTarget(currShipObj, agent)) {
				// Target is invalid, only clear follow if Ship is not following a friendly
				if (!(agent->getShipBitmask() & ShipFlag::FOLLOW)) {
					agent->setFollowShipObject(nullptr);
					agent->setMovementState(ShipAiAgent::PATHING_HOME);
				}

#ifdef DEBUG_SHIP_AI
				if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
					agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - FAILURE at 3";
#endif // DEBUG_SHIP_AI

				return FAILURE;
			} else {
				agent->writeBlackboard("targetShipProspect", currShipObj);
				return child->doAction(agent);
			}
		}

		auto targetVector = agent->getTargetVector();

		if (targetVector == nullptr) {
#ifdef DEBUG_SHIP_AI
			if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
				agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - FAILURE at 4";
#endif // DEBUG_SHIP_AI
			return FAILURE;
		}

		SortedVector<ManagedReference<ShipObject*>> targetVectorCopy;
		targetVector->safeCopyTo(targetVectorCopy);

		// Shuffle closeobjects to randomize target checks
		std::shuffle(targetVectorCopy.begin(), targetVectorCopy.end(), *System::getMTRand());

#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - targetVectorCopy Size: " << targetVectorCopy.size();
#endif // DEBUG_SHIP_AI

		for (int i = 0; i < targetVectorCopy.size(); ++i) {
			auto targetShip = targetVectorCopy.get(i).castTo<ShipObject*>();

			if (isInvalidTarget(targetShip, agent)) {
				continue;
			}

			agent->writeBlackboard("targetShipProspect", targetShip);

#ifdef DEBUG_SHIP_AI
			if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
				agent->info(true) << agent->getDisplayedName() << " - LookForTargetSpace - found target prospect: " << targetShip->getDisplayedName();
#endif // DEBUG_SHIP_AI

			BehaviorSpace::Status result = child->doAction(agent);

			if (result != FAILURE) {
				return result;
			}
		}

		return FAILURE;
	}

	bool isInvalidTarget(ShipObject* targetShip, ShipAiAgent* agent) const {
		if (targetShip == nullptr || targetShip->getObjectID() == agent->getObjectID())
			return true;

		if (targetShip->isShipAiAgent()) {
			ShipAiAgent* targetAgent = targetShip->asShipAiAgent();

			if (targetAgent == nullptr)
				return true;

			return !targetAgent->isAttackableBy(agent);
		} else if (!targetShip->isAttackableBy(agent)) {
			return true;
		}

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
