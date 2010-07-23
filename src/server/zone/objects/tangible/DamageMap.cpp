/*
 * DamageMap.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "server/zone/objects/player/PlayerCreature.h"
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

void DamageMap::addDamage(PlayerCreature* player, uint32 damage) {
	int idx = find(player);

	WeaponObject* weapon = player->getWeapon();

	if (idx == -1) {
		DamageMapEntry entry;
		entry.addDamage(weapon, damage);

		put(player, entry);
	} else {
		DamageMapEntry* entry = &elementAt(idx).getValue();

		entry->addDamage(weapon, damage);
	}
}

void DamageMap::dropDamage(PlayerCreature* player) {
	drop(player);
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

PlayerCreature* DamageMap::getHighestDamagePlayer() {
	uint32 maxDamage = 0;
	PlayerCreature* player = NULL;

	for (int i = 0; i < size(); ++i) {
		DamageMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = 0;

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();

			totalDamage += damage;
		}

		if (totalDamage > maxDamage) {
			maxDamage = totalDamage;
			player = elementAt(i).getKey();
		}
	}

	return player;
}
