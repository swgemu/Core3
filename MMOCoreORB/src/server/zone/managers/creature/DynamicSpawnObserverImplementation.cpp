#include "server/zone/managers/creature/DynamicSpawnObserver.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
#include "server/zone/objects/creature/events/DespawnDynamicSpawnTask.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/Creature.h"

int DynamicSpawnObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if (eventType == ObserverEventType::OBJECTREMOVEDFROMZONE) {
		despawnSpawns();
		return 1;
	} else if (eventType != ObserverEventType::CREATUREDESPAWNED) {
		return 0;
	}

	Reference<AiAgent*> ai = cast<AiAgent*>(arg1);
	Reference<SceneObject*> spawn = cast<SceneObject*>(observable);

	if (ai == NULL || spawn == NULL)
		return 0;

	if (ai->getRespawnCounter() > 1) {
		spawnedCreatures.removeElement(ai.get());
		ai->setHomeObject(NULL);
		ai->resetRespawnCounter();

		if (spawnedCreatures.isEmpty()) {

			Reference<Task*> task = new DespawnDynamicSpawnTask(spawn);
			task->schedule(60000);

			return 1;
		}

		return 0;
	}

	Zone* zone = spawn->getZone();

	if (zone == NULL)
		return 0;

	int level = ai->getLevel();

	if (ai->isCreature()) {
		Creature* creature = ai.castTo<Creature*>();
		level = creature->getAdultLevel();
	}

	Reference<Task*> task = new RespawnCreatureTask(ai.get(), zone, level);
	task->schedule((60 + (level * 2)) * 1000);

	return 0;
}

void DynamicSpawnObserverImplementation::spawnInitialMobiles(SceneObject* building) {
	if (building->getZone() == NULL)
		return;

	int spawnLimitAdjustment = (difficulty - 2) / 2;

	int totalNumberToSpawn = (lairTemplate->getSpawnLimit() / 3) + spawnLimitAdjustment;
	VectorMap<String, int> objectsToSpawn; // String mobileTemplate, int number to spawn
	Vector<String>* mobiles = lairTemplate->getWeightedMobiles();

	if (totalNumberToSpawn < 1)
		totalNumberToSpawn = 1;

	for (int i = 0; i < totalNumberToSpawn; i++) {
		int num = System::random(mobiles->size() - 1);
		String mob = mobiles->get(num);

		if (objectsToSpawn.contains(mob)) {
			int value = objectsToSpawn.get(mob);
			objectsToSpawn.drop(mob);
			objectsToSpawn.put(mob, value + 1);
		} else {
			objectsToSpawn.put(mob, 1);
		}
	}

	for(int i = 0; i < objectsToSpawn.size(); ++i) {

		String templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.get(templateToSpawn);

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == NULL)
			continue;

		float tamingChance = creatureTemplate->getTame();

		CreatureManager* creatureManager = building->getZone()->getCreatureManager();

		for (int j = 0; j < numberToSpawn; j++) {

			float x = building->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = building->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = building->getZone()->getHeight(x, y);

			ManagedReference<CreatureObject*> creo = NULL;

			if (creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, 500)) {
				creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
				babiesSpawned++;
			}

			if (creo == NULL)
				creo = creatureManager->spawnCreatureWithAi(templateToSpawn.hashCode(), x, z, y);

			if (creo == NULL)
				continue;

			if (!creo->isAiAgent()) {
				error("spawned non player creature with template " + templateToSpawn);
			} else {
				AiAgent* ai = cast<AiAgent*>( creo.get());

				ai->setDespawnOnNoPlayerInRange(false);
				ai->setHomeLocation(x, z, y);
				ai->setRespawnTimer(0);
				ai->resetRespawnCounter();
				ai->setHomeObject(building);

				spawnedCreatures.add(creo);

			}
		}
	}
}
