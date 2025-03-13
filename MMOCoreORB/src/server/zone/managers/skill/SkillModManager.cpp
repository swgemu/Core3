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

// #define DEBUG_SKILL_MOD

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
		lua = nullptr;
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
	lua = nullptr;
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
	if (creature == nullptr) {
		return;
	}

	Locker locker(creature);

	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	SortedVector<uint64> usedObjects;
	usedObjects.setNoDuplicateInsertPlan();

#ifdef DEBUG_SKILL_MOD
	info(true) << "SkillModManager::verifyWearableSkillMods - Player: " << creature->getDisplayedName() << " ID: " << creature->getObjectID();
#endif // DEBUG_SKILL_MOD

	for (int i = 0; i < creature->getSlottedObjectsSize(); i++) {
		ManagedReference<TangibleObject*> object = creature->getSlottedObject(i).castTo<TangibleObject*>();

		// Check if null and verify mods have not been calculated already
		if (object == nullptr || usedObjects.contains(object->getObjectID())) {
			continue;
		}

		if (object->isWearableObject()) {
			WearableObject* wearable = cast<WearableObject*>(object.get());

			if (wearable == nullptr) {
				continue;
			}

			const VectorMap<String, int>* wearableSkillMods = wearable->getWearableSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Wearable - " << wearable->getDisplayedName() << " Total Wearable Mods: " << wearableSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < wearableSkillMods->size(); j++) {
				String name = wearableSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = wearableSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}

			// Template skill mods
			const VectorMap<String, int>* templateSkillMods = wearable->getTemplateSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Wearable - " << wearable->getDisplayedName() << " Total Template Mods: " << templateSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < templateSkillMods->size(); j++) {
				String name = templateSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = templateSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Template Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}
		} else if (object->isWearableContainerObject()) {
			WearableContainerObject* wearable = cast<WearableContainerObject*>(object.get());

			if (wearable == nullptr) {
				continue;
			}

			// Wearable skill mods
			const VectorMap<String, int>* wearableSkillMods = wearable->getWearableSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Wearable Container - " << wearable->getDisplayedName() << " Total Wearable Mods: " << wearableSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < wearableSkillMods->size(); j++) {
				String name = wearableSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = wearableSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}

			// Template skill mods
			const VectorMap<String, int>* templateSkillMods = wearable->getTemplateSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Wearable Container - " << wearable->getDisplayedName() << " Total Template Mods: " << templateSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < templateSkillMods->size(); j++) {
				String name = templateSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = templateSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Template Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}
		} else if (object->isWeaponObject()) {
			WeaponObject* weapon = cast<WeaponObject*>(object.get());

			if (weapon == nullptr) {
				continue;
			}

			const VectorMap<String, int>* wearableSkillMods = weapon->getWearableSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Weapon - " << weapon->getDisplayedName() << " Total Wearable Mods: " << wearableSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < wearableSkillMods->size(); j++) {
				String name = wearableSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = wearableSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}

			// Template skill mods
			const VectorMap<String, int>* templateSkillMods = weapon->getTemplateSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Weapon - " << weapon->getDisplayedName() << " Total Template Mods: " << templateSkillMods->size();
#endif // DEBUG_SKILL_MOD

			for (int j = 0; j < templateSkillMods->size(); j++) {
				String name = templateSkillMods->elementAt(j).getKey();

				if (isWearableModDisabled(name)) {
					continue;
				}

				int value = templateSkillMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Template Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}
		}

		usedObjects.put(object->getObjectID());
	}

	if (!compareMods(mods, creature, SkillModManager::WEARABLE)) {
		warning() << "Wearable mods don't match for " << creature->getFirstName() << " ID: " << creature->getObjectID();
	}
}

void SkillModManager::verifyStructureSkillMods(TangibleObject* tano) {
	if (tano == nullptr || !tano->isCreatureObject()) {
		return;
	}

	auto creature = tano->asCreatureObject();

	if (creature == nullptr) {
		return;
	}

#ifdef DEBUG_SKILL_MOD
	info(true) << "SkillModManager::verifyStructureSkillMods - Player: " << creature->getDisplayedName() << " ID: " << creature->getObjectID();
#endif // DEBUG_SKILL_MOD

	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	ManagedReference<SceneObject*> parent = creature->getRootParent();

	if (parent == nullptr) {
		ManagedReference<CampSiteActiveArea*> campArea = creature->getCurrentCamp();

		if (campArea != nullptr) {
			parent = campArea->getCamp();
		}
	}

	if (parent != nullptr && parent->isStructureObject()) {
		StructureObject* structure = parent.castTo<StructureObject*>();

		if (structure != nullptr) {
			const auto templateMods = structure->getTemplateSkillMods();

#ifdef DEBUG_SKILL_MOD
			info(true) << "Checking Structure - " << structure->getDisplayedName() << " Total Template Mods: " << templateMods->size();
#endif // DEBUG_SKILL_MOD

			for (int i = 0; i < templateMods->size(); i++) {
				String name = templateMods->elementAt(i).getKey();
				int value = templateMods->get(name);

				if (mods.contains(name)) {
					value += mods.get(name);
				}

#ifdef DEBUG_SKILL_MOD
				info(true) << "Template Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

				mods.put(name, value);
			}
		}
	}

	if (!compareMods(mods, creature, SkillModManager::STRUCTURE)) {
		warning() << "Structure mods don't match for Player: " << creature->getFirstName() << " ID: " << creature->getObjectID();
	}
}

void SkillModManager::verifySkillBoxSkillMods(CreatureObject* creature) {
	if (creature == nullptr) {
		return;
	}

	Locker locker(creature);

#ifdef DEBUG_SKILL_MOD
	info(true) << "SkillModManager::verifySkillBoxSkillMods - Player: " << creature->getDisplayedName() << " ID: " << creature->getObjectID();
#endif // DEBUG_SKILL_MOD

	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	const SkillList* skillList = creature->getSkillList();

	for (int i = 0; i < skillList->size(); i++) {
		Reference<Skill*> skill = skillList->get(i);
		auto skillMods = skill->getSkillModifiers();

#ifdef DEBUG_SKILL_MOD
		info(true) << "Skill: " << skill->getSkillName() << " Total Mods: " << skillMods->size();
#endif // DEBUG_SKILL_MOD

		for (int j = 0; j < skillMods->size(); j++) {
			const String& name = skillMods->elementAt(j).getKey();
			int value = skillMods->get(name);

			if (mods.contains(name)) {
				value += mods.get(name);
			}

#ifdef DEBUG_SKILL_MOD
			info(true) << "Skill Modifier: " << name << " Value: " << value;
#endif // DEBUG_SKILL_MOD

			mods.put(name, value);
		}
	}

	if (!compareMods(mods, creature, SkillModManager::SKILLBOX)) {
		warning() << "SkillBox mods don't match for " << creature->getFirstName() << " ID: " << creature->getObjectID();
	}
}

void SkillModManager::verifyBuffSkillMods(CreatureObject* creature) {
	Locker locker(creature);

	VectorMap<String, int> mods;
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	const BuffList* buffList = creature->getBuffList();
	for (int i = 0; i < buffList->getBuffListSize(); i++) {
		ManagedReference<Buff*> buff = buffList->getBuffByIndex(i);
		const VectorMap<String, int>* skillMods = buff->getSkillModifiers();

		for (int j = 0; j < skillMods->size(); j++) {
			const String& name = skillMods->elementAt(j).getKey();
			int value = skillMods->elementAt(j).getValue();

			if (mods.contains(name)) {
				value += mods.get(name);
			}

			mods.put(name, value);
		}
	}

	if (!compareMods(mods, creature, SkillModManager::BUFF)) {
		warning() << "Buff mods don't match for Player: " << creature->getFirstName() << " ID: " << creature->getObjectID();
	}
}

bool SkillModManager::compareMods(VectorMap<String, int>& mods, CreatureObject* creature, uint32 type) {
	mods.setAllowOverwriteInsertPlan();
	mods.setNullValue(0);

	auto skillModMutex = creature->getSkillModMutex();

	Locker skillModLocker(skillModMutex);

	SkillModList* skillModList = creature->getSkillModList();

	if (skillModList == nullptr) {
		error() << "SkillmodList is a nullptr for " + creature->getFirstName() << " ID: " << creature->getObjectID();
		return false;
	}

	const SkillModGroup* group = skillModList->getSkillModGroup(type);

	if (group == nullptr) {
		error() << "SkillModGroup is a nullptr for " + creature->getFirstName() << " ID: " << creature->getObjectID();
		return false;
	}

	bool match = true;

	StringBuffer compare;
	compare << "SkillModManager::compareMods\nPlayer: " << creature->getDisplayedName() << " ID: " << creature->getObjectID() << " Modifier Type: " << type << " Mod Group Size: " << group->size() << "\n";

	if (group->size() > 0) {
		SkillModGroup checkGroup = *group;

		// Check the SkillModGroup for the passed type
		for (int i = 0; i < checkGroup.size(); i++) {
			String key = checkGroup.elementAt(i).getKey();
			int value = checkGroup.elementAt(i).getValue();

			int properValue = mods.get(key);
			mods.drop(key);

			compare << "Modifier: " << key << " Current Value on Player: " << value << " Proper Value from Equipped Items: " << properValue << "\n";

			// If the mod values are different, adjust to proper value
			if (value != properValue) {
				creature->removeSkillMod(type, key, value, false);
				creature->addSkillMod(type, key, properValue, true);

				match = false;
			}
		}
	}

	if (type == SkillModManager::WEARABLE) {
		const SkillModGroup* templateGroup = skillModList->getSkillModGroup(TEMPLATE);

		if (templateGroup != nullptr) {
			compare << "Template Modifier Group Size: " << templateGroup->size() << "\n";

			SkillModGroup tempGroup = *templateGroup;

			// Check the TEMPLATE SkillModGroup
			for (int i = 0; i < tempGroup.size(); i++) {
				String key = tempGroup.elementAt(i).getKey();
				int value = tempGroup.elementAt(i).getValue();

				int properValue = mods.get(key);
				mods.drop(key);

				compare << "TEMPLATE Modifier: " << key << " Current Value on Player: " << value << " Proper Value from Equipped Items: " << properValue << "\n";

				// If the mod values are different, adjust to proper value
				if (value != properValue) {
					creature->removeSkillMod(TEMPLATE, key, value, true);
					creature->addSkillMod(TEMPLATE, key, properValue, true);

					match = false;
				}
			}
		}
	}

	// Playery current has more modifiers then their equipped items should allow for
	if (!mods.isEmpty()) {
		match = false;

		// Player has improper mods on them, remove the remaining
		for (int i = 0; i < mods.size(); i++) {
			String key = mods.elementAt(i).getKey();
			int value = mods.elementAt(i).getValue();

			compare << "Excess Modifier: " << key << " Value: " << value << "\n";
		}
	}

	if (match == false) {
#ifdef DEBUG_SKILL_MOD
		// Send output to log
		creature->info(true) << compare;
#endif // DEBUG_SKILL_MOD

		// Only send system message if player is actively set to debug
		auto ghost = creature->getPlayerObject();

		if (ghost != nullptr && ghost->getDebug()) {
			creature->sendSystemMessage(compare.toString());
		}
	}

	return match;
}
