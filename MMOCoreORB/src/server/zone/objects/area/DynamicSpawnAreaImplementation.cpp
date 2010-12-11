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
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "engine/util/ObserverEventType.h"

void DynamicSpawnAreaImplementation::registerObservers() {
	for (int i = 0; i < noSpawnAreas.size(); ++i) {
		ManagedReference<SpawnArea*> notHere = noSpawnAreas.get(i);

		ManagedReference<SpawnObserver*> enterObserver = new SpawnObserver(_this);
		ObjectManager::instance()->persistObject(enterObserver, 1, "spawnobservers");
		notHere->registerObserver(ObserverEventType::ENTEREDAREA, enterObserver);
		observers.put(enterObserver);

		ManagedReference<SpawnObserver*> exitObserver = new SpawnObserver(_this);
		ObjectManager::instance()->persistObject(exitObserver, 1, "spawnobservers");
		notHere->registerObserver(ObserverEventType::EXITEDAREA, exitObserver);
		observers.put(exitObserver);
	}
}

void DynamicSpawnAreaImplementation::notifyEnter(SceneObject* object) {
	if (!object->isPlayerObject())
		return;

	PlayerObject* player = (PlayerObject*)object;

	notifyObservers(ObserverEventType::ENTEREDAREA, player, 0);

	if (!excludedPlayerOccupants.contains(player))
		playerOccupants.put(player, addSpawnTask(player));
}

void DynamicSpawnAreaImplementation::notifyExit(SceneObject* object) {
	if (!object->isPlayerObject())
		return;

	PlayerObject* player = (PlayerObject*)object;

	notifyObservers(ObserverEventType::EXITEDAREA, player, 0);

	SpawnDynamicAreaCreatureTask* task = playerOccupants.get(player);
	if (task != NULL)
		task->cancel();

	playerOccupants.drop(player);
	while (excludedPlayerOccupants.contains(player))
		excludedPlayerOccupants.drop(player);
	// TODO: add despawn task if players are gone
}

SpawnDynamicAreaCreatureTask* DynamicSpawnAreaImplementation::addSpawnTask(PlayerObject* player) {
	Reference<SpawnDynamicAreaCreatureTask*> task = new SpawnDynamicAreaCreatureTask(_this, player);
	task->schedule(10000 / (spawnConstant > 0 ? spawnConstant : 1)); // is 10 seconds appropriate?

	return task;
}

void DynamicSpawnAreaImplementation::doSpawnEvent(PlayerObject* player) {
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
	PlayerObject* player = (PlayerObject*)arg1;
	DynamicSpawnArea* area = (DynamicSpawnArea*)observable;

	VectorMapEntry<ManagedReference<PlayerObject*>, ManagedReference<DynamicSpawnArea*> > entry(player, area);
	int pos = excludedPlayerOccupants.SortedVector<VectorMapEntry<ManagedReference<PlayerObject*>, ManagedReference<DynamicSpawnArea*> > >::find(entry);
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

void DynamicSpawnAreaImplementation::spawnCreature(uint32 templateCRC, PlayerObject* player) {
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

	ManagedReference<AiGroup*> group = dynamic_cast<AiGroup*>(zone->getZoneServer()->createObject(crc, 0));
	if (group == NULL)
		return;

	Vector3 rOuter = getRandomPosition(player);

	float x = rOuter.getX() + getPositionX();
	float y = rOuter.getY() + getPositionY();
	float z = zone->getHeight(x, y);

	group->setPosition(x, z, y);

	group->insertToZone(zone);

	group->setup(templ);

	spawnedGroups.put(group);
}

Vector3 DynamicSpawnAreaImplementation::getRandomPosition(PlayerObject* player) {
	double angle = System::random(359) * Math::DEG2RAD;
	Vector3 rOuter(64.f * (float)Math::cos(angle), 64.f * (float)Math::sin(angle), 0);
	float lowIntersect = 1, highIntersect = 0;

	for (int i = 0; i < noSpawnAreas.size(); ++i) {
		SpawnArea* noSpawnArea = noSpawnAreas.get(i);
		Vector3 offset(noSpawnArea->getPositionX() - player->getPositionX(), noSpawnArea->getPositionY() - player->getPositionY(), 0);
		if (offset.squaredLength() >= noSpawnArea->getRadius2() + (64.f * 64.f))
			continue;

		float t1 = 0, t2 = 0;
		float a = rOuter.dotProduct(rOuter);
		float b = 2 * (offset.dotProduct(rOuter));
		float c = offset.dotProduct(offset) - noSpawnArea->getRadius2();

		float discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0)
			continue;

		if (discriminant == 0)
			t1 = (-b)/(2 * a);
		else {
			discriminant = Math::sqrt(discriminant);
			t1 = (-b + discriminant)/(2 * a);
			t2 = (-b - discriminant)/(2 * a);
		}

		if (t1 > 0 && t1 < lowIntersect)
			lowIntersect = t1;
		else if (t1 <= 1 && t1 > highIntersect)
			highIntersect = t1;

		if (t2 > 0 && t2 < lowIntersect)
			lowIntersect = t2;
		else if (t2 <= 1 && t2 > highIntersect)
			highIntersect = t2;
	}

	float difference = (highIntersect - lowIntersect) * 1000;
	if (difference < 0)
		difference = 0;

	float randomLength = (float)System::random(1000 - (int)difference);
	if (randomLength >= lowIntersect)
		randomLength = randomLength + difference;

	randomLength /= 1000;

	rOuter = randomLength * rOuter;

	return rOuter;
}
