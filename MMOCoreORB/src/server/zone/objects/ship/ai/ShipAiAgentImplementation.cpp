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

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
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

//#define DEBUG_SPACE_AI

/*

	Ship Agent Loading

*/

void ShipAiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);
}

void ShipAiAgentImplementation::initializeTransientMembers() {
	ShipObjectImplementation::initializeTransientMembers();

	auto aiLogLevel = ConfigManager::instance()->getInt("Core3.ShipAiAgent.LogLevel", LogLevel::WARNING);

	if (aiLogLevel >= 0) {
		// Files should end up in: log/ai/YYYY-MM-DD/HH-MM/oid/AiAgent-{timestamp}-{oid}.log
		Time now;
		StringBuffer logFilename;
		logFilename << "log/ai_space/"
			<< now.getFormattedTime("%Y-%m-%d/%H-%M")
			<< "/" << getObjectID()
			<< "/ShipAiAgent-" << now.getTime() << "-" << getObjectID() << ".log";

		setFileLogger(logFilename.toString(), false, false);
		setLogSynchronized(true);
		setLogToConsole(false);
		setGlobalLogging(false);
		setLogLevel(static_cast<Logger::LogLevel>(aiLogLevel));
	} else {
		setLogLevel(LogLevel::ERROR);
		setGlobalLogging(true);
	}

	setLoggingName("ShipAiAgent");

	setAITemplate();
}

/*

	Behavior Event

*/

void ShipAiAgentImplementation::activateAiBehavior(bool reschedule) {
	if (getZoneUnsafe() == nullptr)
		return;

#ifdef DEBUG_SPACE_AI
	bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_SPACE_AI
	bool alwaysActive = false;
#endif // DEBUG_SPACE_AI

	ZoneServer* zoneServer = getZoneServer();

	if ((!alwaysActive /*&& numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr*/) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		cancelBehaviorEvent();
		return;
	}

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

void ShipAiAgentImplementation::runBehaviorTree() {
	try {
		if (getZoneUnsafe() == nullptr || !(getOptionsBitmask() & OptionBitmask::AIENABLED))
			return;

#ifdef DEBUG_AI
		bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_AI
		bool alwaysActive = false;
#endif // DEBUG_AI

		ZoneServer* zoneServer = getZoneServer();

		if (/*(!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr) ||*/ zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
			cancelBehaviorEvent();
			//setFollowObject(nullptr);
			return;
		}

		Reference<BehaviorSpace*> rootBehavior = getBehaviorTreeSpace(BehaviorTreeSlotSpace::NONE);
		assert(rootBehavior != nullptr);

#ifdef DEBUG_AI
		Time startTime;
		startTime.updateToCurrentTime();

		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("Performing root behavior: " + rootBehavior->print(), true);
#endif // DEBUG_AI

		// activate AI
		BehaviorSpace::Status actionStatus = rootBehavior->doAction(asShipAiAgent());

		if (actionStatus == BehaviorSpace::RUNNING)
			popRunningChain(); // don't keep root in the running chain

#ifdef DEBUG_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("rootBehavior->doAction() took " + String::valueOf((int)startTime.miliDifference()) + "ms to complete.", true);
#endif // DEBUG_AI

		activateAiBehavior(true);
	} catch (Exception& ex) {
		cancelBehaviorEvent();
		handleException(ex, __FUNCTION__);
	}
}

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

/*

	Movement

*/





/*

	Various Management Functions

*/

void ShipAiAgentImplementation::setAITemplate() {
	btreeMap.removeAll();
	blackboard.removeAll();

	uint64 customMap = customAiMap;

	// if (npcTemplate.get() != nullptr && customAiMap == 0)
	//	customMap = npcTemplate.get()->getCustomAiMap();

	for (const auto& slot : BehaviorTreeSlotSpace()) {
		BehaviorSpace* btree = SpaceAiMap::instance()->getTemplate(creatureBitmask, slot, customMap);

		if (btree == nullptr)
			continue;

		setTree(btree, slot);
	}

	activateAiBehavior();
}

void ShipAiAgentImplementation::writeBlackboard(const String& key, const BlackboardDataSpace& data) {
	blackboard.drop(key);
	blackboard.put(key, data);
}

BehaviorSpace* ShipAiAgentImplementation::getBehaviorTreeSpace(const BehaviorTreeSlotSpace& slot) {
	return btreeMap.get(slot).get();
}

void ShipAiAgentImplementation::setTree(BehaviorSpace* subRoot, const BehaviorTreeSlotSpace& slot) {
	if (subRoot == nullptr) {
		btreeMap.drop(slot);
		return;
	}

	btreeMap.put(slot, subRoot);
}

void ShipAiAgentImplementation::removeTree(const BehaviorTreeSlotSpace& slot) {
	setTree(NULL, slot);
}

void ShipAiAgentImplementation::handleException(const Exception& ex, const String& context) {
	auto numExceptions = SpaceAiMap::instance()->countExceptions.increment();
	auto consoleToo = (numExceptions - 1) % ConfigManager::instance()->getAiAgentConsoleThrottle() == 0;

	StringBuffer msg;

	msg << "Unhandled AiAgent exception from " << context << ": " << ex.getMessage() << "; AiMap::countExceptions=" << numExceptions << "; AiAgentID=" << getObjectID();

	if (consoleToo) {
		auto fileName = getLogFileName();

		Logger::console.error() << msg << (fileName.isEmpty() ? "" : "; logFileName=" + fileName);
	}

	auto trace = ex.getStackTrace();
	error() << msg << endl << trace.toStringData() << endl << *this;
}

ShipAiAgent* ShipAiAgentImplementation::asShipAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipAiAgent* ShipAiAgent::asShipAiAgent() {
	return this;
}