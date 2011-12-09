/*
 * DestroyMissionObjectiveImplementation.cpp
 *
 *  Created on: 16/07/2010
 *      Author: victor
 */

#include "DestroyMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/tangible/lair/LairObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"

void DestroyMissionObjectiveImplementation::setLairTemplateToSpawn(SharedObjectTemplate* sp) {
	lairTemplateToSpawn = sp;
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
	/*
	if ((observers.size() != 0 && lairObject != NULL) || mission == NULL) {
		return;
	}

	if (spawnActiveArea == NULL) {
		spawnActiveArea = cast<MissionSpawnActiveArea*>( Core::lookupObject<ZoneServer>("ZoneServer")->createObject(String("object/mission_spawn_area.iff").hashCode(), 1));
		spawnActiveArea->setMissionObjective(_this);
	}

	if (!spawnActiveArea->isInQuadTree()) {
		uint32 startPlanetCRC = mission->getStartPlanetCRC();

		String planetName = Planet::getPlanetNameByCrc(startPlanetCRC);
		int id = Planet::getPlanetID(planetName);

		if (id >= 0) {
			Zone* zone = Core::lookupObject<ZoneServer>("ZoneServer")->getZone(id);
			spawnActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
			spawnActiveArea->setRadius(128.f);
			spawnActiveArea->insertToZone(zone);
		}

		//info("inserting to zone " + zone->getPlanetName(), true);
	}

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
	*/
}

void DestroyMissionObjectiveImplementation::spawnLair() {
	if (lairObject != NULL && lairObject->isInQuadTree())
		return;

	Zone* zone = spawnActiveArea->getZone();

	spawnActiveArea->destroyObjectFromWorld(true);

	float newX = spawnActiveArea->getPositionX() + (256.0f - (float) System::random(512));
	float newY = spawnActiveArea->getPositionY() + (256.0f - (float) System::random(512));

	WaypointObject* waypoint = mission->getWaypointToMission();
	waypoint->setPosition(newX, 0, newY);
	mission->updateMissionLocation();
	//TODO: find correct string id
	CreatureObject* player = getPlayerOwner();

	player->sendSystemMessage("Transmission Received: Mission Target has been located.  Mission waypoint has been updated to exact location");

	if (lairObject == NULL)
		lairObject = cast<LairObject*>( Core::lookupObject<ZoneServer>("ZoneServer")->createObject(lairTemplateToSpawn->getServerObjectCRC(), 0));

	if (!lairObject->isInQuadTree()) {
		lairObject->initializePosition(newX, zone->getHeight(newX, newY), newY);
		//lairObject->insertToZone(zone);
		zone->transferObject(lairObject, -1, true);

		ManagedReference<MissionObserver*> observer = new MissionObserver(_this);
		ObjectManager::instance()->persistObject(observer, 1, "missionobservers");

		lairObject->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);

		observers.put(observer);
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
