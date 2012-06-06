/*
 * DeliverMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "DeliverMissionObjective.h"
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
#include "MissionObject.h"
#include "MissionObserver.h"

void DeliverMissionObjectiveImplementation::activate() {
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
	String deliverNpc = "deliver_npc";
	//Get the terrain height at the spawn point.
	float z = terrainManager->getHeight(targetPosition->getX(), targetPosition->getY());
	//Spawn the NPC.
	target = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, targetPosition->getX(), z, targetPosition->getY(), 0));
	//Update the heading direction of the NPC.
	Quaternion* direction = targetSpawnPoint->getDirection();
	target->updateDirection(direction->getW(), direction->getX(), direction->getY(), direction->getZ());
	//Set the name of the NPC.
	target->setCustomObjectName(mission->getCreatorName(), true);

	//Destination NPC.
	//Find a free spawn point.
	destinationSpawnPoint = missionManager->getRandomFreeNpcSpawnPoint(mission->getEndPlanet().hashCode(), mission->getEndPositionX(), mission->getEndPositionY(), spawnType);
	if (destinationSpawnPoint == NULL) {
		return false;
	}
	Vector3* destinationPosition = destinationSpawnPoint->getPosition();
	if (destinationPosition == NULL) {
		return false;
	}
	//Get the terrain height at the spawn point.
	z = terrainManager->getHeight(destinationPosition->getX(), destinationPosition->getY());
	//Spawn the NPC.
	destination = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, destinationPosition->getX(), z, destinationPosition->getY(), 0));
	//Update the heading direction of the NPC.
	direction = destinationSpawnPoint->getDirection();
	destination->updateDirection(direction->getW(), direction->getX(), direction->getY(), direction->getZ());
	//Set the name of the NPC.
	destination->setCustomObjectName(mission->getTargetName(), true);

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

	if (despawnMissionNpcsTask == NULL) {
		despawnMissionNpcsTask = new DespawnMissionNpcsTask(target, destination, targetSpawnPoint, destinationSpawnPoint, missionManager);
	}

	if (despawnMissionNpcsTask->isScheduled()) {
		return;
	} else {
		//Despawn after 1 minute.
		despawnMissionNpcsTask->schedule(60 * 1000);
	}
}

void DeliverMissionObjectiveImplementation::updateMissionStatus(CreatureObject* player) {
	ManagedReference<MissionObject* > mission = this->mission.get();

	StringBuffer itemEntry;
	itemEntry << "m" << mission->getMissionNumber();

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	StringId itemName;

	Locker lock(player);

	switch (objectiveStatus) {
	case 0:
		itemEntry << "l";
		item = NULL;
		//TODO: create correct item.
		item = cast<TangibleObject*>( player->getZoneServer()->createObject(String("object/tangible/mission/mission_datadisk.iff").hashCode(), 2));
		if (item == NULL) {
			return;
		}

		itemName.setStringId("mission/mission_deliver_neutral_easy", itemEntry.toString());
		item->setObjectName(itemName);
		item->sendTo(player, true);

		//Give player the item to deliver
		inventory->transferObject(item, -1, true);

		updateMissionTarget(player);

		objectiveStatus = PICKEDUPSTATUS;
		break;
	case 1:
		// check for item, then remove item
		if (item == NULL || !inventory->hasObjectInContainer(item->getObjectID())) {
			return;
		}

		item->destroyObjectFromWorld(true);

		complete();

		objectiveStatus = DELIVEREDSTATUS;
		break;
	default:
		break;
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
