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
#include "SpawnObserver.h"

void LairSpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isPlayerCreature())
		return;

	if (spawnGroup == NULL && spawnCreatureTemplates.size() != 0) {
		uint32 templateGroupCRC = spawnCreatureTemplates.get(0);

		spawnGroup = CreatureTemplateManager::instance()->getLairGroup(templateGroupCRC);
	}

	if (spawnGroup == NULL) {
		error("spawnGroup is NULL");
		return;
	}

	Vector<Reference<LairSpawn*> >* lairs = spawnGroup->getLairList();

	int totalSize = lairs->size();

	if (totalSize == 0) {
		error("totalSize is NULL");
		return;
	}

	if (getZone() == NULL) {
		error("zone is NULL");
		return;
	}

	if (currentlySpawnedLairs >= spawnGroup->getMaxSpawnLimit())
		return;

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

	Locker _locker(_this);

	String lairTemplate = finalSpawn->getLairTemplateName();
	uint32 lairHashCode = lairTemplate.hashCode();

	int currentSpawnCount = spawnedGroupsCount.get(lairHashCode);

	if (spawnLimit != -1) {
		if (currentSpawnCount >= spawnLimit)
			return;
	}


	Vector3 randomPosition = getRandomPosition(object);

	float spawnZ = getZone()->getHeight(randomPosition.getX(), randomPosition.getY());

	CreatureManager* creatureManager = getZone()->getCreatureManager();

	ManagedReference<SceneObject*> obj = creatureManager->spawnLair(lairHashCode, randomPosition.getX(), spawnZ, randomPosition.getY());

	if (obj != NULL)
		obj->info("lair spawned");
	else {
		error("could not spawn lair");

		return;
	}

	if (exitObserver == NULL) {
		exitObserver = new SpawnObserver(_this);
		exitObserver->deploy();
	}

	lairTypes.put(obj->getObjectID(), lairHashCode);

	Locker objLocker(obj);

	obj->registerObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, exitObserver);

	++currentlySpawnedLairs;

	spawnedGroupsCount.put(lairTemplate.hashCode(), currentSpawnCount);
}

int LairSpawnAreaImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::OBJECTREMOVEDFROMZONE)
		return 1;

	TangibleObject* tano = dynamic_cast<TangibleObject*>(observable);

	if (tano == NULL)
		return 1;

	Locker locker(_this);

	uint32 lairTemplate = lairTypes.remove(tano->getObjectID());
	int currentSpawnCount = spawnedGroupsCount.get(lairTemplate) - 1;

	if (currentSpawnCount < 1)
		spawnedGroupsCount.remove(lairTemplate);
	else
		spawnedGroupsCount.put(lairTemplate, currentSpawnCount);

	--currentlySpawnedLairs;

	//info("removing spawned lair from here", true);

	return 1;
}

void LairSpawnAreaImplementation::notifyExit(SceneObject* object) {

}
