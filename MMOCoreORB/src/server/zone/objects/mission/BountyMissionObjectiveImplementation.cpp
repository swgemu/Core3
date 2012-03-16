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

	bool missionFailed = false;

	if (objectiveStatus != INITSTATUS) {
		missionFailed = true;
	}

	if (mission->getTargetOptionalTemplate() == "") {
		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();

		if (zoneServer == NULL) {
			missionFailed = true;
		} else {
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
			} else {
				missionFailed = true;
			}
		}
	}

	if (missionFailed) {
		getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");

		abort();

		removeMissionFromPlayer();
	}
}

void BountyMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	cancelAllTasks();

	getPlayerOwner()->getZoneServer()->getMissionManager()->removeBountyHunterFromPlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint != NULL && waypoint->isActive()) {
		waypoint->setActive(false);
	}

	//Remove observers
	if (hasObservers()) {
		if (mission->getTargetOptionalTemplate() != "") {
			if (npcTarget != NULL) {
				ManagedReference<SceneObject*> npcHolder = npcTarget.get();
				Locker locker(npcTarget);

				removeObserver(1, ObserverEventType::DAMAGERECEIVED, npcTarget);
				removeObserver(0, ObserverEventType::OBJECTDESTRUCTION, npcTarget);

				npcTarget->destroyObjectFromDatabase();
				npcTarget->destroyObjectFromWorld(true);

				npcTarget = NULL;
			}
		} else {
			removeObservers();
		}
	}
}

void BountyMissionObjectiveImplementation::complete() {
	cancelAllTasks();

	//Award bountyhunter xp.
	getPlayerOwner()->getZoneServer()->getPlayerManager()->awardExperience(getPlayerOwner(), "bountyhunter", mission->getRewardCredits() / 100, true, 1);

	getPlayerOwner()->getZoneServer()->getMissionManager()->completePlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

	MissionObjectiveImplementation::complete();
}

void BountyMissionObjectiveImplementation::spawnTarget(const String& zoneName) {
	if ((npcTarget != NULL && npcTarget->isInQuadTree()) || mission->getTargetOptionalTemplate() == "") {
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

			addObserverToCreature(ObserverEventType::OBJECTDESTRUCTION, npcTarget);
			addObserverToCreature(ObserverEventType::DAMAGERECEIVED, npcTarget);
		}
	}
}

int BountyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		CreatureObject* attacker = NULL;

		try {
			attacker = cast<CreatureObject*>(arg1);
		} catch (Exception& e) { // ?? cast doesnt ever throw exceptions
			//Killed in a strange way.
			int randomNumber = System::random(4) + 1;
			getPlayerOwner()->sendSystemMessage("@mission/mission_generic:mission_incomplete_0" + String::valueOf(randomNumber));
			abort();
			return 1;
		}

		if (attacker != NULL && attacker->getFirstName() == getPlayerOwner()->getFirstName() &&
				attacker->isPlayerCreature()) {
			//Target killed by player, complete mission.
			complete();
		} else {
			//Target killed by other player, fail mission.
			attacker->sendSystemMessage("@mission/mission_generic:failed");
			abort();
		}

		return 1;
	} else if (eventType == ObserverEventType::DAMAGERECEIVED) {
		CreatureObject* attacker = NULL;
		try {
			attacker = cast<CreatureObject*>(arg1);
		}
		catch (Exception& e) {
			return 0;
		}

		if (getPlayerOwner() != NULL && attacker != NULL && attacker->getFirstName() == getPlayerOwner()->getFirstName() &&
				attacker->isPlayerCreature() && objectiveStatus == HASBIOSIGNATURESTATUS) {
			updateMissionStatus(mission->getMissionLevel());

			String diffString = "easy";

			if (mission->getMissionLevel() == 3) {
				diffString = "hard";
			} else if (mission->getMissionLevel() == 2) {
				diffString = "medium";
			}

			attacker->getZoneServer()->getChatManager()->broadcastMessage(npcTarget, "@mission/mission_bounty_neutral_" + diffString + ":m" + String::valueOf(mission->getMissionNumber()) + "v", 0, 0, 0);
			return 1;
		}
	} else if (eventType == ObserverEventType::PLAYERKILLED) {
		CreatureObject* killer = NULL;
		try {
			killer = cast<CreatureObject*>(arg1);
		}
		catch (Exception& e) {
			return 0;
		}

		if (getPlayerOwner() != NULL && killer != NULL) {
			if (getPlayerOwner()->getObjectID() == killer->getObjectID()) {
				//Target killed by player, complete mission.
				complete();
				return 1;
			} else if (mission->getTargetObjectId() == killer->getObjectID() ||
					(npcTarget != NULL && npcTarget->getObjectID() == killer->getObjectID())) {
				//Player killed by target, fail mission.
				getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");
				killer->sendSystemMessage("You have defeated a bounty hunter, ruining his mission against you!")
				fail();
				return 1;
			}
		}
	} else if (eventType == ObserverEventType::DEFENDERADDED) {
		CreatureObject* defender = NULL;
		try {
			defender = cast<CreatureObject*>(arg1);
		}
		catch (Exception& e) {
			return 0;
		}

		if (getPlayerOwner() != NULL && defender != NULL) {
			if (getPlayerOwner()->getObjectID() == defender->getObjectID() ||
					mission->getTargetObjectId() == defender->getObjectID()) {
				addToBountyLock();
			}
		}
	} else if (eventType == ObserverEventType::DEFENDERDROPPED) {
		CreatureObject* defender = NULL;
		try {
			defender = cast<CreatureObject*>(arg1);
		}
		catch (Exception& e) {
			return 0;
		}

		if (getPlayerOwner() != NULL && defender != NULL) {
			if (getPlayerOwner()->getObjectID() == defender->getObjectID() ||
					mission->getTargetObjectId() == defender->getObjectID()) {
				removeFromBountyLock();
			}
		}
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
			targetTask = new BountyHunterTargetTask(mission, getPlayerOwner(), mission->getEndPlanet());
			if (targetTask != NULL && !targetTask->isScheduled()) {
				targetTask->schedule(10 * 1000);
			}
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
	if (mission->getTargetOptionalTemplate() != "") {
		if (targetTask != NULL) {
			return targetTask->getTargetPosition();
		}
	} else {
		uint64 targetId = mission->getTargetObjectId();

		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
		if (zoneServer != NULL) {
			ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

			if (creature != NULL) {
				return creature->getWorldPosition();
			}
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
	if (mission->getTargetOptionalTemplate() != "") {
		if (targetTask != NULL) {
			return targetTask->getTargetZoneName();
		}
	} else {
		uint64 targetId = mission->getTargetObjectId();

		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
		if (zoneServer != NULL) {
			ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

			if (creature != NULL && creature->getZone() != NULL) {
				return creature->getZone()->getZoneName();
			}
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

	uint64 targetId = mission->getTargetObjectId();

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	if (zoneServer == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

	if (creature == NULL) {
		return;
	}

	ManagedReference<PlayerObject*> targetGhost = creature->getPlayerObject();

	if (targetGhost == NULL) {
		return;
	}

	ghost->addToBountyLockList(creature);
	targetGhost->addToBountyLockList(getPlayerOwner());
	creature->sendPvpStatusTo(getPlayerOwner());
	getPlayerOwner()->sendPvpStatusTo(creature);
}

void BountyMissionObjectiveImplementation::removeFromBountyLock() {
	ManagedReference<PlayerObject*> ghost = getPlayerOwner()->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	uint64 targetId = mission->getTargetObjectId();

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	if (zoneServer == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> creature = cast<CreatureObject*>(zoneServer->getObject(targetId));

	if (creature == NULL) {
		return;
	}

	ManagedReference<PlayerObject*> targetGhost = creature->getPlayerObject();

	if (targetGhost == NULL) {
		return;
	}

	ghost->removeFromBountyLockList(creature);
	targetGhost->removeFromBountyLockList(getPlayerOwner());
	creature->sendPvpStatusTo(getPlayerOwner());
	getPlayerOwner()->sendPvpStatusTo(creature);
}

void BountyMissionObjectiveImplementation::removeObservers() {
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
