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

	exceptionalChance = lua->getGlobalFloat("exceptionalChance");
	exceptionalModifier = lua->getGlobalFloat("exceptionalModifier");
	legendaryChance = lua->getGlobalFloat("legendaryChance");
	legendaryModifier = lua->getGlobalFloat("legendaryModifier");

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
			if(title == "null")
				craftingValues->setHidden(property);
		}
	}

	Vector<String>* customizationData = templateObject->getCustomizationStringNames();
	Vector<Vector<int> >* customizationValues = templateObject->getCustomizationValues();

	for (int i = 0; i < customizationData->size(); ++i) {
		String customizationString = customizationData->get(i);
		Vector<int>* values = &customizationValues->get(i);

		int idx = customizationString.lastIndexOf("/");

		if (idx != -1)
			customizationString = customizationString.subString(idx + 1);

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

TangibleObject* LootManagerImplementation::createLootObject(LootItemTemplate* templateObject, int level) {

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

	if (System::random(exceptionalChance) == exceptionalChance) {
		UnicodeString objectName = prototype->getCustomObjectName();
		uint32 bitmask = prototype->getOptionsBitmask() | OptionBitmask::YELLOW;

		if (objectName.isEmpty())
			objectName = StringIdManager::instance()->getStringId(prototype->getObjectName()->getFullPath().hashCode());

		UnicodeString newName = objectName + " (Exceptional)";
		prototype->setCustomObjectName(newName, false);

		excMod = exceptionalModifier;

		prototype->setOptionsBitmask(bitmask, false);
	} else if (System::random(legendaryChance) == legendaryChance) {
		UnicodeString objectName = prototype->getCustomObjectName();
		uint32 bitmask = prototype->getOptionsBitmask() | OptionBitmask::YELLOW;

		if (objectName.isEmpty())
			objectName = StringIdManager::instance()->getStringId(prototype->getObjectName()->getFullPath().hashCode());

		UnicodeString newName = objectName + " (Legendary)";
		prototype->setCustomObjectName(newName, false);

		excMod = legendaryModifier;

		prototype->setOptionsBitmask(bitmask, false);
	}

	String subtitle;

	float percentage = System::random(10000) / 10000.f; //Generate a base percentage. We will deviate slightly from this on each stat.

	for (int i = 0; i < craftingValues.getExperimentalPropertySubtitleSize(); ++i) {
		subtitle = craftingValues.getExperimentalPropertySubtitle(i);

		if (subtitle == "hitpoints")
			continue;

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

			if (max >= min) {
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

	// Update the Tano with new values
	prototype->updateCraftingValues(&craftingValues, true);

	return prototype;
}

bool LootManagerImplementation::createLoot(SceneObject* container, AiAgent* creature) {
	LootGroupCollection* lootCollection = creature->getLootGroups();

	if (lootCollection == NULL)
		return false;

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

		//Select the loot group to use.
		for (int i = 0; i < lootGroups->count(); ++i) {
			LootGroupEntry* entry = lootGroups->get(i);

			tempChance += entry->getLootChance();

			//Is this entry lower than the roll? If yes, then we want to try the next entry.
			if (tempChance < roll)
				continue;

			createLoot(container, entry->getLootGroupName(), creature->getLevel());

			break;
		}
	}

	return true;
}

bool LootManagerImplementation::createLoot(SceneObject* container, const String& lootGroup, int level) {
	if (container->hasFullContainerObjects())
		return false;

	Reference<LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == NULL) {
		warning("Loot group template requested does not exist: " + lootGroup);
		return false;
	}

	//Now we do the second roll for the item out of the group.
	int roll = System::random(10000000);

	Reference<LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(group->getLootItemTemplateForRoll(roll));

	if (itemTemplate == NULL) {
		warning("Loot item template requested does not exist: " + group->getLootItemTemplateForRoll(roll) + " for templateName: " + group->getTemplateName());
		return false;
	}

	TangibleObject* obj = createLootObject(itemTemplate, level);

	if (obj == NULL)
		return false;

	if (container->transferObject(obj, -1, false))
		container->broadcastObject(obj, true);


	return true;
}
