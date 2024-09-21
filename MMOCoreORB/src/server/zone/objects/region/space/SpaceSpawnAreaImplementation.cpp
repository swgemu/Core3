/*
 * SpaceSpawnAreaImplementation.cpp
 *
 * Created on: 09/12/2024
 * Author: Hakry
 */

#include "server/zone/objects/region/space/SpaceSpawnArea.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/region/space/SpaceSpawnAreaObserver.h"
#include "server/zone/managers/ship/SpaceSpawn.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/objects/intangible/TheaterObject.h"
#include "server/zone/managers/ship/SpaceSpawnObserver.h"

#define DEBUG_SPACE_AREAS
// #define DEBUG_SPACE_SPAWNING

void SpaceSpawnAreaImplementation::notifyPositionUpdate(TreeEntry* entry) {
	if (numberOfPlayerShipsInRange <= 0 || entry == nullptr) {
		return;
	}

	SceneObject* sceneObject = cast<SceneObject*>(entry);

	if (sceneObject == nullptr || !sceneObject->isShipObject() || sceneObject->isShipAiAgent()) {
		return;
	}

	// Spawn limit has been reached
	if (totalSpawnCount >= maxSpawnLimit) {
#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "Total Spawn Count Reached for - " << getAreaName() << " Max Limit: " <<  maxSpawnLimit << " Total Spawn Count: " << totalSpawnCount << " Trigger Ship: " << sceneObject->getDisplayedName();
#endif // DEBUG_SPACE_SPAWNING
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer != nullptr && (zoneServer->isServerLoading() || zoneServer->isServerShuttingDown())) {
		return;
	}

	if (lastSpawn.miliDifference() < ConfigManager::instance()->getMinSpaceSpawnInterval()) {
		return;
	}

	if (ConfigManager::instance()->disableSpaceSpawns()) {
		return;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " --SpaceSpawnAreaImplementation::notifyPositionUpdate called";
#endif // DEBUG_SPACE_SPAWNING

	auto playerShip = sceneObject->asShipObject();

	if (playerShip == nullptr || playerShip->isInvisible()) {
		return;
	}

	tryToSpawn(playerShip);
}

void SpaceSpawnAreaImplementation::notifyEnter(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject() || sceneO->isShipAiAgent()) {
		return;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " -- SpaceSpawnAreaImplementation::notifyEnter for " << sceneO->getDisplayedName();
#endif // DEBUG_SPACE_SPAWNING

#ifdef DEBUG_SPACE_AREAS
	auto entryShip = sceneO->asShipObject();

	if (entryShip != nullptr) {
		StringBuffer msg;
		msg << "notifyEnter - SpaceSpawnAreaImplementation: " << getAreaName() << " Location: " << getAreaCenter().toString();
		entryShip->sendShipMembersMessage(msg.toString());
	}
#endif

	numberOfPlayerShipsInRange.increment();
}

void SpaceSpawnAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject() || sceneO->isShipAiAgent()) {
		return;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " --SpaceSpawnAreaImplementation::notifyExit for " << sceneO->getDisplayedName();
#endif // DEBUG_SPACE_SPAWNING

#ifdef DEBUG_SPACE_AREAS
	auto entryShip = sceneO->asShipObject();

	if (entryShip != nullptr) {
		StringBuffer msg;
		msg << "notifyExit - SpaceSpawnAreaImplementation: " << getAreaName() << " Location: " << getAreaCenter().toString();
		entryShip->sendShipMembersMessage(msg.toString());
	}
#endif

	numberOfPlayerShipsInRange.decrement();

	if (numberOfPlayerShipsInRange <= 0) {
		numberOfPlayerShipsInRange.set(0);
	}
}

int SpaceSpawnAreaImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::OBJECTREMOVEDFROMZONE) {
		return 0;
	}

	SceneObject* sceneO = dynamic_cast<SceneObject*>(observable);

	if (sceneO == nullptr) {
		return 1;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "SpaceSpawnAreaImplementation::notifyObserverEvent -- Event Type: " << eventType << " for " << sceneO->getCustomObjectName() << " ID: " << sceneO->getObjectID();
#endif // DEBUG_SPACE_SPAWNING

	Locker locker(_this.getReferenceUnsafeStaticCast());

	totalSpawnCount--;

	return 1;
}

void SpaceSpawnAreaImplementation::tryToSpawn(ShipObject* playerShip) {
	if (playerShip == nullptr) {
		return;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "SpaceSpawnAreaImplementation::tryToSpawn for " << playerShip->getDisplayedName() << " ID: " << playerShip->getObjectID();
#endif // DEBUG_SPACE_SPAWNING

	ReadLocker _readlocker(_this.getReferenceUnsafeStaticCast());

	auto zone = getZone();

	if (zone == nullptr) {
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto spaceManager = zone->getSpaceManager();

	if (spaceManager == nullptr) {
		return;
	}

	// Update lastSpawn time
	lastSpawn.updateToCurrentTime();

	int weightingRoll = System::random(totalWeighting - 1);
	int counter = 0;

	SpaceSpawn* finalSpawn = nullptr;

	for (int i = 0; i < possibleSpawns.size(); i++) {
		SpaceSpawn* spawn = possibleSpawns.get(i);

		counter += spawn->getWeighting();

		if (weightingRoll < counter) {
			finalSpawn = spawn;
			break;
		}
	}

	if (finalSpawn == nullptr) {
#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "tryToSpawn -- finalSpawn is a nullptr. weightingRoll: " << weightingRoll << " Counter: " << counter;
#endif // DEBUG_SPACE_SPAWNING
		return;
	}

	// Create observer for the area if it does not exist
	if (spawnAreaObserver == nullptr) {
		spawnAreaObserver = new SpaceSpawnAreaObserver(_this.getReferenceUnsafeStaticCast());
		spawnAreaObserver->deploy();
	}

	// Get a random position within the spawn area
	Vector3 position = getRandomPosition();

	// Create the theater
	Reference<TheaterObject*> theater = zoneServer->createObject(STRING_HASHCODE("object/intangible/theater/base_theater.iff"), 0).castTo<TheaterObject*>();
	ManagedReference<SpaceSpawnObserver*> spaceObserver = new SpaceSpawnObserver();

	if (theater == nullptr || spaceObserver == nullptr) {
		error() << "error creating intangible theater or SpaceObserver";
		return;
	}

	Locker theaterLocker(theater);

	theater->initializePosition(position.getX(), position.getZ(), position.getY());
	theater->setDespawnOnNoPlayersInRange(true);

	// Register the observer for the SpaceSpawnArea so it can keep count of current spawns
	theater->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, spawnAreaObserver);

	// Setup the SpaceSpawnObserver
	spaceObserver->deploy();

	spaceObserver->setObserverType(ObserverType::SPACE_SPAWN);
	spaceObserver->setSize(512.f);

	theater->registerObserver(ObserverEventType::SHIPAGENTDESPAWNED, spaceObserver);
	theater->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, spaceObserver);

	zone->transferObject(theater, -1, true);

	// Release the lock on the theater
	theaterLocker.release();

	// Get the total amount of ships to spawn
	int numberToSpawn = finalSpawn->getNumberToSpawn();

	uint32 capitalShipCRC = finalSpawn->getCapitalShipCRC();

	// Spawn the Capital Ship
	ManagedReference<SceneObject*> capitalShip = spaceManager->spaceDynamicSpawn(capitalShipCRC, zone, position, theater);

	if (capitalShip != nullptr) {
#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "captial ship is not nullptr";
#endif // DEBUG_SPACE_SPAWNING

		spaceObserver->setCapitalShip(capitalShip->asShipAiAgent());
	}

	// First spawn the lead ship
	const auto randomLeadShip = finalSpawn->getRandomLeadShip();

	// Spawn lead ShipAiAgent
	ManagedReference<SceneObject*> leadShip = spaceManager->spaceDynamicSpawn(randomLeadShip, zone, position, theater);

	if (leadShip != nullptr) {
		spaceObserver->addSpawnedShip(leadShip->asShipAiAgent());

		numberToSpawn--;
	}

	while (numberToSpawn > 0) {
		// Get a random group ship
		const auto randomGroupShip = finalSpawn->getRandomGroupShip();

		// Spawn lead ShipAiAgent
		ManagedReference<SceneObject*> groupShip = spaceManager->spaceDynamicSpawn(randomGroupShip, zone, position, theater);

		if (groupShip != nullptr) {
			spaceObserver->addSpawnedShip(groupShip->asShipAiAgent());
		}

		// Decrease amount to spawn
		numberToSpawn--;
	}

	// Increase Spawn Count
	totalSpawnCount++;

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "A new ship lair has spawned!";
#endif // DEBUG_SPACE_SPAWNING
}

int SpaceSpawnAreaImplementation::getShipSpawnLevel(ShipObject* playerShip) {
	int level = 1;


	return level;
}

// This will return a random position within the area shape
Vector3 SpaceSpawnAreaImplementation::getRandomPosition() {
	Vector3 position = areaShape->getRandomPosition(getWorldPosition(), 256.f, ZoneServer::SPACEOBJECTRANGE);

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " -- getRandomPosition --  Location = " << position.toString();
#endif // DEBUG_SPACE_SPAWNING

	return position;
}

void SpaceSpawnAreaImplementation::buildSpawnList(Vector<uint32>* groupCRCs) {
	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "buildSpawnList from " << groupCRCs->size() << " total groups";
#endif // DEBUG_SPACE_SPAWNING

	for (int i = 0; i < groupCRCs->size(); i++) {
		SpaceSpawnGroup* group = shipManager->getSpaceSpawnGroup(groupCRCs->get(i));

		if (group == nullptr) {
			continue;
		}

		const Vector<Reference<SpaceSpawn*> >& spawnList = group->getSpawnList();

#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "Group has spawnList with a size of " << spawnList.size();
#endif // DEBUG_SPACE_SPAWNING

		for (int j = 0; j < spawnList.size(); j++) {
			const auto& spawn = spawnList.get(j);

			possibleSpawns.emplace(spawn);

			totalWeighting += spawn->getWeighting();
		}
	}
}