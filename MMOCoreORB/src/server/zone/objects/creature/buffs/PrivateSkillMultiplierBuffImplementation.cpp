/*
 * PrivateSkillMultiplierBuffImplementation.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: swgemu
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/PrivateSkillMultiplierBuff.h"

void PrivateSkillMultiplierBuffImplementation::applySkillModifiers() {
	ManagedReference<CreatureObject*> strongCreo = creature.get();
	if (strongCreo == NULL)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		int prevMod = strongCreo->getSkillMod(key);

		strongCreo->addSkillMod(SkillModManager::BUFF, key, prevMod == 0 ? value : prevMod*(value-1), true);
	}

	creature.get()->updateSpeedAndAccelerationMods();
}

void PrivateSkillMultiplierBuffImplementation::removeSkillModifiers() {
	ManagedReference<CreatureObject*> strongCreo = creature.get();
	if (strongCreo == NULL)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		int prevMod = strongCreo->getSkillMod(key);

		strongCreo->addSkillMod(SkillModManager::BUFF, key, prevMod <= value ? -prevMod : (int)(prevMod*((1/(float)(value))-1)), true);

	}

	creature.get()->updateSpeedAndAccelerationMods();
}



