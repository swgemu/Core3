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
#include "server/zone/ZoneServer.h"
#include "LootGroupMap.h"

void LootManagerImplementation::initialize() {

	lua = new Lua();
	lua->init();

	info("loading configuration");
	if(!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	lootGroupMap = LootGroupMap::instance();
	lootGroupMap->initialize();

	info("initialized");
}

bool LootManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/loot_manager.lua");
}

bool LootManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;

	return true;
}

void LootManagerImplementation::loadDefaultConfig() {

}

void LootManagerImplementation::setInitialObjectStats(LootItemTemplate* templateObject, CraftingValues* craftingValues, TangibleObject* prototype) {
	int size = craftingValues->getExperimentalPropertyTitleSize();

	craftingValues->clear();

	Vector<String>* properties = templateObject->getExperimentalSubGroupTitles();
	Vector<int>* minValues = templateObject->getExperimentalMin();
	Vector<int>* maxValues = templateObject->getExperimentalMax();

	for (int i = 0; i < properties->size(); ++i) {
		String property = properties->get(i);

		craftingValues->setMinValue(property, minValues->get(i));
		craftingValues->setMaxValue(property, maxValues->get(i));

		craftingValues->setMaxPercentage(property, 1.0f);
		craftingValues->setCurrentPercentage(property, .5f);
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

SceneObject* LootManagerImplementation::createLootObject(LootItemTemplate* templateObject) {
	String directTemplateObject = templateObject->getDirectObjectTemplate();

	if (!directTemplateObject.isEmpty()) {
		SceneObject* newObject = zoneServer->createObject(directTemplateObject.hashCode(), 2);
		newObject->createChildObjects();

		if (newObject != NULL && newObject->isTangibleObject())
			setCustomObjectName(cast<TangibleObject*>(newObject), templateObject);

		return newObject;
	}

	ManagedReference<DraftSchematic*> draftSchematic = craftingManager->getSchematic(templateObject->getDraftSchematic().hashCode());

	ManagedReference<ManufactureSchematic*> manufactureSchematic = dynamic_cast<ManufactureSchematic* >(draftSchematic->createManufactureSchematic(NULL));
	manufactureSchematic->setDraftSchematic(NULL, draftSchematic);

	ManagedReference<TangibleObject *> prototype = dynamic_cast<TangibleObject*> (zoneServer->createObject(draftSchematic->getTanoCRC(), 2));
	prototype->createChildObjects();

	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

	prototype->setInitialCraftingValues(manufactureSchematic);
	prototype->updateCraftingValues(manufactureSchematic);

	Vector<byte>* customizationOptions = draftSchematic->getCustomizationOptions();
	Vector<byte>* customizationDefaultValues = draftSchematic->getCustomizationDefaultValues();

	for (int i = 0; i < customizationOptions->size(); ++i) {
		prototype->setCustomizationVariable(customizationOptions->get(i), customizationDefaultValues->get(i));
	}

	manufactureSchematic->setAssembled();

	manufactureSchematic->setFirstCraftingUpdateComplete();

	setInitialObjectStats(templateObject, craftingValues, prototype);

	int qualityResult = System::random(templateObject->getQualityRangeMin() - templateObject->getQualityRangeMax()) + templateObject->getQualityRangeMax();

	//info("qualityResult = " + String::valueOf(qualityResult), true);

	float modifier, newValue;

	String title, subtitle, subtitlesTitle;

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(i);
		subtitle = craftingValues->getExperimentalPropertySubtitle(i);
		modifier = craftingManager->calculateExperimentationValueModifier(qualityResult, 5);
		newValue = craftingValues->getCurrentPercentage(subtitle) + modifier;

		if (newValue > craftingValues->getMaxPercentage(subtitle))
			newValue = craftingValues->getMaxPercentage(subtitle);

		craftingValues->setCurrentPercentage(subtitle, newValue);
	}

	// Use percentages to recalculate the values
	craftingValues->recalculateValues(false);

	// Update the Tano with new values
	prototype->updateCraftingValues(manufactureSchematic);

	setCustomObjectName(prototype, templateObject);

	return prototype;
}

void LootManagerImplementation::createLoot(SceneObject* container, AiAgent* creature) {
	Vector<String>* lootGroups = creature->getLootGroups();

	if (lootGroups == NULL)
		return;

	for (int i = 0; i < lootGroups->size(); ++i) {
		createLoot(container, lootGroups->get(i), creature->getLevel());
	}
}

void LootManagerImplementation::createLoot(SceneObject* container, const String& lootGroup, int level) {
	if (container->hasFullContainerObjects())
		return;

	Reference<LootGroup*> group = lootGroupMap->get(lootGroup);

	if (group == NULL)
		return;

	for (int i = 0; i < group->size(); ++i) {
		if (container->hasFullContainerObjects())
			return;

		/*

		String item = group->get(i);

		LootItemTemplate* itemTemplate = lootGroupMap->getLootItem(item);

		if (itemTemplate != NULL) {
			float chance = itemTemplate->getChance() * 100000;
			int minLevel = itemTemplate->getMinimumLevel();
			int maxLevel = itemTemplate->getMaximumLevel();

			if (level != -1) {
				if (minLevel != -1 && level < minLevel)
					continue;

				if (maxLevel != -1 && level > maxLevel)
					continue;
			}

			if (chance >= System::random(10000000 - 1) + 1) {
				SceneObject* obj = createLootObject(itemTemplate);

				if (container->transferObject(obj, -1, false))
					container->broadcastObject(obj, true);
			}

		} else
			error(item + " loot item template not found");*/
	}
}
