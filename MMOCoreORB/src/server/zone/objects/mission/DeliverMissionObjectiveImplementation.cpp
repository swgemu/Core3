/*
 * DeliverMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "DeliverMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
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
	if (!activateWithResult()) {
		//Send error message to player.
		CreatureObject* owner = getPlayerOwner();
		if (owner == NULL) {
			return;
		}

		int randomNumber = System::random(4) + 1;
		StringIdChatParameter message("@mission/mission_generic:mission_incomplete_0" + String::valueOf(randomNumber));

		owner->sendSystemMessage(message);
	}
}

bool DeliverMissionObjectiveImplementation::activateWithResult() {
	CreatureObject* owner = getPlayerOwner();
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

	//Spawn target and destination NPC's.
	//Target NPC
	//Find a free spawn point.
	targetSpawnPoint = missionManager->getRandomFreeNpcSpawnPoint(mission->getStartPlanetCRC(), mission->getStartPositionX(), mission->getStartPositionY(), NpcSpawnPoint::NEUTRALSPAWN);
	if (targetSpawnPoint == NULL) {
		return false;
	}
	Vector3* targetPosition = targetSpawnPoint->getPosition();
	if (targetPosition == NULL) {
		return false;
	}
	String deliverNpc = "deliver_npc";
	float z = terrainManager->getHeight(targetPosition->getX(), targetPosition->getY());
	target = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, targetPosition->getX(), z, targetPosition->getY(), 0));
	target->setCustomObjectName(mission->getCreatorName(), true);

	//Destination NPC.
	//Find a free spawn point.
	destinationSpawnPoint = missionManager->getRandomFreeNpcSpawnPoint(mission->getEndPlanetCRC(), mission->getEndPositionX(), mission->getEndPositionY(), NpcSpawnPoint::NEUTRALSPAWN);
	if (destinationSpawnPoint == NULL) {
		return false;
	}
	Vector3* destinationPosition = destinationSpawnPoint->getPosition();
	if (destinationPosition == NULL) {
		return false;
	}
	z = terrainManager->getHeight(destinationPosition->getX(), destinationPosition->getY());
	destination = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, destinationPosition->getX(), z, destinationPosition->getY(), 0));
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
		updateMissionTarget(getPlayerOwner());
	}

	return true;
}

void DeliverMissionObjectiveImplementation::abort() {
	ZoneServer* zoneServer = getPlayerOwner()->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();
	missionManager->returnSpawnPoint(targetSpawnPoint);
	missionManager->returnSpawnPoint(destinationSpawnPoint);
	despawnNpcs();
}

void DeliverMissionObjectiveImplementation::complete() {
	CreatureObject* player = cast<CreatureObject*>(getPlayerOwner());

	if (player == NULL) {
		return;
	}

	Locker locker(player);

	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);

	int missionReward = mission->getRewardCredits();

	StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
	stringId.setDI(missionReward);
	player->sendSystemMessage(stringId);

	player->addBankCredits(missionReward, true);

	ZoneServer* zoneServer = player->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	missionManager->removeMission(mission, player);

	missionManager->returnSpawnPoint(targetSpawnPoint);
	missionManager->returnSpawnPoint(destinationSpawnPoint);
	despawnNpcs();
}

void DeliverMissionObjectiveImplementation::updateMissionStatus(CreatureObject* player) {
	StringBuffer itemEntry;
	itemEntry << "m" << mission->getMissionNumber();

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	StringId itemName;

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
	WaypointObject* waypoint = mission->getWaypointToMission();
	if (waypoint == NULL) {
		waypoint = mission->createWaypoint();
	}

	waypoint->setPlanetCRC(mission->getEndPlanetCRC());
	waypoint->setPosition(destinationSpawnPoint->getPosition()->getX(), 0, destinationSpawnPoint->getPosition()->getY());
	waypoint->setActive(true);

	mission->updateMissionLocation();

	return true;
}
