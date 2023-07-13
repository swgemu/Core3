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
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ai/events/ShipAiBehaviorEvent.h"
#include "server/zone/objects/ship/ai/events/ShipAiRecoveryEvent.h"
#include "templates/params/ship/ShipFlags.h"

//#define DEBUG_SHIP_AI

/*

	Ship Agent Loading

*/

void ShipAiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);
}

void ShipAiAgentImplementation::loadTemplateData(SharedShipObjectTemplate* shipTemp) {
	if (shipTemp == nullptr) {
		return;
	}

	shipBitmask = shipTemp->getShipBitmask();

	const auto& componentNames = shipTemp->getComponentNames();
	const auto& componentValues = shipTemp->getComponentValues();

	if (componentNames.size() == 0 || componentValues.size() == 0) {
		return;
	}

	for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; ++slot) {
		String slotName = Components::shipComponentSlotToString(slot);

		if (slotName == "") {
			continue;
		}

		String compName = componentNames.get(slotName);

		if (compName == "") {
			continue;
		}

		const auto& values = componentValues.get(slotName);

		if (values.size() == 0) {
			continue;
		}

		float hitPoints = Math::max(values.get("hitpoints"), 50.f);
		float armor = Math::max(values.get("armor"), 100.f);

		setComponentCRC(slot, compName.hashCode());
		setComponentName(slot, compName);
		setComponentHitpoints(slot, hitPoints);
		setComponentMaxHitpoints(slot, hitPoints);
		setComponentArmor(slot, armor);
		setComponentMaxArmor(slot, armor);
		setEfficiency(slot, 1.f);

		switch (slot) {
			case Components::REACTOR: {
				setReactorGenerationRate(10000.0f);
				break;
			}
			case Components::ENGINE: {
				float speed = values.get("speed");
				float pitch = values.get("pitch") * Math::DEG2RAD;
				float yaw = values.get("yaw") * Math::DEG2RAD;
				float roll = values.get("roll") * Math::DEG2RAD;
				float pitchRate = values.get("pitchRate") * Math::DEG2RAD;
				float yawRate = values.get("yawRate") * Math::DEG2RAD;
				float rollRate = values.get("rollRate") * Math::DEG2RAD;
				float acceleration = values.get("acceleration");
				float deceleration = values.get("deceleration");

				setEngineMaxSpeed(speed, false);
				setEnginePitchAccelerationRate(pitch, false);
				setEnginePitchRate(pitchRate, false);
				setEngineYawAccelerationRate(yaw, false);
				setEngineYawRate(yawRate, false);
				setEngineRollAccelerationRate(roll, false);
				setEngineRollRate(rollRate, false);
				setEngineAccelerationRate(acceleration, false);
				setEngineDecelerationRate(deceleration, false);
				break;
			}
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float front = values.get("front");
				float back = values.get("back");
				float regen = values.get("regen");

				setFrontShield(front, false);
				setFrontShieldMax(front, false);
				setRearShield(back, false);
				setRearShieldMax(back, false);
				setShieldRechargeRate(regen, false);
				break;
			}
			case Components::CAPACITOR: {
				float rechargeRate = values.get("rechargeRate");
				float energy = values.get("energy");

				setCapacitorEnergy(energy, false);
				setCapacitorMaxEnergy(energy, false);
				setCapacitorRechargeRate(rechargeRate, false);
				break;
			}
			case Components::BOOSTER: {
				float rechargeRate = values.get("rechargeRate");
				float energy = values.get("energy");
				float accel = values.get("acceleration");
				float decel = values.get("deceleration");
				float speed = values.get("speed");
				float usage = values.get("energyUsage");
				float consumptionRate = values.get("energyConsumptionRate");

				setBoosterRechargeRate(rechargeRate);
				setBoosterEnergy(energy);
				setBoosterEnergyConsumptionRate(usage);
				setBoosterAcceleration(accel);
				setBoosterMaxSpeed(speed);
				setBoosterEnergyConsumptionRate(consumptionRate);
				break;
			}
			default: {
				if (slot >= Components::WEAPON_START) {
					float fireRate = values.get("rate");
					float drain = values.get("drain");
					float maxDamage = values.get("maxDamage");
					float minDamage = values.get("minDamage");
					float shieldEff = values.get("shieldEfficiency");
					float armorEff = values.get("armorEfficiency");
					float ammo = values.get("ammo");
					float ammoType = values.get("ammo_type");

					float totalEff = shieldEff + armorEff;

					if (totalEff < 1.f) {
						shieldEff += (1.f - totalEff) * 0.5f;
						armorEff += (1.f - totalEff) * 0.5f;
					}

					setMaxDamage(slot, maxDamage);
					setMinDamage(slot, maxDamage);
					setRefireRate(fireRate, false);
					setRefireEfficiency(drain, false);
					setShieldEffectiveness(slot, shieldEff);
					setArmorEffectiveness(slot, armorEff);
					setCurrentAmmo(slot, ammo);
					setMaxAmmo(slot, ammo);
					setAmmoClass(slot, ammoType);
				}
				break;
			}
		};
	}
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

	setShipAiTemplate();
}

void ShipAiAgentImplementation::notifyInsert(TreeEntry* entry) {
	TangibleObjectImplementation::notifyInsert(entry);

	SceneObject* scno = static_cast<SceneObject*>(entry);

	if (scno == nullptr)
		return;

	if (scno->getObjectID() == getObjectID() || !scno->isShipObject())
		return;

	ShipObject* ship = scno->asShipObject();

	if (ship != nullptr && ship->getControlDeviceID() > 0) {
		int newValue = (int) numberOfPlayersInRange.increment();
		activateAiBehavior();
	}
}

void ShipAiAgentImplementation::notifyDissapear(TreeEntry* entry) {
	TangibleObjectImplementation::notifyDissapear(entry);

	SceneObject* scno = static_cast<SceneObject*>(entry);

	if (scno == nullptr || scno->getObjectID() == getObjectID() || !scno->isShipObject())
		return;

	/*
	if (scno == getFollowObject().get()) {
			ManagedReference<AiAgent*> ai = asAiAgent();
			ManagedReference<SceneObject*> sceno = scno;

			Core::getTaskManager()->executeTask([=] () {
				Locker locker(ai);
				Locker clocker(sceno, ai);

				if (sceno == ai->getFollowObject().get()) {
					ai->restoreFollowObject();
				}
			}, "RestoreFollowObjectLambda");
	}*/

	ShipObject* ship = scno->asShipObject();

	if (ship == nullptr || ship->getControlDeviceID() == 0)
		return;

	int32 newValue = (int32) numberOfPlayersInRange.decrement();

	if (newValue < 0) {
		int oldValue;

		do {
			oldValue = (int)numberOfPlayersInRange.get();

			newValue = oldValue;

			if (newValue < 0)
				newValue = 0;
		} while (!numberOfPlayersInRange.compareAndSet((uint32)oldValue, (uint32)newValue));
	}

	if (newValue == 0) {
		/*if (despawnOnNoPlayerInRange && (despawnEvent == nullptr))) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(asAiAgent());
			despawnEvent->schedule(30000);
		}*/
	} else if (newValue < 0) {
		error() << "numberOfPlayersInRange below 0";
	}

	activateAiBehavior();
}

/*

	Behavior Event

*/

void ShipAiAgentImplementation::activateAiBehavior(bool reschedule) {
#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " -- activateAiBehavior called";
	}
#endif // DEBUG_SHIP_AI

	if (getControlDeviceID() > 0 || getZoneUnsafe() == nullptr) {
		// info(true) << getDisplayedName() << " - ID: " << getObjectID()  << " -- activateAiBehavior -- Null zone or has control device";
		return;
	}

#ifdef DEBUG_SPACE_AI
	bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_SPACE_AI
	bool alwaysActive = false;
#endif // DEBUG_SPACE_AI

	ZoneServer* zoneServer = getZoneServer();

	if ((!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " -- activateAiBehavior -- CANCELLING behavior event";

		cancelBehaviorEvent();
		return;
	}

#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " -- activateAiBehavior -- scheduling behavior event";
	}
#endif // DEBUG_SHIP_AI

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

#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " -- cancelBehaviorEvent called";
	}
#endif // DEBUG_SHIP_AI

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

#ifdef DEBUG_SHIP_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
			info(true) << getDisplayedName() << " - ID: " << getObjectID() << " runBehaviorTree -- called";
		}

		bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else // DEBUG_SHIP_AI
		bool alwaysActive = false;
#endif // DEBUG_SHIP_AI

		ZoneServer* zoneServer = getZoneServer();

		if ((!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
			cancelBehaviorEvent();
			//setFollowObject(nullptr);
			return;
		}

		Reference<BehaviorSpace*> rootBehavior = getBehaviorTreeSpace(BehaviorTreeSlotSpace::NONESPACE);
		assert(rootBehavior != nullptr);

#ifdef DEBUG_SHIP_AI
		Time startTime;
		startTime.updateToCurrentTime();

		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info(true) << getDisplayedName() << " - ID: " << getObjectID() << " - Performing root behavior: " << rootBehavior->print();
#endif // DEBUG_SHIP_AI

		// activate AI
		BehaviorSpace::Status actionStatus = rootBehavior->doAction(asShipAiAgent());

		if (actionStatus == BehaviorSpace::RUNNING)
			popRunningChain(); // don't keep root in the running chain

#ifdef DEBUG_SHIP_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info(true) << getDisplayedName() << " - ID: " << getObjectID() << " - rootBehavior->doAction() took " << (int)startTime.miliDifference() << "ms to complete.";
#endif // DEBUG_SHIP_AI

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

float ShipAiAgentImplementation::getMaxDistance() {
	/*if (isRetreating() || isFleeing())
		return 0.1f;*/

	ManagedReference<SceneObject*> followCopy = getFollowObject().get();
	unsigned int stateCopy = getMovementState();

	info(true) << getDisplayedName() << " - ID: " << getObjectID() << " - getmaxDistance - stateCopy: " << stateCopy;

	switch (stateCopy) {
		case ShipAiAgent::OBLIVIOUS:
			return 2.0f;
		case ShipAiAgent::WATCHING:
			return 1.5f;
		case ShipAiAgent::PATROLLING:
			return 0.1f;
		case ShipAiAgent::LEASHING:
			return 0.1f;
	}

	return 50.f;
}

int ShipAiAgentImplementation::setDestination() {
	info("setDestination start", true);

	ManagedReference<SceneObject*> followCopy = getFollowObject().get();
	unsigned int stateCopy = getMovementState();

	info(true) << getDisplayedName() << " - ID: " << getObjectID() << "  setDestination - stateCopy: " << String::valueOf(stateCopy) << "  Patrol Point Size:" << getPatrolPointSize();
	info("homeLocation: " + homeLocation.toString(), true);

	if (patrolPoints.size() > 20) {
		info() << "Patrol points have overflowed. Total points: " << patrolPoints.size();
		clearPatrolPoints();
	}

	switch (stateCopy) {
	case ShipAiAgent::OBLIVIOUS:

	default:
		break;
	}

	info(true) << getDisplayedName() << " - ID: " << getObjectID() << " setDestination end -- patrol point size: " << getPatrolPointSize();

	return getPatrolPointSize();
}


/*

	Various Management Functions

*/

void ShipAiAgentImplementation::setWait(int wait) {
	cooldownTimerMap->updateToCurrentAndAddMili("waitTimer", wait);
}

void ShipAiAgentImplementation::stopWaiting() {
	if (peekBlackboard("isWaiting"))
		eraseBlackboard("isWaiting");

	cooldownTimerMap->updateToCurrentTime("waitTimer");
}

bool ShipAiAgentImplementation::isWaiting() const {
	return !cooldownTimerMap->isPast("waitTimer");
}

void ShipAiAgentImplementation::setShipAiTemplate() {
	btreeMap.removeAll();
	blackboard.removeAll();

	uint64 customMap = customShipAiMap ;

	for (const auto& slot : BehaviorTreeSlotSpace()) {
		BehaviorSpace* btree = SpaceAiMap::instance()->getTemplate(shipBitmask, slot, customMap);

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
	//info(true) << getDisplayedName() << " - ID: " << getObjectID() << "  getBehaviorTreeSpace";

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
	setTree(nullptr, slot);
}

void ShipAiAgentImplementation::addShipFlag(unsigned int flag) {
	if (!(shipBitmask & flag))
		shipBitmask |= flag;
}

void ShipAiAgentImplementation::removeShipFlag(unsigned int flag) {
	if (shipBitmask & flag)
		shipBitmask &= ~flag;
}

void ShipAiAgentImplementation::handleException(const Exception& ex, const String& context) {
	auto numExceptions = SpaceAiMap::instance()->countExceptions.increment();
	auto consoleToo = (numExceptions - 1) % ConfigManager::instance()->getAiAgentConsoleThrottle() == 0;

	StringBuffer msg;

	msg << "Unhandled ShipAiAgent exception from " << context << ": " << ex.getMessage() << "; ShipAiMap::countExceptions=" << numExceptions << "; ShipAiAgentID=" << getObjectID();

	if (consoleToo) {
		auto fileName = getLogFileName();

		Logger::console.error() << msg << (fileName.isEmpty() ? "" : "; logFileName=" + fileName);
	}

	auto trace = ex.getStackTrace();
	error() << msg << endl << trace.toStringData() << endl << *this;
}

void ShipAiAgentImplementation::setShipAiDebug(bool flag) {
#ifdef DEBUG_SHIP_AI
	writeBlackboard("aiDebug", flag);
#endif // DEBUG_SHIP_AI
	info() << "setAIDebug(" << flag << ")";

	if (flag) {
		setLogLevel(LogLevel::DEBUG);

		debug() << "setShipAiDebug(" << flag << ")";
		debug() << "behaviorEvent->isScheduled = " << (behaviorEvent != nullptr ? behaviorEvent->isScheduled() : -1);
		debug() << "recoveryEvent->isScheduled = " << (recoveryEvent != nullptr ? recoveryEvent->isScheduled() : -1);
		debug() << "numberOfPlayersInRange = " << numberOfPlayersInRange.get();
	} else {
		auto aiLogLevel = ConfigManager::instance()->getInt("Core3.AiAgent.LogLevel", -1);

		if (aiLogLevel >= 0) {
			setLogLevel(static_cast<Logger::LogLevel>(aiLogLevel));
		} else {
			setLogLevel(Logger::LogLevel::ERROR);
		}
	}
}

bool ShipAiAgentImplementation::getShipAiDebug() {
#ifdef DEBUG_SHIP_AI
	return peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true;
#else // DEBUG_SHIP_AI
	return getLogLevel() >= LogLevel::DEBUG;
#endif // DEBUG_SHIP_AI
}

ShipAiAgent* ShipAiAgentImplementation::asShipAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipAiAgent* ShipAiAgent::asShipAiAgent() {
	return this;
}