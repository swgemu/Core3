/*
 * ShipAiAgentImplementation.cpp
 */

#include <engine/core/ManagedReference.h>
#include <server/zone/CloseObjectsVector.h>
#include <engine/util/u3d/Vector3.h>
#include <system/lang/IllegalArgumentException.h>
#include <system/lang/ref/Reference.h>
#include <system/lang/String.h>
#include <system/lang/StringBuffer.h>
#include <system/lang/System.h>
#include <system/lang/Time.h>
#include <system/thread/Locker.h>
#include <system/thread/Mutex.h>
#include <system/thread/ReadLocker.h>
#include <system/util/SortedVector.h>
#include <system/util/Vector.h>
#include <system/util/VectorMap.h>

#include "server/zone/objects/ship/ai/bt/Behavior.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
//#include "server/zone/objects/creature/conversation/ConversationObserver.h"
//#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/combat/CombatManager.h"
//#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/managers/space/SpaceAiMap.h"
//#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "templates/SharedObjectTemplate.h"
#include "server/zone/objects/ship/ai/events/ShipAiBehaviorEvent.h"
#include "server/zone/objects/ship/ai/events/ShipAiRecoveryEvent.h"
//#include "server/zone/objects/player/FactionStatus.h"
//#include "templates/params/ObserverEventType.h"
//#include "server/zone/objects/scene/variables/DeltaVector.h"
//#include "server/zone/objects/scene/WorldCoordinates.h"
//#include "server/zone/objects/tangible/threat/ThreatMap.h"

//#include "server/zone/objects/creature/events/DespawnCreatureOnPlayerDissappear.h"
//#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
//#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
//#include "server/zone/objects/creature/ai/PatrolPoint.h"
//#include "server/zone/objects/creature/ai/PatrolPointsVector.h"
//#include "server/zone/objects/creature/ai/variables/CurrentFoundPath.h"
//#include "server/zone/objects/staticobject/StaticObject.h"

//#define DEBUG
//#define SHOW_NEXT_POSITION
//#define DEBUG_FINDNEXTPOSITION

/*

	Behavior Event

*/

void ShipAiAgentImplementation::activateAiBehavior(bool reschedule) {
	/*

	if (getZoneUnsafe() == nullptr || !(getOptionsBitmask() & OptionBitmask::AIENABLED))
		return;

#ifdef DEBUG_AI
	bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_AI
	bool alwaysActive = false;
#endif // DEBUG_AI

	ZoneServer* zoneServer = getZoneServer();

	if ((!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr && !isRetreating()) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		cancelBehaviorEvent();
		return;
	}
	*/

	Locker locker(&behaviorEventMutex);

	if (behaviorEvent == nullptr) {
		behaviorEvent = new ShipAiBehaviorEvent(asShipAiAgent());
		behaviorEvent->schedule(Math::max(10, nextBehaviorInterval));
	} else {
		if (reschedule) {
			try {
				if (!behaviorEvent->isScheduled())
					behaviorEvent->schedule(Math::max(10, nextBehaviorInterval));
			} catch (IllegalArgumentException& e) {
			}
		}
	}


	nextBehaviorInterval = BEHAVIORINTERVAL;
}

void ShipAiAgentImplementation::cancelBehaviorEvent() {
	Locker locker(&behaviorEventMutex);

	if (behaviorEvent == nullptr) {
		return;
	}

	if (behaviorEvent->isScheduled())
		behaviorEvent->cancel();

	behaviorEvent->clearShipAgentObject();
	behaviorEvent = nullptr;
}

/*

	Recovery Event

*/

void ShipAiAgentImplementation::activateRecovery() {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != nullptr && zoneServer->isServerShuttingDown()) {
		cancelRecoveryEvent();

		return;
	}

	Locker tLock(&recoveryEventMutex);

	if (recoveryEvent == nullptr) {
		recoveryEvent = new ShipAiRecoveryEvent(asShipAiAgent());

		recoveryEvent->schedule(2000);
	} else if (!recoveryEvent->isScheduled())
		recoveryEvent->schedule(2000);
}

void ShipAiAgentImplementation::cancelRecoveryEvent() {
	Locker locker(&recoveryEventMutex);

	if (recoveryEvent == nullptr) {
		return;
	}

	if (recoveryEvent->isScheduled())
		recoveryEvent->cancel();

	recoveryEvent->clearShipAgentObject();
	recoveryEvent = nullptr;
}

void ShipAiAgentImplementation::doRecovery(int latency) {
	try {
		if (getZoneUnsafe() == nullptr) {
			blackboard.removeAll();
			return;
		}

		/*
		activateHAMRegeneration(latency);
		activateStateRecovery();
		activatePostureRecovery();

		// we only want to activate recovery if we need to -- it will restart when we need it
		if (defenderList.size() > 0 || damageOverTimeList.hasDot()
				|| getHAM(CreatureAttribute::HEALTH) < getMaxHAM(CreatureAttribute::HEALTH)
				|| getHAM(CreatureAttribute::ACTION) < getMaxHAM(CreatureAttribute::ACTION)
				|| getHAM(CreatureAttribute::MIND) < getMaxHAM(CreatureAttribute::MIND)
				|| getWounds(CreatureAttribute::CONSTITUTION) > 0 || getWounds(CreatureAttribute::STRENGTH) > 0
				|| getWounds(CreatureAttribute::QUICKNESS) > 0 || getWounds(CreatureAttribute::STAMINA) > 0
				|| getWounds(CreatureAttribute::FOCUS) > 0 || getWounds(CreatureAttribute::WILLPOWER) > 0)
			activateRecovery();

		*/
	} catch (const Exception& ex) {
		handleException(ex, __FUNCTION__);
	}
}

/*

	Behavior Handling

*/

bool ShipAiAgentImplementation::isRunningBehavior(unsigned int id) {
	return runningChain.contains(id);
}

void ShipAiAgentImplementation::addRunningID(unsigned int id) {
	runningChain.add(id); // this adds to the back
}

void ShipAiAgentImplementation::popRunningChain() {
	// pop_back
	runningChain.remove(runningChain.size() - 1);
}

uint32 ShipAiAgentImplementation::peekRunningChain() {
	return runningChain.get(runningChain.size() - 1);
}

void ShipAiAgentImplementation::clearRunningChain() {
	runningChain.removeAll();
}

void ShipAiAgentImplementation::setAITemplate() {
	btreeMap.removeAll();
	blackboard.removeAll();

	uint64 customMap = customAiMap;

	// if (npcTemplate.get() != nullptr && customAiMap == 0)
	//	customMap = npcTemplate.get()->getCustomAiMap();

	for (const auto& slot : BehaviorTreeSlot()) {
		Behavior* btree = SpaceAiMap::instance()->getTemplate(creatureBitmask, slot, customMap);

		if (btree == nullptr)
			continue;

		setTree(btree, slot);
	}

	activateAiBehavior();
}

void ShipAiAgentImplementation::writeBlackboard(const String& key, const ShipBlackboardData& data) {
	blackboard.drop(key);
	blackboard.put(key, data);
}

Behavior* ShipAiAgentImplementation::getBehaviorTree(const BehaviorTreeSlot& slot) {
	return btreeMap.get(slot).get();
}

void ShipAiAgentImplementation::setTree(Behavior* subRoot, const BehaviorTreeSlot& slot) {
	if (subRoot == nullptr) {
		btreeMap.drop(slot);
		return;
	}

	btreeMap.put(slot, subRoot);
}

void ShipAiAgentImplementation::removeTree(const BehaviorTreeSlot& slot) {
	setTree(NULL, slot);
}

ShipAiAgent* ShipAiAgentImplementation::asShipAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipAiAgent* ShipAiAgent::asShipAiAgent() {
	return this;
}