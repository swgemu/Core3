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

	if (strongCreo == nullptr)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		strongCreo->addSkillMod(SkillModManager::BUFF, key, value, true);
	}

	strongCreo->updateSpeedAndAccelerationMods();
}

void PrivateSkillMultiplierBuffImplementation::removeSkillModifiers() {
	ManagedReference<CreatureObject*> strongCreo = creature.get();

	if (strongCreo == nullptr)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		int currentMod = strongCreo->getSkillMod(key);
		int newMod = currentMod <= value ? -currentMod : -value;

		strongCreo->addSkillMod(SkillModManager::BUFF, key, newMod, true);
	}

	strongCreo->updateSpeedAndAccelerationMods();
}



