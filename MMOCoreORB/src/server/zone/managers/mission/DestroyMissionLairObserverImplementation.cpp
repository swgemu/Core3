
#include "server/zone/managers/mission/DestroyMissionLairObserver.h"
#include "server/zone/templates/mobile/LairTemplate.h"
#include "server/zone/managers/creature/HealLairObserverEvent.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/managers/creature/LairAggroTask.h"

void DestroyMissionLairObserverImplementation::checkForHeal(TangibleObject* lair, TangibleObject* attacker, bool forceNewUpdate) {
	if (getMobType() == LairTemplate::NPC)
		return;

	LairObserverImplementation::checkForHeal(lair, attacker, forceNewUpdate);
}

bool DestroyMissionLairObserverImplementation::checkForNewSpawns(TangibleObject* lair, TangibleObject* attacker, bool forceSpawn) {
	Zone* zone = lair->getZone();

	if (zone == NULL)
		return false;

	int spawnLimitAdjustment = 0;

	if (difficulty == 0) {
		spawnLimitAdjustment = -3;
	} else if (difficulty == 4) {
		spawnLimitAdjustment = 3;
	}

	int spawnLimit = lairTemplate->getSpawnLimit() + spawnLimitAdjustment;

	if (forceSpawn) {
		spawnNumber.increment();
	} else if (getMobType() == LairTemplate::NPC) {
		return false;
	} else {
		if (spawnedCreatures.size() >= spawnLimit && !lairTemplate->hasBossMobs())
			return true;

		int conditionDamage = lair->getConditionDamage();
		int maxCondition = lair->getMaxCondition();

		switch (spawnNumber) {
		case 0:
			spawnNumber.increment();
			break;
		case 1:
			if (conditionDamage > (maxCondition / 10)) {
				spawnNumber.increment();
			} else {
				return false;
			}
			break;
		case 2:
			if (conditionDamage > (maxCondition / 2)) {
				spawnNumber.increment();
			} else {
				return false;
			}
			break;
		case 3:
			if (lairTemplate->hasBossMobs() && conditionDamage > ((maxCondition * 9) / 10)) {
				spawnNumber.increment();
			} else {
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}

	VectorMap<String, int> objectsToSpawn; // String mobileTemplate, int number to spawn

	if (spawnNumber == 4) {
		if (System::random(100) > 4)
			return false;

		VectorMap<String, int>* mobs = lairTemplate->getBossMobiles();

		for (int i = 0; i < mobs->size(); i++) {
			objectsToSpawn.put(mobs->elementAt(i).getKey(), mobs->elementAt(i).getValue());
		}

	} else {
		Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
		int amountToSpawn = 0;

		if (getMobType() == LairTemplate::CREATURE) {
			amountToSpawn = spawnLimit / 3;
		} else {
			amountToSpawn = System::random(2) + (spawnLimit / 3);
		}

		if (amountToSpawn < 1)
			amountToSpawn = 1;

		for (int i = 0; i < amountToSpawn; i++) {
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
	}

	for(int i = 0; i < objectsToSpawn.size(); ++i) {

		if (spawnNumber != 4 && spawnedCreatures.size() >= spawnLimit)
			return true;

		String templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.get(templateToSpawn);

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == NULL)
			continue;

		float tamingChance = creatureTemplate->getTame();

		CreatureManager* creatureManager = zone->getCreatureManager();

		for (int j = 0; j < numberToSpawn; j++) {
			if (lair->getZone() == NULL)
				break;

			float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = zone->getHeight(x, y);

			ManagedReference<CreatureObject*> creo = NULL;

			if (creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, 1000)) {
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

				Locker clocker(ai, lair);

				ai->setDespawnOnNoPlayerInRange(false);
				ai->setHomeLocation(x, z, y);
				ai->setRespawnTimer(0);
				ai->setHomeObject(lair);

				spawnedCreatures.add(creo);

			}
		}
	}

	if (spawnNumber == 4) {
		Reference<LairAggroTask*> task = new LairAggroTask(lair, attacker, _this.getReferenceUnsafeStaticCast(), true);
		task->schedule(1000);
	}

	return objectsToSpawn.size() > 0;
}

