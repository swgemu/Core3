/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "SkillModManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/wearables/WearableContainerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/area/CampSiteActiveArea.h"

SkillModManager::SkillModManager()
		: Logger("SkillModManager") {
	skillModMin.setNullValue(0);
	skillModMax.setNullValue(0);
	disabledWearableSkillMods.setNoDuplicateInsertPlan();
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
		delete lua;
		lua = NULL;
		return;
	}

	LuaObject skillLimits = lua->getGlobalObject("skillModLimits");

	if (!skillLimits.isValidTable()) {
		error("Invalid configuration");
		setDefaults();
	} else {

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
	}

	LuaObject disabledMods = lua->getGlobalObject("disabledWearableSkillMods");

	if (disabledMods.isValidTable()) {
		for(int i = 1; i <= disabledMods.getTableSize(); ++i) {
			String mod = disabledMods.getStringAt(i);
			disabledWearableSkillMods.put(mod);
		}

		disabledMods.pop();
	}

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

	skillModMin.put(DROID, -110);
	skillModMax.put(DROID, 110);

}

void SkillModManager::verifyWearableSkillMods(CreatureObject* creature) {

	Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	SortedVector<ManagedReference<SceneObject*> > usedObjects;
	usedObjects.setNoDuplicateInsertPlan();

	for(int i = 0; i < creature->getSlottedObjectsSize(); ++i) {
		ManagedReference<TangibleObject*> object = creature->getSlottedObject(i).castTo<TangibleObject*>();
		if(object == NULL || usedObjects.contains(object.get()))
			continue;

		if(object->isWearableObject()) {
			WearableObject* wearable = cast<WearableObject*>(object.get());
			if(wearable != NULL) {

				VectorMap<String, int>* wearableSkillMods = wearable->getWearableSkillMods();

				for (int j = 0; j < wearableSkillMods->size(); ++j) {
					String name = wearableSkillMods->elementAt(j).getKey();

					if (isWearableModDisabled(name))
						continue;

					int value = wearableSkillMods->get(name);

					if(mods.contains(name)) {
						value += mods.get(name);
					}

					mods.put(name, value);
				}
			}
		} else if (object->isWearableContainerObject()) {
			WearableContainerObject* wearable = cast<WearableContainerObject*>(object.get());
			if(wearable != NULL) {

				VectorMap<String, int>* wearableSkillMods = wearable->getWearableSkillMods();

				for (int j = 0; j < wearableSkillMods->size(); ++j) {
					String name = wearableSkillMods->elementAt(j).getKey();

					if (isWearableModDisabled(name))
						continue;

					int value = wearableSkillMods->get(name);

					if(mods.contains(name)) {
						value += mods.get(name);
					}

					mods.put(name, value);
				}
			}
		} else if (object->isWeaponObject()) {
			WeaponObject* weapon = cast<WeaponObject*>(object.get());
			if(weapon != NULL) {

				VectorMap<String, int>* wearableSkillMods = weapon->getWearableSkillMods();

				for (int j = 0; j < wearableSkillMods->size(); ++j) {
					String name = wearableSkillMods->elementAt(j).getKey();

					if (isWearableModDisabled(name))
						continue;

					int value = wearableSkillMods->get(name);

					if(mods.contains(name)) {
						value += mods.get(name);
					}

					mods.put(name, value);
				}
			}
		}

		usedObjects.put(object.get());
	}

	if(!compareMods(mods, creature, WEARABLE)) {
		warning("Wearable mods don't match for " + creature->getFirstName());
	}
}

void SkillModManager::verifyStructureSkillMods(TangibleObject* tano) {

	if (!tano->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(tano);
	if (creature == NULL)
		return;

	//Locker locker(creature);
	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	ManagedReference<SceneObject*> parent = creature->getRootParent();

	if (parent == NULL) {
		if (creature->getCurrentCamp() != NULL) {
			ManagedReference<CampSiteActiveArea*> campArea = creature->getCurrentCamp();
			parent = campArea->getCamp();
		}
	}

	if (parent != NULL && parent->isStructureObject()) {
		StructureObject* structure = parent.castTo<StructureObject*>();

		VectorMap<String, int>* templateMods = structure->getTemplateSkillMods();

		for (int i = 0; i < templateMods->size(); ++i) {

			String name = templateMods->elementAt(i).getKey();
			int value = templateMods->get(name);

			if(mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}


	if (!compareMods(mods, creature, STRUCTURE)) {
		warning("Structure mods don't match for " + creature->getFirstName());
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
		auto skillMods = skill->getSkillModifiers();
		for(int j = 0; j < skillMods->size(); ++j) {
			const String& name = skillMods->elementAt(j).getKey();
			int value = skillMods->get(name);

			if(mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}

	if(!compareMods(mods, creature, SKILLBOX)) {
		warning("SkillBox mods don't match for " + creature->getFirstName());
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
		warning("Buff mods don't match for " + creature->getFirstName());
	}
}

bool SkillModManager::compareMods(VectorMap<String, int>& mods, CreatureObject* creature, uint32 type) {

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
	compare << endl << "	" << "SkillMod" << "  " << "Player" << "	" << "Computed" << endl;

	for(int i = 0; i < group->size(); ++i) {
		String key = group->elementAt(i).getKey();
		int value = group->get(key);

		int currentValue = mods.get(key);
		mods.drop(key);

		compare << "	" << key << "	" << value << "	" << currentValue << endl;

		if(value != currentValue) {

			creature->removeSkillMod(type, key, value, true);
			creature->addSkillMod(type, key, currentValue, true);

			match = false;
		}
	}

	if(!mods.isEmpty()) {
		match = false;

		for (int i = 0; i < mods.size(); i++) {
			String key = mods.elementAt(i).getKey();
			int currentValue = mods.get(key);

			compare << "	" << key << "	" << "none" << "	" << currentValue << endl;
		}
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
