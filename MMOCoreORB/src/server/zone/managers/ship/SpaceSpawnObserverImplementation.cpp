/*
 * SpaceSpawnObserverImplementation.cpp
 *
 * Created on: 2024-09-17
 * Author: Hakry
 */

#include "server/zone/managers/ship/SpaceSpawnObserver.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

// #define DEBUG_SPACE_SPAWN_OBS

int SpaceSpawnObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTREMOVEDFROMZONE) {
#ifdef DEBUG_SPACE_SPAWN_OBS
		info(true) << "SpaceSpawnObserverImplementation::notifyObserverEvent -- OBJECTREMOVEDFROMZONE";
#endif // DEBUG_SPACE_SPAWN_OBS

		despawnSpawns();
		return 1;
	} else if (eventType != ObserverEventType::SHIPAGENTDESPAWNED) {
		return 0;
	}

	Reference<SceneObject*> spaceSpawn = cast<SceneObject*>(observable);

	if (spaceSpawn == nullptr) {
		return 1;
	}

	auto shipAgent = cast<ShipAiAgent*>(arg1);

	if (shipAgent == nullptr) {
		return 0;
	}

	Locker lock(&spawnMutex);

#ifdef DEBUG_SPACE_SPAWN_OBS
	info(true) << "SpaceSpawnObserverImplementation::notifyObserverEvent -- SHIPAGENTDESPAWNED for - " << shipAgent->getDisplayedName() << " ID: " << shipAgent->getObjectID();
#endif // DEBUG_SPACE_SPAWN_OBS

	spawnedShipAgents.drop(shipAgent);

	// TODO: Spawn new agents here until max number is reached



	// Despawn SpaceSpace
	if (spawnedShipAgents.size() < 1) {
		Reference<SceneObject*> spaceSpawnRef = spaceSpawn;

		Core::getTaskManager()->scheduleTask([spaceSpawnRef] () {
			if (spaceSpawnRef == nullptr) {
				return;
			}

			auto zone = spaceSpawnRef->getZone();

			if (zone == nullptr) {
				return;
			}

			Locker locker(spaceSpawnRef);

			spaceSpawnRef->destroyObjectFromWorld(true);

			// spaceSpawnRef->info(true) << "SpaceSpawnRef has been destroyed from world";
		}, "DestroySpaceSpawnLambda", 1000);

		return 1;
	}

	return 0;
}

void SpaceSpawnObserverImplementation::despawnSpawns() {
	// info(true) << "SpaceSpawnObserverImplementation::despawnSpawns() - All observer spawns should be despawning";

	Locker lock(&spawnMutex);

	// Iterate the spawned ship agents and set them to despawn with no players in range
	for (int i = spawnedShipAgents.size() - 1; i >= 0; i--) {
		ManagedReference<ShipAiAgent*> shipAgent = spawnedShipAgents.get(i).get();

		spawnedShipAgents.remove(i);

		if (shipAgent == nullptr) {
			continue;
		}

		Locker lock(shipAgent);

		// shipAgent->info(true) << "ShipAgent -- setting to despawn with no players in range 2";

		shipAgent->setDespawnOnNoPlayerInRange(true);
	}

	// Set Capital Ship to despawn
	ManagedReference<ShipAiAgent*> capitalShip = weakCapitalShip.get();

	if (capitalShip != nullptr) {
		Locker lock(capitalShip);

		capitalShip->setDespawnOnNoPlayerInRange(true);
	}
}

void SpaceSpawnObserverImplementation::addSpawnedShip(ShipAiAgent* shipAgent) {
	Locker lock(&spawnMutex);

	spawnedShipAgents.add(shipAgent);

	shipSpawnCount.increment();
}

void SpaceSpawnObserverImplementation::removeSpawnedShip(ShipAiAgent* shipAgent) {
	Locker lock(&spawnMutex);

	spawnedShipAgents.drop(shipAgent);
}