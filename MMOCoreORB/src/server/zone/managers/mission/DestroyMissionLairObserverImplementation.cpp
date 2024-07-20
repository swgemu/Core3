
#include "server/zone/managers/mission/DestroyMissionLairObserver.h"
#include "templates/mobile/LairTemplate.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/LairAggroTask.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/managers/creature/SpawnLairMobileTask.h"

// #define DEBUG_MISSION_LAIRS

void DestroyMissionLairObserverImplementation::checkForHeal(TangibleObject* lair, TangibleObject* attacker, bool forceNewUpdate) {
	if (getMobType() == LairTemplate::NPC) {
		return;
	}

	LairObserverImplementation::checkForHeal(lair, forceNewUpdate);
}

bool DestroyMissionLairObserverImplementation::checkForNewSpawns(TangibleObject* lair, TangibleObject* attacker, bool forceSpawn) {
	if (lair == nullptr) {
		return false;
	}

	auto zone = lair->getZone();

	if (zone == nullptr) {
		return false;
	}

	auto lairObject = cast<LairObject*>(lair);

	if (lairObject == nullptr) {
		return false;
	}

	auto creatureManager = zone->getCreatureManager();

	if (creatureManager == nullptr) {
		return false;
	}

	int spawnLimitAdjustment = 0;

	if (difficulty == 0) {
		spawnLimitAdjustment = -3;
	} else if (difficulty == 4) {
		spawnLimitAdjustment = 3;
	}

	int spawnLimit = lairTemplate->getSpawnLimit() + spawnLimitAdjustment;
	spawnLimitAdjustment = spawnLimit;

	bool isCreatureLair = false;

	if (getMobType() == LairTemplate::CREATURE) {
		isCreatureLair = true;
	}

	// Lair limit is double due to "milking"
	if (lairObject->isRepopulated()) {
		spawnLimit *= 2;
	}

	// Schedule the aggro task
	if (attacker != nullptr && attacker->isCreatureObject() && lastAggroTime.isPast()) {
		lastAggroTime.updateToCurrentTime();
		lastAggroTime.addMiliTime(LairObserver::AGGRO_CHECK_INTERVAL * 1000);

		auto aggroTask = new LairAggroTask(lairObject, attacker, _this.getReferenceUnsafeStaticCast(), false);

		if (aggroTask != nullptr) {
			aggroTask->schedule(LairObserver::AGGRO_TASK_DELAY * 1000);
		}
	}

#ifdef DEBUG_MISSION_LAIRS
	info(true) << "Mission Lair - " << lair->getDisplayedName() << " Checking for new spawns with spawnNumber = " << spawnNumber << " Spawn Limit = " << spawnLimit << " Total Spawned Creatures = " << spawnedCreatures.size();
#endif // DEBUG_MISSION_LAIRS

	if (forceSpawn) {
		spawnNumber.increment();
	} else if (getMobType() == LairTemplate::NPC) {
		return false;
	} else {
		// Spawn limit has been reached for lair
		if (spawnedCreatures.size() >= spawnLimit) {
			return false;
		}

		int conditionDamage = lair->getConditionDamage();
		int maxCondition = lair->getMaxCondition();

		switch (spawnNumber) {
			// Initial Spawn when lair is inserted to zone
			case 0:
				spawnNumber.increment();
				break;
			// 1st Wave of spawns when lair takes its first damage
			case 1:
				if (conditionDamage > 0) {
					spawnNumber.increment();
				} else {
					return false;
				}
				break;
			// 2nd Wave of spawns when lair condition drops past half of the total condition
			case 2:
				if (conditionDamage > (maxCondition / 2)) {
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

	// String mobileTemplate, int number to spawn
	VectorMap<String, int> objectsToSpawn;

	const Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
	int amountToSpawn = 0;

	if (isCreatureLair) {
		amountToSpawn = spawnLimitAdjustment / 3;

		if (amountToSpawn <= 1) {
			amountToSpawn = 2;
		}
	} else {
		amountToSpawn = System::random(2) + (spawnLimitAdjustment / 3);

		if (amountToSpawn < 1) {
			amountToSpawn = 1;
		}
	}

	for (int i = 0; i < amountToSpawn; i++) {
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

	uint32 lairTemplateCRC = getLairTemplateName().hashCode();

	for (int i = 0; i < objectsToSpawn.size(); ++i) {
		const String& templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.elementAt(i).getValue();

		for (int j = 0; j < numberToSpawn; j++) {
			// Lair mobile spawn task with passive mobile set to spawn
			Reference<SpawnLairMobileTask*> spawnTask = new SpawnLairMobileTask(lairObject, spawnNumber, templateToSpawn, true);

			if (spawnTask == nullptr) {
				continue;
			}

			// Initial spawn wave should spawn quicker then the others
			if (spawnNumber < 2) {
				// Initial spawn is spawned almost immediately
				spawnTask->schedule((j + 1) * 200);
			} else {
				// Create a spawn time that is at least between the min and max
				int spawnTime = System::random(LairObserver::SPAWN_TIME_MAX - LairObserver::SPAWN_TIME_MIN) + LairObserver::SPAWN_TIME_MIN;

				spawnTask->schedule(spawnTime * 1000);
			}
		}
	}

	return objectsToSpawn.size() > 0;
}

void DestroyMissionLairObserverImplementation::spawnLairMobile(LairObject* lair, int spawnNumber, const String& templateToSpawn, bool spawnPassive) {
	if (lair == nullptr) {
		return;
	}

	auto zone = lair->getZone();

	// Lair will have a null zone if it is destroyed
	if (zone == nullptr) {
		return;
	}

	auto creatureManager = zone->getCreatureManager();

	if (creatureManager == nullptr) {
		return;
	}

	auto creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

	if (creatureTemplate == nullptr) {
		return;
	}

	float tamingChance = creatureTemplate->getTame();
	uint32 lairTemplateCRC = templateToSpawn.hashCode();

	float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
	float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
	float z = zone->getHeight(x, y);

	bool spawnScout = false;

	if (getMobType() == LairTemplate::CREATURE && scoutCreatureId == 0 && (System::random(100) <= LairObserver::SCOUT_SPAWN_CHANCE)) {
		spawnScout = true;
	}

	ManagedReference<CreatureObject*> creature = nullptr;

	if (spawnNumber > 0 && creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, LairObserver::BABY_SPAWN_CHANCE)) {
		creature = creatureManager->spawnCreatureAsBaby(lairTemplateCRC, x, z, y);

		babiesSpawned++;

		// Don't spawn baby as a scout
		spawnScout = false;
	}

	if (creature == nullptr) {
		creature = creatureManager->spawnCreatureWithAi(lairTemplateCRC, x, z, y);
	}

	if (creature == nullptr || !creature->isAiAgent()) {
		return;
	}

	auto agent = creature->asAiAgent();

	if (agent == nullptr) {
		return;
	}

	Locker clocker(agent, lair);

	agent->setDespawnOnNoPlayerInRange(false);
	agent->setHomeLocation(x, z, y);
	agent->setRespawnTimer(0);
	agent->setHomeObject(lair);
	agent->setLairTemplateCRC(lairTemplateCRC);

	if (spawnScout) {
		agent->addObjectFlag(ObjectFlag::SCOUT);
		agent->setAITemplate();

		agent->setCustomObjectName(agent->getDisplayedName() + " (scout)", true);

		scoutCreatureId = agent->getObjectID();
	}

	spawnedCreatures.add(agent);

	// Must be at least the baby and one other creature on the spawn to set a adult creature to social follow
	if (spawnedCreatures.size() > 1 && agent->isCreature()) {
		Creature* creature = cast<Creature*>(agent);

		if (creature != nullptr && creature->isBaby()) {
			ManagedReference<CreatureObject*> adultCreo = spawnedCreatures.get(0);

			if (adultCreo != nullptr && adultCreo->getObjectID() != creature->getObjectID()) {
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

	if (getMobType() != LairTemplate::CREATURE || (spawnNumber < 2)) {
		return;
	}

	// Any spawn wave with the exception of the initial wave causes lair damage
	int newDamage = (lair->getMaxCondition() / ((lairTemplate->getSpawnLimit() / 3) * 5));

#ifdef DEBUG_MISSION_LAIRS
	info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Damaging Self from creature spawn: " << newDamage;
#endif // DEBUG_MISSION_LAIRS

	lair->inflictDamage(lair, 0, newDamage, true, true, false);
}
