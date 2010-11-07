/*
 * StaticSpawnAreaImplementation.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: da
 */

#include "StaticSpawnArea.h"
#include "SpawnStaticAreaCreatureTask.h"
#include "SpawnObserver.h"
#include "server/zone/managers/creature/SpawnGroup.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"

void StaticSpawnAreaImplementation::registerObservers() {
	for (int i = 0; i < spawnedAgents.size(); ++i) {
		AiAgent* aiagent = spawnedAgents.get(i);

		ManagedReference<SpawnObserver*> destroyObserver = new SpawnObserver(_this);
		ObjectManager::instance()->persistObject(destroyObserver, 1, "spawnobservers");
		aiagent->registerObserver(ObserverEventType::OBJECTDESTRUCTION, destroyObserver);
		observers.put(destroyObserver);
	}
}

void StaticSpawnAreaImplementation::spawnCreatures() {
	for (int i = 0; i < spawnCreatureTemplates.size(); ++i) {
		StaticSpawnGroup templ = CreatureTemplateManager::instance()->getStaticGroup(spawnCreatureTemplates.get(i));
		Vector<SpawnCoordinate> spawnList = templ.getSpawnList();
		for (int j = 0; j < spawnList.size(); ++j) {
			SpawnCoordinate coord = spawnList.get(j);

			CreatureObject* creature = zone->getCreatureManager()->spawnCreature(coord.getTemplateName().hashCode(), coord.getPositionX(), coord.getPositionZ(), coord.getPositionY(), coord.getCellID());

			if (creature->isAiAgent()) {
				AiAgent* aiagent = (AiAgent*)creature;
				aiagent->setRespawnTimer(60); // TODO: does this need to be scripted?
				SceneObject* cell = zone->getZoneServer()->getObject(coord.getCellID());
				aiagent->setHomeLocation(coord.getPositionX(), coord.getPositionZ(), coord.getPositionY(), cell);

				// TODO: add to ai groups once that functionality is in

				spawnedAgents.put(aiagent);
			}
		}
	}
}

SpawnStaticAreaCreatureTask* StaticSpawnAreaImplementation::addSpawnTask() {
	Reference<SpawnStaticAreaCreatureTask*> task = new SpawnStaticAreaCreatureTask(_this);
	task->schedule(300000);

	return task;
}

void StaticSpawnAreaImplementation::doSpawnEvent() {
	// TODO: does this need to be here?
}

void StaticSpawnAreaImplementation::doDespawnEvent() {
	// despawn all groups, despawning individually handled in AiGroup
}

int StaticSpawnAreaImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		AiAgent* creature = (AiAgent*)observable;
		if (spawnedAgents.contains(creature))
			spawnedAgents.drop(creature);

		unspawnedAgents.put(creature);
	}

	return 1;
}

