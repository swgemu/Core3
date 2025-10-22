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
#include "server/zone/objects/ship/transform/ShipObjectTransform.h"
#include "server/zone/objects/ship/ai/SquadronObserver.h"


// #define DEBUG_SHIP_AI
// #define DEBUG_SHIP_DESPAWN
// #define DEBUG_SHIP_AI_CLIENT_MESSAGES

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

		bool targetable = isComponentTargetable(slot);
		setComponentTargetable(slot, targetable, false);

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

	const String& pilotDataName = agentTemplate->getPilotTemplate();

	if (!pilotDataName.isEmpty() && agentTemplate->getShipType() != "capital") {
		auto pilotData = ShipManager::instance()->getPilotData(pilotDataName);

		if (pilotData != nullptr) {
			float speedRotationFactorMin = pilotData->getSpeedRotationFactorMin();
			float speedRotationFactorOptimal = pilotData->getSpeedRotationFactorOptimal();
			float speedRotationFactorMax = pilotData->getSpeedRotationFactorMax();
			float slideDamp = pilotData->getSlideDamp();
			float engineSpeed = pilotData->getEngineSpeed();
			float engineAccel = pilotData->getEngineAccel();
			float engineDecel = pilotData->getEngineDecel();
			float engineYaw = pilotData->getEngineYaw();
			float engineYawAccel = pilotData->getEngineYawAccel();
			float enginePitch = pilotData->getEnginePitch();
			float enginePitchAccel = pilotData->getEnginePitchAccel();
			float engineRoll = pilotData->getEngineRoll();
			float engineRollAccel = pilotData->getEngineRollAccel();

			setSpeedRotationFactorMin(speedRotationFactorMin);
			setSpeedRotationFactorOptimal(speedRotationFactorOptimal);
			setSpeedRotationFactorMax(speedRotationFactorMax);
			setSlipRate(slideDamp, false);
			setEngineMaxSpeed(engineSpeed, false);
			setEngineAccelerationRate(engineAccel, false);
			setEngineDecelerationRate(engineDecel, false);
			setEngineYawRate(engineYaw, false);
			setEngineYawAccelerationRate(engineYawAccel, false);
			setEnginePitchRate(enginePitch, false);
			setEnginePitchAccelerationRate(enginePitchAccel, false);
			setEngineRollRate(engineRoll, false);
			setEngineRollAccelerationRate(engineRollAccel, false);
		}
	}

	setCargoString(agentTemplate->getCargoString());
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

	cooldownTimerMap = new CooldownTimerMap();

	setHyperspacing(false);

	missileLockTime = 0;

	nextBehaviorInterval = BEHAVIORINTERVALMIN;

	updateZoneTime = 0;

	movementState = OBLIVIOUS;
	movementCount = 0;
	movementTime = 0;
}

void ShipAiAgentImplementation::notifyInsertToZone(Zone* zone) {
	if (zone == nullptr) {
		return;
	}

	// Schedule space agents to activate
	Reference<ShipAiAgent*> agentRef = asShipAiAgent();

	int randomTime = 500;

	auto zoneServer = zone->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	if (zoneServer->isServerLoading()) {
		randomTime = (System::random(120) + 120) * 1000;
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

void ShipAiAgentImplementation::notifyDespawn(Zone* zone) {
#ifdef DEBUG_SHIP_DESPAWN
	info(true) << "notifyDespawn called for - " << getDisplayedName() << " ID: " << getObjectID();
#endif // DEBUG_SHIP_DESPAWN

 	Locker locker(&despawnMutex);

	// Clearing Agent Events
	cancelBehaviorEvent();
	wipeBlackboard();

	clearPatrolPoints();
	clearFixedPatrolPoints();

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

	// Clear the squadron observer
	if (squadron != nullptr) {
		Locker squadronLock(squadron, asShipAiAgent());

		squadron->dropSquadronShip(asShipAiAgent());
		squadron = nullptr;
	}

#ifdef DEBUG_SHIP_DESPAWN
	info(true) << getDisplayedName() << " ID: " << getObjectID() << " notifyDespawn complete - Reference Count: " << getReferenceCount();
#endif // DEBUG_SHIP_DESPAWN
}

void ShipAiAgentImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	numberOfPlayersInRange.set(0);

	ShipObjectImplementation::destroyObjectFromWorld(sendSelfDestroy);

	// Schedule despawn notify
	Reference<ShipAiAgent*> agentRef = asShipAiAgent();
	Reference<Zone*> zoneRef = getZone();

	Core::getTaskManager()->scheduleTask([agentRef, zoneRef] () {
		if (agentRef == nullptr) {
			return;
		}

		Locker lock(agentRef);

		agentRef->notifyDespawn(zoneRef);
	}, "shipAgentDespawnNotify", 500);
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
			printf("\n\n\n");
			info(true) << getDisplayedName() << " - ID: " << getObjectID() << " runBehaviorTree -- called";
		}
#endif // DEBUG_SHIP_AI

		ZoneServer* zoneServer = getZoneServer();

		if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
			cancelBehaviorEvent();

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
	movementTime = System::getMiliTime();
}

uint64 ShipAiAgentImplementation::getMovementDeltaTime() {
	return Math::max(System::getMiliTime() - movementTime, 0ull);
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
	const auto& sPosition = getPosition();
	return sPosition.squaredDistanceTo(position) <= Math::sqr(radius);
}

void ShipAiAgentImplementation::addPatrolPoint(const SpacePatrolPoint& patrolPoint) {
	Locker tLock(&targetMutex);

	int patrolMax = Math::max(getPatrolSizeMax() - 1, 0);

	if (patrolPoints.size() >= patrolMax) {
		patrolPoints.removeRange(0, patrolPoints.size() - patrolMax);
	}

	patrolPoints.add(patrolPoint);
}

void ShipAiAgentImplementation::setNextFollowPosition() {
	auto followShip = getFollowShipObject().get();

	if (followShip == nullptr) {
		return;
	}

	SpacePatrolPoint point = getInterceptPosition(followShip, currentSpeed, Components::CHASSIS);
	addPatrolPoint(point);
}

void ShipAiAgentImplementation::setNextSquadronPosition() {
	if (squadron == nullptr || squadron->getSquadronIndex(asShipAiAgent()) == -1) {
		return;
	}

	SpacePatrolPoint point = squadron->getPosition(asShipAiAgent());
	patrolPoints.removeAll();
	patrolPoints.add(point);
}

void ShipAiAgentImplementation::setNextAttackPosition() {
	auto targetShip = getTargetShipObject().get();

	if (targetShip == nullptr) {
		return;
	}

	SpacePatrolPoint point = getInterceptPosition(targetShip, DEFAULT_PROJECTILE_SPEED, Components::CHASSIS);
	addPatrolPoint(point);
}

void ShipAiAgentImplementation::setNextEvadePosition() {
	auto targetShip = getTargetShipObject().get();

	if (targetShip == nullptr || getFinalPosition().isEvadePoint()) {
		return;
	}

	const auto& tPosition = targetShip->getPosition();
	const auto& hPosition = getHomePosition();
	const auto& sPosition = getPosition();

	Vector3 hVelocity = hPosition - sPosition;
	float hDistance = SpaceMath::qNormalize(hVelocity);

	Vector3 tVelocity = sPosition - tPosition;
	float tDistance = SpaceMath::qNormalize(tVelocity);

	float tDuration = tDistance / Math::max(getActualMaxSpeed(), 1.f);
	tDuration = Math::max(1.f, MAX_EVADE_DURATION - tDuration);

	float eDistance = getActualMaxSpeed() * tDuration;
	float hAnchor = Math::min(hDistance / (float)MAX_ATTACK_DISTANCE, 1.f);

	Vector3 eDirection = Math::linearInterpolate(tVelocity, hVelocity, hAnchor);
	SpaceMath::qNormalize(eDirection);

	SpacePatrolPoint point = (eDirection * eDistance) + sPosition;
	point.setEvadePoint(true);
	addPatrolPoint(point);
}

void ShipAiAgentImplementation::setNextLeashPosition() {
	auto homePosition = getHomePosition();

	if (homeLocation.getCoordinates().getPoint() != homePosition) {
		homeLocation.setPosition(homePosition.getX(), homePosition.getZ(), homePosition.getY());
	}

	bool inRange = isInRangePosition(homePosition, getMaxDistance());
	homeLocation.setReached(inRange);

	SpacePatrolPoint point = homePosition;
	point.setReached(inRange);
	addPatrolPoint(point);
}

Vector3 ShipAiAgentImplementation::getInterceptPosition(ShipObject* target, float speed, int slot, int targetSlot) {
	Vector3 sLocal = Vector3::ZERO;
	Vector3 tLocal = Vector3::ZERO;

	if (slot != Components::CHASSIS) {
		auto data = ShipManager::instance()->getCollisionData(asShipAiAgent());

		if (data != nullptr) {
			const auto& hardpoints = data->getHardpoints(slot);

			if (hardpoints.size() > 0) {
				const auto& sRotation = *getConjugateMatrix();
				const auto& hardpoint = hardpoints.get(0);
				const auto& hPosition = hardpoint.getSphere().getCenter();

				sLocal = SpaceMath::getGlobalVector(hPosition, sRotation);
			}
		}
	}

	if (targetSlot != Components::CHASSIS) {
		auto data = ShipManager::instance()->getCollisionData(target);

		if (data != nullptr) {
			const auto& hardpoints = data->getHardpoints(targetSlot);

			if (hardpoints.size() > 0) {
				const auto& tRotation = *target->getConjugateMatrix();
				const auto& hardpoint = hardpoints.get(0);
				const auto& hPosition = hardpoint.getSphere().getCenter();

				tLocal = SpaceMath::getGlobalVector(hPosition, tRotation);
			}
		}
	}

	const auto& sTransform = getCurrentTransform();
	const auto& tTransform = target->getCurrentTransform();

	Vector3 velocity = tLocal - sLocal;
	float distance = SpaceMath::qNormalize(velocity);
	float time = distance / Math::max(speed, 1.f);

	if (slot == Components::CHASSIS) {
		const auto& sVelocity = sTransform.getVelocity();
		time += SpaceMath::getVelocityTime(velocity, sVelocity, getActualYawRate(), getActualPitchRate());
	}

	time = Math::clamp(0.f, time, 2.f);
	return SpaceMath::predictTransform(tTransform, time) + tLocal;
}

int ShipAiAgentImplementation::getTransformType() {
	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::PATROLLING: {
			return SpaceTransformType::SLOW;
		}
		case ShipAiAgent::ATTACKING:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::FLEEING: {
			return SpaceTransformType::FAST;
		}
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::FOLLOW_FORMATION:
		default: {
			return SpaceTransformType::AUTO;
		}
	}
}

int ShipAiAgentImplementation::getPatrolSizeMax() {
	switch (movementState) {
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::PATROLLING: {
			return PATROLPOINTS_MAX;
		}
		case ShipAiAgent::ATTACKING: {
			return (shipBitmask & ShipFlag::TURRETSHIP) ? 4 : 2;
		}
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::FOLLOW_FORMATION:
		default: {
			return 1;
		}
	}
}

int ShipAiAgentImplementation::setDestination() {
	if (patrolPoints.size() > PATROLPOINTS_MAX) {
		info() << "Patrol points have overflowed. Total points: " << patrolPoints.size();
		clearPatrolPoints();
	}
/*
	if (isSquadronMember() && isSquadronTransform()) {
		setNextSquadronPosition();
		setSquadronTransform();
		return patrolPoints.size();
	}
*/
	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::PATROLLING: {
			break;
		}
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::FOLLOW_FORMATION: {
			setNextFollowPosition();
			break;
		}
		case ShipAiAgent::ATTACKING: {
			setNextAttackPosition();
			break;
		}
		case ShipAiAgent::EVADING: {
			setNextEvadePosition();
			break;
		}
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::PATHING_HOME: {
			if (homeLocation.isReached()) {
				setMovementState(ShipAiAgent::PATROLLING);
			}

			setNextLeashPosition();
			break;
		}
	};

	setNextTransform();
	return patrolPoints.size();
}

void ShipAiAgentImplementation::setNextTransform() {
	if (squadron != nullptr && (isSquadronTransform() || isSquadronLeader())) {
		return setSquadronTransform();
	}

	Vector3 position = getNextPosition().getWorldPosition();
	float speed = getNextSpeed();
	int type = getTransformType();

	shipTransform.setNextTransform(position, speed, type);
	movementCount += 1;
}

void ShipAiAgentImplementation::setSquadronTransform() {
	if (squadron == nullptr || squadron->getSquadronIndex(asShipAiAgent()) == -1) {
		return;
	}

	Vector3 position = squadron->getPosition(asShipAiAgent());
	float speed = squadron->getSpeed(asShipAiAgent());
	int type = getTransformType();

	if (isSquadronMember()) {
		type = SpaceTransformType::FORM;
	}

	shipTransform.setNextTransform(position, speed, type);
	movementCount += 1;

	if (isSquadronLeader()){
		squadron->updateSquadron();

#ifdef DEBUG_SHIP_AI_CLIENT_MESSAGES
		sendDebugPath();
#endif // DEBUG_SHIP_AI_CLIENT_MESSAGES
	}
}

float ShipAiAgentImplementation::getNextSpeed() {
	float speed = getActualMaxSpeed();

	if (escortSpeed > 0.f) {
		speed = Math::min(escortSpeed, speed);
	}

	return speed;
}

bool ShipAiAgentImplementation::setDisabledEngineSpeed() {
	if (currentSpeed > 0.f) {
		shipTransform.setNextTransform(getPosition(), 0.f);
	}

	clearPatrolPoints();

	return true;
}

bool ShipAiAgentImplementation::findNextPosition(int maxDistance) {
	int64 timeNow = System::getMiliTime();
	int64 deltaTime = timeNow - updateZoneTime;

	if (deltaTime >= UPDATEZONEINTERVAL) {
		updateZoneTime = timeNow;

		updateZone(true, false);
		removeOutOfRangeObjects();
	}

	if (getPatrolPointSize() <= 0) {
		return false;
	}

	updatePatrolPoints();
	return true;
}

void ShipAiAgentImplementation::updateTransform(bool lightUpdate) {
	bool notifyClient = numberOfPlayersInRange >= 1;

	if (lightUpdate && !notifyClient) {
		return;
	}

#ifdef DEBUG_SHIP_AI_CLIENT_MESSAGES
	sendDebugMessage();

	if (squadron == nullptr) {
		sendDebugPath();
	}
#endif // DEBUG_SHIP_AI_CLIENT_MESSAGES

	shipTransform.updateTransform(asShipObject(), lightUpdate, notifyClient);
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
		int fixedPointCount = fixedPatrolPoints.size();

		// Add patrol points from the vector selected at spawn
		for (int i = 0; i < fixedPointCount; i++) {
			const uint32 pointHash = fixedPatrolPoints.get(i);
			SpacePatrolPoint patrolPoint = shipAgentTempMan->getSpacePatrolPoint(zoneNameHash, pointHash);

			patrolCopy.add(patrolPoint);
		}

		patrolPoints.removeAll(fixedPointCount, fixedPointCount);
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
		float patrolRadius = distance - SpaceMath::qSqrt((homePosition - patrolPosition).squaredLength());

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
	const auto& homePosition = getHomePosition();

	if (homeLocation.getWorldPosition() != homePosition) {
		homeLocation.setPosition(homePosition.getX(), homePosition.getZ(), homePosition.getY());
	}

	int transformType = getTransformType();

	// info(true) << "ShipAiAgentImplementation::updatePatrolPoints() -- Movement State: " << getMovementState() << " Transform Type: " << transformType << " Patrol Points Size: " << patrolPoints.size();

	switch (transformType) {
		case SpaceTransformType::SLOW:
		case SpaceTransformType::DOCK: {
			if (patrolPoints.size() >= 1) {
				const auto& nextPosition = patrolPoints.get(0).getWorldPosition();
				const auto& thisPosition = getPosition();

				if (thisPosition.squaredDistanceTo(nextPosition) < Math::sqr(getMaxDistance())) {
					patrolPoints.remove(0);

					int movementState = getMovementState();

					if ((movementState == PATROLLING || movementState == WATCHING) && hasSinglePatrolRotation() && patrolPoints.size() < 1) {
						notifyObservers(ObserverEventType::DESTINATIONREACHED);
					}
				}
			}

			break;
		}
		case SpaceTransformType::AUTO:
		case SpaceTransformType::FAST:
		default: {
			float distanceMaxSqr = Math::sqr(getMaxDistance());
			const auto& thisPosition = getPosition();

			for (int i = patrolPoints.size(); -1 < --i;) {
				const auto& nextPosition = patrolPoints.get(i).getWorldPosition();

				if (thisPosition.squaredDistanceTo(nextPosition) <= distanceMaxSqr) {
					patrolPoints.removeRange(0, i+1);
					break;
				}
			}
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
	Vector3 direction = shipTransform.getCurrentTransform().getVelocity();

	float radius = Math::clamp(32.f, targetShip->getBoundingRadius(), 256.f);
	float range = Math::clamp(256.f, projectileData->getRange(), 1024.f);
	float collisionDistance = SpaceCollisionManager::instance()->getPointIntersection(direction * range, difference, radius, range);

	if (collisionDistance == SpaceCollisionManager::MISS) {
		return false;
	}

	auto projectile = new ShipProjectile(asShipAiAgent(), weaponIndex, projectileData->getIndex(), targetSlot, position, direction * 7800.f, 0, 0, 1.f, System::getMiliTime());
	projectile->readProjectileData(projectileData);

	SpaceCombatManager::instance()->addProjectile(asShipAiAgent(), projectile);
	return true;
}

bool ShipAiAgentImplementation::fireMissileAtTarget(ShipObject* targetShip, const ShipProjectileData* projectileData, const ShipMissileData* missileData, uint32 slot, uint32 targetSlot) {
	if (targetShip == nullptr || projectileData == nullptr || missileData == nullptr || targetShip != getTargetShipObject().get()) {
		return false;
	}

	const Vector3& currentRotation = shipTransform.getCurrentTransform().getRotation();
	const Vector3& currentDirection = shipTransform.getCurrentTransform().getVelocity();
	const Vector3& position = getWorldPosition();
	const Vector3& targetPosition = targetShip->getWorldPosition();

	float distanceSqr = position.squaredDistanceTo(targetPosition);
	float distanceMax =  Math::sqr(projectileData->getRange());

	if (distanceSqr > distanceMax) {
		missileLockTime = 0.f;
		return false;
	}

	Vector3 targetDirection = targetPosition - position;
	float targetDistance = SpaceMath::qNormalize(targetDirection);

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

	missileLockTime += DEFAULT_PROJECTILE_REFIRE;

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

	Vector3 turretGlobal = SpaceMath::getGlobalVector(hardpointPosition, conjugateMatrix) + shipPosition;
	Vector3 targetGlobal = targetPosition - turretGlobal;

	if (targetGlobal.squaredLength() > projectileData->getRange() * projectileData->getRange()) {
		return false;
	}

	Vector3 targetLocal = SpaceMath::getLocalVector(targetGlobal, rotationMatrix);

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
	SpaceMath::qNormalize(targetGlobal);

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

	uint32 thisAgentFaction = getShipFaction();

	auto playerShip = cast<ShipObject*>(player->getRootParent());

	if (playerShip == nullptr) {
		return false;
	}

	uint32 playerFactionHash = playerShip->getShipFaction();

	if (playerFactionHash > 0 && (playerFactionHash == thisAgentFaction || alliedFactions.contains(playerFactionHash))) {
		return true;
	}

	return false;
}

bool ShipAiAgentImplementation::isPlayerFactionEnemy(CreatureObject* player) {
	if (player == nullptr) {
		return false;
	}

	auto playerShip = cast<ShipObject*>(player->getRootParent());

	if (playerShip == nullptr) {
		return false;
	}

	auto targetSpaceFaction = playerShip->getShipFaction();

	if (targetSpaceFaction > 0 && enemyFactions.contains(targetSpaceFaction)) {
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

void ShipAiAgentImplementation::swapSpaceFactionAssociations() {
	auto tempAllies = alliedFactions;

	alliedFactions = enemyFactions;
	enemyFactions = tempAllies;
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

	uint32 targetSpaceFaction = targetShip->getShipFaction();

	if (targetSpaceFaction > 0 && enemyFactions.contains(targetSpaceFaction)) {
		return true;
	}

	// ShipAgent is not aggressive due to faction, remaining aggressive check based on pvpStatusBitmask
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

	if (attackerTano->isCreatureObject()) {
		return isAttackableBy(attackerTano->asCreatureObject());
	}

	// info(true) << "ShipAiAgentImplementation::isAttackableBy TangibleObject Check -- Ship Agent: " << getDisplayedName() << " by attackerTano = " << attackerTano->getDisplayedName();

	auto attackerShip = attackerTano->asShipObject();

	if (attackerShip == nullptr) {
		return false;
	}

	if (isMissionShip() && attackerShip->isPlayerShip()) {
		auto zoneServer = getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

		auto missionOwner = cast<CreatureObject*>(zoneServer->getObject(missionOwnerID).get());

		if (missionOwner == nullptr) {
			return false;
		}

		auto attackerOwner = attackerShip->getOwner().get();

		if (attackerOwner == nullptr) {
			return false;
		}

		bool isGroupedWith = false;

		ManagedReference<GroupObject*> group = missionOwner->getGroup();

		if (group != nullptr && group->hasMember(attackerOwner)) {
			isGroupedWith = true;
		}

		if (attackerOwner != missionOwner && !isGroupedWith) {
			return false;
		}
	}

	auto attackerSpaceFaction = attackerShip->getShipFaction();

	if (attackerSpaceFaction > 0 && alliedFactions.contains(attackerSpaceFaction) && !enemyFactions.contains(attackerSpaceFaction)) {
		return false;
	}

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

	if (!attacker->isPlayerCreature()) {
		return false;
	}

	auto rootParent = attacker->getRootParent();

	if (rootParent == nullptr || !rootParent->isShipObject()) {
		return false;
	}

	auto playerShip = rootParent->asShipObject();

	if (playerShip == nullptr) {
		return false;
	}

	return isAttackableBy(playerShip);
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

bool ShipAiAgentImplementation::isDisabledInvulnerable() {
	return shipBitmask & ShipFlag::DISABLED_INVULNERABLE;
}

void ShipAiAgentImplementation::addFixedPatrolPoint(uint32 pointHash) {
	fixedPatrolPoints.add(pointHash);
}

void ShipAiAgentImplementation::clearFixedPatrolPoints() {
	fixedPatrolPoints.removeAll();
}

Vector3 ShipAiAgentImplementation::getHomePosition() {
	auto homeRef = homeObject.get();

	if (homeRef != nullptr) {
		return homeRef->getWorldPosition();
	}

	return homeLocation.getWorldPosition();
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

bool ShipAiAgentImplementation::hasSinglePatrolRotation() const {
	return (shipBitmask & ShipFlag::SINGLE_PATROL_ROTATION);
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

	if (!player->isGrouped()) {
		return;
	}

	auto group = player->getGroup();

	if (group == nullptr) {
		return;
	}

	for (int i = 0; i < group->getGroupSize(); i++) {
		auto groupMember = group->getGroupMember(i);

		if (groupMember == nullptr || groupMember->getObjectID() == player->getObjectID()) {
			continue;
		}

		if (!groupMember->isPilotingShip() && !groupMember->isInShipStation()) {
			continue;
		}

		auto conversationScreen = new ConversationScreen(tauntMessage, true);

		if (conversationScreen != nullptr) {
			conversationScreen->sendTo(groupMember, asShipAiAgent());
		}

		auto task = new SpaceCommTimerTask(groupMember, getObjectID());

		if (task != nullptr) {
			groupMember->addPendingTask("SpaceCommTimer", task, 10 * 1000);
		}
	}
}

void ShipAiAgentImplementation::createSquadron(int formationType) {
	if (squadron != nullptr) {
		squadron->dropSquadronShip(asShipAiAgent());
		squadron = nullptr;
	}

	squadron = new SquadronObserver(asShipAiAgent(), formationType);
}

void ShipAiAgentImplementation::assignToSquadron(ShipAiAgent* squadronAgent) {
	if (squadronAgent == nullptr) {
		return;
	}

	squadron = squadronAgent->getSquadron();

	if (squadron == nullptr) {
		return;
	}

	Locker cLock(squadron, asShipAiAgent());

	squadron->addSquadronShip(asShipAiAgent());
}

void ShipAiAgentImplementation::dropFromSquadron() {
	if (squadron == nullptr) {
		return;
	}

	Locker cLock(squadron, asShipAiAgent());

	squadron->dropSquadronShip(asShipAiAgent());

	cLock.release();

	squadron = nullptr;
}

bool ShipAiAgentImplementation::isSquadronLeader() {
	return squadron != nullptr ? squadron->isSquadronLeader(asShipAiAgent()) : false;
}

bool ShipAiAgentImplementation::isSquadronMember() {
	return squadron != nullptr ? squadron->isSquadronMember(asShipAiAgent()) : false;
}

bool ShipAiAgentImplementation::isSquadronTransform() {
	switch (movementState) {
		case ShipAiAgent::OBLIVIOUS:
		case ShipAiAgent::WATCHING:
		case ShipAiAgent::PATROLLING: {
			return true;
		}
		case ShipAiAgent::ATTACKING:
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOWING:
		case ShipAiAgent::FOLLOW_FORMATION:
		default: {
			return false;
		}
	}
}

int ShipAiAgentImplementation::getSquadronSize() {
	if (squadron == nullptr) {
		return 0;
	}

	Locker squadronLock(squadron, asShipAiAgent());

	return squadron->getSquadronSize();
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
#ifdef DEBUG_SHIP_AI_CLIENT_MESSAGES
	if (!peekBlackboard("aiDebugSystemMessage") || readBlackboard("aiDebugSystemMessage") == false) {
		return;
	}

	StringBuffer msg;

	const auto& homePosition = getHomePosition();
	const auto& currentPosition = getPosition();
	const auto& nextPosition = getNextPosition().getWorldPosition();
	const auto& finalPosition = getFinalPosition().getWorldPosition();

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

	msg << "ShipAiAgent:	   " << getDisplayedName() << endl
		<< "  movementState:   " << movementString <<  endl
		<< "  movementCount:   " << movementCount << endl
		<< "  homePosition:	   " << homePosition.toString() << endl
		<< "  currentPosition: " << currentPosition.toString() << endl
		<< "  nextPosition:	   " << nextPosition.toString() << endl
		<< "  patrolPoints:	   " << patrolPoints.size() << endl
		<< "  speed:           " << getCurrentSpeed() << " / " << getActualMaxSpeed() << endl
		<< shipTransform.toDebugString() << endl
		<< "--------------------------------";

	ChatSystemMessage* smsg = new ChatSystemMessage(msg.toString());
	broadcastMessage(smsg, false);
#endif // DEBUG_SHIP_AI_CLIENT_MESSAGES
}

void ShipAiAgentImplementation::sendDebugPath() {
#ifdef DEBUG_SHIP_AI_CLIENT_MESSAGES

	auto data = ShipManager::instance()->getCollisionData(asShipObject());

	if (data == nullptr) {
		return;
	}

	const Vector3& nextPosition = shipTransform.getNextTransform().getPosition();
	const Vector3& position = getPosition();
	const Matrix4& rotation = *getConjugateMatrix();

	float inRangeDistance = getMaxDistance();
	float radius = getBoundingRadius();

	auto path = new CreateClientPathMessage();

	//path->addCoordinate(position);
	//path->drawBoundingSphere(position, rotation, Sphere(Vector3::ZERO, inRangeDistance));
	//path->addCoordinate(position);

	const auto& currentVelocity = shipTransform.getCurrentTransform().getVelocity();
	float currentSpeed = shipTransform.getCurrentTransform().getSpeed();
	Vector3 velocity = (currentVelocity * currentSpeed) + position;

	path->addCoordinate(position);
	path->addCoordinate(velocity);
	path->addCoordinate(position);

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::SPHERE) {
		path->drawBoundingSphere(position, rotation, data->getChassisSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
		path->drawBoundingSphere(position, rotation, data->getBoundingSphere());
	}

	if (data->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
		path->drawBoundingBox(position, rotation, data->getChassisBox());
	}

	path->addCoordinate(nextPosition);

	for (int i = 0; i < patrolPoints.size(); ++i) {
		auto patrol = patrolPoints.get(i);
		auto point = patrol.getCoordinates().getPoint();

		path->addCoordinate(point);
	}

	broadcastMessage(path, false);
#endif // DEBUG_SHIP_AI_CLIENT_MESSAGES
}
