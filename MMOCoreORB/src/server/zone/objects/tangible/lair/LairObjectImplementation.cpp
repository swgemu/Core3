/*
 * LairObjectImplementation.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "LairObject.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/NonPlayerCreatureObject.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "HealLairEvent.h"

void LairObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	if (templateData->isLairObjectTemplate())
		lairTemplate = (LairObjectTemplate*) templateData;
}

void LairObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	lairTemplate = dynamic_cast<LairObjectTemplate*>(TemplateManager::instance()->getTemplate(serverObjectCRC));
}

int LairObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	TangibleObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);

	checkForNewSpawns();
	checkForHeal(attacker);

	if (attacker->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) attacker;

		if (damage > 0)
			damageMap.addDamage(player, damage);
	}

	return 0;
}

int LairObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	int ret = TangibleObjectImplementation::notifyObjectDestructionObservers(attacker, condition);

	if (getZone() == NULL)
		return ret;

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(_this, "clienteffect/lair_damage_heavy.cef", "");
	broadcastMessage(explode, false);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", getZone()->getZoneName(), positionX, positionZ, positionY);
	broadcastMessage(explodeLoc, false);

	removeFromZone();

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* obj = spawnedCreatures.get(i);

		if (obj->isAiAgent())
			((AiAgent*)obj)->setDespawnOnNoPlayerInRange(true);
	}

	DamageMap copyDamageMap(damageMap);
	damageMap.removeAll(); // we can clear the original one

	spawnedCreatures.removeAll();

	PlayerManager* playerManager = getZoneServer()->getPlayerManager();
	playerManager->disseminateExperience(_this, &copyDamageMap);

	return ret;
}

void LairObjectImplementation::checkForHeal(TangibleObject* attacker, bool forceNewUpdate) {
	if (isDestroyed())
		return;

	bool doUpdate = forceNewUpdate;

	if (!doUpdate)
		doUpdate = (conditionDamage >= maxCondition / 3);

	if (!doUpdate)
		return;

	if (healLairEvent == NULL) {
		healLairEvent = new HealLairEvent(_this, attacker);

		healLairEvent->schedule(1000);
	} else if (!healLairEvent->isScheduled()) {
		healLairEvent->schedule(1000);
	} else if (attacker != NULL)
		healLairEvent->setAttacker(attacker);
}

void LairObjectImplementation::healLair(TangibleObject* attacker) {
	if (getZone() == NULL)
		return;

	int damageToHeal = 0;

	for (int i = 0; i < spawnedCreatures.size(); ++i) {
		CreatureObject* creo = spawnedCreatures.get(i);

		if (creo->isDead() || creo->getZone() == NULL)
			continue;

		damageToHeal += 100;

		if (creo->isAiAgent() && System::random(1) == 1 && attacker != NULL) {
			AiAgent* ai = (AiAgent*) creo;

			Locker clocker(creo, _this);

			creo->setDefender(attacker);
		}
	}

	if (damageToHeal == 0)
		return;

	healDamage(_this, 0, damageToHeal, true);

	PlayClientEffectObjectMessage* heal =
			new PlayClientEffectObjectMessage(_this, "clienteffect/healing_healdamage.cef", "");
	broadcastMessage(heal, false);

	PlayClientEffectLoc* healLoc = new PlayClientEffectLoc("clienteffect/healing_healdamage.cef",
			getZone()->getZoneName(), getPositionX(),
			getPositionZ(), getPositionY());
	broadcastMessage(healLoc, false);
}

void LairObjectImplementation::checkForNewSpawns() {
	if (getZone() == NULL)
		return;

	if (spawnedCreatures.size() >= getMaxObjectsToSpawn())
		return;

	if (System::random(3) == 1)
		return;

	SortedVector<uint32>* objectsToSpawn = getObjectsToSpawn();

	uint32 templateToSpawn = objectsToSpawn->get(System::random(objectsToSpawn->size() - 1));

	CreatureManager* creatureManager = getZone()->getCreatureManager();

	float x = positionX + (20.0f - System::random(400) / 10.0f);
	float y = positionY + (20.0f - System::random(400) / 10.0f);
	float z = getZone()->getHeight(x, y);

	ManagedReference<CreatureObject*> creature = creatureManager->spawnCreature(templateToSpawn, 0, x, z, y);

	if (creature == NULL)
		return;

	if (!creature->isAiAgent()) {
		error("spawned non player creature with template " + TemplateManager::instance()->getTemplateFile(templateToSpawn));
	} else {
		AiAgent* npc = (AiAgent*) creature.get();

		Locker clocker(npc, _this);

		npc->setDespawnOnNoPlayerInRange(false);
		npc->setHomeLocation(x, z, y);

		spawnedCreatures.add(creature);
	}
}
