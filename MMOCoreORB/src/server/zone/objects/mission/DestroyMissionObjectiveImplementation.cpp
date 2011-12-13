/*
 * DestroyMissionObjectiveImplementation.cpp
 *
 *  Created on: 16/07/2010
 *      Author: victor
 */

#include "DestroyMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/DamageMap.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

void DestroyMissionObjectiveImplementation::setLairTemplateToSpawn(const String& sp) {
	lairTemplate = sp;
}

void DestroyMissionObjectiveImplementation::destroyObjectFromDatabase() {
	MissionObjectiveImplementation::destroyObjectFromDatabase();

	if (spawnActiveArea != NULL) {
		spawnActiveArea->destroyObjectFromWorld(true);
		spawnActiveArea->destroyObjectFromDatabase(true);

		spawnActiveArea = NULL;
	}
}

void DestroyMissionObjectiveImplementation::activate() {
	if ((observers.size() != 0 && lairObject != NULL) || mission == NULL) {
		return;
	}

	if (spawnActiveArea == NULL) {
		spawnActiveArea = cast<MissionSpawnActiveArea*>( Core::lookupObject<ZoneServer>("ZoneServer")->createObject(String("object/mission_spawn_area.iff").hashCode(), 1));
		spawnActiveArea->setMissionObjective(_this);
	}

	if (spawnActiveArea->getZone() == NULL) {
		String planetName = mission->getStartPlanet();

		Zone* zone = Core::lookupObject<ZoneServer>("ZoneServer")->getZone(planetName);

		if (zone == NULL)
			return;

		spawnActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
		spawnActiveArea->setRadius(128.f);
		zone->transferObject(spawnActiveArea, -1, false);
		//info("inserting to zone " + zone->getPlanetName(), true);
	}

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanet().hashCode());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

Vector3 DestroyMissionObjectiveImplementation::findValidSpawnPosition(Zone* zone) {
	Vector3 position;

	float newX = spawnActiveArea->getPositionX() + (256.0f - (float) System::random(512));
	float newY = spawnActiveArea->getPositionY() + (256.0f - (float) System::random(512));

	float height = zone->getHeight(newX, newY);

	float waterHeight;
	TerrainManager* terrain = zone->getPlanetManager()->getTerrainManager();

	float distance = 10;
	int tries = 0;

	position.set(newX, height, newY);

	while (((terrain->getWaterHeight(newX, newY, waterHeight) && waterHeight > height)
			|| CollisionManager::checkSphereCollision(position, 25.f , zone)) && tries < 20) {
		newX = spawnActiveArea->getPositionX() + (distance - (float) System::random(distance * 2));
		newY = spawnActiveArea->getPositionY() + (distance - (float) System::random(distance * 2));
		height = zone->getHeight(newX, newY);

		position.set(newX, height, newY);

		distance = distance * 2;
		++tries;
	}

	//info("found with tries " + String::valueOf(tries), true);

	return position;
}

void DestroyMissionObjectiveImplementation::spawnLair() {
	if (lairObject != NULL && lairObject->getZone() != NULL)
		return;

	Zone* zone = spawnActiveArea->getZone();

	spawnActiveArea->destroyObjectFromWorld(true);

	Vector3 pos = findValidSpawnPosition(zone);

	WaypointObject* waypoint = mission->getWaypointToMission();
	waypoint->setPosition(pos.getX(), 0, pos.getY());
	mission->updateMissionLocation();
	//TODO: find correct string id
	CreatureObject* player = getPlayerOwner();

	player->sendSystemMessage("Transmission Received: Mission Target has been located.  Mission waypoint has been updated to exact location");

	if (lairObject == NULL) {
		CreatureManager* creatureManager = zone->getCreatureManager();

		lairObject = creatureManager->spawnLair(lairTemplate.hashCode(), minDifficulty, maxDifficulty, pos.getX(), pos.getZ(), pos.getY());

		if (lairObject != NULL) {
			ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
			ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

			Locker locker(lairObject);

			lairObject->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);

			observers.put(observer);
		}

	}

	if (lairObject != NULL && lairObject->getZone() == NULL) {
		zone->transferObject(lairObject, -1, true);
	}
}

void DestroyMissionObjectiveImplementation::abort() {
	if (observers.size() != 0) {
		ManagedReference<MissionObserver*> observer = observers.get(0);

		CreatureObject* player = getPlayerOwner();

		if (lairObject != NULL) {
			ManagedReference<SceneObject*> lairH = lairObject.get();

			Locker locker(lairObject);

			lairObject->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
			observer->destroyObjectFromDatabase();
			lairObject->destroyObjectFromWorld(true);

			lairObject = NULL;

			observers.drop(observer);
		}
			//spawnActiveArea->destroyObjectFromDatabase(true);
	}

	if (spawnActiveArea != NULL)
		spawnActiveArea->destroyObjectFromWorld(true);
}

void DestroyMissionObjectiveImplementation::complete() {
	CreatureObject* player = cast<CreatureObject*>( getPlayerOwner());

	if (player == NULL)
		return;

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
}

int DestroyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {

		complete();
	}

	return 1;
}
