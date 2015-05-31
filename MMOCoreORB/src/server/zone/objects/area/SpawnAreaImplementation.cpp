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
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/SpawnAreaObserver.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"
#include "server/ServerCore.h"
#include "events/RemoveNoSpawnAreaTask.h"

Vector3 SpawnAreaImplementation::getRandomPosition(SceneObject* player) {
	Vector3 position;
	bool positionFound = false;
	int retries = 10;

	while (!positionFound && retries-- > 0) {
		position = areaShape->getRandomPosition(player->getWorldPosition(), 64.0f, 256.0f);

		positionFound = true;

		for (int i = 0; i < noSpawnAreas.size(); ++i) {
			SpawnArea* noSpawnArea = noSpawnAreas.get(i);

			if (noSpawnArea->containsPoint(position.getX(), position.getY())) {
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
		return 1;

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

		if (sceno->isLairObject()) {
			ManagedReference<ActiveArea*> area = (ServerCore::getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0)).castTo<ActiveArea*>();

			Locker locker(area);

			area->setRadius(64);
			area->setNoSpawnArea(true);
			area->initializePosition(sceno->getPositionX(), sceno->getPositionZ(), sceno->getPositionY());

			zone->transferObject(area, -1, true);

			Reference<Task*> task = new RemoveNoSpawnAreaTask(area);
			task->schedule(300000);
		}
	}

	return 1;
}

SpawnGroup* SpawnAreaImplementation::getSpawnGroup() {
	if (spawnGroup == NULL && spawnGroupTemplateCRC != 0)
		spawnGroup = CreatureTemplateManager::instance()->getSpawnGroup(spawnGroupTemplateCRC);

	return spawnGroup;
}

void SpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!(tier & SpawnAreaMap::SPAWNAREA)) {
		ActiveAreaImplementation::notifyEnter(object);
		return;
	}

	if (!object->isPlayerCreature())
		return;

	CreatureObject* creo = cast<CreatureObject*>(object);
	if (creo->isInvisible()) {
		return;
	}

	ManagedReference<SceneObject*> parent = object->getParent();

	if (parent != NULL && parent->isCellObject())
		return;

	if (object->getCityRegion() != NULL)
		return;

	ManagedReference<SpawnArea*> spawnArea = _this.getReferenceUnsafeStaticCast();
	ManagedReference<SceneObject*> obj = object;

	EXECUTE_TASK_2(spawnArea, obj, {
			spawnArea_p->tryToSpawn(obj_p);
	});

}

void SpawnAreaImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	if (!(tier & SpawnAreaMap::SPAWNAREA))
		return;

	CreatureObject* creature = dynamic_cast<CreatureObject*>(obj);

	if (creature == NULL)
		return;

	if (!creature->isPlayerCreature() || creature->isInvisible())
		return;

	ManagedReference<SceneObject*> parent = creature->getParent();

	if (parent != NULL && parent->isCellObject())
		return;

	if (System::random(25) == 1) {
		ManagedReference<SpawnArea*> spawnArea = _this.getReferenceUnsafeStaticCast();
		ManagedReference<SceneObject*> object = cast<SceneObject*>(obj);

		EXECUTE_TASK_2(spawnArea, object, {
				spawnArea_p->tryToSpawn(object_p);
		});
	}
}

void SpawnAreaImplementation::notifyExit(SceneObject* object) {
	if (!(tier & SpawnAreaMap::SPAWNAREA))
		ActiveAreaImplementation::notifyExit(object);
}

int SpawnAreaImplementation::tryToSpawn(SceneObject* object) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

	if (spawnGroup == NULL && spawnGroupTemplateCRC != 0)
		spawnGroup = CreatureTemplateManager::instance()->getSpawnGroup(spawnGroupTemplateCRC);

	if (spawnGroup == NULL) {
		error("spawnGroup is NULL (crc = " + String::valueOf(spawnGroupTemplateCRC) + ") in spawn area " + getObjectName()->getStringID() + " on planet " + (getZone() != NULL ? getZone()->getZoneName() : "NULL"));
		return 1;
	}

	Vector<Reference<LairSpawn*> >* lairs = spawnGroup->getSpawnList();

	int totalSize = lairs->size();

	if (totalSize == 0) {
		error("totalSize is NULL");
		return 2;
	}

	Zone* zone = getZone();

	if (zone == NULL) {
		error("zone is NULL");
		return 3;
	}

	if (totalSpawnCount >= maxSpawnLimit)
		return 4;

	if (lastSpawn.miliDifference() < MINSPAWNINTERVAL)
		return 5;

	//Lets choose 3 random spawns;
	LairSpawn* firstSpawn = lairs->get(System::random(totalSize - 1));
	LairSpawn* secondSpawn = lairs->get(System::random(totalSize - 1));
	LairSpawn* thirdSpawn = lairs->get(System::random(totalSize - 1));

	LairSpawn* finalSpawn = NULL;

	int totalWeights = firstSpawn->getWeighting() + secondSpawn->getWeighting() + thirdSpawn->getWeighting();

	int finalChoice = System::random(totalWeights);

	if (finalChoice <= firstSpawn->getWeighting()) {
		finalSpawn = firstSpawn;
	} else if (finalChoice <= firstSpawn->getWeighting() + secondSpawn->getWeighting()) {
		finalSpawn = secondSpawn;
	} else {
		finalSpawn = thirdSpawn;
	}

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Vector3 randomPosition = getRandomPosition(object);

	if (randomPosition.getX() == 0 && randomPosition.getY() == 0) {
		return 6;
	}

	float spawnZ = zone->getHeight(randomPosition.getX(), randomPosition.getY());

	randomPosition.setZ(spawnZ);

	//lets check if we intersect with some object (buildings, etc..)
	//if (CollisionManager::checkSphereCollision(randomPosition, 64.f + finalSpawn->getSize(), zone))
	//	return 7;

	// Check the spot to see if spawning is allowed
	if (!planetManager->isSpawningPermittedAt(randomPosition.getX(), randomPosition.getY(), finalSpawn->getSize() + 64.f)) {
		return 9;
	}

	int spawnLimit = finalSpawn->getSpawnLimit();

	lastSpawn.updateToCurrentTime();

	String lairTemplate = finalSpawn->getLairTemplateName();
	uint32 lairHashCode = lairTemplate.hashCode();

	int currentSpawnCount = spawnCountByType.get(lairHashCode);

	if (spawnLimit != -1) {
		if (currentSpawnCount >= spawnLimit)
			return 10;
	}

	int maxDiff = finalSpawn->getMaxDifficulty();
	int minDiff = finalSpawn->getMinDifficulty();
	int difficultyLevel = System::random(maxDiff - minDiff) + minDiff;
	int difficulty = (float)(difficultyLevel - minDiff) / ((maxDiff > (minDiff + 5) ? (float)(maxDiff - minDiff) : 5.f) / 5.f);

	if (difficulty >= 5)
		difficulty = 4;

	_locker.release();

	CreatureManager* creatureManager = zone->getCreatureManager();

	ManagedReference<SceneObject*> obj = creatureManager->spawn(lairHashCode, difficultyLevel, difficulty, randomPosition.getX(), spawnZ, randomPosition.getY(), finalSpawn->getSize());

	if (obj != NULL) {
		StringBuffer msg;
		msg << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
		obj->info(msg.toString());
	} else {
		error("could not spawn lair " + lairTemplate);

		return 11;
	}

	Locker _locker2(_this.getReferenceUnsafeStaticCast());

	if (exitObserver == NULL) {
		exitObserver = new SpawnAreaObserver(_this.getReferenceUnsafeStaticCast());
		exitObserver->deploy();
	}

	spawnTypes.put(obj->getObjectID(), lairHashCode);

	Locker clocker(obj, _this.getReferenceUnsafeStaticCast());

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, exitObserver);

	++totalSpawnCount;

	spawnCountByType.put(lairTemplate.hashCode(), currentSpawnCount);

	return 0;
}
