/*
 * DestroyMissionObjectiveImplementation.cpp
 *
 *  Created on: 16/07/2010
 *      Author: victor
 */

#include "server/zone/objects/mission/DestroyMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/MissionObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/mission/DestroyMissionLairObserver.h"

void DestroyMissionObjectiveImplementation::setLairTemplateToSpawn(const String& sp) {
	lairTemplate = sp;
}

void DestroyMissionObjectiveImplementation::destroyObjectFromDatabase() {
	MissionObjectiveImplementation::destroyObjectFromDatabase();

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea != NULL) {
		Locker locker(spawnActiveArea);

		spawnActiveArea->destroyObjectFromWorld(true);
		spawnActiveArea->destroyObjectFromDatabase(true);

		this->spawnActiveArea = NULL;
	}
}

void DestroyMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();
	ManagedReference<MissionObject* > mission = this->mission.get();

	if ((hasObservers() && lairObject != NULL) || mission == NULL) {
		return;
	}

	if (spawnActiveArea == NULL) {
		spawnActiveArea = ( Core::lookupObject<ZoneServer>("ZoneServer")->createObject(STRING_HASHCODE("object/mission_spawn_area.iff"), 1)).castTo<MissionSpawnActiveArea*>();
		Locker alocker(spawnActiveArea);
		spawnActiveArea->setMissionObjective(_this.get());
	}

	if (spawnActiveArea->getZone() == NULL) {
		String planetName = mission->getStartPlanet();

		Zone* zone = Core::lookupObject<ZoneServer>("ZoneServer")->getZone(planetName);

		if (zone == NULL) {
			abort();
			return;
		}

		Locker alocker(spawnActiveArea);

		spawnActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
		spawnActiveArea->setRadius(128.f);
		zone->transferObject(spawnActiveArea, -1, false);
		//info("inserting to zone " + zone->getPlanetName(), true);
	}

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL) {
		Locker mlocker(mission);
		waypoint = mission->createWaypoint();
	}

	Locker locker(waypoint);

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
	PlanetManager* planetManager = zone->getPlanetManager();

	float distance = 128;
	int tries = 0;
	float size = mission.get()->getSize();

	position.set(newX, height, newY);

	while ((!planetManager->isSpawningPermittedAt(newX, newY, size)
			|| CollisionManager::checkSphereCollision(position, size + 25.f , zone)) && tries < 256) {
		newX = spawnActiveArea->getPositionX() + (distance - (float) System::random(distance * 2));
		newY = spawnActiveArea->getPositionY() + (distance - (float) System::random(distance * 2));
		height = zone->getHeight(newX, newY);

		position.set(newX, height, newY);

		++tries;

		//Increase distance every if 32 tries failed.
		if (tries % 32 == 0) {
			distance = distance * 2;
		}
	}

	if (tries == 128) {
		//Failed to find a spawn point for the lair, fail mission.
		getPlayerOwner().get()->sendSystemMessage("@mission/mission_generic:failed");
		fail();
	}

	//info("found with tries " + String::valueOf(tries), true);

	return position;
}

void DestroyMissionObjectiveImplementation::spawnLair() {
	Locker _lock(_this.get());

	ManagedReference<MissionObject* > mission = this->mission.get();

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea == NULL)
		return;

	if (lairObject != NULL && lairObject->getZone() != NULL)
		return;

	Zone* zone = spawnActiveArea->getZone();

	Locker locker(spawnActiveArea);

	spawnActiveArea->destroyObjectFromWorld(true);

	locker.release();

	Vector3 pos = findValidSpawnPosition(zone);

	ManagedReference<WaypointObject*> waypoint = mission->getWaypointToMission();

	if (waypoint == NULL) {
		Locker mlocker(mission);
		waypoint = mission->createWaypoint();
	}

	Locker wplocker(waypoint);

	waypoint->setPosition(pos.getX(), 0, pos.getY());

	wplocker.release();

	mission->updateMissionLocation();

	Locker mlocker(mission);

	mission->setStartPosition(pos.getX(), pos.getY());

	mlocker.release();

	ManagedReference<CreatureObject*> player = getPlayerOwner();

	if (player != NULL) {
		//TODO: find correct string id
		player->sendSystemMessage("Transmission Received: Mission Target has been located.  Mission waypoint has been updated to exact location");
	}

	LairTemplate* lair = CreatureTemplateManager::instance()->getLairTemplate(lairTemplate.hashCode());

	if (lair == NULL) {
		error("incorrect lair template in destroy mission objective " + lairTemplate);
		abort();
		return;
	}

	if (lairObject == NULL) {
		String buildingToSpawn = lair->getMissionBuilding(difficulty);

	 	if (buildingToSpawn.isEmpty()) {
	 		error("error spawning " + buildingToSpawn);
	 		abort();
	 		return;
	 	}

		lairObject = zone->getZoneServer()->createObject(buildingToSpawn.hashCode(), 0).castTo<LairObject*>();

	 	if (lairObject == NULL) {
	 		error("error spawning " + buildingToSpawn);
	 		abort();
	 		return;
	 	}

	 	Locker llocker(lairObject);

	 	lairObject->setFaction(lair->getFaction());
	 	lairObject->setPvpStatusBitmask(CreatureFlag::ATTACKABLE);
	 	lairObject->setOptionsBitmask(0, false);
	 	lairObject->setMaxCondition(difficultyLevel * (900 + System::random(200)));
	 	lairObject->setConditionDamage(0, false);
	 	lairObject->initializePosition(pos.getX(), pos.getZ(), pos.getY());
	 	lairObject->setDespawnOnNoPlayersInRange(false);

		ManagedReference<MissionObserver*> observer = new MissionObserver(_this.get());
		addObserver(observer, true);

		lairObject->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);

	 	ManagedReference<DestroyMissionLairObserver*> lairObserver = new DestroyMissionLairObserver();
	 	lairObserver->deploy();
	 	lairObserver->setLairTemplate(lair);
	 	lairObserver->setDifficulty(difficulty);
	 	lairObserver->setObserverType(ObserverType::LAIR);
	 	lairObserver->setSize(mission->getSize());

	 	lairObject->registerObserver(ObserverEventType::OBJECTDESTRUCTION, lairObserver);
	 	lairObject->registerObserver(ObserverEventType::DAMAGERECEIVED, lairObserver);
	 	lairObject->registerObserver(ObserverEventType::AIMESSAGE, lairObserver);
	 	lairObject->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, lairObserver);

		zone->transferObject(lairObject, -1, true);

		lairObserver->checkForNewSpawns(lairObject, NULL, true);
	}

	if (lairObject != NULL && lairObject->getZone() == NULL) {
		Locker llocker(lairObject);

		zone->transferObject(lairObject, -1, true);
	}
}

void DestroyMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	if (hasObservers()) {
		ManagedReference<MissionObserver*> observer = getObserver(0);

		ManagedReference<CreatureObject*> player = getPlayerOwner();

		ManagedReference<LairObject*> lair = lairObject;

		if (lair != NULL) {
			Locker locker(lair);

			lair->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
			lair->destroyObjectFromWorld(true);

			lair = NULL;

			dropObserver(observer, true);
		}
			//spawnActiveArea->destroyObjectFromDatabase(true);
	}

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea != NULL) {
		Locker locker(spawnActiveArea);

		spawnActiveArea->destroyObjectFromWorld(true);
	}
}

void DestroyMissionObjectiveImplementation::complete() {

	MissionObjectiveImplementation::complete();
}

int DestroyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {

		complete();
	}

	return 1;
}

Vector3 DestroyMissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;

	missionEndPoint.setX(mission->getStartPositionX());
	missionEndPoint.setY(mission->getStartPositionY());

	Zone* zone = getPlayerOwner().get()->getZone();

	if (zone != NULL) {
		missionEndPoint.setZ(zone->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));
	}

	return missionEndPoint;
}
