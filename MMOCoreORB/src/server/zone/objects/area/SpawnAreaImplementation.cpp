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

	TangibleObject* tano = dynamic_cast<TangibleObject*>(observable);

	if (tano == NULL)
		return 1;

	Locker locker(_this.get());

	uint32 lairTemplate = lairTypes.remove(tano->getObjectID());

	if (lairTemplate != 0) {
		int currentSpawnCount = spawnedGroupsCount.get(lairTemplate) - 1;

		if (currentSpawnCount < 1)
			spawnedGroupsCount.remove(lairTemplate);
		else
			spawnedGroupsCount.put(lairTemplate, currentSpawnCount);

		--currentlySpawnedLairs;

		locker.release();

		ManagedReference<ActiveArea*> area = (ServerCore::getZoneServer()->createObject(String("object/active_area.iff").hashCode(), 0)).castTo<ActiveArea*>();

		area->setRadius(64);
		area->setNoSpawnArea(true);
		area->initializePosition(tano->getPositionX(), tano->getPositionZ(), tano->getPositionY());

		zone->transferObject(area, -1, true);

		Reference<Task*> task = new RemoveNoSpawnAreaTask(area);
		task->schedule(300000);
	}

	//info("removing spawned lair from here", true);

	return 1;
}

SpawnGroup* SpawnAreaImplementation::getSpawnGroup() {
	if (spawnGroup == NULL && spawnGroupTemplateCRC != 0)
		spawnGroup = CreatureTemplateManager::instance()->getSpawnGroup(spawnGroupTemplateCRC);

	return spawnGroup;
}

void SpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isPlayerCreature())
		return;

	ManagedReference<SceneObject*> parent = object->getParent();

	if (parent != NULL && parent->isCellObject())
		return;

	if (object->getCityRegion() != NULL)
		return;

	trySpawnLair(object);
}

void SpawnAreaImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	CreatureObject* creature = dynamic_cast<CreatureObject*>(obj);

	if (creature == NULL)
		return;

	if (!creature->isPlayerCreature())
		return;

	ManagedReference<SceneObject*> parent = creature->getParent();

	if (parent != NULL && parent->isCellObject())
		return;

	if (System::random(25) == 1)
		trySpawnLair(creature);
}

void SpawnAreaImplementation::notifyExit(SceneObject* object) {

}

int SpawnAreaImplementation::trySpawnLair(SceneObject* object) {
	if (spawnGroup == NULL && spawnGroupTemplateCRC != 0)
		spawnGroup = CreatureTemplateManager::instance()->getSpawnGroup(spawnGroupTemplateCRC);

	if (spawnGroup == NULL) {
		error("spawnGroup is NULL");
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

	if (currentlySpawnedLairs >= spawnGroup->getMaxSpawnLimit())
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
	if (CollisionManager::checkSphereCollision(randomPosition, 64.f + finalSpawn->getSize(), zone))
		return 7;

	//dont spawn in cities
	SortedVector<ManagedReference<ActiveArea* > > activeAreas;
	zone->getInRangeActiveAreas(randomPosition.getX(), randomPosition.getY(), &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area->isRegion() || area->isMunicipalZone() || area->isNoSpawnArea())
			return 8;
	}

	//check in range objects for no build radi
	if (!planetManager->isBuildingPermittedAt(randomPosition.getX(), randomPosition.getY(), object, finalSpawn->getSize())) {
		return 9;
	}

	// Only spawn on relatively flat land
	if (planetManager->getTerrainManager()->getHighestHeightDifference(randomPosition.getX() - 10, randomPosition.getY() - 10, randomPosition.getX() + 10, randomPosition.getY() + 10) > 10.0) {
		return 13;
	}

	int spawnLimit = finalSpawn->getSpawnLimit();

	Locker _locker(_this.get());

	lastSpawn.updateToCurrentTime();

	String lairTemplate = finalSpawn->getLairTemplateName();
	uint32 lairHashCode = lairTemplate.hashCode();

	int currentSpawnCount = spawnedGroupsCount.get(lairHashCode);

	if (spawnLimit != -1) {
		if (currentSpawnCount >= spawnLimit)
			return 10;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	int difficulty = System::random(finalSpawn->getMaxDifficulty() - finalSpawn->getMinDifficulty()) + finalSpawn->getMinDifficulty();

	ManagedReference<SceneObject*> obj = creatureManager->spawnLair(lairHashCode, difficulty, randomPosition.getX(), spawnZ, randomPosition.getY(), 0, finalSpawn->getSize());

	if (obj != NULL) {
		StringBuffer msg;
		msg << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
		obj->info(msg.toString());
	} else {
		error("could not spawn lair " + lairTemplate);

		return 11;
	}

	if (exitObserver == NULL) {
		exitObserver = new SpawnAreaObserver(_this.get());
		exitObserver->deploy();
	}

	lairTypes.put(obj->getObjectID(), lairHashCode);

	Locker objLocker(obj);

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, exitObserver);

	++currentlySpawnedLairs;

	spawnedGroupsCount.put(lairTemplate.hashCode(), currentSpawnCount);

	return 0;
}
