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
		npcTarget = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(String("bodyguard").hashCode(), 0, mission->getPositionX(), zone->getHeight(mission->getPositionX(), mission->getPositionY()), mission->getPositionY(), 0));

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

		if (attacker != NULL && attacker->getFirstName() == getPlayerOwner()->getFirstName() &&
				attacker->isPlayerCreature() && objectiveStatus == HASBIOSIGNATURESTATUS) {
			updateMissionStatus(mission->getDifficultyLevel());
			attacker->getZoneServer()->getChatManager()->broadcastMessage(npcTarget, "@mission/mission_bounty_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "v", 0, 0, 0);
			return 1;
		}
	}

	return 0;
}

void BountyMissionObjectiveImplementation::updateMissionStatus(int informantLevel) {
	switch (objectiveStatus) {
	case INITSTATUS:
		if (informantLevel == 1) {
			spawnTarget(getPlayerOwner()->getZone()->getZoneName());

			WaypointObject* waypoint = mission->getWaypointToMission();

			if (waypoint == NULL) {
				waypoint = mission->createWaypoint();
			}

			mission->setEndPosition(npcTarget->getPositionX(), npcTarget->getPositionY(), npcTarget->getPlanetCRC(), true);
			waypoint->setPlanetCRC(npcTarget->getPlanetCRC());
			waypoint->setPosition(npcTarget->getPositionX(), 0, npcTarget->getPositionY());
			waypoint->setActive(true);

			mission->updateMissionLocation();

			getPlayerOwner()->sendSystemMessage("mission/mission_bounty_informant", "target_location_received");
		}

		objectiveStatus = HASBIOSIGNATURESTATUS;
		break;
	case HASBIOSIGNATURESTATUS:
		objectiveStatus = HASTALKED;
		break;
	case HASTALKED:
		break;
	default:
		break;
	}
}
