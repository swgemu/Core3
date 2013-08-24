/*
 * LootManagerImplementation.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: Kyle
 */

#include "engine/engine.h"

#include "LootManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/LootItemTemplate.h"
#include "server/zone/templates/LootGroupTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "LootGroupMap.h"

void LootManagerImplementation::initialize() {
	lua = new Lua();
	lua->init();

	info("Loading configuration.");

	if(!loadConfigData()) {

		loadDefaultConfig();

		info("Failed to load configuration values. Using default.");
	}

	lootGroupMap = LootGroupMap::instance();
	lootGroupMap->initialize();

	info("Loaded " + String::valueOf(lootableMods.size()) + " lootable stat mods.", true);
	info("Loaded " + String::valueOf(lootGroupMap->countLootItemTemplates()) + " loot items.", true);
	info("Loaded " + String::valueOf(lootGroupMap->countLootGroupTemplates()) + " loot groups.", true);

	info("Initialized.");
}

bool LootManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/loot_manager.lua");
}

bool LootManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;
	yellowChance = lua->getGlobalFloat("yellowChance");
	yellowModifier = lua->getGlobalFloat("yellowModifier");
	exceptionalChance = lua->getGlobalFloat("exceptionalChance");
	exceptionalModifier = lua->getGlobalFloat("exceptionalModifier");
	legendaryChance = lua->getGlobalFloat("legendaryChance");
	legendaryModifier = lua->getGlobalFloat("legendaryModifier");
	skillModChance = lua->getGlobalFloat("skillModChance");

	LuaObject lootableModsTable = lua->getGlobalObject("lootableStatMods");


	if (!lootableModsTable.isValidTable())
		return false;

	for (int i = 1; i <= lootableModsTable.getTableSize(); ++i) {
		String mod = lootableModsTable.getStringAt(i);
		lootableMods.put(mod);
	}

	lootableModsTable.pop();

	return true;
}

void LootManagerImplementation::loadDefaultConfig() {

}

void LootManagerImplementation::setInitialObjectStats(LootItemTemplate* templateObject, CraftingValues* craftingValues, TangibleObject* prototype) {
	SharedTangibleObjectTemplate* tanoTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(prototype->getObjectTemplate());

	if (tanoTemplate != NULL) {
		Vector<String>* titles = tanoTemplate->getExperimentalGroupTitles();
		Vector<String>* props = tanoTemplate->getExperimentalSubGroupTitles();
		Vector<float>* mins = tanoTemplate->getExperimentalMin();
		Vector<float>* maxs = tanoTemplate->getExperimentalMax();
		Vector<short>* prec = tanoTemplate->getExperimentalPrecision();

		for (int i = 0; i < props->size(); ++i) {
			String title = titles->get(i);
			String property = props->get(i);

			if (craftingValues->hasProperty(property))
				continue;

			craftingValues->addExperimentalProperty(property, property, mins->get(i), maxs->get(i), prec->get(i), false, CraftingManager::LINEARCOMBINE);
			if (title == "null")
				craftingValues->setHidden(property);
		}
	}

	Vector<String>* customizationData = templateObject->getCustomizationStringNames();
	Vector<Vector<int> >* customizationValues = templateObject->getCustomizationValues();

	for (int i = 0; i < customizationData->size(); ++i) {
		String customizationString = customizationData->get(i);
		Vector<int>* values = &customizationValues->get(i);

		if (values->size() > 0) {
			int randomValue = values->get(System::random(values->size() - 1));

			prototype->setCustomizationVariable(customizationString, randomValue, false);
		}
	}
}

void LootManagerImplementation::setCustomObjectName(TangibleObject* object, LootItemTemplate* templateObject) {
	String customName = templateObject->getCustomObjectName();

	if (!customName.isEmpty()) {
		if (customName.charAt(0) == '@') {
			StringId stringId(customName);

			object->setObjectName(stringId);
		} else {
			object->setCustomObjectName(customName, false);
		}
	}
}

int LootManagerImplementation::calculateLootCredits(int level) {
	int maxcredits = (int) round((.03f * level * level) + (3 * level) + 50);
	int mincredits = (int) round((((float) maxcredits) * .5f) + (2.0f * level));

	int credits = mincredits + System::random(maxcredits - mincredits);

	return credits;
}

TangibleObject* LootManagerImplementation::createLootObject(LootItemTemplate* templateObject, int level, bool maxCondition) {

	if(level > 300)
		level = 300;

	String directTemplateObject = templateObject->getDirectObjectTemplate();

	ManagedReference<TangibleObject*> prototype = dynamic_cast<TangibleObject*> (zoneServer->createObject(directTemplateObject.hashCode(), 2));

	if (prototype == NULL) {
		error("could not create loot object: " + directTemplateObject);
		return NULL;
	}

	prototype->createChildObjects();

	String serial = craftingManager->generateSerial();
	prototype->setSerialNumber(serial);

	CraftingValues craftingValues = templateObject->getCraftingValuesCopy();

	setInitialObjectStats(templateObject, &craftingValues, prototype);

	setCustomObjectName(prototype, templateObject);

	float excMod = 1.0;

	if (System::random(legendaryChance) == legendaryChance) {
			UnicodeString objectName = prototype->getCustomObjectName();
			uint32 bitmask = prototype->getOptionsBitmask() | OptionBitmask::YELLOW;

			if (objectName.isEmpty())
				objectName = StringIdManager::instance()->getStringId(prototype->getObjectName()->getFullPath().hashCode());

			UnicodeString newName = objectName + " (Legendary)";
			prototype->setCustomObjectName(newName, false);

			excMod = legendaryModifier;

			prototype->setOptionsBitmask(bitmask, false);
	} else if (System::random(exceptionalChance) == exceptionalChance) {
		UnicodeString objectName = prototype->getCustomObjectName();
		uint32 bitmask = prototype->getOptionsBitmask() | OptionBitmask::YELLOW;

		if (objectName.isEmpty())
			objectName = StringIdManager::instance()->getStringId(prototype->getObjectName()->getFullPath().hashCode());

		UnicodeString newName = objectName + " (Exceptional)";
		prototype->setCustomObjectName(newName, false);

		excMod = exceptionalModifier;

		prototype->setOptionsBitmask(bitmask, false);
	} else if (System::random(yellowChance) == yellowChance) {
		UnicodeString objectName = prototype->getCustomObjectName();
		uint32 bitmask = prototype->getOptionsBitmask() | OptionBitmask::YELLOW;

		if (objectName.isEmpty())
			objectName = StringIdManager::instance()->getStringId(prototype->getObjectName()->getFullPath().hashCode());

		UnicodeString newName = objectName;
		prototype->setCustomObjectName(newName, false);

		excMod = yellowModifier;

		prototype->setOptionsBitmask(bitmask, false);
	}

	String subtitle;

	float percentage = System::random(10000) / 10000.f; //Generate a base percentage. We will deviate slightly from this on each stat.

	for (int i = 0; i < craftingValues.getExperimentalPropertySubtitleSize(); ++i) {
		subtitle = craftingValues.getExperimentalPropertySubtitle(i);

		if (subtitle == "hitpoints" || subtitle == "armor_integrity") {
			if(!(prototype->isComponent())) {
				continue;
			}
		}

		float min = craftingValues.getMinValue(subtitle);
		float max = craftingValues.getMaxValue(subtitle);

		if(min == max)
			continue;

		if (subtitle != "useCount" &&
				subtitle != "quantity" &&
				subtitle != "charges" &&
				subtitle != "uses" &&
				subtitle != "charge") {

			float minMod = (max >= min) ? 2000.f : -2000.f;
			float maxMod = (max >= min) ? 500.f : -500.f;

			min = (min * level / minMod) + min;
			max = (max * level / maxMod) + max;

			if (max >= min && max > 0) {
				min *= excMod;
				max *= excMod;
			} else if (max <= min && max > 0) {
				min /= excMod;
				max /= excMod;
			} else if (max <= min && max <= 0) {
				min *= excMod;
				max *= excMod;
			} else {
				min /= excMod;
				max /= excMod;
			}

			craftingValues.setMinValue(subtitle, min);
			craftingValues.setMaxValue(subtitle, max);
		}

		float deviation = (((float) System::random(400)) - 200) / 1000.f; //Deviate up to 2%

		craftingValues.setCurrentPercentage(subtitle, percentage + deviation);
	}

	// Use percentages to recalculate the values
	craftingValues.recalculateValues(false);

	craftingValues.addExperimentalProperty("creatureLevel", "creatureLevel", level, level, 0, false, CraftingManager::LINEARCOMBINE);
	craftingValues.setHidden("creatureLevel");

	// Add Dots to weapon objects.
	addDots(prototype, templateObject, level, excMod);

	setSkillMods(prototype, templateObject, level, excMod);

	setSockets(prototype, &craftingValues);

	// Update the Tano with new values
	prototype->updateCraftingValues(&craftingValues, true);

	//add some condition damage where appropriate
	if (!maxCondition)
		addConditionDamage(prototype, &craftingValues);

	return prototype;
}

void LootManagerImplementation::addConditionDamage(TangibleObject* loot, CraftingValues* craftingValues) {
	if (!loot->isWeaponObject() && !loot->isArmorObject())
		return;

	float min = 0;

	if(loot->isWeaponObject())
		min = craftingValues->getMinValue("hitpoints");

	if(loot->isArmorObject())
		min = craftingValues->getMinValue("armor_integrity");

	float damage = (float) System::random(min / 3);

	loot->setConditionDamage(damage);
}

void LootManagerImplementation::setSkillMods(TangibleObject* object, LootItemTemplate* templateObject, int level, float excMod) {
	VectorMap<String, int>* skillMods = templateObject->getSkillMods();
	VectorMap<String, int> additionalMods;

	if (System::random(skillModChance / excMod) == 0) {
		int modCount = 1;
		int roll = System::random(100);

		if(roll > (100 - excMod))
			modCount += 2;

		if(roll < (5 * excMod))
			modCount += 1;

		for(int i = 0; i < modCount; ++i) {
			//Mods can't be lower than -1 or greater than 25
			int max = MAX(-1, MIN(25, round(0.1f * level + 3)));
			int min = MAX(-1, MIN(25, round(0.075f * level - 1)));

			int mod = System::random(max - min) + min;

			if(mod == 0)
				mod = 1;

			String modName = getRandomLootableMod();

			additionalMods.put(modName, mod);
		}
	}

	if (object->isWearableObject()) {
		ManagedReference<WearableObject*> wearableObject = cast<WearableObject*>(object);

		for (int i = 0; i < additionalMods.size(); i++) {
			wearableObject->addSkillMod(SkillModManager::WEARABLE, additionalMods.elementAt(i).getKey(), additionalMods.elementAt(i).getValue());
		}

		for (int i = 0; i < skillMods->size(); i++) {
			wearableObject->addSkillMod(SkillModManager::WEARABLE, skillMods->elementAt(i).getKey(), skillMods->elementAt(i).getValue());
		}
	} else if (object->isWeaponObject()) {
		ManagedReference<WeaponObject*> weaponObject = cast<WeaponObject*>(object);

		for (int i = 0; i < additionalMods.size(); i++) {
			weaponObject->addSkillMod(SkillModManager::WEARABLE, additionalMods.elementAt(i).getKey(), additionalMods.elementAt(i).getValue());
		}

		for (int i = 0; i < skillMods->size(); i++) {
			weaponObject->addSkillMod(SkillModManager::WEARABLE, skillMods->elementAt(i).getKey(), skillMods->elementAt(i).getValue());
		}
	}
}

void LootManagerImplementation::setSockets(TangibleObject* object, CraftingValues* craftingValues) {
	if (object->isWearableObject() && craftingValues->hasProperty("sockets")) {
		ManagedReference<WearableObject*> wearableObject = cast<WearableObject*>(object);
		// Round number of sockets to closes integer.
		wearableObject->setMaxSockets(craftingValues->getCurrentValue("sockets") + 0.5);
	}
}

bool LootManagerImplementation::createLoot(SceneObject* container, AiAgent* creature) {
	LootGroupCollection* lootCollection = creature->getLootGroups();

	if (lootCollection == NULL)
		return false;

	return createLootFromCollection(container, lootCollection, creature->getLevel());
}

bool LootManagerImplementation::createLootFromCollection(SceneObject* container, LootGroupCollection* lootCollection, int level) {
	for (int i = 0; i < lootCollection->count(); ++i) {
		LootGroupCollectionEntry* entry = lootCollection->get(i);
		int lootChance = entry->getLootChance();

		if (lootChance <= 0)
			continue;

		int roll = System::random(10000000);

		if (roll > lootChance)
			continue;

		int tempChance = 0; //Start at 0.

		LootGroups* lootGroups = entry->getLootGroups();

		//Now we do the second roll to determine loot group.
		roll = System::random(10000000);

		//Select the loot group to use.
		for (int i = 0; i < lootGroups->count(); ++i) {
			LootGroupEntry* entry = lootGroups->get(i);

			tempChance += entry->getLootChance();

			//Is this entry lower than the roll? If yes, then we want to try the next entry.
			if (tempChance < roll)
				continue;

			createLoot(container, entry->getLootGroupName(), level);

			break;
		}
	}

	return true;
}

bool LootManagerImplementation::createLoot(SceneObject* container, const String& lootGroup, int level, bool maxCondition) {
	Reference<LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == NULL) {
		warning("Loot group template requested does not exist: " + lootGroup);
		return false;
	}

	//Now we do the third roll for the item out of the group.
	int roll = System::random(10000000);

	Reference<LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(group->getLootItemTemplateForRoll(roll));

	if (itemTemplate == NULL) {
		warning("Loot item template requested does not exist: " + group->getLootItemTemplateForRoll(roll) + " for templateName: " + group->getTemplateName());
		return false;
	}

	TangibleObject* obj = createLootObject(itemTemplate, level, maxCondition);

	if (obj == NULL)
		return false;

	if (container->transferObject(obj, -1, false, true))
		container->broadcastObject(obj, true);


	return true;
}

void LootManagerImplementation::addDots(TangibleObject* object, LootItemTemplate* templateObject, int level, float excMod) {

	if (object == NULL)
		return;

	if (!object->isWeaponObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(object);

	bool shouldGenerateDots = false;

	float dotChance = templateObject->getDotChance();

	// Apply the Dot if the chance roll equals the number or is zero.
	if (dotChance == 0 || System::random(dotChance / excMod) == 0) { // Defined in loot item script.
		shouldGenerateDots = true;
	}

	if (shouldGenerateDots) {

		int dotType = templateObject->getDotType();
		bool random = false;

		if (dotType < 1 || dotType > 5)
			dotType = 5;

		VectorMap<String, SortedVector<int> >* dotValues = templateObject->getDotValues();
		int size = dotValues->size();

		// Check if they specified correct vals.
		if (size > 0) {
			if (dotType == 5) {
				dotType = System::random(2) + 1; // Poison, Disease, or Fire. No random bleeds.
				random = true;
			}
			weapon->setDotType(dotType);

			for (int i = 0; i < size; i++) {

				String property = dotValues->elementAt(i).getKey();
				SortedVector<int> theseValues = dotValues->elementAt(i).getValue();
				int min = theseValues.elementAt(0);
				int max = theseValues.elementAt(1);
				float value = 0;

				if (max != min) {
					value = MAX(min, MIN(max, System::random(max - min) * (1 + (level / 1000)))); // Used for Str, Pot, Dur, Uses.
						if (value < min) {
							value = min;
						}
				}
				else { value = max; }

				if(property == "attribute") {
					if (min != max)
						value = System::random(max - min) + min;

					if (dotType != 2 && (value != 0 && value != 3 && value != 6)) {
						int numbers[] = { 0, 3, 6 }; // The main pool attributes.
						int choose = System::random(2);
						value = numbers[choose];
					}

					weapon->setDotAttribute(value);
				} else if (property == "strength") {
					if (random) {
						if (dotType == 1)
							value = value * 2;
						else if (dotType == 3)
							value = value * 1.5;
					}

					weapon->setDotStrength(value * excMod);
				} else if (property == "duration") {
					if (random) {
						if (dotType == 2)
							value = value * 5;
						else if (dotType == 3)
							value = value * 1.5;
					}

					weapon->setDotDuration(value * excMod);
				} else if (property == "potency") {
					weapon->setDotPotency(value * excMod);
				} else if (property == "uses") {
					weapon->setDotUses(value * excMod);
				}
			}
		}
	}
}
