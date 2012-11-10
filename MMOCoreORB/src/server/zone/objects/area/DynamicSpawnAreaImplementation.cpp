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

	if (!excludedPlayerOccupants.contains(player))
		playerOccupants.put(player, addSpawnTask(player));
}

void DynamicSpawnAreaImplementation::notifyExit(SceneObject* object) {
	if (!object->isCreatureObject())
		return;

	CreatureObject* player = cast<CreatureObject*>(object);

	notifyObservers(ObserverEventType::EXITEDAREA, player, 0);

	SpawnDynamicAreaCreatureTask* task = playerOccupants.get(player);
	if (task != NULL)
		task->cancel();

	playerOccupants.drop(player);
	while (excludedPlayerOccupants.contains(player))
		excludedPlayerOccupants.drop(player);
	// TODO: add despawn task if players are gone
}

SpawnDynamicAreaCreatureTask* DynamicSpawnAreaImplementation::addSpawnTask(CreatureObject* player) {
	Reference<SpawnDynamicAreaCreatureTask*> task = new SpawnDynamicAreaCreatureTask(_this.get(), player);
	task->schedule(10000 / (spawnConstant > 0 ? spawnConstant : 1)); // is 10 seconds appropriate?

	return task;
}

void DynamicSpawnAreaImplementation::doSpawnEvent(CreatureObject* player) {
	// TODO: add death rate to spawn chance
	if (excludedPlayerOccupants.contains(player))
		return;

	if (System::random(spawnConstant + 5) < spawnConstant)
		spawnCreature(spawnCreatureTemplates.get(System::random(spawnCreatureTemplates.size() - 1)), player);

	// add a spawn task
	playerOccupants.drop(player);
	playerOccupants.put(player, addSpawnTask(player));
}

void DynamicSpawnAreaImplementation::doDespawnEvent() {
	// despawn all groups, despawning individually handled in AiGroup
}

int DynamicSpawnAreaImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	CreatureObject* player = cast<CreatureObject*>(arg1);
	DynamicSpawnArea* area = cast<DynamicSpawnArea*>(observable);

	VectorMapEntry<ManagedReference<CreatureObject*>, ManagedReference<DynamicSpawnArea*> > entry(player, area);
	int pos = excludedPlayerOccupants.SortedVector<VectorMapEntry<ManagedReference<CreatureObject*>, ManagedReference<DynamicSpawnArea*> > >::find(entry);
	SpawnDynamicAreaCreatureTask* task = playerOccupants.get(player);

	switch (eventType) {
	case ObserverEventType::ENTEREDAREA:
		if (task != NULL)
			task->cancel();

		playerOccupants.drop(player);

		if (pos == -1)
			excludedPlayerOccupants.put(player, area);

		break;
	case ObserverEventType::EXITEDAREA:
		if (pos != -1)
			excludedPlayerOccupants.remove(pos);

		if (!excludedPlayerOccupants.contains(player))
			playerOccupants.put(player, addSpawnTask(player));

		break;
	default:
		return 0;
	}

	return 0;
}

void DynamicSpawnAreaImplementation::spawnCreature(uint32 templateCRC, CreatureObject* player) {
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

	Vector3 rOuter = getRandomPosition(player);

	if (rOuter.getX() != 0 || rOuter.getY() != 0) {
		ManagedReference<AiGroup*> group = dynamic_cast<AiGroup*>(getZone()->getZoneServer()->createObject(crc, 0));
		if (group == NULL)
			return;

		float x = rOuter.getX();
		float y = rOuter.getY();
		float z = getZone()->getHeight(x, y);

		group->setPosition(x, z, y);

		//group->insertToZone(getZone());
		getZone()->transferObject(group, -1, true);

		group->setup(templ);

		spawnedGroups.put(group);
	}
}
