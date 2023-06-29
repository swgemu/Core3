/*
 * SpawnAreaImplementation.cpp
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#include "server/zone/objects/region/SpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/SpawnGroup.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/SpawnAreaObserver.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"
#include "server/ServerCore.h"
#include "server/zone/objects/area/events/RemoveNoSpawnAreaTask.h"

//#define DEBUG_SPAWNING

void SpawnAreaImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	if (numberOfPlayersInRange <= 0)
		return;

	if (entry == nullptr)
		return;

	SceneObject* sceneObject = cast<SceneObject*>(entry);

	if (sceneObject == nullptr || !sceneObject->isPlayerCreature())
		return;

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != nullptr && (zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()))
		return;

	if (lastSpawn.miliDifference() < MINSPAWNINTERVAL)
		return;

#ifdef DEBUG_SPAWNING
	info(true) << getAreaName() << " --SpawnAreaImplementation::notifyPositionUpdate called";
#endif // DEBUG_SPAWNING

	CreatureObject* player = sceneObject->asCreatureObject();

	if (player == nullptr || player->isInvisible())
		return;

	tryToSpawn(player);
}

void SpawnAreaImplementation::notifyEnter(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isPlayerCreature())
		return;

	if (sceneO->isDebuggingRegions())
		sendDebugMessage(sceneO, true);

#ifdef DEBUG_SPAWNING
	info(true) << getAreaName() << " --SpawnAreaImplementation::notifyEnter for " << sceneO->getCustomObjectName();
#endif // DEBUG_SPAWNING

	numberOfPlayersInRange.increment();
}

void SpawnAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isPlayerCreature())
		return;

	if (sceneO->isDebuggingRegions())
		sendDebugMessage(sceneO, false);

#ifdef DEBUG_SPAWNING
	info(true) << getAreaName() << " --SpawnAreaImplementation::notifyExit for " << sceneO->getCustomObjectName();
#endif // DEBUG_SPAWNING

	numberOfPlayersInRange.decrement();

	if (numberOfPlayersInRange <= 0) {
		numberOfPlayersInRange.set(0);
	}
}

void SpawnAreaImplementation::buildSpawnList(Vector<uint32>* groupCRCs) {
	CreatureTemplateManager* ctm = CreatureTemplateManager::instance();

	for (int i = 0; i < groupCRCs->size(); i++) {
		SpawnGroup* group = ctm->getSpawnGroup(groupCRCs->get(i));

		const Vector<Reference<LairSpawn*> >& spawnList = group->getSpawnList();

		for (int j = 0; j < spawnList.size(); j++) {
			const auto& spawn = spawnList.get(j);

			possibleSpawns.emplace(spawn);

			totalWeighting += spawn->getWeighting();
		}
	}
}

// This will return a random position near the player within the area shape
Vector3 SpawnAreaImplementation::getRandomPosition(SceneObject* player) {
	Vector3 position;

	if (player == nullptr) {
		position.set(0, 0, 0);
		return position;
	}

#ifdef DEBUG_SPAWNING
	info(true) << getAreaName() << " -- getRandomPosition -- for Player " << player->getObjectName() << " ID: " << player->getObjectID();
	info(true) << getAreaName() << " Location = " << getPositionX() << " , " << getPositionY();
#endif // DEBUG_SPAWNING

	const auto worldPosition = player->getWorldPosition();

	position = areaShape->getRandomPosition(worldPosition, 32.0f, ZoneServer::CLOSEOBJECTRANGE);

	return position;
}

int SpawnAreaImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::OBJECTREMOVEDFROMZONE)
		return 0;

	SceneObject* sceneO = dynamic_cast<SceneObject*>(observable);

	if (sceneO == nullptr)
		return 1;

#ifdef DEBUG_SPAWNING
	info(true) << "SpawnAreaImplementation::notifyObserverEvent -- Event Type: " << eventType << " for " << sceneO->getCustomObjectName() << " ID: " << sceneO->getObjectID();
#endif // DEBUG_SPAWNING

	Locker locker(_this.getReferenceUnsafeStaticCast());

	uint32 lairTemplate = spawnTypes.remove(sceneO->getObjectID());

	if (lairTemplate != 0) {
		int currentSpawnCount = spawnCountByType.get(lairTemplate) - 1;

		if (currentSpawnCount < 1)
			spawnCountByType.remove(lairTemplate);
		else
			spawnCountByType.put(lairTemplate, currentSpawnCount);

		--totalSpawnCount;

		locker.release();

		Zone* thisZone = getZone();

		if (sceneO->isLairObject() && thisZone != nullptr) {
			ManagedReference<ActiveArea*> area = (ServerCore::getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0)).castTo<ActiveArea*>();

			Locker locker(area);

			area->setRadius(64.f);
			area->addAreaFlag(ActiveArea::NOSPAWNAREA);
			area->initializePosition(sceneO->getPositionX(), sceneO->getPositionZ(), sceneO->getPositionY());

			thisZone->transferObject(area, -1, true);

			Reference<Task*> task = new RemoveNoSpawnAreaTask(area);
			task->schedule(30000);
		}
	}

	return 1;
}

void SpawnAreaImplementation::tryToSpawn(CreatureObject* player) {
	if (player == nullptr)
		return;

#ifdef DEBUG_SPAWNING
	info(true) << "SpawnAreaImplementation::tryToSpawn for " << player->getObjectName() << " ID: " << player->getObjectID() << " Possible Spawns Size = " << possibleSpawns.size();
#endif // DEBUG_SPAWNING

	ReadLocker _readlocker(_this.getReferenceUnsafeStaticCast());

	Zone* zone = getZone();

	if (zone == nullptr) {
		return;
	}

	if (totalSpawnCount >= maxSpawnLimit) {
#ifdef DEBUG_SPAWNING
		info(true) << "total spawn count is great than max spawn limit";
#endif // DEBUG_SPAWNING
		return;
	}

	int choice = System::random(totalWeighting - 1);
	int counter = 0;

	LairSpawn* finalSpawn = nullptr;

	for (int i = 0; i < possibleSpawns.size(); i++) {
		LairSpawn* spawn = possibleSpawns.get(i);

		counter += spawn->getWeighting();

		if (choice < counter) {
			finalSpawn = spawn;
			break;
		}
	}

	if (finalSpawn == nullptr) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn Final Spawn is nullptr";
#endif // DEBUG_SPAWNING
		return;
	}

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Vector3 randomPosition = getRandomPosition(player);

	if (randomPosition.getX() == 0 && randomPosition.getY() == 0) {
		return;
	}

	// Check the spot to see if spawning is allowed
	if (!planetManager->isSpawningPermittedAt(randomPosition.getX(), randomPosition.getY(), finalSpawn->getSize() + 64.f, isWorldSpawnArea())) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn Spawning is not permitted at " << randomPosition.toString();
#endif // DEBUG_SPAWNING
		return;
	}

	float spawnZ = zone->getHeight(randomPosition.getX(), randomPosition.getY());
	randomPosition.setZ(spawnZ);

	int spawnLimit = finalSpawn->getSpawnLimit();

	String lairTemplate = finalSpawn->getLairTemplateName();
	uint32 lairHashCode = lairTemplate.hashCode();

	int currentSpawnCount = spawnCountByType.get(lairHashCode);

	if (spawnLimit != -1) {
		if (currentSpawnCount >= spawnLimit)
			return;
	}

	int maxDifficulty = finalSpawn->getMaxDifficulty();
	int minDifficulty = finalSpawn->getMinDifficulty();
	int playerLevel = getPlayerSpawnLevel(player);

	if (maxDifficulty == 500)
		maxDifficulty = minDifficulty + (playerLevel * 2.f);

	float difficultyLevel = (((maxDifficulty - minDifficulty) / 25.f) * playerLevel) + minDifficulty + System::random(5);

	if (difficultyLevel < minDifficulty)
		difficultyLevel = minDifficulty;

	int difficulty = (float)(difficultyLevel - minDifficulty) / ((maxDifficulty > (minDifficulty + 5) ? (float)(maxDifficulty - minDifficulty) : 5.f) / 5.f);

	if (difficulty >= 5)
		difficulty = 4;

#ifdef DEBUG_SPAWNING
	info(true) << "Player Level = " << playerLevel << " Min Difficulty = " << minDifficulty << " Max Difficulty = " << maxDifficulty << " Calculated Difficulty Level: " << difficultyLevel << " Difficulty: " << difficulty;
#endif // DEBUG_SPAWNING

	_readlocker.release();

	CreatureManager* creatureManager = zone->getCreatureManager();

	ManagedReference<SceneObject*> obj = creatureManager->spawn(lairHashCode, difficultyLevel, difficulty, randomPosition.getX(), spawnZ, randomPosition.getY(), finalSpawn->getSize());

	if (obj != nullptr) {
#ifdef DEBUG_SPAWNING
		info(true) << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
#endif // DEBUG_SPAWNING
	} else {
		error("Failed to spawn lair: " + lairTemplate);
		return;
	}

	Locker _locker2(_this.getReferenceUnsafeStaticCast());

	lastSpawn.updateToCurrentTime();

	if (spawnAreaObserver == nullptr) {
		spawnAreaObserver = new SpawnAreaObserver(_this.getReferenceUnsafeStaticCast());
		spawnAreaObserver->deploy();
	}

	spawnTypes.put(obj->getObjectID(), lairHashCode);

	Locker clocker(obj, _this.getReferenceUnsafeStaticCast());

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, spawnAreaObserver);

	++totalSpawnCount;

	spawnCountByType.put(lairTemplate.hashCode(), currentSpawnCount);

#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn Complete";
#endif // DEBUG_SPAWNING

	return;
}

int SpawnAreaImplementation::getPlayerSpawnLevel(CreatureObject* player) {
	int level = 0;

	if (player == nullptr)
		return level;

	if (player->isGrouped()) {
		GroupObject* group = player->getGroup();

		if (group != nullptr) {
			level = group->getGroupLevel();
		}
	} else {
		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer != nullptr) {
			PlayerManager* playerMan = zoneServer->getPlayerManager();

			if (playerMan != nullptr)
				level = playerMan->calculatePlayerLevel(player);
		}
	}

	return level;
}
