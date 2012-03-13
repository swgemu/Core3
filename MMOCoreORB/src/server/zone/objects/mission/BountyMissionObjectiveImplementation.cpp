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

	if (objectiveStatus != INITSTATUS) {
		getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");

		abort();

		removeMissionFromPlayer();

		return;
	}

	if (mission->getTargetOptionalTemplate() == "") {
		ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();

		if (zoneServer == NULL) {
			return;
		}

		ManagedReference<CreatureObject*> target = cast<CreatureObject*>(zoneServer->getObject(mission->getTargetObjectId()));

		if (target != NULL) {
			CreatureObject* playerOwner = getPlayerOwner();

			ManagedReference<MissionObserver*> observer1 = new MissionObserver(_this);
			addObserver(observer1, true);
			target->registerObserver(ObserverEventType::PLAYERKILLED, observer1);

			ManagedReference<MissionObserver*> observer2 = new MissionObserver(_this);
			addObserver(observer2, true);

			playerOwner->registerObserver(ObserverEventType::PLAYERKILLED, observer2);

			ManagedReference<MissionObserver*> observer3 = new MissionObserver(_this);
			addObserver(observer3, true);

			target->registerObserver(ObserverEventType::DEFENDERADDED, observer3);

			ManagedReference<MissionObserver*> observer4 = new MissionObserver(_this);
			addObserver(observer4, true);

			playerOwner->registerObserver(ObserverEventType::DEFENDERADDED, observer4);

			ManagedReference<MissionObserver*> observer5 = new MissionObserver(_this);
			addObserver(observer5, true);

			target->registerObserver(ObserverEventType::DEFENDERDROPPED, observer5);

			ManagedReference<MissionObserver*> observer6 = new MissionObserver(_this);
			addObserver(observer6, true);

			playerOwner->registerObserver(ObserverEventType::DEFENDERDROPPED, observer6);

			playerOwner->getZoneServer()->getMissionManager()->addPlayerToBountyList(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());
		}
	}
}

void BountyMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	cancelAllTasks();

	getPlayerOwner()->getZoneServer()->getMissionManager()->removeBountyHunterFromPlayerBounty(mission->getTargetObjectId(), getPlayerOwner()->getObjectID());

	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint != NULL) {
		waypoint->setActive(false);
	}

	//Remove observers
	if (hasObservers()) {
		if (mission->getTargetOptionalTemplate() != "") {
			ManagedReference<MissionObserver*> observer1 = getObserver(0);
			ManagedReference<MissionObserver*> observer2 = getObserver(1);

			if (npcTarget != NULL) {
				ManagedReference<SceneObject*> npcHolder = npcTarget.get();
				Locker locker(npcTarget);

				npcTarget->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer1);
				npcTarget->dropObserver(ObserverEventType::DAMAGERECEIVED, observer2);
				npcTarget->destroyObjectFromDatabase();
				npcTarget->destroyObjectFromWorld(true);

				npcTarget = NULL;

				dropObserver(observer1, true);
				dropObserver(observer2, true);
			}
		} else {
			ManagedReference<MissionObserver*> observer1 = getObserver(0);
			ManagedReference<MissionObserver*> observer3 = getObserver(2);
			ManagedReference<MissionObserver*> observer5 = getObserver(4);

			ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();

			if (zoneServer == NULL) {
				return;
			}

			ManagedReference<CreatureObject*> target = cast<CreatureObject*>(zoneServer->getObject(mission->getTargetObjectId()));

			if (target != NULL) {
				target->dropObserver(ObserverEventType::PLAYERKILLED, observer1);
				dropObserver(observer1, false);
				target->dropObserver(ObserverEventType::DEFENDERADDED, observer3);
				dropObserver(observer3, false);
				target->dropObserver(ObserverEventType::DEFENDERDROPPED, observer5);
				dropObserver(observer5, false);
			}

			ManagedReference<MissionObserver*> observer2 = getObserver(1);
			ManagedReference<MissionObserver*> observer4 = getObserver(3);
			ManagedReference<MissionObserver*> observer6 = getObserver(5);

			getPlayerOwner()->dropObserver(ObserverEventType::PLAYERKILLED, observer2);
			dropObserver(observer2, true);
			getPlayerOwner()->dropObserver(ObserverEventType::DEFENDERADDED, observer4);
			dropObserver(observer4, true);
			getPlayerOwner()->dropObserver(ObserverEventType::DEFENDERDROPPED, observer6);
			dropObserver(observer6, true);
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

			ManagedReference<MissionObserver*> observer1 = new MissionObserver(_this);
			addObserver(observer1, true);

			npcTarget->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer1);

			ManagedReference<MissionObserver*> observer2 = new MissionObserver(_this);
			addObserver(observer2, true);

			npcTarget->registerObserver(ObserverEventType::DAMAGERECEIVED, observer2);
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
