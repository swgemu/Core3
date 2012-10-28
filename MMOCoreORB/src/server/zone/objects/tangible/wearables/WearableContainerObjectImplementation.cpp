/*
 * WearableContainerObjectImplementation.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: loshult
 */

#include "WearableContainerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

void WearableContainerObjectImplementation::applySkillModsTo(CreatureObject* creature, bool doCheck) {
	if (creature == NULL) {
		return;
	}

	for (int i = 0; i < wearableSkillMods.size(); ++i) {
		String name = wearableSkillMods.elementAt(i).getKey();
		int value = wearableSkillMods.get(name);

		creature->addSkillMod(SkillModManager::WEARABLE, name, value, true);
	}

	if(doCheck)
		SkillModManager::instance()->verifyWearableSkillMods(creature);
}

void WearableContainerObjectImplementation::removeSkillModsFrom(CreatureObject* creature) {
	if (creature == NULL) {
		return;
	}

	for (int i = 0; i < wearableSkillMods.size(); ++i) {
		String name = wearableSkillMods.elementAt(i).getKey();
		int value = wearableSkillMods.get(name);

		creature->removeSkillMod(SkillModManager::WEARABLE, name, value, true);
	}
}
