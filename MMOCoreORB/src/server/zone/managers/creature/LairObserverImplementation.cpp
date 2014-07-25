/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

 */

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/NonPlayerCreatureObject.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/Zone.h"
#include "HealLairObserverEvent.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "LairAggroTask.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/DisseminateExperienceTask.h"

int LairObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	int ret = 1;
	int i = 0;

	Reference<LairAggroTask*> task = NULL;
	SceneObject* sourceObject = cast<SceneObject*>(arg1);
	AiAgent* agent = NULL;

	switch (eventType) {
	case ObserverEventType::OBJECTREMOVEDFROMZONE:
		despawnSpawns();
		return 1;
		break;
	case ObserverEventType::OBJECTDESTRUCTION:
		notifyDestruction(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1), (int)arg2);
		return 1;
		break;
	case ObserverEventType::DAMAGERECEIVED:
		// if there are living creatures, make them aggro
		if(getLivingCreatureCount() > 0 ){
			task = new LairAggroTask(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1), _this.get(), false);
			task->execute();
		}

		// if new creatures have spawned or there are live creatures near the lair
		if( checkForNewSpawns(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1)) || getLivingCreatureCount() > 0 )
			checkForHeal(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1));

		break;
	case ObserverEventType::AIMESSAGE:
		if (sourceObject == NULL) {
			Logger::console.error("LairObserverImplemenation::notifyObserverEvent does not have a source object");
			return 1;
		}

		for (i = 0; i < spawnedCreatures.size(); i++) {
			agent = cast<AiAgent*>(spawnedCreatures.get(i).get());
			if (agent == NULL)
				continue;

			agent->activateInterrupt(sourceObject, arg2);
		}

		break;
	}

	return 0;
}

void LairObserverImplementation::notifyDestruction(TangibleObject* lair, TangibleObject* attacker, int condition) {
	ThreatMap* threatMap = lair->getThreatMap();

	Reference<DisseminateExperienceTask*> deTask = new DisseminateExperienceTask(lair, threatMap, &spawnedCreatures);
	deTask->execute();

	threatMap->removeObservers();
	threatMap->removeAll(); // we can clear the original one

	if (lair->getZone() == NULL) {
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
	Vector<ManagedReference<CreatureObject*> > pets;

	for(int i = 0; i < spawnedCreatures.size(); i++){
		ManagedReference<CreatureObject*> cr = spawnedCreatures.get(i);

		if (cr->isPet()) {
			pets.add(cr);
			continue;
		}

		if(!cr->isDead() && cr->getZone() != NULL)
			alive++;
	}

	for (int j = 0; j < pets.size(); j++) {
		CreatureObject* pet = pets.get(j);
		spawnedCreatures.removeElement(pet);
	}

	return alive;
}

void LairObserverImplementation::doAggro(TangibleObject* lair, TangibleObject* attacker, bool allAttack){

	for (int i = 0; i < spawnedCreatures.size() ; ++i) {
			CreatureObject* creo = spawnedCreatures.get(i);

			if (creo->isDead() || creo->getZone() == NULL)
				continue;

			if (creo->isAiAgent() && attacker != NULL && (allAttack || (System::random(1) == 1))) {
				// TODO: only set defender if needed
				AiAgent* ai = cast<AiAgent*>( creo);
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

	if (healLairEvent == NULL) {
		healLairEvent = new HealLairObserverEvent(lair, attacker, _this.get());
		healLairEvent->schedule(1000);
	} else if (!healLairEvent->isScheduled()) {
		healLairEvent->schedule(1000);
	} else if (attacker != NULL)
		healLairEvent->setAttacker(attacker);
}

void LairObserverImplementation::healLair(TangibleObject* lair, TangibleObject* attacker){
	Locker locker(lair);

	if (lair->getZone() == NULL)
		return;

	int damageToHeal = 0;
	int lairMaxCondition = lair->getMaxCondition();

	for (int i = 0; i < spawnedCreatures.size() ; ++i) {
		CreatureObject* creo = spawnedCreatures.get(i);

		if (creo->isDead() || creo->getZone() == NULL)
			continue;

		//  TODO: Range check
		damageToHeal += lairMaxCondition / 100;

	}

	if (damageToHeal == 0)
		return;

	if (lair->getZone() == NULL)
		return;

	lair->healDamage(lair, 0, damageToHeal, true);

	PlayClientEffectObjectMessage* heal =
			new PlayClientEffectObjectMessage(lair, "clienteffect/healing_healdamage.cef", "");
	lair->broadcastMessage(heal, false);

	PlayClientEffectLoc* healLoc = new PlayClientEffectLoc("clienteffect/healing_healdamage.cef",
			lair->getZone()->getZoneName(), lair->getPositionX(),
			lair->getPositionZ(), lair->getPositionY());
	lair->broadcastMessage(healLoc, false);
}

bool LairObserverImplementation::checkForNewSpawns(TangibleObject* lair, TangibleObject* attacker, bool forceSpawn) {
	if (lair->getZone() == NULL)
		return false;

	if (spawnedCreatures.size() >= lairTemplate->getSpawnLimit() && !lairTemplate->hasBossMobs())
		return false;

	if (forceSpawn) {
		spawnNumber++;
	} else if (getMobType() == LairTemplate::NPC) {
		return false;
	} else {
		int conditionDamage = lair->getConditionDamage();
		int maxCondition = lair->getMaxCondition();

		switch (spawnNumber) {
		case 0:
			spawnNumber++;
			break;
		case 1:
			if (conditionDamage > (maxCondition / 10)) {
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
			if (lairTemplate->hasBossMobs() && conditionDamage > ((maxCondition * 9) / 10)) {
				spawnNumber++;
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

		VectorMap<String, int>* mobs = lairTemplate->getBossMobiles();

		for (int i = 0; i < mobs->size(); i++) {
			objectsToSpawn.put(mobs->elementAt(i).getKey(), mobs->elementAt(i).getValue());
		}

	} else {
		Vector<String>* mobiles = lairTemplate->getWeightedMobiles();
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

		if (spawnNumber != 4 && spawnedCreatures.size() >= lairTemplate->getSpawnLimit())
			return true;

		String templateToSpawn = objectsToSpawn.elementAt(i).getKey();
		int numberToSpawn = objectsToSpawn.get(templateToSpawn);

		CreatureTemplate* creatureTemplate = CreatureTemplateManager::instance()->getTemplate(templateToSpawn);

		if (creatureTemplate == NULL)
			continue;

		float tamingChance = creatureTemplate->getTame();

		CreatureManager* creatureManager = lair->getZone()->getCreatureManager();

		for (int j = 0; j < numberToSpawn; j++) {

			float x = lair->getPositionX() + (size - System::random(size * 20) / 10.0f);
			float y = lair->getPositionY() + (size - System::random(size * 20) / 10.0f);
			float z = lair->getZone()->getHeight(x, y);

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

				//Locker clocker(npc, lair);

				ai->setDespawnOnNoPlayerInRange(false);
				ai->setHomeLocation(x, z, y);
				ai->setRespawnTimer(0);
				ai->setHomeObject(lair);

				spawnedCreatures.add(creo);
			}
		}
	}

	if (spawnNumber == 4) {
		Reference<LairAggroTask*> task = new LairAggroTask(lair, attacker, _this.get(), true);
		task->schedule(1000);
	}

	return objectsToSpawn.size() > 0;
}

