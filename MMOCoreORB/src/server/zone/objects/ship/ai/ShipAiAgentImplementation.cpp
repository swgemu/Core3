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

#include "server/zone/managers/ship/ShipAgentTemplateManager.h"
#include "server/zone/objects/ship/ai/ShipAgentTemplate.h"
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
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ai/events/ShipAiBehaviorEvent.h"
#include "server/zone/objects/ship/ai/events/DespawnAiShipOnNoPlayersInRange.h"
#include "server/zone/objects/ship/ai/events/DespawnShipAgentTask.h"
#include "templates/params/ship/ShipFlag.h"
#include "templates/params/creature/ObjectFlag.h"
#include "server/zone/objects/ship/ai/events/RotationLookupTable.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/ship/ai/events/ShipAiPatrolPathFinder.h"
#include "server/zone/managers/spacecombat/projectile/ShipMissile.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/faction/FactionManager.h"


// #define DEBUG_SHIP_AI
// #define DEBUG_FINDNEXTPOSITION
// #define DEBUG_SHIP_DESPAWN

/*

	Ship Agent Loading

*/

void ShipAiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	FighterShipObjectImplementation::loadTemplateData(templateData);

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (shipTemp == nullptr) {
		return;
	}

	const auto& componentNames = shipTemp->getComponentNames();
	const auto& componentValues = shipTemp->getComponentValues();

	if (componentNames.size() == 0 || componentValues.size() == 0) {
		return;
	}

	for (uint32 slot = 0; slot <= Components::CAPITALSLOTMAX; ++slot) {
		String slotName = Components::shipComponentSlotToString(slot);

		if (slotName.isEmpty()) {
			continue;
		}

		String compName = componentNames.get(slotName);

		if (compName.isEmpty()) {
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

				setBoosterRechargeRate(rechargeRate, false);
				setBoosterEnergy(energy, false);
				setBoosterEnergyConsumptionRate(usage, false);
				setBoosterAcceleration(accel, false);
				setBoosterMaxSpeed(speed, false);
				setBoosterEnergyConsumptionRate(consumptionRate, false);
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
					setRefireRate(slot, fireRate);
					setEnergyPerShot(slot, drain);
					setRefireEfficiency(slot, 1.f);
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

void ShipAiAgentImplementation::loadTemplateData(ShipAgentTemplate* agentTemp) {
	if (agentTemp == nullptr) {
		return;
	}

	// Store the ShipAgent Template
	agentTemplate = agentTemp;

	// Set Options Bitmask
	optionsBitmask = agentTemplate->getOptionsBitmask();

	// Set Faction
	setShipFactionString(agentTemplate->getSpaceFaction(), false);
	setFactionStatus(FactionStatus::OVERT);

	// Handles attackable flags (ObjectFlag::ATTACKABLE, ObjectFlag::AGGRESSIVE etc)
	uint32 templatePvpStatusBitmask = agentTemplate->getPvpBitmask();

	if (agentTemplate->getAggressive() == 1 && !(templatePvpStatusBitmask & ObjectFlag::AGGRESSIVE)) {
		templatePvpStatusBitmask |= ObjectFlag::AGGRESSIVE;
	}

	setPvpStatusBitmask(templatePvpStatusBitmask, false);

	if (getPvpStatusBitmask() == 0) {
		closeobjects = nullptr;
	}

	// Handles special flags for differnt AI Template bitmasks (ESCORT, FOLLOW etc)
	shipBitmask = agentTemplate->getShipBitmask();

	// Special AI Template behavior tree
	customShipAiMap = agentTemplate->getCustomShipAiMap();

	experienceValue = agentTemplate->getExperience();

	lootChance = agentTemplate->getLootChance();
	lootRolls = agentTemplate->getLootRolls();
	lootTable = agentTemplate->getLootTable();

	minCredits = agentTemplate->getMinCredits();
	maxCredits = agentTemplate->getMaxCredits();

	imperialFactionReward = agentTemplate->getImperialFactionReward();
	rebelFactionReward = agentTemplate->getRebelFactionReward();

	// Set conversation templates, out of range message and mobile
	uint32 conversationTemp = agentTemplate->getConversationTemplate();

	if (conversationTemp == 0) {
		conversationTemp = STRING_HASHCODE("default_ship_convo_template");
	}

	setConversationTemplate(conversationTemp);
	setConversationMessage(agentTemplate->getConversationMessage());
	setConversationMobile(agentTemplate->getConversationMobile());

	// Add allied factions
	int totalAllies = agentTemplate->getTotalAlliedFactions();

	for (int i = 0; i < totalAllies; i++) {
		auto ally = agentTemplate->getAlliedFaction(i);

		alliedFactions.add(ally.hashCode());
	}

	// Make sure our own faction is set as allied
	if (shipFaction > 0 && !alliedFactions.contains(shipFaction)) {
		alliedFactions.add(shipFaction);
	}

	// Add Enemy factions
	int totalEnemies = agentTemplate->getTotalEnemyFactions();

	for (int i = 0; i < totalEnemies; i++) {
		auto enemy = agentTemplate->getEnemyFaction(i);

		enemyFactions.add(enemy.hashCode());
	}

	// Set the ships texture
	setCustomizationVariable("/shared_owner/index_texture_1", agentTemplate->getTexture(), true);

	// Set Ships color scheme
	String indexOneKey = "/shared_owner/index_color_1";
	String indexTwoKey = "/shared_owner/index_color_2";

	setCustomizationVariable(indexOneKey, agentTemplate->getColor1(), true);
	setCustomizationVariable(indexTwoKey, agentTemplate->getColor2(), true);
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

	initializeTransform(getPosition(), *getDirection());

	cooldownTimerMap = new CooldownTimerMap();

	setHyperspacing(false);

	missileLockTime = 0;

	lastDeltaTime = 0.f;
	deltaTime = 0.f;

	nextBehaviorInterval = BEHAVIORINTERVALMIN;
	updateZoneTime = 0;
}

void ShipAiAgentImplementation::notifyInsertToZone(Zone* zone) {
	// Schedule space agents to activate
	Reference<ShipAiAgent*> agentRef = asShipAiAgent();

	int randomTime = 500;

	if (zone != nullptr) {
		auto zoneServer = zone->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		if (zoneServer->isServerLoading()) {
			randomTime = (System::random(120) + 120) * 1000;
		}
	}

	Core::getTaskManager()->scheduleTask([agentRef] () {
		if (agentRef == nullptr ) {
			return;
		}

		Locker lock(agentRef);

		agentRef->activateAiBehavior();
	}, "activateShipAiLambda", randomTime);

	ShipObjectImplementation::notifyInsertToZone(zone);
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
}

void ShipAiAgentImplementation::notifyDissapear(TreeEntry* entry) {
	ShipObjectImplementation::notifyDissapear(entry);

	SceneObject* scno = static_cast<SceneObject*>(entry);

	if (scno == nullptr || (scno->getObjectID() == getObjectID()) || !scno->isShipObject()  || scno->isShipAiAgent()) {
		return;
	}

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

#ifdef DEBUG_COV
	info(true) << "ShipAiAgentImplementation::notifyDissapear - for Object: " << scno->getDisplayedName() << " number of players in range: " << newValue;
#endif // DEBUG_COV

	if (newValue <= 0) {
		if (newValue < 0) {
			error() << "numberOfPlayersInRange below 0";
		}

		if (despawnOnNoPlayerInRange) {
			if (despawnEvent == nullptr) {
				despawnEvent = new DespawnAiShipOnNoPlayersInRange(asShipAiAgent());
			}

			if (!despawnEvent->isScheduled()) {
				despawnEvent->schedule(300000);
			}
		}
	}
}

void ShipAiAgentImplementation::notifyDespawn() {
#ifdef DEBUG_SHIP_DESPAWN
	info(true) << "notifyDespawn called for - " << getDisplayedName() << " ID: " << getObjectID();
#endif // DEBUG_SHIP_DESPAWN

 	Locker locker(&despawnMutex);

	// Clearing Agent Events
	cancelBehaviorEvent();
	wipeBlackboard();

	clearPatrolPoints();

	ManagedReference<SceneObject*> home = homeObject.get();

	// Notify lairspawns that a creature/NPC has been killed and it will handle respawn
	if (home != nullptr && home->getObserverCount(ObserverEventType::SHIPAGENTDESPAWNED) > 0) {
#ifdef DEBUG_SHIP_DESPAWN
		info(true) << getDisplayedName() << " ID: " << getObjectID() << " notifying home space in regards of despawn.";
#endif // DEBUG_SHIP_DESPAWN

		home->notifyObservers(ObserverEventType::SHIPAGENTDESPAWNED, asShipAiAgent());
	} else {
		notifyObservers(ObserverEventType::SHIPAGENTDESPAWNED);
	}

	// Drop Squadron Observer when implemented
	if (getObserverCount(ObserverEventType::SQUADRON) > 0) {
		SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::SQUADRON);

		for (int i = 0; i < observers.size(); i++) {
			/*SquadObserver* squadObserver = cast<SquadObserver*>(observers.get(i).get());

			if (squadObserver != nullptr) {
				dropObserver(ObserverEventType::SQUAD, squadObserver);
			}
			*/
		}
	}

#ifdef DEBUG_SHIP_DESPAWN
	info(true) << getDisplayedName() << " ID: " << getObjectID() << " notifyDespawn complete - Reference Count: " << getReferenceCount();
#endif // DEBUG_SHIP_DESPAWN
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

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
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

	int interval = Math::clamp((int)BEHAVIORINTERVALMIN, nextBehaviorInterval, (int)BEHAVIORINTERVALMAX);

	if (behaviorEvent == nullptr) {
		behaviorEvent = new ShipAiBehaviorEvent(asShipAiAgent());
		behaviorEvent->schedule(interval);
	} else {
		if (reschedule) {
			try {
				if (!behaviorEvent->isScheduled())
					behaviorEvent->schedule(interval);
			} catch (IllegalArgumentException& e) {
			}
		}
	}

	int iterate = behaviorIntervalIterator.get() % 1000;
	int timeLast = behaviorIntervalSchedule.get();
	int timeNow = System::getMiliTime() % 1000;

	if (timeNow <= timeLast) {
		iterate += 1;
	} else {
		iterate = 0;
	}

	nextBehaviorInterval = getNextBehaviorInterval() + iterate;
	behaviorIntervalIterator.set(iterate);
	behaviorIntervalSchedule.set(timeNow);
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
#endif // DEBUG_SHIP_AI

		ZoneServer* zoneServer = getZoneServer();

		if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
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
		if (shipBitmask & ShipFlag::ESCORT) {
			maxDistance = getEscortSpeed() + getBoundingRadius();
		}

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
		maxDistance = 1000.f;
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

	Vector3 iPosition = getInterceptPosition(targetShip, DEFAULT_PROJECTILE_SPEED, Components::CHASSIS);

	return SpacePatrolPoint(iPosition);
}

SpacePatrolPoint ShipAiAgentImplementation::getNextEvadePosition() {
	const Vector3& sPosition = getWorldPosition();
	const Vector3& hPosition = getHomePosition();

	Vector3 homeDirection = hPosition - sPosition;
	float homeDistance = qNormalize(homeDirection);
	float homeAnchor = Math::clamp(0.f, homeDistance / MAX_ATTACK_DISTANCE, 1.f);
	float evadeDistance = (getActualMaxSpeed() * MAX_EVADE_DURATION) + getMaxDistance();

	Vector3 inverseDirection = currentDirection * -1.f;
	Vector3 evadeDirection = (inverseDirection * (1.f - homeAnchor)) + (homeDirection * homeAnchor);
	Vector3 evadePosition = (evadeDirection * evadeDistance) + sPosition;

	return SpacePatrolPoint(evadePosition);
}

Vector3 ShipAiAgentImplementation::getInterceptPosition(ShipObject* target, float speed, int slot, int targetSlot) {
	Vector3 sPosition = getWorldPosition();

	if (slot != Components::CHASSIS) {
		const Matrix4& sRotation = *getConjugateMatrix();
		auto data = ShipManager::instance()->getCollisionData(asShipAiAgent());

		if (data != nullptr) {
			const auto& slotName = Components::shipComponentSlotToString(slot);
			const auto& hardpoints = data->getHardpoints(slotName);

			if (hardpoints.size() > 0) {
				const auto& hardpoint = hardpoints.get(0);
				const auto& hPosition = hardpoint.getSphere().getCenter();

				Vector3 localPoint = hPosition * sRotation;
				sPosition = Vector3(localPoint.getX(), localPoint.getZ(), localPoint.getY()) + sPosition;
			}
		}
	}

	const Matrix4& tRotation = *target->getConjugateMatrix();
	Vector3 tPosition = target->getWorldPosition();

	if (targetSlot != Components::CHASSIS) {
		auto data = ShipManager::instance()->getCollisionData(target);

		if (data != nullptr) {
			const auto& slotName = Components::shipComponentSlotToString(targetSlot);
			const auto& hardpoints = data->getHardpoints(slotName);

			if (hardpoints.size() > 0) {
				const auto& hardpoint = hardpoints.get(0);
				const auto& hPosition = hardpoint.getSphere().getCenter();

				Vector3 localPoint = hPosition * tRotation;
				tPosition = Vector3(localPoint.getX(), localPoint.getZ(), localPoint.getY()) + tPosition;
			}
		}
	}

	Vector3 deltaT = Vector3(tRotation[2][0], tRotation[2][2], tRotation[2][1]);
	Vector3 deltaV = tPosition - sPosition;

	float vRange = qNormalize(deltaV);
	float tSpeed = target->getCurrentSpeed();
	float vTime = Math::clamp(0.f, vRange / speed, 10.f);

	return (deltaT * tSpeed * vTime) + tPosition;
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
		if (getOptionsBitmask() & OptionBitmask::WINGS_OPEN) {
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

		if (!(getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
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

		if (!(getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
			setOptionBit(OptionBitmask::WINGS_OPEN, true);
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

Quaternion ShipAiAgentImplementation::radiansToQuaterion(float yaw, float pitch, float roll) {
	yaw = getRotationRate(-yaw + M_PI_2);

	if (getBoundingRadius() >= 128.f) {
		int degY = Math::rad2deg(yaw);
		int degP = Math::rad2deg(pitch);
		int degR = Math::rad2deg(roll);

		Quaternion qDirection;
		qDirection.rotate(Vector3::UNIT_Z, -degR);
		qDirection.rotate(Vector3::UNIT_X, -degP);
		qDirection.rotate(Vector3::UNIT_Y, degY);
		qDirection.normalize();

		return qDirection;
	}

	return RotationLookupTable::instance()->getDirection(yaw, pitch, roll);
}

Vector3 ShipAiAgentImplementation::radiansToUnitVector(float yaw, float pitch) {
	float cosY = cos(yaw);
	float sinY = sin(yaw);
	float cosP = cos(pitch);
	float sinP = sin(pitch);

	Vector3 thrustV(cosY * cosP, sinY * cosP, sinP);
	qNormalize(thrustV);

	return thrustV;
}

Quaternion ShipAiAgentImplementation::unitVectorToQuaternion() {
	return radiansToQuaterion(currentRotation.getX(), currentRotation.getY(), currentRotation.getZ());
}

Vector3 ShipAiAgentImplementation::unitVectorToRotation() {
	return Vector3(atan2(currentDirection.getY(),currentDirection.getX()), asin(currentDirection.getZ()), 0.f);
}

Vector3 ShipAiAgentImplementation::matrixToUnitVector() {
	return Vector3(conjugateMatrix[2][0], conjugateMatrix[2][2], conjugateMatrix[2][1]);
}

float ShipAiAgentImplementation::getRotationRate(float thisRadians, float lastRadians) {
	float radians = thisRadians - lastRadians;

	if (radians > M_PI) {
		return radians - (M_PI * 2.f);
	}

	if (radians < -M_PI) {
		return radians + (M_PI * 2.f);
	}

	return radians;
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

float ShipAiAgentImplementation::getMaxTurnRate() {
	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::PATROLLING: {
			return 0.4f;
		}
		case ShipAiAgent::ATTACKING:
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOW_FORMATION:
		default: {
			return 0.8f;
		}
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

float ShipAiAgentImplementation::qSqrt(float x) {
	return x <= FLT_EPSILON  ? 0.f : 1.f / qInvSqrt(x);
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

void ShipAiAgentImplementation::setNextSpeed() {
	float speedMax = getActualMaxSpeed() * getMaxThrottle();
	float speedMin = getActualMaxSpeed() * getMinThrottle();

	float escortSpeed = getEscortSpeed();

	if (escortSpeed > 0.f) {
		speedMax = escortSpeed;
	}

	const Vector3& currentPosition = getWorldPosition();
	const Vector3& nextPosition = getFinalPosition().getWorldPosition();

	float distanceSqr = Math::max(currentPosition.squaredDistanceTo(nextPosition) - Math::sqr(getMaxDistance()), 0.f);
	float speed = speedMin;

	if (distanceSqr > 0.f || currentSpeed > 0.f) {
		float decelRate = getActualDecelerationRate() * 2.f;
		float accelRate = getActualAccelerationRate();

		float decelDistSqr = Math::sqr((speedMax * speedMax) / decelRate);
		speed = decelDistSqr > distanceSqr ? qSqrt(distanceSqr / decelDistSqr) * speedMax : speedMax;
		speed = Math::clamp(-decelRate * deltaTime, speed - currentSpeed, accelRate * deltaTime) + currentSpeed;
	}

	lastSpeed = currentSpeed;
	currentSpeed = Math::clamp(speedMin, ceil(speed), speedMax);
}

void ShipAiAgentImplementation::setNextDirection() {
	const Vector3& currentPosition = getPosition();
	const Vector3& nextPosition = getNextPosition().getWorldPosition();

	if (currentPosition == nextPosition) {
		return;
	}

	Vector3 deltaV = nextPosition - currentPosition;
	qNormalize(deltaV);

	if (deltaV != nextDirection) {
		float nextY = atan2(nextDirection.getY(), nextDirection.getX());
		float nextP = asin(nextDirection.getZ());

		nextDirection = deltaV;
		nextRotation = Vector3(nextY, nextP, 0.f);
	}

	Vector3 thrustV = nextDirection;
	Vector3 thrustR = currentRotation;

	float dotProduct = currentDirection.dotProduct(nextDirection);

	if (dotProduct <= 0.999f || fabs(thrustR.getZ()) >= 0.001f) {
		float rateMax = getMaxTurnRate() * deltaTime;

		Vector3 accel = Vector3(getActualYawAccelerationRate(), getActualPitchAccelerationRate(), getActualRollAccelerationRate()) * rateMax;
		Vector3 actual = Vector3(getActualYawRate(), getActualPitchRate(), getActualRollRate()) * rateMax;
		Vector3 delta;
		Vector3 rate;

		for (int axis = 0; axis < 3; ++axis) {
			delta[axis] = getRotationRate(nextRotation[axis], currentRotation[axis]);
			float lastDelta = getRotationRate(currentRotation[axis], lastRotation[axis]);

			if (axis == 2 && fabs(delta[axis]) < fabs(delta[0])) {
				delta[axis] = -delta[0];
			}

			float thisDelta = Math::clamp(lastDelta - accel[axis], delta[axis], lastDelta + accel[axis]);
			rate[axis] = getRotationRate(Math::clamp(-actual[axis], thisDelta, actual[axis])) + currentRotation[axis];

			if (axis == 2) {
				rate[axis] = Math::clamp((float)-M_PI_2, rate[axis], (float)M_PI_2);
			}
		}

		if (rate != Vector3::ZERO) {
			auto direction = radiansToQuaterion(rate.getX(), rate.getY(), rate.getZ());
			setDirection(direction);
			setRotationMatrix(direction);

			thrustV = radiansToUnitVector(rate.getX(), rate.getY());
			thrustR = rate;
		}
	}

	lastRotation = currentRotation;
	currentRotation = thrustR;

	lastDirection = currentDirection;
	currentDirection = thrustV;
}

void ShipAiAgentImplementation::setNextPosition() {
	if (currentSpeed == 0.f || currentDirection == Vector3::ZERO) {
		return;
	}

	const Vector3& currentPosition = getPosition();

	currentDirection.setX(Math::clamp(-1.f, currentDirection.getX(), 1.f));
	currentDirection.setY(Math::clamp(-1.f, currentDirection.getY(), 1.f));
	currentDirection.setZ(Math::clamp(-1.f, currentDirection.getZ(), 1.f));

	Vector3 thrustV = (currentDirection * currentSpeed * deltaTime) + currentPosition;

	thrustV.setX(Math::clamp(-7999.f, thrustV.getX(), 7999.f));
	thrustV.setY(Math::clamp(-7999.f, thrustV.getY(), 7999.f));
	thrustV.setZ(Math::clamp(-7999.f, thrustV.getZ(), 7999.f));

	if (thrustV == currentPosition) {
		return;
	}

	nextStepPosition = SpacePatrolPoint(thrustV);

#ifdef DEBUG_FINDNEXTPOSITION
	info(true) << getDisplayedName() << " - setNextPosition set to: " << thisMove.toString();
#endif
}

bool ShipAiAgentImplementation::findNextPosition(int maxDistance) {
	int64 timeNow = System::getMiliTime();
	int64 deltaTime = timeNow - updateZoneTime;

	if (deltaTime >= UPDATEZONEINTERVAL) {
		updateZoneTime = timeNow;

		updateZone(false, false);
		removeOutOfRangeObjects();
		doRecovery(deltaTime);
	}

	if (getPatrolPointSize() <= 0) {
		return false;
	}

	updatePatrolPoints();
	return true;
}

void ShipAiAgentImplementation::updateTransform(bool lightUpdate) {
	if (lightUpdate && numberOfPlayersInRange < 1) {
		return;
	}

	setDeltaTime();
	setNextSpeed();
	setNextDirection();
	setNextPosition();

#ifdef DEBUG_SHIP_AI
	sendDebugMessage();
	sendDebugPath();
#endif

	const Vector3& position = nextStepPosition.getWorldPosition();

	setPosition(position);
	broadcastTransform(position);
}

void ShipAiAgentImplementation::setDeltaTime() {
	long timeSync = (0xFFFFFFFF) & System::getMiliTime();
	int deltaSync = Math::max(timeSync - syncStamp, 0ull);

	lastDeltaTime = deltaTime;
	deltaTime = Math::clamp(0.1f, deltaSync * 0.001f, 2.f);
	syncStamp = timeSync;
}

int ShipAiAgentImplementation::getNextBehaviorInterval() {
	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::PATROLLING: {
			return BEHAVIORINTERVALMAX;
		}
		case ShipAiAgent::ATTACKING:
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOW_FORMATION:
		default: {
			return BEHAVIORINTERVAL;
		}
	}
}

bool ShipAiAgentImplementation::generatePatrol(int totalPoints, float distance, int pathShape) {
	// info(true) << getDisplayedName() << " ID: " << getObjectID() << "  generatePatrol called with a state of " << getMovementState() << " and point size of = " << totalPoints << " Max Distance: " << distance;

	auto zone = getZoneUnsafe();

	if (zone == nullptr) {
		return false;
	}

	uint32 savedState = getMovementState();

	if (savedState == ShipAiAgent::LEASHING) {
		return false;
	}

	if (savedState != ShipAiAgent::PATROLLING && savedState != ShipAiAgent::WATCHING) {
		clearPatrolPoints();
		setMovementState(ShipAiAgent::PATROLLING);
	}

	/* ShipFlag.h
		GUARD_PATROL - For ships that patrol a specific area in a spherical pattern where they will have a min range and max range to stay within
			used for ships in patrol around a point or object such as a space station.
		RANDOM_PATROL - Default method for patrolling. Randomly generates points around its home location.
		FIXED_PATROL - For ships that have specific set of patrol points assigned to them and will only navigate to those points.
		SQUADRON_PATROL - For ships that are in a squadron, this will be used to create and assign them to an observer as well as the behaviors needed to operate in the squadron.
		SQUADRON_FOLLOW - Similar to above, but for ships that have to follow another ship while in a squadron.
	*/

	Locker locker(&targetMutex);

	const Vector3& homePosition = getHomePosition();
	Vector3 patrolPosition = homePosition;
	Vector<SpacePatrolPoint> patrolCopy;

	if (isFixedPatrolShipAgent()) {
		auto shipAgentTempMan = ShipAgentTemplateManager::instance();

		if (shipAgentTempMan == nullptr) {
			return false;
		}

		const auto zoneNameHash = zone->getZoneName().hashCode();
		int totalPoints = fixedPatrolPoints.size();

		// Add patrol points from the vector selected at spawn
		for (int i = 0; i < totalPoints; i++) {
			const uint32 pointHash = fixedPatrolPoints.get(i);
			SpacePatrolPoint patrolPoint = shipAgentTempMan->getSpacePatrolPoint(zoneNameHash, pointHash);

			patrolCopy.add(patrolPoint);
		}

		patrolPoints.removeAll(totalPoints, totalPoints);
		patrolPoints.addAll(patrolCopy);
	} else if (shipBitmask & ShipFlag::GUARD_PATROL) {
		float minimumGuardPatrol = getMinimumGuardPatrol();
		float maximumGuardPatrol = getMaximumGuardPatrol();
		int randomPatrol = System::random((int)(maximumGuardPatrol - minimumGuardPatrol)) + minimumGuardPatrol;

		patrolCopy = ShipAiPatrolPathFinder::generatePatrolSphere(Sphere(patrolPosition, randomPatrol), Matrix4(), totalPoints);

		patrolPoints.removeAll(totalPoints, totalPoints);
		patrolPoints.addAll(patrolCopy);
	} else {
		float radiusMax = distance * 0.5f;
		float radiusMin = distance * 0.1f;

		patrolPosition = ShipAiPatrolPathFinder::getRandomPosition(homePosition, radiusMin, radiusMax);
		float patrolRadius = distance - qSqrt((homePosition - patrolPosition).squaredLength());

		switch (pathShape) {
			case ShipAiPatrolPathFinder::PathShape::SPHERE: {
				patrolCopy = ShipAiPatrolPathFinder::generatePatrolSphere(Sphere(patrolPosition, patrolRadius), Matrix4(), totalPoints);
				break;
			}
			default: {
				patrolCopy = ShipAiPatrolPathFinder::generatePatrolCircle(Sphere(patrolPosition, patrolRadius), Matrix4(), totalPoints);
			}
		}

		patrolPoints.removeAll(totalPoints, totalPoints);
		patrolPoints.addAll(patrolCopy);
	}

	// info(true) << getDisplayedName() << " ID: " << getObjectID() << " Finished generating points. TotaL: " << getPatrolPointSize();

	return true;
}

void ShipAiAgentImplementation::updatePatrolPoints() {
	float inRangeDistance = Math::sqr(getMaxDistance());

	// Fixed patrol point ships move from point to point
	if (isFixedPatrolShipAgent() && (getMovementState() == ShipAiAgent::PATROLLING)) {
		const auto& nextPosition = patrolPoints.get(0).getWorldPosition();
		const auto& thisPosition = getPosition();

		if (thisPosition.squaredDistanceTo(nextPosition) < inRangeDistance) {
			patrolPoints.remove(0);
		}

		return;
	}

	for (int i = patrolPoints.size(); -1 < --i;) {
		const auto& nextPosition = patrolPoints.get(i).getWorldPosition();
		const auto& thisPosition = getPosition();

		if (thisPosition.squaredDistanceTo(nextPosition) <= inRangeDistance) {
			patrolPoints.removeRange(0, i+1);
			break;
		}
	}
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
	if (numberOfPlayersInRange < 1) {
		return;
	}

	auto shipCov = getCloseObjects();

	if (shipCov == nullptr) {
		return;
	}

	if (currentSpeed == lastSpeed && currentRotation == lastRotation && movementCount % 5) {
		return;
	}

	const Vector3& currentPosition = getPosition();

	PackedVelocity velocity;
	PackedRotationRate rateY;
	PackedRotationRate rateP;
	PackedRotationRate rateR;

	if (currentSpeed > 0.f) {
		Vector3 deltaV = currentDirection * currentSpeed;
		velocity.set(Vector3(deltaV.getX(), deltaV.getZ(), deltaV.getY()));

		float rT = 1.f / Math::clamp(0.1f, (deltaTime + lastDeltaTime) * 0.5f, 10.f) * 0.5f;
		float rY = -getRotationRate(currentRotation.getX(), lastRotation.getX()) * rT;
		float rP = -getRotationRate(currentRotation.getX(), lastRotation.getX()) * rT;
		float rR = getRotationRate(currentRotation.getX(), lastRotation.getX()) * rT;

		rateY.set(rY);
		rateP.set(rP);
		rateR.set(rR);
	}

	SortedVector<ManagedReference<TreeEntry*>> closeObjects;
	shipCov->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		auto playerEntry = closeObjects.get(i).castTo<SceneObject*>();

		if (playerEntry == nullptr) {
			continue;
		}

		int updateFreq = Math::clamp(1.f, 20.f / calculatePixelHeight(playerEntry->getWorldPosition()), 5.f);

		if (movementCount % updateFreq) {
			continue;
		}

		uint32 syncStamp = playerEntry->getSyncStamp();

		auto data = new ShipUpdateTransformMessage(asShipObject(), currentPosition, velocity, rateY, rateP, rateR, syncStamp);
		playerEntry->sendMessage(data);
	}
}

float ShipAiAgentImplementation::calculatePixelHeight(const Vector3& position) {
	static constexpr float SCREEN_HEIGHT = 1080.f;
	static constexpr float SCREEN_FOV = 70.f * (M_PI / 180.f);
	static constexpr float INVERSE_FOV = (1.f / SCREEN_FOV) * SCREEN_HEIGHT;

	float distance = qSqrt(getWorldPosition().squaredDistanceTo(position));
	float radius = getBoundingRadius();
	float angle = atan2(radius, distance) * 2.f;

	return Math::max(angle * INVERSE_FOV, 1.f);
}

/*

	Combat

*/

Vector<uint32> ShipAiAgentImplementation::getActiveWeaponVector() {
	Vector<uint32> activeWeapons;

	bool isCapacitorActive = isComponentFunctional(Components::CAPACITOR);

	for (int slot = Components::WEAPON_START; slot <= Components::CAPITALSLOTMAX; ++slot) {
		if (!isComponentFunctional(slot)) {
			continue;
		}

		if (!isCapacitorActive && getEnergyPerShotMap()->get(slot) > 0.f) {
			continue;
		}

		activeWeapons.add(slot);
	}

	return activeWeapons;
}

bool ShipAiAgentImplementation::fireWeaponAtTarget(ShipObject* targetShip, uint32 slot, uint32 targetSlot) {
	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return false;
	}

	uint32 componentCRC = getShipComponentMap()->get(slot);
	auto projectileData = shipManager->getProjectileData(componentCRC);

	if (projectileData == nullptr) {
		return false;
	}

	uint32 weaponIndex = slot - Components::WEAPON_START;
	auto turretData = shipManager->getShipTurretData(chassisDataName, weaponIndex);

	if (turretData != nullptr) {
		return fireTurretAtTarget(targetShip, projectileData, turretData, slot, targetSlot);
	}

	if (projectileData->isMissile()) {
		uint32 missileType = getAmmoClassMap()->get(slot);
		auto missileData = shipManager->getMissileData(missileType);

		if (missileData == nullptr) {
			return false;
		}

		return fireMissileAtTarget(targetShip, projectileData, missileData, slot, targetSlot);
	}

	if (projectileData->isTractorBeam()) {
		return false;
	}

	if (projectileData->isMiningLaser()) {
		return false;
	}

	if (projectileData->isCountermeasure()) {
		return false;
	}

	return fireProjectileAtTarget(targetShip, projectileData, slot, targetSlot);
}

bool ShipAiAgentImplementation::fireProjectileAtTarget(ShipObject* targetShip, const ShipProjectileData* projectileData, uint32 slot, uint32 targetSlot) {
	if (targetShip == nullptr || projectileData == nullptr) {
		return false;
	}

	const Vector3& position = getWorldPosition();
	const Vector3& targetPosition = targetShip->getWorldPosition();

	uint32 weaponIndex = slot - Components::WEAPON_START;
	Vector3 difference = targetPosition - position;

	float radius = Math::max(32.f, targetShip->getBoundingRadius());
	float range = Math::max(512.f, projectileData->getRange());
	float collisionDistance = SpaceCollisionManager::instance()->getPointIntersection(currentDirection * range, difference, radius, range);

	if (collisionDistance == SpaceCollisionManager::MISS) {
		return false;
	}

	auto projectile = new ShipProjectile(asShipAiAgent(), weaponIndex, projectileData->getIndex(), targetSlot, position, currentDirection * 7800.f, 0, 0, 1.f, System::getMiliTime());
	projectile->readProjectileData(projectileData);

	SpaceCombatManager::instance()->addProjectile(asShipAiAgent(), projectile);
	return true;
}

bool ShipAiAgentImplementation::fireMissileAtTarget(ShipObject* targetShip, const ShipProjectileData* projectileData, const ShipMissileData* missileData, uint32 slot, uint32 targetSlot) {
	if (targetShip == nullptr || projectileData == nullptr || missileData == nullptr || targetShip != getTargetShipObject().get()) {
		return false;
	}

	const Vector3& position = getWorldPosition();
	const Vector3& targetPosition = targetShip->getWorldPosition();
	float distanceSqr = position.squaredDistanceTo(targetPosition);
	float distanceMax =  Math::sqr(projectileData->getRange());

	if (distanceSqr > distanceMax) {
		missileLockTime = 0.f;
		return false;
	}

	Vector3 targetDirection = targetPosition - position;
	float targetDistance = qNormalize(targetDirection);

	float targetY = atan2(targetDirection.getY(), targetDirection.getX());
	float targetP = asin(targetDirection.getZ());
	float deltaY = fabs(targetY - currentRotation.getX());
	float deltaP = fabs(targetP - currentRotation.getY());

	float targetAngle = atan2(targetShip->getBoundingRadius(), targetDistance);
	float aquireAngle = Math::deg2rad(missileData->getTargetAquisitionAngle()) + targetAngle;

	if (deltaY > aquireAngle || deltaP > aquireAngle) {
		missileLockTime = 0.f;
		return false;
	}

	float deltaBase = fabs(DEFAULT_PROJECTILE_REFIRE - (BEHAVIORINTERVAL * 0.001f));
	missileLockTime += deltaBase + deltaTime;

	if (missileLockTime < missileData->getTargetAquisitionTime()) {
		return false;
	}

	float missileSpeedMax = missileData->getServerSpeed();
	float missileRangeMin = missileData->getMinTime() * missileSpeedMax;
	float missileRangeMax = missileData->getMaxTime() * missileSpeedMax;

	if (targetDistance < missileRangeMin || targetDistance > missileRangeMax) {
		return false;
	}

	float refireTime = getWeaponRefireDeltaTime(slot) * 0.001f;
	float refireRate = getComponentRefireRate()->get(slot);

	if (refireTime < refireRate) {
		return false;
	}

	int missileType = getAmmoClassMap()->get(slot);
	int weaponIndex = slot - Components::WEAPON_START;

	auto missile = new ShipMissile(asShipAiAgent(), weaponIndex, missileType, targetSlot, position, currentDirection * 7800.f, 0, 0, 1.f, System::getMiliTime());
	missile->readMissileData(missileData);
	missile->setTarget(targetShip);
	missile->calculateTimeToHit();

	SpaceCombatManager::instance()->addMissile(asShipAiAgent(), missile);
	setWeaponRefireDeltaTime(slot);
	return true;
}

bool ShipAiAgentImplementation::fireTurretAtTarget(ShipObject* targetShip, const ShipProjectileData* projectileData, const ShipTurretData* turretData, uint32 slot, uint32 targetSlot) {
	auto crc = getShipComponentMap()->get(slot);

	if (crc == 0 || targetShip == nullptr || projectileData == nullptr || turretData == nullptr) {
		return false;
	}

	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return false;
	}

	auto collisionData = shipManager->getCollisionData(asShipAiAgent());

	if (collisionData == nullptr) {
		return false;
	}

	const auto& slotName = Components::shipComponentSlotToString(slot);
	const auto& hardpoints = collisionData->getHardpoints(slotName);
	const auto& hardpoint = hardpoints.get(crc);

	const Matrix4& shipRotation = *getConjugateMatrix();
	const Vector3& shipPosition = getPosition();
	const Vector3& targetPosition = getInterceptPosition(targetShip, projectileData->getSpeed(), slot, targetSlot);
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

float ShipAiAgentImplementation::getWeaponRefireDeltaTime(uint32 slot) {
	auto cooldownTime = cooldownTimerMap->getTime("weapon_refire_" + String::valueOf(slot));

	if (cooldownTime == nullptr) {
		return FLT_MAX;
	}

	return cooldownTime->miliDifference();
}

void ShipAiAgentImplementation::setWeaponRefireDeltaTime(uint32 slot) {
	if (slot == Components::CHASSIS || slot > Components::CAPITALSLOTMAX) {
		return;
	}

	cooldownTimerMap->updateToCurrentTime("weapon_refire_" + String::valueOf(slot));
}

void ShipAiAgentImplementation::setDefender(ShipObject* defender) {
	if (defender == nullptr)
		return;

	TangibleObjectImplementation::setDefender(defender);

	setTargetShipObject(defender);
	setMovementState(ShipAiAgent::ATTACKING);

	defender->addDefender(asShipAiAgent());

	// Add Ship to enemy list
	if (addEnemyShip(defender->getObjectID()) && defender->isPlayerShip()) {
		broadcastPvpStatusBitmask();
	}
}

bool ShipAiAgentImplementation::addEnemyShip(uint64 enemyShipID) {
	Locker locker(&enemyListMutex);

	if (enemyShipList.contains(enemyShipID)) {
		return false;
	}

	enemyShipList.add(enemyShipID);
	return true;
}

bool ShipAiAgentImplementation::removeEnemyShip(uint64 enemyShipID) {
	Locker locker(&enemyListMutex);

	if (!enemyShipList.contains(enemyShipID)) {
		return false;
	}

	enemyShipList.removeElement(enemyShipID);

	return true;
}

bool ShipAiAgentImplementation::isEnemyShip(uint64 shipID) {
	Locker locker(&enemyListMutex);

	return enemyShipList.contains(shipID);
}

bool ShipAiAgentImplementation::isPlayerFactionAlly(CreatureObject* player) {
	if (player == nullptr) {
		return false;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return false;
	}

	int pilotSquadron = ghost->getPilotSquadron();
	int pilotTier = ghost->getPilotTier();

	uint32 playerFactionHash = FactionManager::instance()->getSpaceFactionBySquadron(pilotSquadron, pilotTier);
	uint32 thisAgentFaction = getShipFaction();

	// Player is ally faction
	if (playerFactionHash > 0 && (playerFactionHash == thisAgentFaction || alliedFactions.contains(playerFactionHash))) {
		return true;
	}

	return false;
}

bool ShipAiAgentImplementation::isPlayerFactionEnemy(CreatureObject* player) {
	if (player == nullptr) {
		return false;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return false;
	}

	int pilotSquadron = ghost->getPilotSquadron();
	int pilotTier = ghost->getPilotTier();

	uint32 playerFactionHash = FactionManager::instance()->getSpaceFactionBySquadron(pilotSquadron, pilotTier);

	// Player is enemy faction
	if (playerFactionHash > 0 && enemyFactions.contains(playerFactionHash)) {
		return true;
	}

	return false;
}

void ShipAiAgentImplementation::addSpaceFactionAlly(uint32 factionHash) {
	if (factionHash == 0 || alliedFactions.contains(factionHash)) {
		return;
	}

	alliedFactions.add(factionHash);
	broadcastPvpStatusBitmask();
}

void ShipAiAgentImplementation::removeSpaceFactionAlly(uint32 factionHash) {
	if (factionHash == 0 || !alliedFactions.contains(factionHash)) {
		return;
	}

	alliedFactions.removeElement(factionHash);
	broadcastPvpStatusBitmask();
}

void ShipAiAgentImplementation::addSpaceFactionEnemy(uint32 factionHash) {
	if (factionHash == 0 || enemyFactions.contains(factionHash)) {
		return;
	}

	info(true) << getDisplayedName() << " addSpaceFactionEnemy -- adding enemy faction: " << factionHash;

	enemyFactions.add(factionHash);
	broadcastPvpStatusBitmask();
}

void ShipAiAgentImplementation::removeSpaceFactionEnemy(uint32 factionHash) {
	if (factionHash == 0 || !enemyFactions.contains(factionHash)) {
		return;
	}

	enemyFactions.removeElement(factionHash);
	broadcastPvpStatusBitmask();
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

	if (!target->isShipObject()) {
		return false;
	}

	auto targetShip = target->asShipObject();

	if (targetShip == nullptr) {
		return false;
	}

	bool targetIsShipAgent = target->isShipAiAgent();
	bool targetIsPlayer = target->isPlayerShip();

	/* Space Faction Check differentiate from ground checks

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
			// Faction checks against the ships owner
			auto shipOwner = targetShip->getOwner().get();

			if (shipOwner == nullptr) {
				return false;
			}

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
	*/

	uint32 spaceFaction = getShipFaction();

	if (targetIsShipAgent) {
		auto targetAgent = target->asShipAiAgent();

		if (targetAgent != nullptr) {
			auto targetSpaceFaction = targetAgent->getShipFaction();

			if (targetSpaceFaction > 0 && enemyFactions.contains(targetSpaceFaction)) {
				return true;
			}
		}
	} else if (targetIsPlayer && spaceFaction > 0) {
		auto shipOwner = targetShip->getOwner().get();

		if (shipOwner == nullptr) {
			return false;
		}

		if (isPlayerFactionEnemy(shipOwner)) {
			return true;
		}
	}

	// ShipAgent is not aggressive due to faction or standing, remaining aggressive check based on pvpStatusBitmask
	return (pvpStatusBitmask & ObjectFlag::AGGRESSIVE) || isEnemyShip(target->getObjectID());
}

// This will handle checks for other ShipAgents or tangible objects
bool ShipAiAgentImplementation::isAttackableBy(TangibleObject* attackerTano) {
	if (attackerTano == nullptr)
		return false;

	if (pvpStatusBitmask == 0 || !(pvpStatusBitmask & ObjectFlag::ATTACKABLE)) {
		return false;
	}

	if (movementState == ShipAiAgent::LEASHING) {
		return false;
	}

	if (isDestroying() || isInvulnerable()) {
		return false;
	}

	if (isInNoCombatArea()) {
		return false;
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy TangibleObject Check -- Ship Agent: " << getDisplayedName() << " by attackerTano = " << attackerTano->getDisplayedName();

	if (attackerTano->isCreatureObject()) {
		return isAttackableBy(attackerTano->asCreatureObject());
	} else if (attackerTano->isPlayerShip()) {
		auto attackerShip = attackerTano->asShipObject();

		if (attackerShip != nullptr) {
			auto owner = attackerShip->getOwner().get();

			if (owner != nullptr) {
				return isAttackableBy(owner);
			}
		}
	} else if (attackerTano->isShipAiAgent()) {
		auto attackerAgent = attackerTano->asShipAiAgent();

		if (attackerAgent != nullptr) {
			auto attackerSpaceFaction = attackerAgent->getShipFaction();

			if (attackerSpaceFaction > 0 && alliedFactions.contains(attackerSpaceFaction) && !enemyFactions.contains(attackerSpaceFaction)) {
				return false;
			}
		}
	}

	/*
	// Get factions
	uint32 thisFaction = getShipFaction();
	uint32 shipFaction = attackerTano->getFaction();

	if (thisFaction != 0 || shipFaction != 0) {
		if (thisFaction == shipFaction) {
			return false;
		}

		if (thisFaction == 0 && shipFaction != 0) {
			return false;
		}
	}
	*/

	// info(true) << "ShipAiAgentImplementation::isAttackableBy TangibleObject Check returned true";

	return true;
}

bool ShipAiAgentImplementation::isAttackableBy(CreatureObject* attacker) {
	if (attacker == nullptr) {
		return false;
	}

	if (isDestroying() || isInvulnerable()) {
		return false;
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy Creature Check -- ShipAgent: " << getDisplayedName() << " by attacker = " << attacker->getDisplayedName() " Agent Space Faction: " << getShipFactionString();

	if (attacker->isPlayerCreature() && isPlayerFactionAlly(attacker)) {
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

	float maxAttackDistance = ShipAiAgent::MAX_ATTACK_DISTANCE + getBoundingRadius() + targetShip->getBoundingRadius();

	if (!targetShip->isAttackableBy(asShipAiAgent()) || !targetShip->isInRange3d(asShipAiAgent(), maxAttackDistance)) {
		//info("validateTarget FALSE attackable checks", true);
		return false;
	}

	// info(true) << "validateTarget returning true";

	return true;
}

int ShipAiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition, bool isCombatAction) {
	if (getOptionsBitmask() & OptionBitmask::DESTROYING) {
		return 1;
	}

	setOptionBit(OptionBitmask::DESTROYING, false);

	if (attacker == nullptr) {
		attacker = asShipAiAgent();
	} else if (attacker->isPlayerShip()) {
		sendReactionChat(attacker, ReactionManager::DEATH);
	}

	// info(true) << "ShipAiAgentImplementation::notifyObjectDestructionObservers -- ShipAgent: " << getDisplayedName();

	ShipManager* shipManager = ShipManager::instance();

	if (shipManager != nullptr) {
		shipManager->notifyDestruction(attacker->asShipObject(), asShipAiAgent(), condition, isCombatAction);
	}

	return TangibleObjectImplementation::notifyObjectDestructionObservers(attacker, condition, isCombatAction);
}

void ShipAiAgentImplementation::sendReactionChat(SceneObject* object, int type, int state, bool force) {
	if (object == nullptr) {
		return;
	}

	// TODO: Ship Agent Needs reaction chats

	// ReactionManager* reactionManager = getZoneServer()->getReactionManager();

	// if (reactionManager != nullptr)
	//	reactionManager->sendChatReaction(asAiAgent(), object, type, state, force);
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

		if (!despawnEvent->isScheduled()) {
			despawnEvent->schedule(300000);
		}
	}
}

void ShipAiAgentImplementation::scheduleDespawn(int timeToDespawn, bool force) {
	// info(true) << getDisplayedName() << " calling - scheduleDespawn()";

	Reference<DespawnShipAgentTask*> despawn = getPendingTask("despawn").castTo<DespawnShipAgentTask*>();

	if (!force && despawn != nullptr) {
		return;
	}

	if (despawn != nullptr) {
		despawn->cancel();
		despawn->reschedule(timeToDespawn * 1000);
	} else {
		despawn = new DespawnShipAgentTask(asShipAiAgent());

		if (despawn == nullptr) {
			error() << "ShipAiAgent failed to create a despawn task." << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ": " << *_this.getReferenceUnsafeStaticCast();
			return;
		}

		addPendingTask("despawn", despawn, timeToDespawn * 1000);
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

void ShipAiAgentImplementation::addShipFlag(uint32 flag) {
	if (!(shipBitmask & flag))
		shipBitmask |= flag;
}

void ShipAiAgentImplementation::removeShipFlag(uint32 flag) {
	if (shipBitmask & flag)
		shipBitmask &= ~flag;
}

void ShipAiAgentImplementation::addFixedPatrolPoint(uint32 pointHash) {
	fixedPatrolPoints.add(pointHash);
}

void ShipAiAgentImplementation::initializeTransform(const Vector3& position, const Quaternion& direction) {
	initializePosition(position);
	nextStepPosition = SpacePatrolPoint(position);

	setDirection(direction);
	setRotationMatrix(direction);

	lastDirection = matrixToUnitVector();
	currentDirection = lastDirection;

	lastRotation = unitVectorToRotation();
	currentRotation = lastRotation;

	lastSpeed = 0.f;
	currentSpeed = 0.f;

	lastDeltaTime = 0.f;
	deltaTime = 0.f;
}

Vector3 ShipAiAgentImplementation::getHomePosition() {
	auto homeRef = homeObject.get();

	if (homeRef != nullptr) {
		return homeRef->getWorldPosition();
	}

	return homeLocation.getWorldPosition();
}

Vector3 ShipAiAgentImplementation::getNextStepPosition() {
	return nextStepPosition.getWorldPosition();
}

Vector3 ShipAiAgentImplementation::getNextDirectionVector() const {
	return nextDirection;
}

Vector3 ShipAiAgentImplementation::getCurrentDirectionVector() const {
	return currentDirection;
}

Vector3 ShipAiAgentImplementation::getLastDirectionVector() const {
	return lastDirection;
}

Vector3 ShipAiAgentImplementation::getNextRotationVector() const {
	return nextRotation;
}

Vector3 ShipAiAgentImplementation::getCurrentRotationVector() const {
	return currentRotation;
}

Vector3 ShipAiAgentImplementation::getLastRotationVector() const {
	return lastRotation;
}

float ShipAiAgentImplementation::getLastSpeed() const {
	return lastSpeed;
}

String ShipAiAgentImplementation::getShipAgentTemplateName() {
	String templateName = "";

	if (agentTemplate == nullptr) {
		return templateName;
	}

	templateName = agentTemplate->getTemplateName();

	return templateName;
}

float ShipAiAgentImplementation::getOutOfRangeDistance(uint64 specialRangeID) {
	return ZoneServer::SPACECLOSEOBJECTRANGE;
}

String ShipAiAgentImplementation::getLootTable() {
	return lootTable;
}

bool ShipAiAgentImplementation::checkLineOfSight(SceneObject* obj) {
	return CollisionManager::checkLineOfSight(asShipAiAgent(), obj);
}

bool ShipAiAgentImplementation::isFixedPatrolShipAgent() const {
	return (shipBitmask & ShipFlag::FIXED_PATROL);
}

bool ShipAiAgentImplementation::sendConversationStartTo(SceneObject* playerSceneO) {
	if (playerSceneO == nullptr || !playerSceneO->isPlayerCreature()) {
		return false;
	}

	auto player = playerSceneO->asCreatureObject();

	if (player == nullptr) {
		return false;
	}

	auto rootParent = player->getRootParent();

	if (rootParent == nullptr || !rootParent->isShipObject()) {
		return false;
	}

	ShipObject* playerShip = rootParent->asShipObject();

	if (playerShip == nullptr) {
		return false;
	}

	uint64 agentID = getObjectID();
	uint32 mobileCRC = getConversationMobile();

	StartNpcConversation* conversation = new StartNpcConversation(player, agentID, 0, "", mobileCRC);

	if (conversation == nullptr) {
		return false;
	}

	player->sendMessage(conversation);

	uint32 convoCRC = getConversationTemplate();

	SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::STARTCONVERSATION);

	for (int i = 0; i < observers.size(); ++i) {
		if (dynamic_cast<ConversationObserver*>(observers.get(i).get()) != nullptr)
			return true;
	}

	ConversationObserver* conversationObserver = ConversationManager::instance()->getConversationObserver(convoCRC);

	if (conversationObserver != nullptr) {
		registerObserver(ObserverEventType::CONVERSE, conversationObserver);
		registerObserver(ObserverEventType::STARTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::SELECTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::STOPCONVERSATION, conversationObserver);
	} else {
		error() << "Ship AI Agent: " << getObjectID() << " Failed to create conversation observer.";
		return false;
	}

	return true;
}

void ShipAiAgentImplementation::tauntPlayer(CreatureObject* player, const String& tauntString) {
	if (player == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	// Start the Conversation
	ghost->setConversatingObject(asShipAiAgent());

	if (!sendConversationStartTo(player)) {
		return;
	}

	notifyObservers(ObserverEventType::STARTCONVERSATION, player);

	StringIdChatParameter tauntMessage(tauntString);

	auto conversationScreen = new ConversationScreen(tauntMessage, true);

	if (conversationScreen != nullptr) {
		conversationScreen->sendTo(player, asShipAiAgent());
	}

	auto task = new SpaceCommTimerTask(player, getObjectID());

	if (task != nullptr) {
		player->addPendingTask("SpaceCommTimer", task, 10 * 1000);
	}
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

	const Vector3& currentPosition = getPosition();
	Vector3 nextPosition = nextStepPosition.getWorldPosition();

	float yawMax  = round(getActualYawRate() * deltaTime * Math::RAD2DEG * 1000.f) * 0.001f;
	float pitchMax = round(getActualPitchRate() * deltaTime * Math::RAD2DEG * 1000.f) * 0.001f;
	float rollMax = round(getActualRollRate() * deltaTime * Math::RAD2DEG * 1000.f) * 0.001f;

	float yawRate  = round(getRotationRate(currentRotation.getX(), lastRotation.getX()) * Math::RAD2DEG * 1000.f) * 0.001f;
	float pitchRate = round(getRotationRate(currentRotation.getY(), lastRotation.getY()) * Math::RAD2DEG * 1000.f) * 0.001f;
	float rollRate = round(getRotationRate(currentRotation.getZ(), lastRotation.getZ()) * Math::RAD2DEG * 1000.f) * 0.001f;

	String movementString = "";

	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:		movementString = "OBLIVIOUS"; break;
		case ShipAiAgent::WATCHING:			movementString = "WATCHING"; break;
		case ShipAiAgent::FOLLOWING:		movementString = "FOLLOWING"; break;
		case ShipAiAgent::PATROLLING:		movementString = "PATROLLING"; break;
		case ShipAiAgent::ATTACKING:		movementString = "ATTACKING"; break;
		case ShipAiAgent::FLEEING:			movementString = "FLEEING"; break;
		case ShipAiAgent::LEASHING:			movementString = "LEASHING"; break;
		case ShipAiAgent::EVADING:			movementString = "EVADING"; break;
		case ShipAiAgent::PATHING_HOME:		movementString = "PATHING_HOME"; break;
		case ShipAiAgent::FOLLOW_FORMATION:	movementString = "FOLLOW_FORMATION"; break;
	}

	Locker sLock(asShipObject());
	auto targetVector = getTargetVector();

	msg << "ShipAiAgent:	  " << getDisplayedName() << endl
		<< " movementState:   " << movementString <<  endl
		<< " movementCount:   " << movementCount << endl
		<< " deltaTime:       " << deltaTime * 1000.f << endl
		<< " targetVector:	  " << (targetVector ? targetVector->size() : 0) << endl
		<< " patrolPoints:	  " << patrolPoints.size() << endl
		<< " thisPosition:	  " << currentPosition.getX() << " " << currentPosition.getY() << " " << currentPosition.getZ() << endl
		<< " nextPosition:	  " << nextPosition.getX() << " " << nextPosition.getY() << " " << nextPosition.getZ() << endl
		<< " lastDirection:   " << lastDirection.getX() << " " << lastDirection.getY() << " " << lastDirection.getZ() << endl
		<< " thisDirection:   " << currentDirection.getX() << " " << currentDirection.getY() << " " << currentDirection.getZ() << endl
		<< " lastRotation:	  " << lastRotation.getX() << " " << lastRotation.getY() << " " << lastRotation.getZ() << endl
		<< " thisRotation:	  " << currentRotation.getX() << " " << currentRotation.getY() << " " << currentRotation.getZ() << endl
		<< " yawRate:         " << yawRate << "/" << yawMax << endl
		<< " pitchRate:       " << pitchRate << "/" << pitchMax<< endl
		<< " yawRate:         " << rollRate << "/" << rollMax<< endl
		<< " currentSpeed:	  " << currentSpeed << endl
		<< " lastSpeed:	      " << lastSpeed << endl
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

	const Vector3& homePosition = homeLocation.getWorldPosition();
	const Vector3& nextPosition = nextStepPosition.getWorldPosition();
	const Vector3& position = getPosition();
	const Matrix4& rotation = *getConjugateMatrix();

	float inRangeDistance = getMaxDistance();
	float radius = getBoundingRadius();

	auto path = new CreateClientPathMessage();

	path->addCoordinate(position);
	path->drawBoundingSphere(position, rotation, Sphere(Vector3::ZERO, inRangeDistance));
	path->addCoordinate(position);

	Vector3 velocity = ((radius + currentSpeed) * currentDirection) + position;

	path->addCoordinate(position);
	path->addCoordinate(velocity);
	path->addCoordinate(position);

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::SPHERE) {
		path->drawBoundingSphere(nextPosition, rotation, data->getChassisSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
		path->drawBoundingSphere(nextPosition, rotation, data->getBoundingSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
		path->drawBoundingBox(nextPosition, rotation, data->getChassisBox());
	}

	path->addCoordinate(nextPosition);

	for (int i = 0; i < patrolPoints.size(); ++i) {
		auto patrol = patrolPoints.get(i);
		auto point = patrol.getCoordinates().getPoint();

		path->addCoordinate(point);
	}

	broadcastMessage(path, false);
#endif // DEBUG_SHIP_AI
}
