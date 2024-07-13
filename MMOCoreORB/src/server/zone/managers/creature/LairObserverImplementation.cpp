/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/LairObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/Zone.h"
#include "HealLairObserverEvent.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "LairAggroTask.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/DisseminateExperienceTask.h"
#include "server/zone/managers/creature/LairRepopulateTask.h"
#include "server/zone/managers/creature/SpawnLairMobileTask.h"

// #define DEBUG_WILD_LAIRS

int LairObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (observable == nullptr || arg1 == nullptr) {
		return 1;
	}

	ManagedReference<TangibleObject*> attacker = cast<TangibleObject*>(arg1);
	ManagedReference<TangibleObject*> lair = cast<TangibleObject*>(observable);

	if (attacker == nullptr || lair == nullptr) {
		return 1;
	}

	Reference<LairAggroTask*> task = nullptr;
	AiAgent* agent = nullptr;

	ManagedReference<LairObserver*> lairObserver = _this.getReferenceUnsafeStaticCast();

#ifdef DEBUG_WILD_LAIRS
	info(true) << "Lair - " << lair->getDisplayedName() << " Observer Event Type = " << eventType;
#endif // DEBUG_WILD_LAIRS

	switch (eventType) {
		// Lair despawned, remove mobiles
		case ObserverEventType::OBJECTREMOVEDFROMZONE:
			despawnSpawns();
			return 1;
		// Lair destroyed notify destruction observers
		case ObserverEventType::OBJECTDESTRUCTION:
			notifyDestruction(lair, attacker, (int)arg2);
			return 1;
		// Lair received damage handle spawning, healing, and boss mobiles
		case ObserverEventType::DAMAGERECEIVED: {
			auto zone = lair->getZone();

			if (zone == nullptr) {
				return 1;
			}

			String zoneQueueName = zone->getZoneName();

			// Check for new spawns when the lair is not past the max spawn waves
			if (spawnNumber < 3) {
				// Check for new spawns Lambda
				Reference<TangibleObject*> lairRef = lair;
				Reference<TangibleObject*> attackerRef = attacker;

				Core::getTaskManager()->scheduleTask([lairObserver, lairRef, attackerRef]() {
					if (lairObserver == nullptr || lairRef == nullptr || attackerRef == nullptr) {
						return;
					}

					Locker locker(lairRef);

					lairObserver->checkForNewSpawns(lairRef, attackerRef);
				}, "CheckForNewSpawnsLambda", 1000, zoneQueueName.toCharArray());
			// Check to see if we should spawn a boss mobile
			} else if ((getMobType() == LairTemplate::CREATURE) && !lair->isDestroyed() && lairTemplate->hasBossMobs()) {
				int lairMaxCondition = lair->getMaxCondition();
				int lairConditionDamage = lair->getConditionDamage();
				int difficultyLevel = getDifficultyLevel();

#ifdef DEBUG_WILD_LAIRS
				info(true) << "Creature Lair - " << lair->getDisplayedName() << " attempting to spawn Boss Mobile - Condition Calc: " << (difficultyLevel * (lairMaxCondition / 5)) << " Condition Damage: " << lairConditionDamage;
#endif // DEBUG_WILD_LAIRS

				// Lair condition needs to be at the appropriate amount
				if ((difficultyLevel * (lairMaxCondition / 5)) > lairConditionDamage) {
					return 0;
				}

				Reference<TangibleObject*> lairRef = lair;
				Reference<TangibleObject*> attackerRef = attacker;

				Core::getTaskManager()->scheduleTask([lairObserver, lairRef, attackerRef]() {
					if (lairObserver == nullptr || lairRef == nullptr || attackerRef == nullptr) {
						return;
					}

					Locker locker(lairRef);

					lairObserver->checkForBossSpawn(lairRef, attackerRef);
				}, "CheckForBossSpawnLambda", 500, zoneQueueName.toCharArray());
			}

			// Check for heal on lair -- TODO: Fix how agents heal their lairs
			// Add pathing to lair, check healing amounts, remove constant healing
			if (lastHealTime.isPast() && (attacker->getObjectID() != lair->getObjectID())) {
				lastHealTime.updateToCurrentTime();
				lastHealTime.addMiliTime(LairObserver::HEAL_CHECK_INTERVAL * 1000);

				checkForHeal(lair, attacker);
			}

			break;
		}
		case ObserverEventType::AIMESSAGE:
			for (int i = 0; i < spawnedCreatures.size(); i++) {
				agent = cast<AiAgent*>(spawnedCreatures.get(i).get());

				if (agent == nullptr) {
					continue;
				}

				agent->notifyObservers(arg2, attacker);
			}

			break;
		// Used for checking if a creature lair should be repopulated for "milking"
		case ObserverEventType::NOPLAYERSINRANGE:
			if ((getMobType() == LairTemplate::CREATURE) && getSpawnNumber() > 1 && getLivingCreatureCount() == 1) {
				Reference<LairRepopulateTask*> repopTask = new LairRepopulateTask(lair, lairObserver);

				if (repopTask != nullptr) {
					repopTask->schedule(10 * 1000);
				}
			}

			break;
		case ObserverEventType::CREATUREDESPAWNED: {
			auto zone = lair->getZone();

			if (zone == nullptr) {
				return 1;
			}

			String zoneQueueName = zone->getZoneName();

			// attacker is the agent for this observer trigger
			Reference<LairObject*> lairRef = lair.castTo<LairObject*>();
			Reference<TangibleObject*> mobileRef = attacker;

			Core::getTaskManager()->scheduleTask([lairObserver, lairRef, mobileRef]() {
				if (lairObserver == nullptr || lairRef == nullptr || mobileRef == nullptr) {
					return;
				}

				Locker locker(lairRef);

				lairObserver->checkRespawn(lairRef, mobileRef);
			}, "RespawnLairMobileLambda", 1000, zoneQueueName.toCharArray());

			break;
		}
		default:
			break;
	}

	return 0;
}

void LairObserverImplementation::notifyDestruction(TangibleObject* lair, TangibleObject* attacker, int condition) {
	ThreatMap* threatMap = lair->getThreatMap();

	Reference<DisseminateExperienceTask*> deTask = new DisseminateExperienceTask(lair, threatMap, &spawnedCreatures, lair->getZone());
	deTask->execute();

	threatMap->removeObservers();
	threatMap->removeAll(); // we can clear the original one

	if (lair->getZone() == nullptr) {
		spawnedCreatures.removeAll();
		return;
	}

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(lair, "clienteffect/lair_damage_heavy.cef", "");
	lair->broadcastMessage(explode, false);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", lair->getZone()->getZoneName(), lair->getPositionX(), lair->getPositionZ(), lair->getPositionY());
	lair->broadcastMessage(explodeLoc, false);

	lair->destroyObjectFromWorld(true);
}

int LairObserverImplementation::getLivingCreatureCount() {
	int totalLiving = 0;
	Vector<ManagedReference<CreatureObject*>> pets;

	for (int i = 0; i < spawnedCreatures.size(); i++) {
		ManagedReference<CreatureObject*> cr = spawnedCreatures.get(i);

		if (cr->isPet()) {
			pets.add(cr);
			continue;
		}

		if (!cr->isDead() && cr->getZone() != nullptr) {
			totalLiving++;
		}
	}

	for (int j = 0; j < pets.size(); j++) {
		CreatureObject* pet = pets.get(j);
		spawnedCreatures.removeElement(pet);
	}

	return totalLiving;
}

void LairObserverImplementation::doAggro(TangibleObject* lair, TangibleObject* attacker, bool allAttack) {
	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* creo = spawnedCreatures.get(i);

		if (creo->isDead() || creo->getZone() == nullptr)
			continue;

		if (creo->isAiAgent() && attacker != nullptr && (allAttack || (System::random(1) == 1))) {
			// TODO: only set defender if needed
			AiAgent* ai = cast<AiAgent*>(creo);
			Locker clocker(creo, lair);
			creo->setDefender(attacker);
		}
	}
}

void LairObserverImplementation::checkForHeal(TangibleObject* lair, TangibleObject* attacker, bool forceNewUpdate) {
	if (lair->isDestroyed() || getMobType() == LairTemplate::NPC) {
		return;
	}

	if (lair->getConditionDamage() < 1 || getLivingCreatureCount() < 1) {
		return;
	}

	if (healLairEvent == nullptr) {
		healLairEvent = new HealLairObserverEvent(lair, attacker, _this.getReferenceUnsafeStaticCast());
		healLairEvent->schedule(1000);
	} else if (!healLairEvent->isScheduled()) {
		healLairEvent->schedule(1000);
	} else if (attacker != nullptr)
		healLairEvent->setAttacker(attacker);
}

void LairObserverImplementation::healLair(TangibleObject* lair, TangibleObject* attacker) {
	Locker locker(lair);

	if (lair->getZone() == nullptr)
		return;

	int damageToHeal = 0;
	int lairMaxCondition = lair->getMaxCondition();

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* creo = spawnedCreatures.get(i);

		if (creo->isDead() || creo->getZone() == nullptr) {
			continue;
		}

		if (lair->getDistanceTo(creo) > 20.0f) {
			continue;
		}

		damageToHeal += lairMaxCondition / 100;
	}

	if (damageToHeal == 0)
		return;

	if (lair->getZone() == nullptr)
		return;

	lair->healDamage(lair, 0, damageToHeal, true);

	PlayClientEffectObjectMessage* heal = new PlayClientEffectObjectMessage(lair, "clienteffect/healing_healdamage.cef", "");
	lair->broadcastMessage(heal, false);

	PlayClientEffectLoc* healLoc = new PlayClientEffectLoc("clienteffect/healing_healdamage.cef", lair->getZone()->getZoneName(), lair->getPositionX(), lair->getPositionZ(), lair->getPositionY());
	lair->broadcastMessage(healLoc, false);
}

bool LairObserverImplementation::checkForNewSpawns(TangibleObject* lair, TangibleObject* attacker, bool forceSpawn) {
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

	bool isCreatureLair = false;
	int spawnLimit = lairTemplate->getSpawnLimit();

	if (getMobType() == LairTemplate::CREATURE) {
		isCreatureLair = true;
		spawnLimit *= 3;
	}

	// Lair limit is double due to "milking"
	if (lairObject->isRepopulated()) {
		spawnLimit *= 2;
	}

#ifdef DEBUG_WILD_LAIRS
	info(true) << "Wild Lair - " << lair->getDisplayedName() << " Checking for new spawns with spawnNumber = " << spawnNumber << " Spawn Limit = " << spawnLimit << " Total Spawned Creatures = " << spawnedCreatures.size();
#endif // DEBUG_WILD_LAIRS

	if (forceSpawn) {
		spawnNumber.increment();
	} else if (getMobType() == LairTemplate::NPC) {
		return false;
	} else {
		// Spawn limit has been reached for lair
		if (spawnedCreatures.size() >= spawnLimit) {
			return false;
		}

		int conditionDamage = lairObject->getConditionDamage();
		int maxCondition = lairObject->getMaxCondition();

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

	const Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
	int amountToSpawn = 0;

	// The amount to spawn should be figured out using the lair difficulty
	if (isCreatureLair) {
		int difficultyLevel = getDifficultyLevel();

		amountToSpawn = Math::min(difficultyLevel, lairTemplate->getSpawnLimit() / 3);

		if (amountToSpawn <= 1) {
			amountToSpawn = 2;
		}
	} else {
		amountToSpawn = System::random(lairTemplate->getSpawnLimit() / 2) + (lairTemplate->getSpawnLimit() / 2);

		if (amountToSpawn < 1) {
			amountToSpawn = 1;
		}
	}

	// Build a spawn template map
	VectorMap<String, int> objectsToSpawn;

	for (int i = 0; i < amountToSpawn; i++) {
		int num = System::random(mobiles->size() - 1);
		const String& mob = mobiles->get(num);

		int find = objectsToSpawn.find(mob);

		if (find != -1) {
			int& value = objectsToSpawn.elementAt(find).getValue();

			value++;
		} else {
			objectsToSpawn.put(mob, 1);
		}
	}

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

void LairObserverImplementation::checkForBossSpawn(TangibleObject* lair, TangibleObject* attacker) {
	if (lair == nullptr || attacker == nullptr || lair->isDestroyed()) {
		return;
	}

	auto lairObject = cast<LairObject*>(lair);

	if (lairObject == nullptr) {
		return;
	}

	const VectorMap<String, int>* bossMobiles = lairTemplate->getBossMobiles();

	if (bossMobiles == nullptr || bossMobiles->size() < 1) {
		return;
	}

	int totalBossMobiles = bossMobiles->size();

	// Get a random boss mobile template from the list and spawn it
	try {
		int randomBoss = System::random(totalBossMobiles - 1);
		String templateToSpawn = bossMobiles->elementAt(randomBoss).getKey();

		Reference<SpawnLairMobileTask*> spawnTask = new SpawnLairMobileTask(lairObject, spawnNumber, templateToSpawn, false);

		if (spawnTask == nullptr) {
			return;
		}

		spawnTask->schedule(500);
	} catch (Exception& e) {
		e.printStackTrace();
		error() << "exception in LairObserverImplementation::checkForBossSpawn -- " << e.getMessage();
	}

	Reference<LairAggroTask*> aggroTask = new LairAggroTask(lair, attacker, _this.getReferenceUnsafeStaticCast(), true);

	if (aggroTask != nullptr) {
		aggroTask->schedule(1000);
	}


	// if there are living creatures, make them aggro

	// TODO: this does not seem right, given there are accounts that players attack lairs and the creatures do not always aggro
	/*
	if (getLivingCreatureCount() > 0) {
		task = new LairAggroTask(lair, attacker.get(), _this.getReferenceUnsafeStaticCast(), false);
		task->execute();
	}
	*/
}

void LairObserverImplementation::checkRespawn(LairObject* lair, TangibleObject* agent) {
	if (lair == nullptr || agent == nullptr || lair->isDestroyed()) {
		return;
	}

	auto zone = lair->getZone();

	// Lair will have a null zone if it is destroyed
	if (zone == nullptr) {
		return;
	}

	String agentTemplate = agent->getObjectNameStringIdName();

	Reference<SpawnLairMobileTask*> spawnTask = new SpawnLairMobileTask(lair, spawnNumber, agentTemplate, false);

	if (spawnTask == nullptr) {
		return;
	}

	// Agents at lairs should auto respawn until the lair is destroyed
	int randomRespawn = (System::random(LairObserver::RESPAWN_TIME_MAX - LairObserver::RESPAWN_TIME_MIN) + LairObserver::RESPAWN_TIME_MIN);

#ifdef DEBUG_WILD_LAIRS
	randomRespawn = 20;
	info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Respawning: " << agentTemplate << " in " << randomRespawn << " seconds.";
#endif // DEBUG_WILD_LAIRS

	spawnTask->schedule(randomRespawn * 1000);

}

void LairObserverImplementation::spawnLairMobile(LairObject* lair, int spawnNumber, const String& templateToSpawn, bool spawnPassive) {
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

	int spawnLimit = lairTemplate->getSpawnLimit();
	bool isCreatureLair = false;

	if (getMobType() == LairTemplate::CREATURE) {
		isCreatureLair = true;
		spawnLimit *= 3;
	}

	if (spawnedCreatures.size() >= spawnLimit) {
		return;
	}

	float tamingChance = creatureTemplate->getTame();
	uint32 lairTemplateCRC = templateToSpawn.hashCode();

	float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
	float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
	float z = zone->getHeight(x, y);

	ManagedReference<CreatureObject*> creature = nullptr;

	if (spawnNumber > 0 && creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, LairObserver::BABY_SPAWN_CHANCE)) {
		creature = creatureManager->spawnCreatureAsBaby(lairTemplateCRC, x, z, y);

		babiesSpawned++;
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

#ifdef DEBUG_WILD_LAIRS
	if (spawnPassive) {
		info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Spawned a regular Agent: " << agent->getDisplayedName() << " Total Spawned Creatures = " << spawnedCreatures.size();
	} else {
		info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Spawned a (PASSIVE/Respawn/Boss) Wave Agent: " << agent->getDisplayedName() << " Total Spawned Creatures = " << spawnedCreatures.size();
	}
#endif // DEBUG_WILD_LAIRS

	Locker clocker(agent, lair);

	agent->setDespawnOnNoPlayerInRange(false);
	agent->setRespawnTimer(0);
	agent->setHomeLocation(x, z, y);
	agent->setHomeObject(lair);
	agent->setLairTemplateCRC(lairTemplateCRC);

	// Add agent to the lairs creature list
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

	if (!spawnPassive || !isCreatureLair || (spawnNumber < 2) || (spawnedCreatures.size() > LairObserver::WILD_LAIR_PASSIVE_MAX)) {
		return;
	}

	// Any spawn wave with the exception of the initial wave causes lair damage
	int totalAllowedSpawns = Math::min(getDifficultyLevel(), lairTemplate->getSpawnLimit() / 3);
	int newDamage = (lair->getMaxCondition() / (totalAllowedSpawns * 5));

#ifdef DEBUG_WILD_LAIRS
	info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Damaging Self from creature spawn: " << newDamage;
#endif // DEBUG_WILD_LAIRS

	lair->inflictDamage(lair, 0, newDamage, true, true, false);

	if (lair->isDestroyed()) {
		return;
	}

	// Spawn passive mobile
	Reference<SpawnLairMobileTask*> spawnTask = new SpawnLairMobileTask(lair, spawnNumber, templateToSpawn, false);

	if (spawnTask == nullptr) {
		return;
	}

	int totalThreats = 1;
	auto threatMap = lair->getThreatMap();

	if (threatMap != nullptr) {
		totalThreats = threatMap->size();
		threatMap = nullptr;
	}

#ifdef DEBUG_WILD_LAIRS
	info(true) << "Wild Lair - Name: " << lair->getDisplayedName() << " ID: " << lair->getObjectID() << " Total Threats = " << totalThreats;
#endif // DEBUG_WILD_LAIRS

	// Create a spawn time that is at least between the min and max
	int min = LairObserver::PASSIVE_SPAWN_TIME_MIN;
	int max = LairObserver::PASSIVE_SPAWN_TIME_MAX;

	if (totalThreats > 15) {
		min = 1;
		max = 2;
	} else if (totalThreats > 10) {
		min = LairObserver::PASSIVE_SPAWN_TIME_MIN - 10;
		max = LairObserver::PASSIVE_SPAWN_TIME_MAX - 10;
	} else if (totalThreats > 5) {
		min = LairObserver::PASSIVE_SPAWN_TIME_MIN - 5;
		max = LairObserver::PASSIVE_SPAWN_TIME_MAX - 5;
	}

	int spawnTime = System::random(max - min) + min;
	spawnTask->schedule(spawnTime * 1000);
}

void LairObserverImplementation::repopulateLair(TangibleObject* lairTano) {
	if (lairTano == nullptr) {
		return;
	}

	Locker lock(lairTano);

	int lairCond = lairTano->getMaxCondition();

	lairTano->setMaxCondition(lairCond * 0.75);
	lairTano->healDamage(lairTano, 0, lairCond, true);
	spawnNumber.set(0);

	LairObject* lair = cast<LairObject*>(lairTano);

	if (lair != nullptr)
		lair->setLairRepopulated(true);

	Reference<LairObserver*> lairObserver = _this.getReferenceUnsafeStaticCast();
	Reference<TangibleObject*> lairTanoRef = lairTano;

	Core::getTaskManager()->scheduleTask([lairTanoRef, lairObserver]() {
		Locker locker(lairTanoRef);
		lairObserver->checkForNewSpawns(lairTanoRef, nullptr);
	}, "CheckForNewSpawnsLambda", 1000);
}
