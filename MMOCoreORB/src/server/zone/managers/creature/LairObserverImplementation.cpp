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

#include "LairObserver.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/NonPlayerCreatureObject.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/Zone.h"
#include "HealLairObserverEvent.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/templates/TemplateManager.h"

int LairObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	switch (eventType) {
	case ObserverEventType::OBJECTDESTRUCTION:
		notifyDestruction(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1), (int)arg2);
		return 1;
		break;
	case ObserverEventType::DAMAGERECEIVED:

		checkForNewSpawns(cast<TangibleObject*>(observable));
		checkForHeal(cast<TangibleObject*>(observable), cast<TangibleObject*>(arg1));

		break;
	}

	return 0;
}

void LairObserverImplementation::notifyDestruction(TangibleObject* lair, TangibleObject* attacker, int condition) {
	ThreatMap* threatMap = lair->getThreatMap();

	ThreatMap copyThreatMap(*threatMap);
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

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* obj = spawnedCreatures.get(i);

		if (obj->isAiAgent())
			(cast<AiAgent*>(obj))->setDespawnOnNoPlayerInRange(true);
	}

	spawnedCreatures.removeAll();

	PlayerManager* playerManager = lair->getZoneServer()->getPlayerManager();
	playerManager->disseminateExperience(lair, &copyThreatMap);
}

void LairObserverImplementation::checkForHeal(TangibleObject* lair, TangibleObject* attacker, bool forceNewUpdate) {
	if (lair->isDestroyed())
		return;

	bool doUpdate = forceNewUpdate;

	int conditionDamage = lair->getConditionDamage();
	int maxCondition = lair->getMaxCondition();

	if (!doUpdate)
		doUpdate = (conditionDamage >= maxCondition / 3);

	if (!doUpdate)
		return;

	if (healLairEvent == NULL) {
		healLairEvent = new HealLairObserverEvent(lair, attacker, _this);

		healLairEvent->schedule(1000);
	} else if (!healLairEvent->isScheduled()) {
		healLairEvent->schedule(1000);
	} else if (attacker != NULL)
		healLairEvent->setAttacker(attacker);
}

void LairObserverImplementation::healLair(TangibleObject* lair, TangibleObject* attacker) {
	Locker locker(lair);

	if (lair->getZone() == NULL)
		return;

	int damageToHeal = 0;

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* creo = spawnedCreatures.get(i);

		if (creo->isDead() || creo->getZone() == NULL)
			continue;

		damageToHeal += 100;

		if (creo->isAiAgent() && System::random(1) == 1 && attacker != NULL) {
			AiAgent* ai = cast<AiAgent*>( creo);

			Locker clocker(creo, lair);

			creo->setDefender(attacker);
		}
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

void LairObserverImplementation::checkForNewSpawns(TangibleObject* lair, bool forceSpawn) {
	if (lair->getZone() == NULL)
		return;

	if (spawnedCreatures.size() >= lairTemplate->getSpawnLimit())
		return;

	if (!forceSpawn && System::random(3) == 1)
		return;

	//SortedVector<uint32>* objectsToSpawn = getObjectsToSpawn();

	VectorMap<String, uint32>* objectsToSpawn = lairTemplate->getMobiles();

	String templateToSpawn = objectsToSpawn->elementAt((int)System::random(objectsToSpawn->size() - 1)).getKey();

	CreatureManager* creatureManager = lair->getZone()->getCreatureManager();

	float x = lair->getPositionX() + (20.0f - System::random(400) / 10.0f);
	float y = lair->getPositionY() + (20.0f - System::random(400) / 10.0f);
	float z = lair->getZone()->getHeight(x, y);

	int defaultLevel = objectsToSpawn->get(templateToSpawn);

	if (minDifficulty != 0 || maxDifficulty != 0) {
		defaultLevel = minDifficulty + System::random(abs(maxDifficulty - minDifficulty));
	}

	ManagedReference<CreatureObject*> creature = creatureManager->spawnCreatureWithLevel(templateToSpawn.hashCode(), defaultLevel, x, z, y);

	if (creature == NULL)
		return;

	if (!creature->isAiAgent()) {
		error("spawned non player creature with template " + templateToSpawn);
	} else {
		AiAgent* npc = cast<AiAgent*>( creature.get());

		//Locker clocker(npc, lair);

		npc->setDespawnOnNoPlayerInRange(false);
		npc->setHomeLocation(x, z, y);
		npc->setRespawnTimer(0);

		spawnedCreatures.add(creature);
	}
}

