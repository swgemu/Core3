
#include "server/zone/managers/mission/DestroyMissionLairObserver.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/HealLairObserverEvent.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/Creature.h"

void DestroyMissionLairObserverImplementation::checkForHeal(TangibleObject* lair, TangibleObject* attacker, bool forceNewUpdate) {
	if (getMobType() == LairTemplate::NPC)
		return;

	LairObserverImplementation::checkForHeal(lair, attacker, forceNewUpdate);
}

bool DestroyMissionLairObserverImplementation::checkForNewSpawns(TangibleObject* lair, bool forceSpawn) {
	if (lair->getZone() == NULL)
		return false;

	if (spawnedCreatures.size() >= lairTemplate->getSpawnLimit())
		return true;

	if (forceSpawn) {
		spawnNumber++;
	} else if (lairTemplate->getMobType() == LairTemplate::NPC) {
		return false;
	} else {
		int conditionDamage = lair->getConditionDamage();
		int maxCondition = lair->getMaxCondition();

		switch (spawnNumber) {
		case 0:
			spawnNumber++;
			break;
		case 1:
			if (conditionDamage > (maxCondition / 4)) {
				spawnNumber++;
			} else {
				return false;
			}
			break;
		case 2:
			if (conditionDamage > (maxCondition / 2)) {
				spawnNumber++;
			} else {
				return false;
			}
			break;
		case 3:
			return false;
			break;
		}
	}

	VectorMap<String, int>* objectsToSpawn = lairTemplate->getMobiles();
	int amountToSpawn = 0;

	if (lairTemplate->getMobType() == LairTemplate::CREATURE) {
		amountToSpawn = System::random(3) + ((lairTemplate->getSpawnLimit() / 3) - 2);
	} else {
		amountToSpawn = System::random(lairTemplate->getSpawnLimit() / 2) + (lairTemplate->getSpawnLimit() / 2);
	}

	if (amountToSpawn < 1)
		amountToSpawn = 1;

	for(int i = 0; i < amountToSpawn; ++i) {

		if (spawnedCreatures.size() >= lairTemplate->getSpawnLimit())
			return true;

		String templateToSpawn = objectsToSpawn->elementAt((int)System::random(objectsToSpawn->size() - 1)).getKey();

		CreatureManager* creatureManager = lair->getZone()->getCreatureManager();

		float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
		float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
		float z = lair->getZone()->getHeight(x, y);

		int levelDiff = objectsToSpawn->get(templateToSpawn);

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == NULL)
			continue;

		float tamingChance = creatureTemplate->getTame();

		ManagedReference<CreatureObject*> creo = NULL;

		if (tamingChance > 0) {
			if (babiesSpawned == 0 && System::random(500) < (tamingChance * 100.0f)) {
				creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
				babiesSpawned++;
			} else if (System::random(500 * babiesSpawned) < (tamingChance * 100.0f)) {
				creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
				babiesSpawned++;
			} else
				creo = creatureManager->spawnCreatureWithLevel(templateToSpawn.hashCode(), difficulty + levelDiff, x, z, y);

		} else
			creo = creatureManager->spawnCreatureWithLevel(templateToSpawn.hashCode(), difficulty + levelDiff, x, z, y);

		if (creo == NULL)
			continue;

		if (!creo->isAiAgent()) {
			error("spawned non player creature with template " + templateToSpawn);
		} else {
			AiAgent* ai = cast<AiAgent*>( creo.get());

			//Locker clocker(npc, lair);

			ai->setDespawnOnNoPlayerInRange(false);
			ai->setHomeLocation(x, z, y);
			ai->setRespawnTimer(0);

			spawnedCreatures.add(creo);

		}
	}

	return amountToSpawn > 0;
}

