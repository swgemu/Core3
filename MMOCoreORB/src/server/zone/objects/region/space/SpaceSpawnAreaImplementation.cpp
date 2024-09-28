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
#include "server/zone/objects/tangible/space/content_infrastructure/SpaceSpawner.h"
#include "server/zone/managers/ship/SpaceSpawnObserver.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"
#include "server/zone/objects/area/events/RemoveNoSpawnAreaTask.h"

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

	if (sceneO == nullptr || !sceneO->isSpaceSpawner()) {
		return 1;
	}

#ifdef DEBUG_SPACE_SPAWNING
	info(true) << "SpaceSpawnAreaImplementation::notifyObserverEvent -- Event Type: " << eventType << " for " << sceneO->getCustomObjectName() << " ID: " << sceneO->getObjectID();
#endif // DEBUG_SPACE_SPAWNING

	Locker locker(_this.getReferenceUnsafeStaticCast());

	// Update Spawn Count
	totalSpawnCount--;

	// Destroy the spawner
	ManagedReference<SpaceSpawner*> spaceSpawner = cast<SpaceSpawner*>(sceneO);

	if (spaceSpawner == nullptr) {
		return 1;
	}

	auto spaceActiveArea = spaceSpawner->getSpaceActiveArea().get();

	if (spaceActiveArea != nullptr) {
		auto removeTask = new RemoveNoSpawnAreaTask(spaceActiveArea);

		if (removeTask != nullptr) {
			removeTask->schedule(60000);
		}
	}

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

	String spawnGroupName = finalSpawn->getShipSpawnGroupName();
	uint32 nameHash = spawnGroupName.hashCode();

	int spawnLimit = finalSpawn->getSpawnLimit();
	int currentSpawnCount = spawnCountByType.get(nameHash);

	// Make sure spawn area limit has not been reached
	if (spawnLimit > -1 && currentSpawnCount >= spawnLimit) {
#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "tryToSpawn -- Spawn Limit Reached - spawnLimit: " << spawnLimit << " currentSpawnCount: " << currentSpawnCount;
#endif // DEBUG_SPACE_SPAWNING
		return;
	}

	float checkRange = SpaceSpawnArea::SPAWN_SPAWN_SIZE + ConfigManager::instance()->getSpaceSpawnCheckRange();

	// Get a random position within the spawn area
	Vector3 position = getRandomPosition();

	// Check the spot to see if spawning is allowed
	if (!spaceManager->isSpawningPermittedAt(position.getX(), position.getZ(), position.getY(), checkRange)) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn Spawning is not permitted at " << position.toString();
#endif // DEBUG_SPAWNING
		return;
	}

	// Create observer for the area if it does not exist
	if (spawnAreaObserver == nullptr) {
		spawnAreaObserver = new SpaceSpawnAreaObserver(_this.getReferenceUnsafeStaticCast());
		spawnAreaObserver->deploy();
	}

	// Create the SpaceSpawner
	Reference<SpaceSpawner*> spaceSpawner = zoneServer->createObject(STRING_HASHCODE("object/tangible/space/content_infrastructure/basic_spawner.iff"), 0).castTo<SpaceSpawner*>();
	ManagedReference<SpaceSpawnObserver*> spaceObserver = new SpaceSpawnObserver();

	if (spaceSpawner == nullptr || spaceObserver == nullptr) {
		error() << "error creating intangible spaceSpawner or SpaceObserver";
		return;
	}

	Locker spawnerLocker(spaceSpawner);

	spaceSpawner->initializePosition(position.getX(), position.getZ(), position.getY());
	spaceSpawner->setDespawnOnNoPlayersInRange(true);

	// Register the observer for the SpaceSpawnArea so it can keep count of current spawns
	spaceSpawner->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, spawnAreaObserver);

	Locker obsClock(spaceObserver, spaceSpawner);

	// Setup the SpaceSpawnObserver
	spaceObserver->deploy();

	spaceObserver->setObserverType(ObserverType::SPACE_SPAWN);
	spaceObserver->setSize(SpaceSpawnArea::SPAWN_SPAWN_SIZE);

	spaceSpawner->registerObserver(ObserverEventType::SHIPAGENTDESPAWNED, spaceObserver);
	spaceSpawner->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, spaceObserver);

	obsClock.release();

	zone->transferObject(spaceSpawner, -1, true);

	ManagedReference<SpaceActiveArea*> spaceArea = (zoneServer->createObject(STRING_HASHCODE("object/space_active_area.iff"), 0)).castTo<SpaceActiveArea*>();
	ManagedReference<SphereAreaShape*> sphereAreaShape = new SphereAreaShape();

	if (spaceArea != nullptr && sphereAreaShape != nullptr) {
		Locker areaClock(spaceArea, spaceSpawner);

		spaceArea->setRadius(SpaceSpawnArea::SPAWN_SPAWN_SIZE);
		spaceArea->addAreaFlag(ActiveArea::NOSPAWNAREA);

		spaceArea->initializePosition(position.getX(), position.getZ(), position.getY());

		// Lock the shape for mutation
		Locker shapeLocker(sphereAreaShape, spaceSpawner);

		sphereAreaShape->setAreaCenter(position.getX(), position.getZ(), position.getY());
		sphereAreaShape->setRadius(radius);

		shapeLocker.release();

		spaceArea->setAreaShape(sphereAreaShape);

		zone->transferObject(spaceArea, -1, true);

		spaceSpawner->setSpaceArea(spaceArea);
	}

	// Release the lock on the spaceSpawner
	spawnerLocker.release();

	// Get the total amount of ships to spawn
	int numberToSpawn = finalSpawn->getNumberToSpawn();

	uint32 capitalShipCRC = finalSpawn->getCapitalShipCRC();

	// Spawn the Capital Ship
	ManagedReference<SceneObject*> capitalShip = spaceManager->spaceDynamicSpawn(capitalShipCRC, zone, position, spaceSpawner);

	if (capitalShip != nullptr) {
#ifdef DEBUG_SPACE_SPAWNING
		info(true) << "captial ship is not nullptr";
#endif // DEBUG_SPACE_SPAWNING

		spaceObserver->setCapitalShip(capitalShip->asShipAiAgent());
	}

	// First spawn the lead ship
	const auto randomLeadShip = finalSpawn->getRandomLeadShip();

	// Spawn lead ShipAiAgent
	ManagedReference<SceneObject*> leadShip = spaceManager->spaceDynamicSpawn(randomLeadShip, zone, position, spaceSpawner);

	if (leadShip != nullptr) {
		spaceObserver->addSpawnedShip(leadShip->asShipAiAgent());

		numberToSpawn--;
	}

	while (numberToSpawn > 0) {
		// Get a random group ship
		const auto randomGroupShip = finalSpawn->getRandomGroupShip();

		// Spawn lead ShipAiAgent
		ManagedReference<SceneObject*> groupShip = spaceManager->spaceDynamicSpawn(randomGroupShip, zone, position, spaceSpawner);

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
