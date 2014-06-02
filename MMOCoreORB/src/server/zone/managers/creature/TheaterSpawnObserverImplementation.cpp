#include "server/zone/managers/creature/TheaterSpawnObserver.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
#include "server/zone/objects/creature/events/DespawnTheaterTask.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

int TheaterSpawnObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::CREATUREDESPAWNED)
		return 0;

	Reference<AiAgent*> ai = cast<AiAgent*>(arg1);
	Reference<TangibleObject*> theater = cast<TangibleObject*>(observable);

	if (ai == NULL || theater == NULL)
		return 0;

	if (ai->getRespawnCounter() > 1) {
		spawnedCreatures.removeElement(ai.get());
		ai->setHomeObject(NULL);
		ai->resetRespawnCounter();

		if (spawnedCreatures.isEmpty()) {

			Reference<Task*> task = new DespawnTheaterTask(theater);
			task->schedule(2 * 60 * 1000);

			return 1;
		}

		return 0;
	}

	Zone* zone = theater->getZone();

	if (zone == NULL)
		return 0;

	Reference<Task*> task = new RespawnCreatureTask(ai.get(), zone, ai->getLevel());
	task->schedule(60 * 1000);

	return 0;
}

void TheaterSpawnObserverImplementation::spawnInitialMobiles(TangibleObject* theater) {
	if (theater->getZone() == NULL)
		return;

	int totalNumberToSpawn = lairTemplate->getSpawnLimit() / 3;
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

		CreatureManager* creatureManager = theater->getZone()->getCreatureManager();

		for (int j = 0; j < numberToSpawn; j++) {

			float x = theater->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = theater->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = theater->getZone()->getHeight(x, y);

			ManagedReference<CreatureObject*> creo = NULL;

			if (tamingChance > 0) {
				if (babiesSpawned == 0) {
					if (System::random(1000) < (tamingChance * 100.0f)) {
						creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
						babiesSpawned++;
					}
				} else if (System::random(1000 * babiesSpawned) < (tamingChance * 100.0f)) {
					creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
					babiesSpawned++;
				}
			}

			if (creo == NULL)
				creo = creatureManager->spawnCreature(templateToSpawn.hashCode(), 0, x, z, y);

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
				ai->setHomeObject(theater);

				spawnedCreatures.add(creo);

			}
		}
	}
}
