/*
 * SpawnAreaImplementation.cpp
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#include "server/zone/objects/region/SpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
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

#ifdef DEBUG_SPAWNING
	info(true) << getAreaName() << " --SpawnAreaImplementation::notifyPositionUpdate called ";
#endif // DEBUG_SPAWNING

	if (lastSpawn.miliDifference() < MINSPAWNINTERVAL)
		return;

	tryToSpawn(sceneObject);
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

	if (numberOfPlayersInRange < 0) {
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

// This should return a random position inside the Area
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

	bool positionFound = false;
	int retries = 10;

	const auto worldPosition = player->getWorldPosition();

	while (!positionFound && retries-- > 0) {
		#ifdef DEBUG_SPAWNING
			info(true) << "getRandomPosition -- using area shape";
#endif // DEBUG_SPAWNING

		position = areaShape->getRandomPosition(worldPosition, 64.0f, ZoneServer::CLOSEOBJECTRANGE);

		positionFound = true;

		for (int i = 0; i < noSpawnAreas.size(); ++i) {
			auto noSpawnArea = noSpawnAreas.get(i).get();

			if (noSpawnArea != nullptr && noSpawnArea->containsPoint(position.getX(), position.getY())) {
				positionFound = false;

#ifdef DEBUG_SPAWNING
				info(true) << "getRandomPosition -- position found is no spawn area";
#endif // DEBUG_SPAWNING
				break;
			}
		}
	}

	if (!positionFound) {
		position.set(0, 0, 0);
	}

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

			area->setRadius(64);
			area->addAreaFlag(ActiveArea::NOSPAWNAREA);
			area->initializePosition(sceneO->getPositionX(), sceneO->getPositionZ(), sceneO->getPositionY());

			thisZone->transferObject(area, -1, true);

			Reference<Task*> task = new RemoveNoSpawnAreaTask(area);
			task->schedule(300000);
		}
	}

	return 1;
}

void SpawnAreaImplementation::tryToSpawn(SceneObject* object) {
	if (object == nullptr)
		return;

	#ifdef DEBUG_SPAWNING
		info(true) << "SpawnAreaImplementation::tryToSpawn for " << object->getObjectName() << " ID: " << object->getObjectID() << " Possible Spawns Size = " << possibleSpawns.size();
#endif // DEBUG_SPAWNING

	ReadLocker _readlocker(_this.getReferenceUnsafeStaticCast());

	Zone* zone = getZone();

	if (zone == nullptr) {
		warning("zone is nullptr");
		return;
	}

	if (totalSpawnCount >= maxSpawnLimit) {
#ifdef DEBUG_SPAWNING
		info(true) << "total spawn count is great than max spawn limit";
#endif // DEBUG_SPAWNING
		return;
	}

	if (lastSpawn.miliDifference() < MINSPAWNINTERVAL) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn total spawn count is greater than max spawn limit -- returning";
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

	Vector3 randomPosition = getRandomPosition(object);

	if (randomPosition.getX() == 0 && randomPosition.getY() == 0) {
		return;
	}

	if (!zone->isWithinBoundaries(randomPosition)) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn failed due to server boundaries";
#endif // DEBUG_SPAWNING
		return;
	}

	float spawnZ = zone->getHeight(randomPosition.getX(), randomPosition.getY());

	randomPosition.setZ(spawnZ);

	// Check the spot to see if spawning is allowed
	if (!planetManager->isSpawningPermittedAt(randomPosition.getX(), randomPosition.getY(), finalSpawn->getSize() + 64.f)) {
#ifdef DEBUG_SPAWNING
		info(true) << "tryToSpawn Spawning is not permitted at " << randomPosition.toString();
#endif // DEBUG_SPAWNING
		return;
	}

	int spawnLimit = finalSpawn->getSpawnLimit();

	String lairTemplate = finalSpawn->getLairTemplateName();
	uint32 lairHashCode = lairTemplate.hashCode();

	int currentSpawnCount = spawnCountByType.get(lairHashCode);

	if (spawnLimit != -1) {
		if (currentSpawnCount >= spawnLimit)
			return;
	}

	int maxDiff = finalSpawn->getMaxDifficulty();
	int minDiff = finalSpawn->getMinDifficulty();
	int difficultyLevel = System::random(maxDiff - minDiff) + minDiff;
	int difficulty = (float)(difficultyLevel - minDiff) / ((maxDiff > (minDiff + 5) ? (float)(maxDiff - minDiff) : 5.f) / 5.f);

	if (difficulty >= 5)
		difficulty = 4;

	_readlocker.release();

	CreatureManager* creatureManager = zone->getCreatureManager();

	ManagedReference<SceneObject*> obj = creatureManager->spawn(lairHashCode, difficultyLevel, difficulty, randomPosition.getX(), spawnZ, randomPosition.getY(), finalSpawn->getSize());

	if (obj != nullptr) {
#ifdef DEBUG_SPAWNING
		info(true) << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
#endif // DEBUG_SPAWNING
	} else {
		error("could not spawn lair " + lairTemplate);

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
