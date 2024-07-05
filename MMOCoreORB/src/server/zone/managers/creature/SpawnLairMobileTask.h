/*
 * SpawnLairMobileTask.h
 *
 * Created on: 2024-07-06
 * Author: Hakry
 */

#ifndef SPAWNLAIRMOBILETASK_H_
#define SPAWNLAIRMOBILETASK_H_

#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/managers/creature/CreatureManager.h"

class SpawnLairMobileTask : public Task {
	ManagedWeakReference<LairObject*> lairWeak;
	int spawnNumber;

public:
	SpawnLairMobileTask(LairObject* lair, int spawnNum, String lai) {
		lairWeak = lair;
		spawnNumber = spawnNum;
	}

	void run() {
		auto lairObject = lairWeak.get();

		if (lairObject == nullptr) {
			return;
		}

		auto zone = lairObject->getZone();

		if (zone == nullptr) {
			return;
		}

		auto creatureManager = zone->getCreatureManager();

		if (creatureManager == nullptr) {
			return;
		}

		float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
		float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
		float z = zone->getHeight(x, y);

		ManagedReference<CreatureObject*> creature = nullptr;

		if (spawnNumber > 0 && creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, LairObserver::BABY_SPAWN_CHANCE)) {
			creature = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);

			// Need to increase baby spawn count with a function
			// babiesSpawned++;
		}

		if (creature == nullptr) {
			creature = creatureManager->spawnCreatureWithAi(templateToSpawn.hashCode(), x, z, y);
		}

		if (creature == nullptr || !creature->isAiAgent()) {
			return;
		}

		auto agent = creature->asAiAgent();

		if (agent == nullptr) {
			return;
		}

		Locker clocker(agent, lairObject);

		agent->setDespawnOnNoPlayerInRange(false);
		agent->setHomeLocation(x, z, y);
		agent->setRespawnTimer(0);
		agent->setHomeObject(lair);
		agent->setLairTemplateCRC(lairTemplateCRC);

		spawnedCreatures.add(lairObject);

		// Must be at least the baby and one other creature on the spawn to set a adult creature to social follow
		if (spawnedCreatures.size() > 1 && agent->isCreature()) {
			Creature* creature = cast<Creature*>(lairObject);

			if (creature != nullptr && creature->isBaby()) {
				ManagedReference<CreatureObject*> adultCreo = spawnedCreatures.get(0);

				if (adultCreo != nullptr && adultCreo->getObjectID() != creo->getObjectID()) {
					Locker adultLock(adultCreo, agent);

					agent->addObjectFlag(ObjectFlag::ESCORT);
					agent->addObjectFlag(ObjectFlag::FOLLOW);

					agent->setFollowObject(adultCreo);
					agent->setMovementState(AiAgent::FOLLOWING);

					agent->setAITemplate();

					Vector3 formationOffset;
					formationOffset.setX(2.0);
					agent->writeBlackboard("formationOffset", formationOffset);
				}
			}
		}
	}
};

#endif /* SPAWNLAIRMOBILETASK_H_ */