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
		info(true) << "Total Spawn Count Reached for - " << getAreaName() << " Max Limit: " <<  maxSpawnLimit << " Total Spawn Count: " << totalSpawnCount;
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

	if (sceneO->isDebuggingRegions()) {
		sendDebugMessage(sceneO, true);
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " -- SpaceSpawnAreaImplementation::notifyEnter for " << sceneO->getCustomObjectName();
#endif // DEBUG_SPACE_SPAWNING

	numberOfPlayerShipsInRange.increment();
}

void SpaceSpawnAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject() || sceneO->isShipAiAgent()) {
		return;
	}

	if (sceneO->isDebuggingRegions()) {
		sendDebugMessage(sceneO, true);
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << getAreaName() << " --SpaceSpawnAreaImplementation::notifyExit for " << sceneO->getCustomObjectName();
#endif // DEBUG_SPACE_SPAWNING

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

	// Update lastSpawn time
	lastSpawn.updateToCurrentTime();

	// Temporary TODO: Remove
	Vector<String> tempShips = {"object/ship/freighterlight_tier1.iff", "object/ship/z95_tier1.iff", "object/ship/yt1300_tier1.iff", "object/ship/sorosuub_space_yacht.iff", "object/ship/merchant_cruiser_light_tier1.iff"};
	String templateToSpawn = tempShips.get(System::random(tempShips.size() - 1));


	// Spawn ShipAiAgent
	ManagedReference<ShipAiAgent*> shipAgent = ShipManager::instance()->createAiShip(templateToSpawn);

	if (shipAgent == nullptr) {
		error() << "Failed to spawn AI Ship - invalid ship agent template: " << templateToSpawn;
		return;
	}

	Locker lock(shipAgent);

	if (shipAgent->getFaction() > 0) {
		//shipAgent->setFactionStatus(FactionStatus::OVERT);
	}

	Vector3 position = getRandomPosition();

	shipAgent->initializePosition(position.getX(), position.getZ(), position.getY());

	shipAgent->setHomeLocation(position.getX(), position.getZ(), position.getY(), Quaternion::IDENTITY);
	shipAgent->initializeTransform(position, Quaternion::IDENTITY);

	if (!zone->transferObject(shipAgent, -1, true)) {
		shipAgent->destroyObjectFromWorld(true);
		shipAgent->destroyObjectFromDatabase(true);

		return;
	}

	// Increase Spawn Count
	totalSpawnCount++;

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "A new ship has spawned!";
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
	info(true) << getAreaName() << " -- getRandomPosition --  Location = " << getPositionX() << " , " << getPositionY();
#endif // DEBUG_SPACE_SPAWNING

	return position;
}

void SpaceSpawnAreaImplementation::buildSpawnList(Vector<uint32>* groupCRCs) {

}