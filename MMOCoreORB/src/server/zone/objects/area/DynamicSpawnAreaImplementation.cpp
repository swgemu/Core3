/*
 * DynamicSpawnAreaImplementation.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: dannuic
 */

#include "DynamicSpawnArea.h"
#include "SpawnDynamicAreaCreatureTask.h"
#include "SpawnObserver.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/DynamicSpawnGroup.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/objects/creature/aigroup/AiGroup.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"

void DynamicSpawnAreaImplementation::registerObservers() {
	for (int i = 0; i < noSpawnAreas.size(); ++i) {
		ManagedReference<SpawnArea*> notHere = noSpawnAreas.get(i);

		ManagedReference<SpawnObserver*> enterObserver = new SpawnObserver(_this.get());
		ObjectManager::instance()->persistObject(enterObserver, 1, "spawnobservers");
		notHere->registerObserver(ObserverEventType::ENTEREDAREA, enterObserver);
		observers.put(enterObserver);

		ManagedReference<SpawnObserver*> exitObserver = new SpawnObserver(_this.get());
		ObjectManager::instance()->persistObject(exitObserver, 1, "spawnobservers");
		notHere->registerObserver(ObserverEventType::EXITEDAREA, exitObserver);
		observers.put(exitObserver);
	}
}

void DynamicSpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isCreatureObject())
		return;

	CreatureObject* player = cast<CreatureObject*>(object);

	notifyObservers(ObserverEventType::ENTEREDAREA, player, 0);
}

void DynamicSpawnAreaImplementation::notifyExit(SceneObject* object) {
	if (!object->isCreatureObject())
		return;

	CreatureObject* player = cast<CreatureObject*>(object);

	notifyObservers(ObserverEventType::EXITEDAREA, player, 0);
}

void DynamicSpawnAreaImplementation::addSpawnTask() {
	//Approximately 1 spawn in a circle with radius of 50 m.
	maxCreaturesToSpawn = areaShape->getArea() / 7500;

	spawnTask = new SpawnDynamicAreaCreatureTask(_this.get(), 60000);
	spawnTask->schedule(10000); // 10 s delay
}

void DynamicSpawnAreaImplementation::doSpawnEvent() {
	spawnCreature(spawnCreatureTemplates.get(System::random(spawnCreatureTemplates.size() - 1)));
}

void DynamicSpawnAreaImplementation::doDespawnEvent() {
	// despawn all groups, despawning individually handled in AiGroup
}

int DynamicSpawnAreaImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	CreatureObject* player = cast<CreatureObject*>(arg1);
	DynamicSpawnArea* area = cast<DynamicSpawnArea*>(observable);

	switch (eventType) {
	case ObserverEventType::ENTEREDAREA:

		break;
	case ObserverEventType::EXITEDAREA:

		break;
	default:
		return 0;
	}

	return 0;
}

Vector3 DynamicSpawnAreaImplementation::getRandomPosition() {
	Vector3 position;
	bool foundPosition = false;
	int retries = 20;

	while (!foundPosition && retries-- > 0) {
		position = areaShape->getRandomPosition();

		for (int i = 0; i < noSpawnAreas.size(); ++i) {
			if (noSpawnAreas.get(i)->containsPoint(position.getX(), position.getY())) {
				continue;
			}
		}
		foundPosition = true;
	}

	if (!foundPosition) {
		position.set(0, 0, 0);
	}

	return position;
}

int DynamicSpawnAreaImplementation::getNumberOfSpawnsToGenerate() {
	return MIN(MAX((maxCreaturesToSpawn - spawnedGroups.size()) / 10, 1), maxCreaturesToSpawn - spawnedGroups.size());
}

void DynamicSpawnAreaImplementation::spawnCreature(uint32 templateCRC) {
	int numberOfSpawnsToGenerate = getNumberOfSpawnsToGenerate();

	while(numberOfSpawnsToGenerate-- > 0) {
		DynamicSpawnGroup* templ = CreatureTemplateManager::instance()->getDynamicGroup(templateCRC);

		uint32 crc;
		switch (templ->getType()) {
		case CreatureFlag::HERD:
			crc = String("object/aigroup/herd_group.iff").hashCode();
			break;
		case CreatureFlag::PACK:
			crc = String("object/aigroup/pack_group.iff").hashCode();
			break;
		case CreatureFlag::LAIR:
			crc = String("object/aigroup/lair_group.iff").hashCode();
			break;
		default:
			crc = String("object/aigroup/ai_group.iff").hashCode();
			break;
		}

		Vector3 rOuter = getRandomPosition();

		if (rOuter.getX() != 0 || rOuter.getY() != 0) {
			ManagedReference<AiGroup*> group = dynamic_cast<AiGroup*>(getZone()->getZoneServer()->createObject(crc, 0));
			if (group == NULL)
				return;

			float x = rOuter.getX();
			float y = rOuter.getY();
			float z = getZone()->getHeight(x, y);

			group->setPosition(x, z, y);

			group->info("Spawn at " + rOuter.toString(), true);

			//group->insertToZone(getZone());
			getZone()->transferObject(group, -1, true);

			group->setup(templ);

			spawnedGroups.put(group);
		}
	}
}
