#include "server/zone/managers/creature/DynamicSpawnObserver.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
#include "server/zone/objects/creature/events/DespawnDynamicSpawnTask.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"

int DynamicSpawnObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::OBJECTREMOVEDFROMZONE) {
		despawnSpawns();
		return 1;
	} else if (eventType != ObserverEventType::CREATUREDESPAWNED) {
		return 0;
	}

	Reference<SceneObject*> spawn = cast<SceneObject*>(observable);

	if (spawn == nullptr)
		return 1;

	Reference<AiAgent*> agent = cast<AiAgent*>(arg1);

	if (agent == nullptr)
		return 0;

	// Each creature should spawn 4 times
	if (agent->getRespawnCounter() > 2) {
		spawnedCreatures.removeElement(agent.get());

		agent->setHomeObject(nullptr);
		agent->resetRespawnCounter();

		// Remove Squad observer from herding creatures
		if (agent->isMonster()) {
			SortedVector<ManagedReference<Observer* > > observers = agent->getObservers(ObserverEventType::SQUAD);

			for (int i = observers.size() - 1; i >= 0; --i) {
				ManagedReference<SquadObserver*> squadObserver = cast<SquadObserver*>(observers.get(i).get());

				if (squadObserver != nullptr) {
					agent->dropObserver(ObserverEventType::SQUAD, squadObserver);
				}
			}
		}

		// Despawn dynamic lair if all the creatures have spawned 4 times
		if (spawnedCreatures.isEmpty()) {
			Reference<DespawnDynamicSpawnTask*> task = new DespawnDynamicSpawnTask(spawn);

			if (task != nullptr)
				task->schedule(60000);

			return 1;
		}

		return 0;
	}

	Zone* zone = spawn->getZone();

	if (zone == nullptr)
		return 0;

	int level = agent->getLevel();

	if (agent->isCreature()) {
		Creature* creature = agent.castTo<Creature*>();
		level = creature->getAdultLevel();
	}

	Reference<Task*> task = new RespawnCreatureTask(agent.get(), zone, level);
	task->schedule((60 + (level * 2)) * 1000);

	return 0;
}

void DynamicSpawnObserverImplementation::spawnInitialMobiles(SceneObject* building) {
	Zone* zone = building->getZone();

	if (zone == nullptr)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();

	if (creatureManager == nullptr)
		return;

	int spawnLimitAdjustment = (difficulty - 2) / 2;

	int totalNumberToSpawn = (lairTemplate->getSpawnLimit() / 3) + spawnLimitAdjustment;
	VectorMap<String, int> objectsToSpawn; // String mobileTemplate, int number to spawn
	const Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
	uint32 lairTemplateCRC = getLairTemplateName().hashCode();

	if (totalNumberToSpawn < 1)
		totalNumberToSpawn = 1;

	for (int i = 0; i < totalNumberToSpawn; i++) {
		int num = System::random(mobiles->size() - 1);
		const String& mob = mobiles->get(num);

		int find = objectsToSpawn.find(mob);

		if (find != -1) {
			int& value = objectsToSpawn.elementAt(find).getValue();
			++value;
		} else {
			objectsToSpawn.put(mob, 1);
		}
	}

	ManagedReference<AiAgent*> herdLeader = nullptr;
	ManagedReference<SquadObserver*> squadObserver = nullptr;

	for (int i = 0; i < objectsToSpawn.size(); ++i) {
		const String& templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.elementAt(i).getValue();

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == nullptr)
			continue;

		float tamingChance = creatureTemplate->getTame();

		for (int j = 0; j < numberToSpawn; j++) {
			float x = building->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = building->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = building->getZone()->getHeight(x, y);

			ManagedReference<CreatureObject*> creo = nullptr;

			// Ensure baby is not the first to spawn
			if (j > 0 && creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, BABY_SPAWN_CHANCE)) {
				creo = creatureManager->spawnCreatureAsBaby(templateToSpawn.hashCode(), x, z, y);
				babiesSpawned++;
			}

			if (creo == nullptr)
				creo = creatureManager->spawnCreatureWithAi(templateToSpawn.hashCode(), x, z, y);

			if (creo == nullptr)
				continue;

			if (!creo->isAiAgent()) {
				error("spawned non player creature with template " + templateToSpawn);
			} else {
				AiAgent* agent = cast<AiAgent*>(creo.get());

				if (agent == nullptr)
					continue;

				Locker clocker(agent, building);

				agent->setDespawnOnNoPlayerInRange(false);
				agent->setHomeLocation(x, z, y);
				agent->setRespawnTimer(0);
				agent->resetRespawnCounter();
				agent->setHomeObject(building);
				agent->setLairTemplateCRC(lairTemplateCRC);

				spawnedCreatures.add(creo);

				// Here we will setup creatures to move in herds
				if (agent->isMonster()) {
					if (j == 0 && herdLeader == nullptr && creatureTemplate->isHerd()) {
						herdLeader = agent;
						squadObserver = new SquadObserver();

						if (squadObserver != nullptr) {
							squadObserver->addMember(agent);
							agent->registerObserver(ObserverEventType::SQUAD, squadObserver);

							//info(true) << "Herd Leader " << agent->getDisplayedName() << " " << agent->getObjectID() << " set";
						}
					} else if (herdLeader != nullptr && squadObserver != nullptr) {
						squadObserver->addMember(agent);
						agent->registerObserver(ObserverEventType::SQUAD, squadObserver);

						Locker adultLock(herdLeader, agent);

						agent->addCreatureFlag(CreatureFlag::FOLLOW);
						agent->addCreatureFlag(CreatureFlag::SQUAD);

						agent->setFollowObject(herdLeader);
						agent->setMovementState(AiAgent::FOLLOWING);

						agent->setAITemplate();
						agent->clearPatrolPoints();

						// Double the template radius to account for both creatures
						float templateRad = agent->getTemplateRadius() * 2.f;
						float x = templateRad + System::random((j * 3));
						float y = (-2.f * templateRad * j);

						// Random chance to shift mobs to left side of leader
						if (System::random(100) > 50)
							x *= -1.f;

						Vector3 formationOffset(x, y, 0);

						agent->writeBlackboard("formationOffset", formationOffset);

						//info(true) << "Agent " << agent->getDisplayedName() << " - " << agent->getObjectID() << " following leader: " << herdLeader->getDisplayedName() << " - " << herdLeader->getObjectID() << " Offset: " << formationOffset.toString() << " Template Radius: " << templateRad;
					}
				}
			}
		}
	}
}
