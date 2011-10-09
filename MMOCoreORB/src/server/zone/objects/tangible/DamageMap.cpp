/*
 * DamageMap.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

#include "DamageMap.h"

void DamageMapEntry::addDamage(WeaponObject* weapon, uint32 damage) {
	int idx = find(weapon);

	if (idx == -1) {
		put(weapon, damage);
	} else {
		uint32* dmg = &elementAt(idx).getValue();

		*dmg = *dmg + damage;
	}
}

void DamageMap::addDamage(CreatureObject* creo, uint32 damage) {
	int idx = find(creo);

	WeaponObject* weapon = creo->getWeapon();

	if (idx == -1) {
		DamageMapEntry entry;
		entry.addDamage(weapon, damage);

		put(creo, entry);
	} else {
		DamageMapEntry* entry = &elementAt(idx).getValue();

		entry->addDamage(weapon, damage);
	}
}

void DamageMap::dropDamage(CreatureObject* creo) {
	drop(creo);
}

uint32 DamageMap::getTotalDamage() {
	uint32 totalDamage = 0;

	for (int i = 0; i < size(); ++i) {
		DamageMapEntry* entry = &elementAt(i).getValue();

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();

			totalDamage += damage;
		}
	}

	return totalDamage;
}

CreatureObject* DamageMap::getHighestDamagePlayer() {
	uint32 maxDamage = 0;
	CreatureObject* player = NULL;

	for (int i = 0; i < size(); ++i) {
		DamageMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = 0;

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();

			totalDamage += damage;
		}

		CreatureObject* creature = elementAt(i).getKey();

		if (totalDamage > maxDamage && creature->isPlayerCreature()) {
			maxDamage = totalDamage;
			player = cast<CreatureObject*>(creature);
		}
	}

	return player;
}

CreatureObject* DamageMap::getHighestThreatCreature() {
	// TODO: add logic to this
	return getHighestDamagePlayer();
}
