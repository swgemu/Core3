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

int LairObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	int i = 0;

	Reference<LairAggroTask*> task = nullptr;
	SceneObject* sourceObject = cast<SceneObject*>(arg1);
	AiAgent* agent = nullptr;
	ManagedReference<LairObserver*> lairObserver = _this.getReferenceUnsafeStaticCast();
	ManagedReference<TangibleObject*> lair = cast<TangibleObject*>(observable);
	ManagedReference<TangibleObject*> attacker = cast<TangibleObject*>(arg1);

	auto zone = lair->getZone();
	String queueName = zone == nullptr ? "" : zone->getZoneName();

	switch (eventType) {
	case ObserverEventType::OBJECTREMOVEDFROMZONE:
		despawnSpawns();
		return 1;
	case ObserverEventType::OBJECTDESTRUCTION:
		notifyDestruction(lair, attacker, (int)arg2);
		return 1;
	case ObserverEventType::DAMAGERECEIVED:
		// if there are living creatures, make them aggro
		if (getLivingCreatureCount() > 0) {
			task = new LairAggroTask(lair, attacker.get(), _this.getReferenceUnsafeStaticCast(), false);
			task->execute();
		}

		Core::getTaskManager()->executeTask([=]() {
			Locker locker(lair);
			lairObserver->checkForNewSpawns(lair, attacker);
		}, "CheckForNewSpawnsLambda", queueName.toCharArray());

		checkForHeal(lair, attacker);

		break;
	case ObserverEventType::AIMESSAGE:
		if (sourceObject == nullptr) {
			Logger::console.error("LairObserverImplemenation::notifyObserverEvent does not have a source object");
			return 1;
		}

		for (i = 0; i < spawnedCreatures.size(); i++) {
			agent = cast<AiAgent*>(spawnedCreatures.get(i).get());
			if (agent == nullptr)
				continue;

			agent->notifyObservers(arg2, sourceObject);
		}

		break;
	case ObserverEventType::NOPLAYERSINRANGE:
		if (!(getMobType() == LairTemplate::NPC) && getSpawnNumber() >= 2 && getLivingCreatureCount() >= 1) {
			Reference<LairRepopulateTask*> repopTask = new LairRepopulateTask(lair, lairObserver);

			if (repopTask != nullptr) {
				repopTask->schedule(10 * 1000);
			}
		}

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
	int alive = 0;
	Vector<ManagedReference<CreatureObject*>> pets;

	for (int i = 0; i < spawnedCreatures.size(); i++) {
		ManagedReference<CreatureObject*> cr = spawnedCreatures.get(i);

		if (cr->isPet()) {
			pets.add(cr);
			continue;
		}

		if (!cr->isDead() && cr->getZone() != nullptr)
			alive++;
	}

	for (int j = 0; j < pets.size(); j++) {
		CreatureObject* pet = pets.get(j);
		spawnedCreatures.removeElement(pet);
	}

	return alive;
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
	if (lair->isDestroyed() || getMobType() == LairTemplate::NPC)
		return;

	if (!(getLivingCreatureCount() > 0 && lair->getConditionDamage() > 0))
		return;

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
	Zone* zone = lair->getZone();

	if (zone == nullptr)
		return false;

	CreatureManager* creatureManager = zone->getCreatureManager();

	if (creatureManager == nullptr)
		return false;

	int spawnLimit = lairTemplate->getSpawnLimit();

	LairObject* lairObject = cast<LairObject*>(lair);

	if (lairObject != nullptr && lairObject->isRepopulated())
		spawnLimit *= 2;

	if (spawnedCreatures.size() >= spawnLimit && !lairTemplate->hasBossMobs())
		return false;

	if (forceSpawn) {
		spawnNumber.increment();
	} else if (getMobType() == LairTemplate::NPC) {
		return false;
	} else {
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
		if (System::random(100) > 9)
			return false;

		const VectorMap<String, int>* mobs = lairTemplate->getBossMobiles();

		for (int i = 0; i < mobs->size(); i++) {
			objectsToSpawn.put(mobs->elementAt(i).getKey(), mobs->elementAt(i).getValue());
		}

	} else {
		const Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
		int amountToSpawn = 0;

		if (getMobType() == LairTemplate::CREATURE) {
			amountToSpawn = System::random(3) + ((lairTemplate->getSpawnLimit() / 3) - 2);
		} else {
			amountToSpawn = System::random(lairTemplate->getSpawnLimit() / 2) + (lairTemplate->getSpawnLimit() / 2);
		}

		if (amountToSpawn < 1)
			amountToSpawn = 1;

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
	}

	uint32 lairTemplateCRC = getLairTemplateName().hashCode();

	for (int i = 0; i < objectsToSpawn.size(); ++i) {
		if (spawnNumber != 4 && spawnedCreatures.size() >= spawnLimit)
			return true;

		const String& templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.elementAt(i).getValue();

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == nullptr)
			continue;

		float tamingChance = creatureTemplate->getTame();

		for (int j = 0; j < numberToSpawn; j++) {
			float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = zone->getHeight(x, y);

			ManagedReference<CreatureObject*> creo = nullptr;

			if (j > 0 && creatureManager->checkSpawnAsBaby(tamingChance, babiesSpawned, LairObserver::BABY_SPAWN_CHANCE)) {
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

				Locker clocker(agent, lair);

				agent->setDespawnOnNoPlayerInRange(false);
				agent->setHomeLocation(x, z, y);
				agent->setRespawnTimer(0);
				agent->setHomeObject(lair);
				agent->setLairTemplateCRC(lairTemplateCRC);

				spawnedCreatures.add(creo);

				// Must be at least the baby and one other creature on the spawn to set a adult creature to social follow
				if (spawnedCreatures.size() > 1 && agent->isCreature()) {
					Creature* creature = cast<Creature*>(agent);

					if (creature != nullptr && creature->isBaby()) {
						ManagedReference<CreatureObject*> adultCreo = spawnedCreatures.get(0);

						if (adultCreo != nullptr && adultCreo->getObjectID() != creo->getObjectID()) {
							Locker adultLock(adultCreo, agent);

							agent->addCreatureFlag(CreatureFlag::ESCORT);
							agent->addCreatureFlag(CreatureFlag::FOLLOW);

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
		}
	}

	if (spawnNumber == 4) {
		Reference<LairAggroTask*> task = new LairAggroTask(lair, attacker, _this.getReferenceUnsafeStaticCast(), true);
		task->schedule(1000);
	}

	return objectsToSpawn.size() > 0;
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
