/*
 * DeliverMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"
#include "server/ServerCore.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/MissionObserver.h"

void DeliverMissionObjectiveImplementation::activate() {
	if (activated) {
		return;
	}

	MissionObjectiveImplementation::activate();

	if (!activateWithResult()) {
		//Send error message to player.
		ManagedReference<CreatureObject*> owner = getPlayerOwner();
		if (owner == NULL) {
			return;
		}

		int randomNumber = System::random(4) + 1;
		StringIdChatParameter message("@mission/mission_generic:mission_incomplete_0" + String::valueOf(randomNumber));

		owner->sendSystemMessage(message);

		removeMissionFromPlayer();
	}
}

void DeliverMissionObjectiveImplementation::deactivate() {
	if (activated) {
		MissionObjectiveImplementation::deactivate();
		despawnNpcs();
	}
}

bool DeliverMissionObjectiveImplementation::activateWithResult() {
	ManagedReference<CreatureObject*> owner = getPlayerOwner();
	ManagedReference<MissionObject* > mission = this->mission.get();

	if (owner == NULL) {
		return false;
	}
	Zone* zone = owner->getZone();
	if (zone == NULL) {
		return false;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	PlanetManager* planetManager = zone->getPlanetManager();
	if (planetManager == NULL) {
		return false;
	}
	TerrainManager* terrainManager = planetManager->getTerrainManager();
	if (terrainManager == NULL) {
		return false;
	}

	ZoneServer* zoneServer = owner->getZoneServer();
	if (zoneServer == NULL) {
		return false;
	}

	MissionManager* missionManager = zoneServer->getMissionManager();
	if (missionManager == NULL) {
		return false;
	}

	//Select spawn type.
	int spawnType = NpcSpawnPoint::NEUTRALSPAWN;
	switch (mission->getFaction()) {
	case MissionObject::FACTIONIMPERIAL:
		spawnType = NpcSpawnPoint::IMPERIALSPAWN;
		break;
	case MissionObject::FACTIONREBEL:
		spawnType = NpcSpawnPoint::REBELSPAWN;
		break;
	default:
		spawnType = NpcSpawnPoint::NEUTRALSPAWN;
		break;
	}

	//Spawn target and destination NPC's.

	//Target NPC
	//Find a free spawn point.
	targetSpawnPoint = missionManager->getRandomFreeNpcSpawnPoint(mission->getStartPlanetCRC(), mission->getStartPositionX(), mission->getStartPositionY(), spawnType);
	if (targetSpawnPoint == NULL) {
		return false;
	}
	Vector3* targetPosition = targetSpawnPoint->getPosition();
	if (targetPosition == NULL) {
		return false;
	}

	//Destination NPC.
	//Find a free spawn point.
	int retries = 10;
	destinationSpawnPoint = NULL;
	while (retries > 0 && (destinationSpawnPoint == NULL || destinationSpawnPoint == targetSpawnPoint)) {
		destinationSpawnPoint = missionManager->getRandomFreeNpcSpawnPoint(mission->getEndPlanet().hashCode(), mission->getEndPositionX(), mission->getEndPositionY(), spawnType);
		retries--;
	}
	if (destinationSpawnPoint == NULL || destinationSpawnPoint == targetSpawnPoint) {
		return false;
	}

	missionManager->allocateMissionNpcs(targetSpawnPoint, destinationSpawnPoint, terrainManager, creatureManager);

	//Create waypoint and activate it.
	if (objectiveStatus == 0) {
		WaypointObject* waypoint = mission->getWaypointToMission();

		if (waypoint == NULL) {
			waypoint = mission->createWaypoint();
		}

		waypoint->setPlanetCRC(mission->getStartPlanetCRC());
		waypoint->setPosition(targetPosition->getX(), 0, targetPosition->getY());
		waypoint->setActive(true);

		mission->updateMissionLocation();
	} else {
		updateMissionTarget(getPlayerOwner().get());
	}

	return true;
}

void DeliverMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	despawnNpcs();
}

void DeliverMissionObjectiveImplementation::complete() {
	despawnNpcs();

	MissionObjectiveImplementation::complete();
}

void DeliverMissionObjectiveImplementation::despawnNpcs() {
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	if (targetSpawnPoint != NULL)
		missionManager->freeMissionNpc(targetSpawnPoint);

	if (destinationSpawnPoint != NULL)
		missionManager->freeMissionNpc(destinationSpawnPoint);
}

void DeliverMissionObjectiveImplementation::updateMissionStatus(CreatureObject* player) {
	ManagedReference<MissionObject* > mission = this->mission.get();

	StringBuffer itemEntry;
	itemEntry << "m" << mission->getMissionNumber();

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	StringId itemName;

	Locker lock(player);

	if (objectiveStatus == 0) {
		itemEntry << "l";
		item = NULL;
		//TODO: create correct item.
		item = (player->getZoneServer()->createObject(String("object/tangible/mission/mission_datadisk.iff").hashCode(), 2)).castTo<TangibleObject*>();
		if (item == NULL) {
			abort();
			return;
		}

		Locker clocker(item, player);

		itemName.setStringId("mission/mission_deliver_neutral_easy", itemEntry.toString());
		item->setObjectName(itemName);

		//Give player the item to deliver
		if (inventory->transferObject(item, -1, true)) {
			item->sendTo(player, true);
		} else {
			abort();
			item->destroyObjectFromDatabase(true);
			return;
		}

		updateMissionTarget(player);

		objectiveStatus = PICKEDUPSTATUS;

	} else if (objectiveStatus == 1) {
		// check for item, then remove item
		if (item == NULL || !inventory->hasObjectInContainer(item->getObjectID())) {
			return;
		}

		Locker clocker2(item, player);

		item->destroyObjectFromWorld(true);
		item->destroyObjectFromDatabase(true);

		complete();

		objectiveStatus = DELIVEREDSTATUS;
	}
}

bool DeliverMissionObjectiveImplementation::updateMissionTarget(CreatureObject* player) {
	//Now update the waypoint to the new target
	ManagedReference<MissionObject* > mission = this->mission.get();

	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint == NULL) {
		waypoint = mission->createWaypoint();
	}

	waypoint->setPlanetCRC(mission->getEndPlanet().hashCode());
	waypoint->setPosition(destinationSpawnPoint->getPosition()->getX(), 0, destinationSpawnPoint->getPosition()->getY());
	waypoint->setActive(true);

	mission->updateMissionLocation();

	return true;
}
