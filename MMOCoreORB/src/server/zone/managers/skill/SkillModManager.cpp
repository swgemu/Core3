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

#include "SkillModManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/area/CampSiteActiveArea.h"

SkillModManager::SkillModManager()
		: Logger("SkillModManager") {
	skillModMin.setNullValue(0);
	skillModMax.setNullValue(0);
	init();
}

SkillModManager::~SkillModManager() {

}

void SkillModManager::init() {

	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/skill_mod_manager.lua")) {
		error("Cannot read configuration, using default");
		setDefaults();
		return;
	}

	LuaObject skillLimits = lua->getGlobalObject("skillModLimits");

	if (!skillLimits.isValidTable()) {
		error("Invalid configuration");
		setDefaults();
		return;
	}

	for(int i = 1; i <= skillLimits.getTableSize(); ++i) {
		LuaObject entry = skillLimits.getObjectAt(i);

		uint32 type = entry.getIntAt(1);
		int min = entry.getIntAt(2);
		int max = entry.getIntAt(3);

		skillModMin.put(type, min);
		skillModMax.put(type, max);

		entry.pop();
	}

	skillLimits.pop();
	delete lua;
	lua = NULL;
	return;

}

void SkillModManager::setDefaults() {

	skillModMin.put(WEARABLE, -25);
	skillModMax.put(WEARABLE, 25);

	skillModMin.put(ABILITYBONUS, -125);
	skillModMax.put(ABILITYBONUS, 125);

	skillModMin.put(STRUCTURE, -125);
	skillModMax.put(STRUCTURE, 125);

	skillModMin.put(BUFF, -125);
	skillModMax.put(BUFF, 125);
}

void SkillModManager::verifyWearableSkillMods(CreatureObject* creature) {

	Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	for(int i = 0; i < creature->getSlottedObjectsSize(); ++i) {
		ManagedReference<TangibleObject*> object = cast<TangibleObject*>(creature->getSlottedObject(i));
		if(object == NULL)
			continue;

		if(object->isWearableObject()) {
			WearableObject* wearable = cast<WearableObject*>(object.get());
			if(wearable != NULL) {

				VectorMap<String, int>* wearableSkillMods = wearable->getWearableSkillMods();

				for (int i = 0; i < wearableSkillMods->size(); ++i) {
					String name = wearableSkillMods->elementAt(i).getKey();
					int value = wearableSkillMods->get(name);

					if(mods.contains(name)) {
						value += mods.get(name);
					}

					mods.put(name, value);
				}
			}
		}

		if(object->isWeaponObject()) {

		}
	}

	if(!compareMods(mods, creature, WEARABLE)) {
		error("Wearable mods don't match for " + creature->getFirstName());
	}
}

void SkillModManager::verifyStructureSkillMods(TangibleObject* tano) {

	if(!tano->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(tano);
	if(creature == NULL)
		return;

	//Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	ManagedReference<SceneObject*> parent = creature->getRootParent();

	if (parent == NULL) {
		if(creature->getCurrentCamp() != NULL) {
			ManagedReference<CampSiteActiveArea*> campArea = creature->getCurrentCamp();
			parent = campArea->getCamp();
		}
	}

	if (parent != NULL && parent->isStructureObject()) {
		StructureObject* structure = cast<StructureObject*>(parent.get());

		VectorMap<String, int>* templateMods = structure->getTemplateSkillMods();

		for(int i = 0; i < templateMods->size(); ++i) {

			String name = templateMods->elementAt(i).getKey();
			int value = templateMods->get(name);

			if(mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}


	if(!compareMods(mods, creature, STRUCTURE)) {
		error("Structure mods don't match for " + creature->getFirstName());
	}
}

void SkillModManager::verifySkillBoxSkillMods(CreatureObject* creature) {

	Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	SkillList* skillList = creature->getSkillList();
	for(int i = 0; i < skillList->size(); ++i) {
		Reference<Skill*> skill = skillList->get(i);
		VectorMap<String, int>* skillMods = skill->getSkillModifiers();
		for(int j = 0; j < skillMods->size(); ++j) {
			String name = skillMods->elementAt(j).getKey();
			int value = skillMods->get(name);

			if(mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}

	if(!compareMods(mods, creature, SKILLBOX)) {
		error("SkillBox mods don't match for " + creature->getFirstName());
	}
}

void SkillModManager::verifyBuffSkillMods(CreatureObject* creature) {

	Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	BuffList* buffList = creature->getBuffList();
	for(int i = 0; i < buffList->getBuffListSize(); ++i) {
		ManagedReference<Buff*> buff = buffList->getBuffByIndex(i);
		VectorMap<String, int>* skillMods = buff->getSkillModifiers();
		for(int j = 0; j < skillMods->size(); ++j) {
			String name = skillMods->elementAt(j).getKey();
			int value = skillMods->get(name);

			if(mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}

	if(!compareMods(mods, creature, BUFF)) {
		error("Buff mods don't match for " + creature->getFirstName());
	}
}

bool SkillModManager::compareMods(VectorMap<String, int> mods, CreatureObject* creature, uint32 type) {

	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	Mutex* skillModMutex = creature->getSkillModMutex();

	Locker skillModLocker(skillModMutex);

	SkillModList* skillModList = creature->getSkillModList();

	if(skillModList == NULL) {
		error("NULL SkillmodList for " + creature->getFirstName());
		return false;
	}

	SkillModGroup* group = skillModList->getSkillModGroup(type);

	if(group == NULL){
		error("NULL SkillModGroup for " + creature->getFirstName());
		return false;
	}

	bool match = true;

	StringBuffer compare;
	compare << "	" << "SkillMod" << "  " << "Player" << "	" << "Computed" << endl;

	for(int i = 0; i < group->size(); ++i) {
		String key = group->elementAt(i).getKey();
		int value = group->get(key);

		int currentValue = mods.get(key);
		mods.drop(key);

		compare << "	" << key << "	" << value << "	" << currentValue << endl;

		if(value != currentValue) {
			if(currentValue == 0)
				group->drop(key);
			else
				group->put(key, currentValue);

			match = false;
		}
	}

	if(!mods.isEmpty()) {
		match = false;
	}

	if(match == false) {
		error(compare.toString());

		if(creature->getPlayerObject() != NULL) {
			if(creature->getPlayerObject()->getDebug()) {
				creature->sendSystemMessage(compare.toString());
			}
		}
	}

	return match;
}
