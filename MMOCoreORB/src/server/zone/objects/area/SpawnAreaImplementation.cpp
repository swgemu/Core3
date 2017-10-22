/*
 * SpawnAreaImplementation.cpp
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/SpawnGroup.h"
//#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/SpawnAreaObserver.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"
#include "server/ServerCore.h"
#include "events/RemoveNoSpawnAreaTask.h"

void SpawnAreaImplementation::buildSpawnList(Vector<uint32>* groupCRCs) {
	CreatureTemplateManager* ctm = CreatureTemplateManager::instance();

	for (int i = 0; i < groupCRCs->size(); i++) {
		SpawnGroup* group = ctm->getSpawnGroup(groupCRCs->get(i));

		Vector<Reference<LairSpawn*> >* spawnList = group->getSpawnList();

		for (int j = 0; j < spawnList->size(); j++) {
			Reference<LairSpawn*> spawn = spawnList->get(j);

			possibleSpawns.add(spawn);

			totalWeighting += spawn->getWeighting();
		}
	}
}

Vector3 SpawnAreaImplementation::getRandomPosition(SceneObject* player) {
	Vector3 position;
	bool positionFound = false;
	int retries = 10;

	const auto worldPosition = player->getWorldPosition();

	while (!positionFound && retries-- > 0) {
		position = areaShape->getRandomPosition(worldPosition, 64.0f, 256.0f);

		positionFound = true;

		for (int i = 0; i < noSpawnAreas.size(); ++i) {
			ManagedReference<SpawnArea*> noSpawnArea = noSpawnAreas.get(i).get();

			if (noSpawnArea != NULL && noSpawnArea->containsPoint(position.getX(), position.getY())) {
				positionFound = false;
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

	SceneObject* sceno = dynamic_cast<SceneObject*>(observable);

	if (sceno == NULL)
		return 1;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	uint32 lairTemplate = spawnTypes.remove(sceno->getObjectID());

	if (lairTemplate != 0) {
		int currentSpawnCount = spawnCountByType.get(lairTemplate) - 1;

		if (currentSpawnCount < 1)
			spawnCountByType.remove(lairTemplate);
		else
			spawnCountByType.put(lairTemplate, currentSpawnCount);

		--totalSpawnCount;

		locker.release();

		Zone* thisZone = getZone();

		if (sceno->isLairObject() && thisZone != NULL) {
			ManagedReference<ActiveArea*> area = (ServerCore::getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0)).castTo<ActiveArea*>();

			Locker locker(area);

			area->setRadius(64);
			area->setNoSpawnArea(true);
			area->initializePosition(sceno->getPositionX(), sceno->getPositionZ(), sceno->getPositionY());

			thisZone->transferObject(area, -1, true);

			Reference<Task*> task = new RemoveNoSpawnAreaTask(area);
			task->schedule(300000);
		}
	}

	return 1;
}

void SpawnAreaImplementation::tryToSpawn(SceneObject* object) {
	ReadLocker _readlocker(_this.getReferenceUnsafeStaticCast());

	Zone* zone = getZone();

	if (zone == NULL) {
		error("zone is NULL");
		return;
	}

	if (totalSpawnCount >= maxSpawnLimit)
		return;

	if (lastSpawn.miliDifference() < MINSPAWNINTERVAL)
		return;

	int choice = System::random(totalWeighting - 1);
	int counter = 0;

	LairSpawn* finalSpawn = NULL;

	for (int i = 0; i < possibleSpawns.size(); i++) {
		LairSpawn* spawn = possibleSpawns.get(i);

		counter += spawn->getWeighting();

		if (choice < counter) {
			finalSpawn = spawn;
			break;
		}
	}

	if (finalSpawn == NULL)
		return;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Vector3 randomPosition = getRandomPosition(object);

	if (randomPosition.getX() == 0 && randomPosition.getY() == 0) {
		return;
	}

	if (!zone->isWithinBoundaries(randomPosition)) {
		return;
	}

	float spawnZ = zone->getHeight(randomPosition.getX(), randomPosition.getY());

	randomPosition.setZ(spawnZ);

	//lets check if we intersect with some object (buildings, etc..)
	//if (CollisionManager::checkSphereCollision(randomPosition, 64.f + finalSpawn->getSize(), zone))
	//	return;

	// Check the spot to see if spawning is allowed
	if (!planetManager->isSpawningPermittedAt(randomPosition.getX(), randomPosition.getY(), finalSpawn->getSize() + 64.f)) {
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

	if (obj != NULL) {
		StringBuffer msg;
		msg << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
		obj->info(msg.toString());
	} else {
		error("could not spawn lair " + lairTemplate);

		return;
	}

	Locker _locker2(_this.getReferenceUnsafeStaticCast());

	lastSpawn.updateToCurrentTime();

	if (exitObserver == NULL) {
		exitObserver = new SpawnAreaObserver(_this.getReferenceUnsafeStaticCast());
		exitObserver->deploy();
	}

	spawnTypes.put(obj->getObjectID(), lairHashCode);

	Locker clocker(obj, _this.getReferenceUnsafeStaticCast());

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, exitObserver);

	++totalSpawnCount;

	spawnCountByType.put(lairTemplate.hashCode(), currentSpawnCount);

	return;
}
