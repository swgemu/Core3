/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

*/

#include "LairSpawnArea.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/LairSpawnGroup.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "SpawnObserver.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "events/RemoveNoSpawnAreaTask.h"
#include "server/ServerCore.h"
#include "server/zone/templates/mobile/LairTemplate.h"

void LairSpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isPlayerCreature())
		return;

	ManagedReference<SceneObject*> parent = object->getParent();

	if (parent != NULL && parent->isCellObject())
		return;
		
	if (object->getCityRegion() != NULL)
		return;

	trySpawnLair(object);
}

int LairSpawnAreaImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
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

		ManagedReference<ActiveArea*> area = cast<ActiveArea*>(ServerCore::getZoneServer()->createObject(String("object/active_area.iff").hashCode(), 0));

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

LairSpawnGroup* LairSpawnAreaImplementation::getSpawnGroup() {
	if (spawnGroup == NULL && spawnCreatureTemplates.size() != 0) {
		uint32 templateGroupCRC = spawnCreatureTemplates.get(0);

		spawnGroup = CreatureTemplateManager::instance()->getLairGroup(templateGroupCRC);
	}

	return spawnGroup;
}

int LairSpawnAreaImplementation::trySpawnLair(SceneObject* object) {
	if (spawnGroup == NULL && spawnCreatureTemplates.size() != 0) {
		uint32 templateGroupCRC = spawnCreatureTemplates.get(0);

		spawnGroup = CreatureTemplateManager::instance()->getLairGroup(templateGroupCRC);
	}

	if (spawnGroup == NULL) {
		error("spawnGroup is NULL");
		return 1;
	}

	Vector<Reference<LairSpawn*> >* lairs = spawnGroup->getLairList();

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

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Vector3 randomPosition = getRandomPosition(object);

	if (randomPosition.getX() == 0 && randomPosition.getY() == 0) {
		return 6;
	}

	float spawnZ = zone->getHeight(randomPosition.getX(), randomPosition.getY());

	randomPosition.setZ(spawnZ);

	//lets check if we intersect with some object (buildings, etc..)
	if (CollisionManager::checkSphereCollision(randomPosition, 64, zone))
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
	if (!planetManager->isBuildingPermittedAt(randomPosition.getX(), randomPosition.getY(), object)) {
		return 9;
	}

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

	LairTemplate* lair = CreatureTemplateManager::instance()->getLairTemplate(lairHashCode);

	if (lair == NULL)
		return 12;

	unsigned int faction = lair->getFaction();

	ManagedReference<SceneObject*> obj = creatureManager->spawnLair(lairHashCode, difficulty, randomPosition.getX(), spawnZ, randomPosition.getY(), faction);

	if (obj != NULL) {
		StringBuffer msg;
		msg << "lair spawned at " << obj->getPositionX() << " " << obj->getPositionY();
		obj->info(msg.toString());
	} else {
		error("could not spawn lair " + lairTemplate);

		return 11;
	}

	if (exitObserver == NULL) {
		exitObserver = new SpawnObserver(_this.get());
		exitObserver->deploy();
	}

	lairTypes.put(obj->getObjectID(), lairHashCode);

	Locker objLocker(obj);

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, exitObserver);

	++currentlySpawnedLairs;

	spawnedGroupsCount.put(lairTemplate.hashCode(), currentSpawnCount);

	return 0;
}

void LairSpawnAreaImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
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

void LairSpawnAreaImplementation::notifyExit(SceneObject* object) {

}
