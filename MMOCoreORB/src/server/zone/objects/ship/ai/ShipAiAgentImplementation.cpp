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
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/space/SpaceAiMap.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ai/events/ShipAiBehaviorEvent.h"
#include "server/zone/objects/ship/ai/events/DespawnAiShipOnNoPlayersInRange.h"
#include "templates/params/ship/ShipFlags.h"
#include "templates/params/creature/ObjectFlag.h"
#include "server/zone/objects/ship/ai/events/RotationLookupTable.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/player/FactionStatus.h"

//#define DEBUG_SHIP_AI
//#define DEBUG_FINDNEXTPOSITION

/*

	Ship Agent Loading

*/

void ShipAiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	FighterShipObjectImplementation::loadTemplateData(templateData);
}

void ShipAiAgentImplementation::loadTemplateData(SharedShipObjectTemplate* shipTemp) {
	if (shipTemp == nullptr) {
		return;
	}

	FighterShipObjectImplementation::loadTemplateData(shipTemp);

	// Handles attackable flags (ObjectFlag::ATTACKABLE, ObjectFlag::AGGRESSIVE etc)
	setPvpStatusBitmask(shipTemp->getPvpBitmask());

	if (getPvpStatusBitmask() == 0)
		closeobjects = nullptr;

	// Handles special flags for differnt AI Template bitmasks (ESCORT, FOLLOW etc)
	shipBitmask = shipTemp->getShipBitmask();

	// Special AI Template behavior tree
	customShipAiMap = shipTemp->getCustomShipAiMap();

	const auto& componentNames = shipTemp->getComponentNames();
	const auto& componentValues = shipTemp->getComponentValues();

	if (componentNames.size() == 0 || componentValues.size() == 0) {
		return;
	}

	for (uint32 slot = 0; slot <= Components::CAPITALSLOTMAX; ++slot) {
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

				if (slot > Components::FIGHTERSLOTMAX) {
					setComponentTargetable(slot, true);
				}
			}
			break;
		}
		};
	}
}

void ShipAiAgentImplementation::initializeTransientMembers() {
	FighterShipObjectImplementation::initializeTransientMembers();

	auto aiLogLevel = ConfigManager::instance()->getInt("Core3.ShipAiAgent.LogLevel", LogLevel::WARNING);

	if (aiLogLevel >= 0) {
		// Files should end up in: log/ai_space/YYYY-MM-DD/HH-MM/oid/AiAgent-{timestamp}-{oid}.log
		Time now;
		StringBuffer logFilename;
		logFilename << "log/ai_space/" << now.getFormattedTime("%Y-%m-%d/%H-%M") << "/" << getObjectID() << "/ShipAiAgent-" << now.getTime() << "-" << getObjectID() << ".log";

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

	lastDirection = Vector3::UNIT_Y;
	currentDirection = Vector3::UNIT_Y;

	cooldownTimerMap = new CooldownTimerMap();

	setHyperspacing(false);
}

void ShipAiAgentImplementation::notifyInsert(TreeEntry* entry) {
	ShipObjectImplementation::notifyInsert(entry);

	SceneObject* scno = static_cast<SceneObject*>(entry);

#ifdef DEBUG_COV
	info(true) << "ShipObjectImplementation::notifyInsert -- Object inserted: " << scno->getDisplayedName();
#endif // DEBUG_COV

	if (scno == nullptr)
		return;

	if (scno->getObjectID() == getObjectID() || !scno->isShipObject())
		return;

	ShipObject* ship = scno->asShipObject();

	if (ship == nullptr || ship->isShipAiAgent())
		return;

	CreatureObject* pilot = ship->getPilot();

	if (pilot != nullptr)
		sendPvpStatusTo(pilot);

	numberOfPlayersInRange.increment();
	activateAiBehavior();
}

void ShipAiAgentImplementation::notifyDissapear(TreeEntry* entry) {
	ShipObjectImplementation::notifyDissapear(entry);

	SceneObject* scno = static_cast<SceneObject*>(entry);

#ifdef DEBUG_COV
	info(true) << "ShipAiAgentImplementation::notifyDissapear - for Object: " << scno->getDisplayedName();
#endif // DEBUG_COV

	if (scno == nullptr || (scno->getObjectID() == getObjectID()) || !scno->isShipObject())
		return;

	ShipObject* ship = scno->asShipObject();

	if (ship == nullptr || ship->isShipAiAgent())
		return;

	int32 newValue = (int32)numberOfPlayersInRange.decrement();

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
		if (despawnOnNoPlayerInRange && (despawnEvent == nullptr)) {
			despawnEvent = new DespawnAiShipOnNoPlayersInRange(asShipAiAgent());
			despawnEvent->schedule(30000);
		}
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
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " ---------- activateShipAiBehavior called -----------";
	}
#endif // DEBUG_SHIP_AI

	if (getControlDeviceID() > 0 || getZoneUnsafe() == nullptr) {
		// info(true) << getDisplayedName() << " - ID: " << getObjectID()  << " -- activateAiBehavior -- Null zone or has control device";
		return;
	}

#ifdef DEBUG_SPACE_AI
	bool alwaysActive = ConfigManager::instance()->getAiAgentLoadTesting();
#else  // DEBUG_SPACE_AI
	bool alwaysActive = false;
#endif // DEBUG_SPACE_AI

	ZoneServer* zoneServer = getZoneServer();

	if ((!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowShipObject().get() == nullptr) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
		cancelBehaviorEvent();
		cancelRecovery();

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

	scheduleRecovery();
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
#else  // DEBUG_SHIP_AI
		bool alwaysActive = false;
#endif // DEBUG_SHIP_AI

		ZoneServer* zoneServer = getZoneServer();

		if ((!alwaysActive && numberOfPlayersInRange.get() <= 0 && getFollowShipObject().get() == nullptr) || zoneServer == nullptr || zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
			cancelBehaviorEvent();
			cancelRecovery();

			setFollowShipObject(nullptr);
			setTargetShipObject(nullptr);

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
			info(true) << getDisplayedName() << " - ID: " << getObjectID() << " ---------- rootBehavior->doAction() took " << (int)startTime.miliDifference() << "ms to complete -----------";
#endif // DEBUG_SHIP_AI

		activateAiBehavior(true);
	} catch (Exception& ex) {
		cancelBehaviorEvent();
		cancelRecovery();

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
	unsigned int stateCopy = getMovementState();

	float maxDistance = getEngineMaxSpeed() + getBoundingRadius();

	switch (stateCopy) {
	case ShipAiAgent::OBLIVIOUS:
		break;
	case ShipAiAgent::WATCHING:
		break;
	case ShipAiAgent::FOLLOWING: {
		ManagedReference<ShipObject*> followShip = getFollowShipObject().get();

		if (followShip != nullptr) {
			maxDistance += followShip->getBoundingRadius();
		}

		break;
	}
	case ShipAiAgent::PATROLLING:
		break;
	case ShipAiAgent::ATTACKING: {
		ManagedReference<ShipObject*> targetShip = getTargetShipObject().get();

		if (targetShip != nullptr) {
			maxDistance += targetShip->getBoundingRadius();
		}

		break;
	}
	case ShipAiAgent::FLEEING:
		break;
	case ShipAiAgent::LEASHING:
		break;
	case ShipAiAgent::EVADING:
		break;
	case ShipAiAgent::PATHING_HOME:
		break;
	case ShipAiAgent::FOLLOW_FORMATION:
		break;
	default:
		break;
	}

	return Math::max(50.f, maxDistance);
}

void ShipAiAgentImplementation::setMovementState(int state) {
	if (movementState == state) {
		return;
	}

	Locker locker(&targetMutex);

	movementCount = 0;
	movementState = state;
}

void ShipAiAgentImplementation::setNextPathPosition(ShipObject* targetShip) {
	SpacePatrolPoint nextPoint = targetShip->getPosition();

	patrolPoints.add(nextPoint);
}

SpacePatrolPoint ShipAiAgentImplementation::getNextPosition() {
	Locker tLock(&targetMutex);

	if (patrolPoints.size() == 0) {
		return getPosition();
	}

	return patrolPoints.get(0);
}

SpacePatrolPoint ShipAiAgentImplementation::getFinalPosition() {
	Locker tLock(&targetMutex);

	return patrolPoints.size() > 1 ? patrolPoints.get(patrolPoints.size() - 1) : getNextPosition();
}

bool ShipAiAgentImplementation::isInRangePosition(const Vector3& position, float radius) {
	const Vector3 thisPosition = getPosition();
	return thisPosition.squaredDistanceTo(position) < (radius * radius);
}

SpacePatrolPoint ShipAiAgentImplementation::getNextFollowPosition(ShipObject* followShip) {
	if (followShip == nullptr) {
		return getPosition();
	}

	setNextPathPosition(followShip);

	const Vector3& targetPosition = followShip->getPosition();
	const Vector3& targetPrevious = followShip->getPreviousPosition();

	SpacePatrolPoint nextPoint = (((targetPosition - targetPrevious) * 5.f) + targetPosition);

	return nextPoint;
}

SpacePatrolPoint ShipAiAgentImplementation::getNextAttackPosition(ShipObject* targetShip) {
	if (targetShip == nullptr) {
		return getPosition();
	}

	const Vector3& tPosition = targetShip->getPosition();
	const Vector3& tPrevious = targetShip->getPreviousPosition();
	const Vector3& sPosition = getPosition();

	Vector3 deltaT = tPosition - tPrevious;
	Vector3 deltaV = tPosition - sPosition;

	float tDistance = qNormalize(deltaT);
	float vDistance = qNormalize(deltaV);

	float tSpeed = targetShip->getCurrentSpeed();
	float vSpeed = Math::clamp(0.f, vDistance / currentSpeed, 1.f);

	Vector3 tTarget = (deltaT * tSpeed * vSpeed) + tPosition;

	float tRange = getMaxDistance();
	float vRange = Math::clamp(-1.f, 1.f - (tRange / vDistance), 1.f);

	return ((tTarget - sPosition) * vRange) + sPosition;
}

SpacePatrolPoint ShipAiAgentImplementation::getNextEvadePosition() {
	const Vector3& currentPosition = getPosition();
	Vector3 deltaV = (homeLocation.getWorldPosition() - currentPosition);

	deltaV.setZ(deltaV.getZ() * 0.5f);

	if (deltaV == Vector3::ZERO) {
		return ((getEngineMaxSpeed() * 5.f) * currentDirection) + currentPosition;
	} else {
		qNormalize(deltaV);
	}

	Vector3 evadePosition = ((getEngineMaxSpeed() * 5.f) * deltaV) + currentPosition;

#ifdef DEBUG_FINDNEXTPOSITION
	info(true) << getDisplayedName() << " -- Next evade position = " << evadePosition.toString();
#endif

	SpacePatrolPoint evadePoint = evadePosition;

	return evadePoint;
}

Vector3 ShipAiAgentImplementation::getInterceptPosition(ShipObject* target, float speed, int slot) {
	Vector3 tPosition = target->getPosition();
	Vector3 tPrevious = target->getPreviousPosition();

	if (slot != Components::CHASSIS) {
		auto data = ShipManager::instance()->getCollisionData(target);

		if (data != nullptr) {
			const auto& slotName = Components::shipComponentSlotToString(slot);
			const auto& hardpoints = data->getHardpoints(slotName);

			if (hardpoints.size() > 0) {
				const auto& hardpoint = hardpoints.get(0);
				const auto& hPosition = hardpoint.getSphere().getCenter();
				const auto& hRotation = *target->getRotationMatrix();

				Vector3 localPoint = hPosition * hRotation;
				tPosition = localPoint + tPosition;
				tPrevious = localPoint + tPrevious;
			}
		}
	}

	const Vector3& sPosition = getPosition();

	Vector3 deltaT = tPosition - tPrevious;
	Vector3 deltaV = tPosition - sPosition;

	float vRange = qNormalize(deltaV);
	float tRange = qNormalize(deltaT);

	float tSpeed = target->getCurrentSpeed();
	float vSpeed = Math::clamp(0.f, vRange / speed, 5.f);

	return (deltaT * tSpeed * vSpeed) + tPosition;
}

int ShipAiAgentImplementation::setDestination() {
	// info("setDestination start", true);

	unsigned int stateCopy = getMovementState();

#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << "  setDestination - stateCopy: " << stateCopy << "  Patrol Point Size:" << getPatrolPointSize();
	}
#endif // DEBUG_SHIP_AI

	// info(true) << getDisplayedName() << " - ID: " << getObjectID() << "  setDestination - stateCopy: " << stateCopy << "  Patrol Point Size:" << getPatrolPointSize();

	if (patrolPoints.size() > 20) {
		info() << "Patrol points have overflowed. Total points: " << patrolPoints.size();
		clearPatrolPoints();
	}

	switch (stateCopy) {
	case ShipAiAgent::OBLIVIOUS: {
		break;
	}
	case ShipAiAgent::FOLLOWING: {
		ManagedReference<ShipObject*> followCopy = getFollowShipObject().get();

		if (followCopy == nullptr) {
			break;
		}

		clearPatrolPoints();

		patrolPoints.add(getNextFollowPosition(followCopy));
		break;
	}
	case ShipAiAgent::WATCHING:
	case ShipAiAgent::PATROLLING: {
		if (hasShipWings() && (getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
			clearOptionBit(OptionBitmask::WINGS_OPEN, true);
		}

		if (patrolPoints.size() <= 1) {
			const SpacePatrolPoint finalPosition = getFinalPosition();

			if (finalPosition.isReached()) {
				clearPatrolPoints();
			}
		}

		break;
	}
	case ShipAiAgent::ATTACKING: {
		ManagedReference<ShipObject*> targetShip = getTargetShipObject().get();

		if (targetShip == nullptr) {
			break;
		}

		clearPatrolPoints();

		if (hasShipWings() && !(getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
			setOptionBit(OptionBitmask::WINGS_OPEN, true);
		}

		patrolPoints.add(getNextAttackPosition(targetShip));
		break;
	}
	case ShipAiAgent::FLEEING:
	case ShipAiAgent::LEASHING:{
		clearPatrolPoints();

		if (!homeLocation.isInRange(asShipAiAgent(), getMaxDistance())) {
			homeLocation.setReached(false);

			patrolPoints.add(homeLocation);
		} else {
			homeLocation.setReached(true);

			// TODO: remove when CheckIsHome is added
			setMovementState(ShipAiAgent::PATROLLING);
		}

		break;
	}
	case ShipAiAgent::EVADING: {
		// We have no evade point, set one
		if (getPatrolPointSize() == 0) {
			SpacePatrolPoint evadePoint = getNextEvadePosition();
			evadePoint.setEvadePoint(true);

			patrolPoints.add(evadePoint);
			break;
		}

		// we have at least one patrol point, if it is not and evade point, clear all points and set one
		const SpacePatrolPoint finalPoint = getFinalPosition();

		if (!finalPoint.isEvadePoint()) {
			clearPatrolPoints();

			SpacePatrolPoint evadePoint = getNextEvadePosition();
			evadePoint.setEvadePoint(true);

			patrolPoints.add(evadePoint);
		}

		break;
	}
	case ShipAiAgent::PATHING_HOME: {
		clearPatrolPoints();

		patrolPoints.add(homeLocation);
	}
	default: {
		break;
	}
	};

	movementCount += 1;

#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true) {
		info(true) << getDisplayedName() << " - ID: " << getObjectID() << " setDestination end -- patrol point size: " << getPatrolPointSize();
	}
#endif // DEBUG_SHIP_AI

	return getPatrolPointSize();
}

const Quaternion* ShipAiAgentImplementation::unitVectorToQuaternion() {
	if (currentDirection == lastDirection) {
		return getDirection();
	}

	float yaw = atan2(currentDirection.getX(), currentDirection.getY());
	float pitch = asin(currentDirection.getZ());
	float lastYaw = atan2(lastDirection.getX(), lastDirection.getY());
	float roll = Math::clamp((float)-M_PI_2, getRotationRate(yaw, lastYaw) * 2.f, (float)M_PI_2);

	return &RotationLookupTable::instance()->getDirection(yaw, pitch, roll);
}

float ShipAiAgentImplementation::getRotationRate(float thisRadians, float lastRadians) {
	float deltaR = (thisRadians - lastRadians) * M_1_PI;

	if (deltaR > 1.f) {
		deltaR -= 2.f;
	} else if (deltaR < -1.f) {
		deltaR += 2.f;
	}

	return Math::clamp(-1.f, deltaR, 1.f) * M_PI;
}

float ShipAiAgentImplementation::getMaxThrottle() {
	switch (movementState) {
	case ShipAiAgent::OBLIVIOUS:
		return 0.8f;
	case ShipAiAgent::WATCHING:
		return 0.5f;
	case ShipAiAgent::FOLLOWING:
		return 1.0f;
	case ShipAiAgent::PATROLLING:
		return 0.5f;
	case ShipAiAgent::ATTACKING:
		return 1.0f;
	case ShipAiAgent::FLEEING:
	case ShipAiAgent::LEASHING:
	case ShipAiAgent::EVADING:
		return 1.0f;
	case ShipAiAgent::PATHING_HOME:
	case ShipAiAgent::FOLLOW_FORMATION:
	default:
		return 0.75f;
	}
}

float ShipAiAgentImplementation::getMinThrottle() {
	switch (movementState) {
	case ShipAiAgent::OBLIVIOUS:
		return 0.4f;
	case ShipAiAgent::WATCHING:
		return 0.25f;
	case ShipAiAgent::FOLLOWING:
		return 0.25f;
	case ShipAiAgent::PATROLLING:
		return 0.25f;
	case ShipAiAgent::ATTACKING:
		return 0.75f;
	case ShipAiAgent::FLEEING:
	case ShipAiAgent::LEASHING:
	case ShipAiAgent::EVADING:
		return 0.75f;
	case ShipAiAgent::PATHING_HOME:
	case ShipAiAgent::FOLLOW_FORMATION:
	default:
		return 0.5f;
	}
}

float ShipAiAgentImplementation::qInvSqrt(float x) {
	float xHalf = 0.5f * x;
	int32_t i = 0;

	memcpy(&i, &x, sizeof(int32_t));
	i = 1597463007 - (i >> 1);
	memcpy(&x, &i, sizeof(float));
	x = x * (1.5f - xHalf * x * x);

	return x;
}

float ShipAiAgentImplementation::qNormalize(Vector3& vector) {
	float sqrLength = vector.squaredLength();
	float invLength = qInvSqrt(sqrLength);

	if (invLength == 0) {
		vector = Vector3::ZERO;
	} else {
		vector = vector * invLength;
	}

	return invLength <= FLT_EPSILON ? 0.f : 1.f / invLength;
}

bool ShipAiAgentImplementation::setDisabledEngineSpeed() {
	lastSpeed = currentSpeed;
	currentSpeed = 0.f;

	if (lastSpeed > 0.f) {
		updateZone(false, false);
		broadcastTransform(nextStepPosition.getWorldPosition());
	}

	clearPatrolPoints();

	return true;
}

bool ShipAiAgentImplementation::isTargetForward() {
	auto targetShip = getTargetShipObject().get();
	if (targetShip == nullptr) {
		return false;
	}

	const Vector3& sPosition = getPosition();
	const Vector3& tPosition = targetShip->getPosition();

	return sPosition.dotProduct(tPosition) >= 0.75f;
}

void ShipAiAgentImplementation::setSpeed() {
	const static float stepRate = (BEHAVIORINTERVAL * 0.001f);

	float shipSpeed = getActualMaxSpeed();
	if (shipSpeed == 0.f) {
		currentSpeed = 0.f;
		return;
	}

	const Vector3& currentPosition = getWorldPosition();
	const Vector3& nextPosition = getFinalPosition().getWorldPosition();

	if (currentPosition == nextPosition) {
		currentSpeed = 0.f;
		return;
	}

	float throMax = getMaxThrottle();
	float throMin = getMinThrottle();

	float speedMax = shipSpeed * throMax;
	float speedMin = shipSpeed * throMin;

	float distMax = getMaxDistance();
	float distSqr = currentPosition.squaredDistanceTo(nextPosition);
	float distCap = (distSqr < distMax * distMax) ? sqrt(distSqr) / distMax : 1.f;

	float turnCap = Math::max(0.f, currentDirection.dotProduct(nextDirection));
	float throNew = ((throMax - throMin) * (distCap * turnCap)) + throMin;

    float targetSpeed = Math::clamp(speedMin, speedMax * throNew, speedMax);
    float speedChange = targetSpeed - currentSpeed;

    float speedAccel = getEngineAccelerationRate() * stepRate;
    float speedDecel = getEngineDecelerationRate() * stepRate;

    speedChange = Math::clamp(-speedDecel, speedChange, speedAccel);

    lastSpeed = currentSpeed;
    currentSpeed = currentSpeed + speedChange;
}

void ShipAiAgentImplementation::setShipDirection() {
	const static float stepRate = (BEHAVIORINTERVAL * 0.001f);

	float shipSpeed = getActualMaxSpeed();
	if (shipSpeed == 0.f) {
		return;
	}

	const Vector3& thisPosition = getPosition();
	const Vector3& lastPosition = getPreviousPosition();
	const Vector3& nextPosition = getNextPosition().getWorldPosition();

	Vector3 deltaT = nextPosition - thisPosition;
	qNormalize(deltaT);

	Vector3 deltaV = (deltaT - currentDirection);

	float dotProduct = currentDirection.dotProduct(deltaV);

	float accelRate = getEngineYawAccelerationRate() * M_1_PI;
	float pitchRate = getEnginePitchRate() * M_1_PI;
	float yawRate = getEngineYawRate() * M_1_PI;

	Vector3 pyRate = Vector3(yawRate, yawRate, pitchRate);
	float turnRate = Math::clamp(0.2f, 1.f - dotProduct, 1.f) * accelRate * stepRate;

    if (turnRate < yawRate) {
    	turnRate = 1.f;
    }

	Vector3 thrustD = currentDirection - lastDirection;
	Vector3 thrustV = (((deltaV * pyRate) * turnRate) + (thrustD * (1.f - turnRate))) + currentDirection;
	qNormalize(thrustV);

	lastDirection = currentDirection;
	currentDirection = thrustV;
	nextDirection = deltaT;
}

void ShipAiAgentImplementation::setNextPosition() {
	if (currentSpeed == 0.f) {
		return;
	}

	Vector3 currentPosition = getWorldPosition();
	Vector3 thisMove = ((currentSpeed * (BEHAVIORINTERVAL * 0.001f)) * currentDirection) + currentPosition;

	if (thisMove == currentPosition) {
		return;
	}

	lastPosition = currentPosition;
	nextStepPosition = thisMove;

#ifdef DEBUG_FINDNEXTPOSITION
	info(true) << getDisplayedName() << " - setNextPosition set to: " << thisMove.toString();
#endif
}

bool ShipAiAgentImplementation::findNextPosition(int maxDistance) {
#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
		info(true) << getDisplayedName() << " - findNextPosition - " << maxDistance;
#endif // DEBUG_SHIP_AI

#ifdef DEBUG_FINDNEXTPOSITION
	info(true) << getDisplayedName() << " ----- findNextPosition -- Start -----";
#endif

	Locker locker(&targetMutex);

	if (getPatrolPointSize() <= 0) {
		return false;
	}

	// Set Speed
	setSpeed();

	// Set Ship Direction
	setShipDirection();

	// Set the ships next position
	setNextPosition();

	uint32 moveCount = getMovementCounter() + BEHAVIORINTERVAL;
	Quaternion direction = *unitVectorToQuaternion();

	// Update Zone with position
	setMovementCounter(moveCount);

	setDirection(direction);
	setRotationMatrix(direction);

	Vector3 nextMovementPosition = nextStepPosition.getWorldPosition();

#ifdef DEBUG_SHIP_AI
	sendDebugMessage();
	sendDebugPath();
#endif

	setPosition(nextMovementPosition.getX(), nextMovementPosition.getZ(), nextMovementPosition.getY());
	updateZone(false, false);

	broadcastTransform(nextMovementPosition);
	removeOutOfRangeObjects();

	// Remove Point
	float sqrMaxDist = Math::sqr(Math::max(32.f, getMaxDistance()));

	for (int i = patrolPoints.size(); -1 < --i;) {
		const auto& nextPosition = patrolPoints.get(i).getWorldPosition();
		const auto& thisPosition = getPosition();

		if (thisPosition.squaredDistanceTo(nextPosition) <= sqrMaxDist) {
			patrolPoints.remove(i);
		}
	}

#ifdef DEBUG_SHIP_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
		info("findNextPosition - complete returning true", true);
#endif // DEBUG_SHIP_AI

#ifdef DEBUG_FINDNEXTPOSITION
	info(true) << getDisplayedName() << " ------ findNextPosition -- End ------ Next Position: " << nextMovementPosition.toString();
#endif

	return true;
}

bool ShipAiAgentImplementation::generatePatrol(int totalPoints, float distance) {
	//info(true) << getDisplayedName() << " ID: " << getObjectID() << "  generatePatrol called with a state of " << getMovementState() << " and point size of = " << getPatrolPointSize() << " Max Distance: " << distance;

	Zone* zone = getZoneUnsafe();

	if (zone == nullptr)
		return false;

	uint32 savedState = getMovementState();

	if (savedState == ShipAiAgent::LEASHING)
		return false;

	if (savedState != ShipAiAgent::PATROLLING) {
		patrolPoints.removeAll();
		setMovementState(ShipAiAgent::PATROLLING);
	}

	Vector3 homePosition = homeLocation.getWorldPosition();
	Vector3 currentPosition = getWorldPosition();

	for (int i = 0; i < totalPoints; i++) {
		Vector3 deltaV = currentPosition - homePosition;

		float x = homePosition.getX() + (distance - System::frandom(distance * 2.f));
		float y = homePosition.getY() + (distance - System::frandom(distance * 2.f));
		float z = homePosition.getZ() + (distance - System::frandom(distance * 2.f));

		Vector3 position = Vector3(x, y, z);
		SpacePatrolPoint newPoint(position);

		patrolPoints.add(newPoint);

		currentPosition = position;
	}

	// info(true) << getDisplayedName() << " ID: " << getObjectID() << " Finished generating points. TotaL: " << getPatrolPointSize();

	return true;
}

void ShipAiAgentImplementation::leash() {
	Locker locker(&targetMutex);

	clearPatrolPoints();

	setFollowShipObject(nullptr);
	storeFollowObject();

	setTargetShipObject(nullptr);
	removeDefenders();

	eraseBlackboard("targetShipProspect");

	homeLocation.setReached(false);
}

void ShipAiAgentImplementation::broadcastTransform(const Vector3& position) {
	const static float tickRate = BEHAVIORINTERVAL / 1000.f;
	const static float invTickRate = 1000.f / BEHAVIORINTERVAL;
	const static float turnEpsilon = 1.f - (M_PI / 180.f);

	auto shipCov = getCloseObjects();

	if (shipCov == nullptr) {
		return;
	}

	float turnRate = currentDirection.dotProduct(lastDirection);

	if (turnRate > turnEpsilon && currentSpeed == lastSpeed && movementCount % 5) {
		return;
	}

	Vector3 thisPosition = getPosition();
	Vector3 lastPosition = getPreviousPosition();
	Vector3 nextPosition = getNextPosition().getWorldPosition();

	Vector3 deltaV = Vector3::ZERO;
	PackedRotationRate yaw;
	PackedRotationRate pitch;
	PackedRotationRate roll;

	if (currentSpeed > 0.f) {
		deltaV = (thisPosition - lastPosition) * invTickRate;

		if (turnRate < turnEpsilon) {
			float lastYaw = atan2(lastDirection.getX(), lastDirection.getY());
			float thisYaw = atan2(currentDirection.getX(), currentDirection.getY());
			float yawRate = getRotationRate(thisYaw, lastYaw) * invTickRate;

			float thisPitch = asin(currentDirection.getZ());
			float lastPitch = asin(lastDirection.getZ());
			float pitchRate = getRotationRate(thisPitch, lastPitch) * invTickRate;

			yaw.set(yawRate);
			pitch.set(-pitchRate);
		}
	}

	PackedVelocity velocity;
	velocity.set(Vector3(deltaV.getX(), deltaV.getZ(), deltaV.getY()));

	SortedVector<ManagedReference<TreeEntry*>> closeObjects;
	shipCov->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		auto playerEntry = closeObjects.get(i).castTo<SceneObject*>();

		if (playerEntry == nullptr) {
			continue;
		}

		uint32 syncStamp = playerEntry->getSyncStamp();

		auto data = new ShipUpdateTransformMessage(asShipObject(), thisPosition, velocity, yaw, pitch, roll, syncStamp);
		playerEntry->sendMessage(data);
	}
}

/*

	Combat

*/

bool ShipAiAgentImplementation::fireWeaponAtTarget(ShipObject* targetShip, uint32 slot, uint32 targetSlot) {
	auto crc = getShipComponentMap()->get(slot);

	if (crc == 0) {
		return false;
	}

	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return false;
	}

	auto projectileData = shipManager->getProjectileData(crc);

	if (projectileData == nullptr) {
		return false;
	}

	const Vector3& targetPosition = getInterceptPosition(targetShip, projectileData->getSpeed(), targetSlot);

	Vector3 difference = targetPosition - getPosition();
	Vector3 direction = getCurrentDirectionVector();

	float radius = Math::max(32.f, targetShip->getBoundingRadius());
	float range = Math::max(512.f, projectileData->getRange());
	float collisionDistance = SpaceCollisionManager::getPointIntersection(direction * range, difference, radius, range);

	if (collisionDistance == SpaceCollisionManager::MISS) {
		return false;
	}

	if (projectileData->isMissile()) {
		return false;
	} else if (projectileData->isCountermeasure()) {
		return false;
	} else {
		auto projectile = new ShipProjectile(asShipAiAgent(), slot - Components::WEAPON_START, projectileData->getIndex(), 0, getPosition(), direction * 7800.f, 500, 500, 1.f, System::getMiliTime());
		projectile->readProjectileData(projectileData);
		SpaceCombatManager::instance()->addProjectile(asShipAiAgent(), projectile);
	}

	return true;
}

bool ShipAiAgentImplementation::fireTurretAtTarget(ShipObject* targetShip, uint32 slot, uint32 targetSlot) {
	auto crc = getShipComponentMap()->get(slot);

	if (crc == 0) {
		return false;
	}

	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return false;
	}

	auto projectileData = shipManager->getProjectileData(crc);

	if (projectileData == nullptr) {
		return false;
	}

	auto collisionData = shipManager->getCollisionData(asShipAiAgent());

	if (collisionData == nullptr) {
		return false;
	}

	auto turretData = shipManager->getShipTurretData(getShipChassisName(), slot - Components::WEAPON_START);

	if (turretData == nullptr) {
		return false;
	}

	const auto& slotName = Components::shipComponentSlotToString(slot);
	const auto& hardpoints = collisionData->getHardpoints(slotName);
	const auto& hardpoint = hardpoints.get(crc);

	const Matrix4& shipRotation = *getRotationMatrix();
	const Vector3& shipPosition = getPosition();
	const Vector3& targetPosition = getInterceptPosition(targetShip, projectileData->getSpeed(), targetSlot);
	const Vector3& hardpointPosition = hardpoint.getSphere().getCenter();

	Vector3 turretGlobal = (hardpointPosition * shipRotation);
	turretGlobal = Vector3(turretGlobal.getX(), turretGlobal.getZ(), turretGlobal.getY()) + shipPosition;

	Vector3 targetGlobal = targetPosition - turretGlobal;

	if (targetGlobal.squaredLength() > projectileData->getRange() * projectileData->getRange()) {
		return false;
	}

	Vector3 targetLocal = targetGlobal;
	targetLocal = Vector3(targetLocal.getX(), targetLocal.getZ(), targetLocal.getY()) * shipRotation;

	const Matrix4* hardpointRotation = hardpoint.getRotation();

	if (hardpointRotation != nullptr) {
		targetLocal = targetLocal * *hardpointRotation;
	}

	float yaw = atan2(targetLocal.getX(), targetLocal.getZ());
	float pitch = atan2(-targetLocal.getY(), Math::sqrt(Math::sqr(targetLocal.getX()) + Math::sqr(targetLocal.getZ())));

	float maxPitch = turretData->getMaxPitch() * Math::DEG2RAD;
	float minPitch = turretData->getMinPitch() * Math::DEG2RAD;
	float maxYaw = turretData->getMaxYaw() * Math::DEG2RAD;
	float minYaw = turretData->getMinYaw() * Math::DEG2RAD;

	if (yaw < minYaw || yaw > maxYaw) {
		return false;
	}

	if (pitch < minPitch || pitch > maxPitch) {
		return false;
	}

	float accuracy = 0.05f;

	float randomX = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);
	float randomY = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);
	float randomZ = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);

	targetGlobal *= Vector3(randomX, randomY, randomZ);
	qNormalize(targetGlobal);

	auto projectile = new ShipProjectile(asShipAiAgent(), slot - Components::WEAPON_START, projectileData->getIndex(), 0, turretGlobal, targetGlobal * 7800.f, 500, 500, 1.f, System::getMiliTime());
	projectile->readProjectileData(projectileData);

	SpaceCombatManager::instance()->addProjectile(asShipAiAgent(), projectile);

	return true;
}

void ShipAiAgentImplementation::setDefender(ShipObject* defender) {
	if (defender == nullptr)
		return;

	TangibleObjectImplementation::setDefender(defender);

	setTargetShipObject(defender);
	setMovementState(ShipAiAgent::ATTACKING);

	defender->addDefender(asShipAiAgent());
}

bool ShipAiAgentImplementation::isAggressiveTo(TangibleObject* target) {
	if (target == nullptr || getObjectID() == target->getObjectID())
		return false;

	// info(true) << "ShipAiAgentImplementation isAggressiveTo called for Agent: " << getDisplayedName() << " towards Target: " << target->getDisplayedName();

	if (isAggressive(target)) {
		// info(true) << "ShipAgent isAggressiveTo check returned true";
		return true;
	}

	// info(true) << "ShipAgent isAggressiveTo check returned FALSE";

	return false;
}

bool ShipAiAgentImplementation::isAggressive(TangibleObject* target) {
	if (target == nullptr)
		return false;

	if (target->isInvisible())
		return false;

	bool targetIsShipAgent = target->isShipAiAgent();
	bool targetIsPlayer = !targetIsShipAgent;

	// Get factions
	uint32 thisFaction = getFaction();
	uint32 targetFaction = target->getFaction();

	// GCW Faction Checks -- Both the agent and attcking CreO have GCW Factions and they are different
	if (thisFaction != 0 && targetFaction != 0) {
		// Same factions, non-aggressive
		if (thisFaction == targetFaction)
			return false;

		// Target is an AiAgent
		if (targetIsShipAgent) {
			return true;
		// Target is a player ship
		} else {
			auto targetShip = target->asShipObject();

			if (targetShip == nullptr)
				return false;

			// Faction checks against the ships owner
			auto shipOwner = targetShip->getOwner().get();

			if (shipOwner == nullptr)
				return false;

			bool covertOvert = ConfigManager::instance()->useCovertOvertSystem();

			if (covertOvert) {
				PlayerObject* ghost = shipOwner->getPlayerObject();

				if (ghost == nullptr)
					return false;

				uint32 targetStatus = shipOwner->getFactionStatus();
				bool gcwTef = ghost->hasGcwTef();

				if (!gcwTef && targetStatus == FactionStatus::COVERT)
					return false;

				if (targetStatus == FactionStatus::OVERT || gcwTef) {
					return true;
				}
			} else {
				// this is the same thing, but ensures that if the target is a player, that they aren't on leave
				if (shipOwner->getFactionStatus() != FactionStatus::ONLEAVE) {
					return true;
				}
			}
		}
	}

	// ShipAgent is not aggressive due to faction or standing, remaining aggressive check based on pvpStatusBitmask
	return pvpStatusBitmask & ObjectFlag::AGGRESSIVE;
}

// This will handle checks for other ShipAgents or tangible objects
bool ShipAiAgentImplementation::isAttackableBy(TangibleObject* attackerTano) {
	if (attackerTano == nullptr)
		return false;

	if (pvpStatusBitmask == 0 || !(pvpStatusBitmask & ObjectFlag::ATTACKABLE))
		return false;

	if (movementState == ShipAiAgent::LEASHING)
		return false;

	auto optionsBit = getOptionsBitmask();

	if ((optionsBit & OptionBitmask::DESTROYING) || (optionsBit & OptionBitmask::INVULNERABLE)) {
		return false;
	}

	if (isInNoCombatArea())
		return false;

	if (attackerTano->isCreatureObject()) {
		return isAttackableBy(attackerTano->asCreatureObject());
	} else if (attackerTano->isShipObject() && !attackerTano->isShipAiAgent()) {
		auto attackerShip = attackerTano->asShipObject();

		if (attackerShip != nullptr) {
			auto owner = attackerShip->getOwner().get();

			if (owner != nullptr)
				return isAttackableBy(owner);
		}
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy TangibleObject Check -- Ship Agent: " << getDisplayedName() << " by attackerTano = " << attackerTano->getDisplayedName();

	// Get factions
	uint32 thisFaction = getFaction();
	uint32 shipFaction = attackerTano->getFaction();

	if (thisFaction != 0 || shipFaction != 0) {
		if (thisFaction == shipFaction) {
			return false;
		}

		if (thisFaction == 0 && shipFaction != 0) {
			return false;
		}
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy TangibleObject Check returned true";

	return true;
}

bool ShipAiAgentImplementation::isAttackableBy(CreatureObject* attacker) {
	if (attacker == nullptr)
		return false;

	// info(true) << "ShipAiAgentImplementation::isAttackableBy Creature Check -- ShipAgent: " << getDisplayedName() << " by attacker = " << attacker->getDisplayedName();

	// Get factions
	uint32 thisFaction = getFaction();
	uint32 attackerFaction = attacker->getFaction();

	// Faction Checks
	if (thisFaction != 0) {
		auto ghost = attacker->getPlayerObject();

		if (ghost != nullptr && ghost->hasCrackdownTefTowards(thisFaction)) {
			return true;
		}

		// Attacker has no faction
		if (attackerFaction == 0)
			return false;

		// This faction and attacking creature are same faction
		if (thisFaction == attackerFaction)
			return false;

		// Attack creature is not an AiAgent && their faction status is OnLeave
		if (attacker->getFactionStatus() < FactionStatus::COVERT)
			return false;
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy Creature Check returned true";

	return true;
}

bool ShipAiAgentImplementation::validateTarget() {
	ManagedReference<ShipObject*> targetShip = getTargetShipObject().get();

	return validateTarget(targetShip);
}

bool ShipAiAgentImplementation::validateTarget(ShipObject* targetShip) {
	if (targetShip == nullptr) {
		// info("validateTarget target == nullptr", true);
		return false;
	}

	if (!targetShip->isAttackableBy(asShipAiAgent()) || !targetShip->isInRange3d(asShipAiAgent(), ShipAiAgent::MAX_ATTACK_DISTANCE)) {
		//info("validateTarget FALSE attackable checks", true);
		return false;
	}

	// info(true) << "validateTarget returning true";

	return true;
}

/*

	Various Management Functions

*/

void ShipAiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == nullptr) {
			despawnEvent = new DespawnAiShipOnNoPlayersInRange(asShipAiAgent());
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

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

	uint64 customMap = customShipAiMap;

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
	// info(true) << getDisplayedName() << " - ID: " << getObjectID() << "  getBehaviorTreeSpace";

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

Vector3 ShipAiAgentImplementation::getCurrentDirectionVector() {
	return currentDirection;
}

bool ShipAiAgentImplementation::checkLineOfSight(SceneObject* obj) {
	return CollisionManager::checkLineOfSight(asShipAiAgent(), obj);
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
#else  // DEBUG_SHIP_AI
	return getLogLevel() >= LogLevel::DEBUG;
#endif // DEBUG_SHIP_AI
}

ShipAiAgent* ShipAiAgentImplementation::asShipAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipAiAgent* ShipAiAgent::asShipAiAgent() {
	return this;
}

// Debugging
void ShipAiAgentImplementation::sendDebugMessage() {
#ifdef DEBUG_SHIP_AI

	if (!peekBlackboard("aiDebug") || readBlackboard("aiDebug") == false)
		return;

	StringBuffer msg;

	const Vector3& thisPosition = getPosition();
	const Vector3& nextPosition = nextStepPosition.getCoordinates().getPoint();
	const Vector3& thisDirection = currentDirection;

	float thisDist = nextPosition.distanceTo(thisPosition);
	float nextDist = thisPosition.distanceTo(lastPosition);

	Locker sLock(asShipObject());
	auto targetVector = getTargetVector();

	msg << "ShipAiAgent:      " << getDisplayedName() << endl
		<< " movementState:   " << movementState << endl
		<< " movementCount:   " << movementCount << endl
		<< " targetVector:    " << (targetVector ? targetVector->size() : 0) << endl
		<< " patrolPoints:    " << patrolPoints.size() << endl
		<< " lastPosition:    " << lastPosition.getX() << " " << lastPosition.getY() << " " << lastPosition.getZ() << endl
		<< " thisPosition:    " << thisPosition.getX() << " " << thisPosition.getY() << " " << thisPosition.getZ() << endl
		<< " nextPosition:    " << nextPosition.getX() << " " << nextPosition.getY() << " " << nextPosition.getZ() << endl
		<< " lastDirection:   " << lastDirection.getX() << " " << lastDirection.getY() << " " << lastDirection.getZ() << endl
		<< " thisDirection:   " << thisDirection.getX() << " " << thisDirection.getY() << " " << thisDirection.getZ() << endl
		<< " currentSpeed:    " << currentSpeed << endl
		<< " lastSpeed:       " << lastSpeed << endl
		<< " timeStamp:       " << movementCounter << endl
		<< "--------------------------------";

	ChatSystemMessage* smsg = new ChatSystemMessage(msg.toString());
	broadcastMessage(smsg, false);
#endif // DEBUG_SHIP_AI
}

void ShipAiAgentImplementation::sendDebugPath() {
#ifdef DEBUG_SHIP_AI
	if (!peekBlackboard("aiDebug") || readBlackboard("aiDebug") == false)
		return;

	auto data = ShipManager::instance()->getCollisionData(asShipObject());
	if (data == nullptr) {
		return;
	}

	const Vector3& position = getPosition();

	Matrix4 rotation;
	rotation.setRotationMatrix(getDirection()->getConjugate().toMatrix3());

	auto path = new CreateClientPathMessage();
	path->addCoordinate(position);

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::SPHERE) {
		path->drawBoundingSphere(position, rotation, data->getChassisSphere());
		//path->drawBoundingSphere(position, rotation, data->getBoundingSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
		path->drawBoundingSphere(position, rotation, data->getBoundingSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
		path->drawBoundingBox(position, rotation, data->getChassisBox());
		//path->drawBoundingSphere(position, rotation, data->getBoundingSphere());
	}

	path->addCoordinate(nextStepPosition.getCoordinates().getPoint());

	for (int i = 0; i < patrolPoints.size(); ++i) {
		auto patrol = patrolPoints.get(i);
		auto point = patrol.getCoordinates().getPoint();

		path->addCoordinate(point);
	}

	broadcastMessage(path, false);
#endif // DEBUG_SHIP_AI
}
