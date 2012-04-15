/*
 * BountyMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "BountyMissionObjective.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/mission/bountyhunter/BountyHunterDroid.h"
#include "server/zone/objects/mission/bountyhunter/events/BountyHunterTargetTask.h"

void BountyMissionObjectiveImplementation::setNpcTemplateToSpawn(SharedObjectTemplate* sp) {
	npcTemplateToSpawn = sp;
}

void BountyMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();

	activeDroid = NULL;

	bool failMission = false;

	//Start NPC task or add observers to player target.
	if (getObserverCount() == 2) {
		removeNpcTargetObservers();
		startNpcTargetTask();
	} else if (getObserverCount() != 6) {
		if (isPlayerTarget()) {
			failMission = !addPlayerTargetObservers();
		} else {
			startNpcTargetTask();
		}
	}

	if (failMission) {
		getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");
		abort();
		removeMissionFromPlayer();
	}
}

void BountyMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	cancelAllTasks();

	getPlayerOwner()->getZoneServer()->getMissionManager()->removeBountyHunterFromPlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

	removeFromBountyLock(true);

	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint != NULL && waypoint->isActive()) {
		waypoint->setActive(false);
	}

	//Remove observers
	if (hasObservers()) {
		if (isPlayerTarget()) {
			removePlayerTargetObservers();
		} else {
			removeNpcTargetObservers();
		}
	}
}

void BountyMissionObjectiveImplementation::complete() {
	cancelAllTasks();

	//Award bountyhunter xp.
	getPlayerOwner()->getZoneServer()->getPlayerManager()->awardExperience(getPlayerOwner(), "bountyhunter", mission->getRewardCredits() / 100, true, 1);

	getPlayerOwner()->getZoneServer()->getMissionManager()->completePlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

	removeFromBountyLock(true);

	MissionObjectiveImplementation::complete();
}

void BountyMissionObjectiveImplementation::spawnTarget(const String& zoneName) {
	if ((npcTarget != NULL && npcTarget->isInQuadTree()) || isPlayerTarget()) {
		return;
	}

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	Zone* zone = zoneServer->getZone(zoneName);
	CreatureManager* cmng = zone->getCreatureManager();

	if (npcTarget == NULL) {
		Vector3 position = getTargetPosition();

		npcTarget = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(mission->getTargetOptionalTemplate().hashCode(), 0, position.getX(), zone->getHeight(position.getX(), position.getY()), position.getY(), 0));

		if (npcTarget != NULL) {
			npcTarget->setCustomObjectName(mission->getTargetName(), true);
			//TODO add observer to catch player kill and fail mission in that case.
			addObserverToCreature(ObserverEventType::OBJECTDESTRUCTION, npcTarget);
			addObserverToCreature(ObserverEventType::DAMAGERECEIVED, npcTarget);
		}
	}
}

int BountyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		handleNpcTargetKilled(arg1);
	} else if (eventType == ObserverEventType::DAMAGERECEIVED) {
		return handleNpcTargetReceivesDamage(arg1);
	} else if (eventType == ObserverEventType::PLAYERKILLED) {
		handlePlayerKilled(arg1);
	} else if (eventType == ObserverEventType::DEFENDERADDED) {
		handleDefenderAdded(arg1);
	} else if (eventType == ObserverEventType::DEFENDERDROPPED) {
		handleDefenderDropped(arg1);
	}

	return 0;
}

void BountyMissionObjectiveImplementation::updateMissionStatus(int informantLevel) {
	if (getPlayerOwner() == NULL) {
		return;
	}

	switch (objectiveStatus) {
	case INITSTATUS:
		if (mission->getTargetOptionalTemplate() != "") {
			startNpcTargetTask();
		}

		if (informantLevel == 1) {
			updateWaypoint();
		}
		objectiveStatus = HASBIOSIGNATURESTATUS;
		break;
	case HASBIOSIGNATURESTATUS:
		if (informantLevel > 1) {
			updateWaypoint();
		}
		objectiveStatus = HASTALKED;
		break;
	case HASTALKED:
		if (informantLevel > 1) {
			updateWaypoint();
		}
		break;
	default:
		break;
	}
}

void BountyMissionObjectiveImplementation::updateWaypoint() {
	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL) {
		waypoint = mission->createWaypoint();
	}

	waypoint->setPlanetCRC(getTargetZoneName().hashCode());
	Vector3 position = getTargetPosition();
	waypoint->setPosition(position.getX(), 0, position.getY());
	waypoint->setActive(true);

	mission->updateMissionLocation();

	if (mission->getMissionLevel() == 1) {
		getPlayerOwner()->sendSystemMessage("@mission/mission_bounty_informant:target_location_received");
	}
}

void BountyMissionObjectiveImplementation::performDroidAction(int action, SceneObject* sceneObject, CreatureObject* player) {
	if (!playerHasMissionOfCorrectLevel(action)) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return;
	}

	if (droid == NULL) {
		droid = new BountyHunterDroid();
	}

	Reference<Task*> task = droid->performAction(action, sceneObject, player, getMissionObject());

	droidTasks.add(task);
}

bool BountyMissionObjectiveImplementation::playerHasMissionOfCorrectLevel(int action) {
	int levelNeeded = 2;
	if (action == BountyHunterDroid::CALLDROID || action == BountyHunterDroid::TRANSMITBIOLOGICALSIGNATURE) {
		levelNeeded = 3;
	}

	return mission->getMissionLevel() >= levelNeeded;
}

Vector3 BountyMissionObjectiveImplementation::getTargetPosition() {
	if (isPlayerTarget()) {
		uint64 targetId = mission->getTargetObjectId();

		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
		if (zoneServer != NULL) {
			ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

			if (creature != NULL) {
				return creature->getWorldPosition();
			}
		}
	} else {
		if (targetTask != NULL) {
			return targetTask->getTargetPosition();
		}
	}

	Vector3 empty;
	return empty;
}

void BountyMissionObjectiveImplementation::cancelAllTasks() {
	if (targetTask != NULL && targetTask->isScheduled()) {
		targetTask->cancel();
		targetTask = NULL;
	}

	for (int i = 0; i < droidTasks.size(); i++) {
		Task* droidTask = droidTasks.get(i);

		if (droidTask != NULL && droidTask->isScheduled()) {
			droidTask->cancel();
		}
	}

	droidTasks.removeAll();
}

String BountyMissionObjectiveImplementation::getTargetZoneName() {
	if (isPlayerTarget()) {
		uint64 targetId = mission->getTargetObjectId();

		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
		if (zoneServer != NULL) {
			ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

			if (creature != NULL && creature->getZone() != NULL) {
				return creature->getZone()->getZoneName();
			}
		}
	} else {
		if (targetTask != NULL) {
			return targetTask->getTargetZoneName();
		}
	}

	//No target task, return dungeon1 which is not able to find.
	return "dungeon1";
}

void BountyMissionObjectiveImplementation::addToBountyLock() {
	ManagedReference<PlayerObject*> ghost = getPlayerOwner()->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	ghost->addToBountyLockList(mission->getTargetObjectId());
}

void BountyMissionObjectiveImplementation::removeFromBountyLock(bool immediately) {
	ManagedReference<PlayerObject*> ghost = getPlayerOwner()->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	ghost->removeFromBountyLockList(mission->getTargetObjectId(), immediately);
}

void BountyMissionObjectiveImplementation::removePlayerTargetObservers() {
	removeObserver(5, ObserverEventType::DEFENDERDROPPED, getPlayerOwner());
	removeObserver(4, ObserverEventType::DEFENDERADDED, getPlayerOwner());
	removeObserver(3, ObserverEventType::PLAYERKILLED, getPlayerOwner());

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();

	if (zoneServer != NULL) {
		ManagedReference<CreatureObject*> target = cast<CreatureObject*>(zoneServer->getObject(mission->getTargetObjectId()));

		removeObserver(2, ObserverEventType::DEFENDERDROPPED, target);
		removeObserver(1, ObserverEventType::DEFENDERADDED, target);
		removeObserver(0, ObserverEventType::PLAYERKILLED, target);
	}
}

void BountyMissionObjectiveImplementation::removeNpcTargetObservers() {
	if (npcTarget != NULL) {
		ManagedReference<SceneObject*> npcHolder = npcTarget.get();
		Locker locker(npcTarget);

		removeObserver(1, ObserverEventType::DAMAGERECEIVED, npcTarget);
		removeObserver(0, ObserverEventType::OBJECTDESTRUCTION, npcTarget);

		npcTarget->destroyObjectFromDatabase();
		npcTarget->destroyObjectFromWorld(true);

		npcTarget = NULL;
	} else {
		// NPC not spawned, remove observers anyway.
		dropObserver(getObserver(1), true);
		dropObserver(getObserver(0), true);
	}
}

void BountyMissionObjectiveImplementation::removeObserver(int observerNumber, unsigned int observerType, CreatureObject* creature) {
	if (getObserverCount() <= observerNumber) {
		//Observer does not exist.
		return;
	}

	ManagedReference<MissionObserver*> observer = getObserver(observerNumber);
	creature->dropObserver(observerType, observer);
	dropObserver(observer, true);
}

void BountyMissionObjectiveImplementation::addObserverToCreature(unsigned int observerType, CreatureObject* creature) {
	ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
	addObserver(observer, true);

	creature->registerObserver(observerType, observer);
}

bool BountyMissionObjectiveImplementation::addPlayerTargetObservers() {
	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();

	if (zoneServer != NULL) {
		ManagedReference<CreatureObject*> target = cast<CreatureObject*>(zoneServer->getObject(mission->getTargetObjectId()));

		if (target != NULL) {
			addObserverToCreature(ObserverEventType::PLAYERKILLED, target);
			addObserverToCreature(ObserverEventType::DEFENDERADDED, target);
			addObserverToCreature(ObserverEventType::DEFENDERDROPPED, target);

			CreatureObject* playerOwner = getPlayerOwner();
			addObserverToCreature(ObserverEventType::PLAYERKILLED, playerOwner);
			addObserverToCreature(ObserverEventType::DEFENDERADDED, playerOwner);
			addObserverToCreature(ObserverEventType::DEFENDERDROPPED, playerOwner);

			playerOwner->getZoneServer()->getMissionManager()->addBountyHunterToPlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

			//Update aggressive status on target for bh.
			target->sendPvpStatusTo(playerOwner);

			return true;
		}
	}

	return false;
}

void BountyMissionObjectiveImplementation::startNpcTargetTask() {
	targetTask = new BountyHunterTargetTask(mission, getPlayerOwner(), mission->getEndPlanet());

	if (targetTask != NULL && !targetTask->isScheduled()) {
		targetTask->schedule(10 * 1000);
	}
}

bool BountyMissionObjectiveImplementation::isPlayerTarget() {
	return mission->getTargetOptionalTemplate() == "";
}

void BountyMissionObjectiveImplementation::handleNpcTargetKilled(ManagedObject* arg1) {
	CreatureObject* attacker = NULL;

	attacker = cast<CreatureObject*>(arg1);

	if (attacker != NULL && attacker->getFirstName() == getPlayerOwner()->getFirstName() &&
			attacker->isPlayerCreature()) {
		//Target killed by player, complete mission.
		complete();
	} else {
		//Target killed by other player, fail mission.
		attacker->sendSystemMessage("@mission/mission_generic:failed");
		abort();
		removeMissionFromPlayer();
	}
}

int BountyMissionObjectiveImplementation::handleNpcTargetReceivesDamage(ManagedObject* arg1) {
	CreatureObject* target = NULL;

	target = cast<CreatureObject*>(arg1);

	if (getPlayerOwner() != NULL && target != NULL && target->getFirstName() == getPlayerOwner()->getFirstName() &&
			target->isPlayerCreature() && objectiveStatus == HASBIOSIGNATURESTATUS) {
		updateMissionStatus(mission->getMissionLevel());

		String diffString = "easy";
		if (mission->getMissionLevel() == 3) {
			diffString = "hard";
		} else if (mission->getMissionLevel() == 2) {
			diffString = "medium";
		}

		target->getZoneServer()->getChatManager()->broadcastMessage(npcTarget, "@mission/mission_bounty_neutral_" + diffString + ":m" + String::valueOf(mission->getMissionNumber()) + "v", 0, 0, 0);
		return 1;
	}

	return 0;
}

void BountyMissionObjectiveImplementation::handlePlayerKilled(ManagedObject* arg1) {
	CreatureObject* killer = NULL;

	killer = cast<CreatureObject*>(arg1);

	if (getPlayerOwner() != NULL && killer != NULL) {
		if (getPlayerOwner()->getObjectID() == killer->getObjectID()) {
			//Target killed by player, complete mission.
			complete();
		} else if (mission->getTargetObjectId() == killer->getObjectID() ||
				(npcTarget != NULL && npcTarget->getObjectID() == killer->getObjectID())) {
			//Player killed by target, fail mission.
			getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");
			killer->sendSystemMessage("You have defeated a bounty hunter, ruining his mission against you!");
			fail();
		}
	}
}

void BountyMissionObjectiveImplementation::handleDefenderAdded(ManagedObject* arg1) {
	CreatureObject* defender = NULL;

	defender = cast<CreatureObject*>(arg1);

	if (getPlayerOwner() != NULL && defender != NULL) {
		if (getPlayerOwner()->getObjectID() == defender->getObjectID() ||
				mission->getTargetObjectId() == defender->getObjectID()) {
			addToBountyLock();
		}
	}
}

void BountyMissionObjectiveImplementation::handleDefenderDropped(ManagedObject* arg1) {
	CreatureObject* defender = NULL;

	defender = cast<CreatureObject*>(arg1);

	if (getPlayerOwner() != NULL && defender != NULL) {
		if (getPlayerOwner()->getObjectID() == defender->getObjectID() ||
				mission->getTargetObjectId() == defender->getObjectID()) {
			removeFromBountyLock(false);
		}
	}
}
