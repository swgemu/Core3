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
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/MissionObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/mission/DestroyMissionLairObserver.h"

void DestroyMissionObjectiveImplementation::setLairTemplateToSpawn(const String& sp) {
	lairTemplate = sp;
}

void DestroyMissionObjectiveImplementation::destroyObjectFromDatabase() {
	MissionObjectiveImplementation::destroyObjectFromDatabase();

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea != nullptr) {
		Locker locker(spawnActiveArea);

		spawnActiveArea->destroyObjectFromWorld(true);
		spawnActiveArea->destroyObjectFromDatabase(true);

		this->spawnActiveArea = nullptr;
	}
}

void DestroyMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();
	ManagedReference<MissionObject* > mission = this->mission.get();

	if ((hasObservers() && lairObject != nullptr) || mission == nullptr) {
		return;
	}

	if (spawnActiveArea == nullptr) {
		spawnActiveArea = ( Core::lookupObject<ZoneServer>("ZoneServer")->createObject(STRING_HASHCODE("object/mission_spawn_area.iff"), 1)).castTo<MissionSpawnActiveArea*>();
		Locker alocker(spawnActiveArea);
		spawnActiveArea->setMissionObjective(_this.getReferenceUnsafeStaticCast());
	}

	if (spawnActiveArea->getZone() == nullptr) {
		String planetName = mission->getStartPlanet();

		Zone* zone = Core::lookupObject<ZoneServer>("ZoneServer")->getZone(planetName);

		if (zone == nullptr) {
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

	Locker locker(waypoint);

	waypoint->setPlanetCRC(mission->getStartPlanet().hashCode());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

Vector3 DestroyMissionObjectiveImplementation::findValidSpawnPosition(Zone* zone) {
	Vector3 position;
	ManagedReference<MissionObject*> mission = this->mission.get();

	if(mission == nullptr)
		return position;

	if (zone == nullptr)
		return position;

	float newX = spawnActiveArea->getPositionX() + (256.0f - (float) System::random(512));
	float newY = spawnActiveArea->getPositionY() + (256.0f - (float) System::random(512));

	float height = zone->isWithinBoundaries(Vector3(newX, newY, 0)) ? zone->getHeight(newX, newY) : 0;

	float waterHeight;
	PlanetManager* planetManager = zone->getPlanetManager();

	float distance = 128;
	int tries = 0;
	float size = mission->getSize();

	position.set(newX, height, newY);

	while ((!planetManager->isSpawningPermittedAt(newX, newY, size)
			|| CollisionManager::checkSphereCollision(position, size + 25.f , zone)) && tries < 256) {
		newX = spawnActiveArea->getPositionX() + (distance - (float) System::random(distance * 2));
		newY = spawnActiveArea->getPositionY() + (distance - (float) System::random(distance * 2));
		height = zone->isWithinBoundaries(Vector3(newX, newY, 0)) ? zone->getHeight(newX, newY) : 0;

		position.set(newX, height, newY);

		++tries;

		//Increase distance every if 32 tries failed.
		if (tries % 32 == 0) {
			distance = distance * 2;
		}
	}

	if (tries == 128) {
		//Failed to find a spawn point for the lair, fail mission.
		getPlayerOwner()->sendSystemMessage("@mission/mission_generic:failed");
		fail();
	}

	//info("found with tries " + String::valueOf(tries), true);

	return position;
}

void DestroyMissionObjectiveImplementation::spawnLair() {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	ManagedReference<MissionObject* > mission = this->mission.get();

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea == nullptr || mission == nullptr)
		return;

	if (lairObject != nullptr && lairObject->getZone() != nullptr)
		return;

	Zone* zone = spawnActiveArea->getZone();

	if (zone == nullptr)
		return;

	Locker locker(spawnActiveArea);

	spawnActiveArea->destroyObjectFromWorld(true);

	locker.release();

	Vector3 pos = findValidSpawnPosition(zone);

	ManagedReference<WaypointObject*> waypoint = mission->getWaypointToMission();

	Locker wplocker(waypoint);

	waypoint->setPosition(pos.getX(), 0, pos.getY());

	wplocker.release();

	mission->updateMissionLocation();

	Locker mlocker(mission);

	mission->setStartPosition(pos.getX(), pos.getY());

	mlocker.release();

	ManagedReference<CreatureObject*> player = getPlayerOwner();

	if (player != nullptr) {
		//TODO: find correct string id
		player->sendSystemMessage("Transmission Received: Mission Target has been located.  Mission waypoint has been updated to exact location");
	}

	LairTemplate* lair = CreatureTemplateManager::instance()->getLairTemplate(lairTemplate.hashCode());

	if (lair == nullptr) {
		error("incorrect lair template in destroy mission objective " + lairTemplate);
		abort();
		return;
	}

	if (lairObject == nullptr) {
		String buildingToSpawn = lair->getMissionBuilding(difficulty);

	 	if (buildingToSpawn.isEmpty()) {
	 		error("error spawning " + buildingToSpawn);
	 		abort();
	 		return;
	 	}

		lairObject = zone->getZoneServer()->createObject(buildingToSpawn.hashCode(), 0).castTo<LairObject*>();

	 	if (lairObject == nullptr) {
	 		error("error spawning " + buildingToSpawn);
	 		abort();
	 		return;
	 	}

		String lairName = lair->getName();

	 	Locker llocker(lairObject);

		lairObject->setObjectName("@lair_n:" + lairName, false);
	 	lairObject->setFaction(lair->getFaction());
	 	lairObject->setPvpStatusBitmask(CreatureFlag::ATTACKABLE);
	 	lairObject->setOptionsBitmask(0, false);
	 	lairObject->setMaxCondition(difficultyLevel * (900 + System::random(200)));
	 	lairObject->setConditionDamage(0, false);
	 	lairObject->initializePosition(pos.getX(), pos.getZ(), pos.getY());
	 	lairObject->setDespawnOnNoPlayersInRange(false);

		ManagedReference<MissionObserver*> observer = new MissionObserver(_this.getReferenceUnsafeStaticCast());
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
		lairObject->registerObserver(ObserverEventType::NOPLAYERSINRANGE, lairObserver);

		zone->transferObject(lairObject, -1, true);

		lairObserver->checkForNewSpawns(lairObject, nullptr, true);
	}

	if (lairObject != nullptr && lairObject->getZone() == nullptr) {
		Locker llocker(lairObject);

		zone->transferObject(lairObject, -1, true);
	}

	if (lairObject != nullptr) {
		lairSpawnTime.updateToCurrentTime();
	}
}

void DestroyMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	if (hasObservers()) {
		ManagedReference<MissionObserver*> observer = getObserver(0);

		ManagedReference<CreatureObject*> player = getPlayerOwner();

		ManagedReference<LairObject*> lair = lairObject;

		if (lair != nullptr) {
			Locker locker(lair);

			lair->dropObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
			lair->destroyObjectFromWorld(true);

			lair = nullptr;

			dropObserver(observer, true);
		}
			//spawnActiveArea->destroyObjectFromDatabase(true);
	}

	ManagedReference<MissionSpawnActiveArea* > spawnActiveArea = this->spawnActiveArea;

	if (spawnActiveArea != nullptr) {
		Locker locker(spawnActiveArea);

		spawnActiveArea->destroyObjectFromWorld(true);
	}
}

void DestroyMissionObjectiveImplementation::addMissionStats(TransactionLog& trx) {
	trx.addState("missionTimeLairDestroyed", lairSpawnTime.miliDifference() / 1000);
}

void DestroyMissionObjectiveImplementation::complete() {

	MissionObjectiveImplementation::complete();
}

int DestroyMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {

		complete();

		return 1;
	}

	return 0;
}

Vector3 DestroyMissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;

	if(mission == nullptr)
		return missionEndPoint;

	missionEndPoint.setX(mission->getStartPositionX());
	missionEndPoint.setY(mission->getStartPositionY());

	Zone* zone = getPlayerOwner()->getZone();

	if (zone != nullptr) {
		missionEndPoint.setZ(zone->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));
	}

	return missionEndPoint;
}
