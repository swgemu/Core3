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
	if (objectiveStatus != INITSTATUS) {
		getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");

		abort();

		removeMissionFromPlayer();
	}
}

void BountyMissionObjectiveImplementation::abort() {
	cancelAllTasks();

	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint != NULL) {
		waypoint->setActive(false);
	}

	//Remove observers
	if (observers.size() != 0) {
		ManagedReference<MissionObserver*> observer1 = observers.get(0);
		ManagedReference<MissionObserver*> observer2 = observers.get(1);

		if (npcTarget != NULL) {
			ManagedReference<SceneObject*> npcHolder = npcTarget.get();
			Locker locker(npcTarget);

			npcTarget->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer1);
			npcTarget->dropObserver(ObserverEventType::DAMAGERECEIVED, observer2);
			npcTarget->destroyObjectFromDatabase();
			npcTarget->destroyObjectFromWorld(true);

			npcTarget = NULL;

			observers.drop(observer1);
			observers.drop(observer2);
		}
	}
}

void BountyMissionObjectiveImplementation::complete() {
	cancelAllTasks();

	//Award bountyhunter xp.
	getPlayerOwner()->getZoneServer()->getPlayerManager()->awardExperience(getPlayerOwner(), "bountyhunter", mission->getRewardCredits() / 100, true, 1);

	MissionObjectiveImplementation::complete();
}

void BountyMissionObjectiveImplementation::spawnTarget(const String& zoneName) {
	if (npcTarget != NULL && npcTarget->isInQuadTree())
		return;

	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	Zone* zone = zoneServer->getZone(zoneName);
	CreatureManager* cmng = zone->getCreatureManager();

	ManagedReference<CreatureObject*> npcCreature = NULL;

	if (npcTarget == NULL) {
		Vector3 position = getTargetPosition();
		//TODO: verify that it is a good position to spawn the target at i.e. not in water, not in a house etc. generate a random coordinate within 100 m if so and try that instead.
		npcTarget = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(mission->getTargetOptionalTemplate().hashCode(), 0, position.getX(), zone->getHeight(position.getX(), position.getY()), position.getY(), 0));

		ManagedReference<MissionObserver*> observer1 = new MissionObserver(_this);
		ObjectManager::instance()->persistObject(observer1, 1, "missionobservers");

		npcTarget->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer1);

		observers.put(observer1);

		ManagedReference<MissionObserver*> observer2 = new MissionObserver(_this);
		ObjectManager::instance()->persistObject(observer2, 1, "missionobservers");

		npcTarget->registerObserver(ObserverEventType::DAMAGERECEIVED, observer2);

		observers.put(observer2);
	}
}

int BountyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		CreatureObject* attacker = NULL;
		try {
			attacker = cast<CreatureObject*>(arg1);
		}
		catch (Exception) {
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
		catch (Exception) {
			return 0;
		}

		if (getPlayerOwner() != NULL && attacker != NULL && attacker->getFirstName() == getPlayerOwner()->getFirstName() &&
				attacker->isPlayerCreature() && objectiveStatus == HASBIOSIGNATURESTATUS) {
			updateMissionStatus(mission->getDifficultyLevel());
			attacker->getZoneServer()->getChatManager()->broadcastMessage(npcTarget, "@mission/mission_bounty_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "v", 0, 0, 0);
			return 1;
		}
	}

	return 0;
}

void BountyMissionObjectiveImplementation::updateMissionStatus(int informantLevel) {
	if (getPlayerOwner() == NULL) {
		return;
	}

	Zone* zone = getPlayerOwner()->getZone();

	if (zone == NULL) {
		return;
	}

	switch (objectiveStatus) {
	case INITSTATUS:
		if (informantLevel == 1) {
			if (zone->getZoneName() == mission->getEndPlanet()) {
				updateWaypoint();
			}
		}
		targetTask = new BountyHunterTargetTask(mission, getPlayerOwner());
		if (targetTask != NULL && !targetTask->isScheduled()) {
			targetTask->schedule(10 * 1000);
		}
		objectiveStatus = HASBIOSIGNATURESTATUS;
		break;
	case HASBIOSIGNATURESTATUS:
		if (informantLevel > 1) {
			if (zone->getZoneName() == mission->getEndPlanet()) {
				updateWaypoint();
			}
		}
		objectiveStatus = HASTALKED;
		break;
	case HASTALKED:
		if (informantLevel > 1) {
			if (zone->getZoneName() == mission->getEndPlanet()) {
				updateWaypoint();
			}
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

	waypoint->setPlanetCRC(getPlayerOwner()->getPlanetCRC());
	Vector3 position = getTargetPosition();
	waypoint->setPosition(position.getX(), 0, position.getY());
	waypoint->setActive(true);

	mission->updateMissionLocation();

	getPlayerOwner()->sendSystemMessage("mission/mission_bounty_informant", "target_location_received");
}

void BountyMissionObjectiveImplementation::performDroidAction(int action, SceneObject* sceneObject, CreatureObject* player) {
	if (!playerHasMissionOfCorrectLevel(action)) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return;
	}

	activeDroid = sceneObject;

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

	return mission->getDifficultyLevel() >= levelNeeded;
}

Vector3 BountyMissionObjectiveImplementation::getTargetPosition() {
	if (targetTask != NULL) {
		return targetTask->getTargetPosition();
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
