/*
 * ResourceLabratory.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: swgemu
 */

#include "ResourceLabratory.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"

ResourceLabratory::ResourceLabratory() {
	setLoggingName("ResourceLabratory");
}

ResourceLabratory::~ResourceLabratory() {
}

void ResourceLabratory::initialize(ZoneServer* server) {
	SharedLabratory::initialize(server);
	Reference<Lua* > lua = new Lua();
	lua->init();
	if (!lua->runFile("scripts/managers/crafting/bio_skill_mods.lua")) {
		return;
	}
	LuaObject bioModsTable = lua->getGlobalObject("bioSkillMods");
	if (!bioModsTable.isValidTable())
		return;
	for (int i = 1; i <= bioModsTable.getTableSize(); ++i) {
		String mod = bioModsTable.getStringAt(i);
		bioMods.put(mod);
	}
	bioModsTable.pop();

}
void ResourceLabratory::setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess) {

	if(manufactureSchematic == NULL || manufactureSchematic->getDraftSchematic() == NULL)
		return;

	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();
	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	float value, maxPercentage, currentPercentage, weightedSum;
	String itemName;
	// These 2 values are pretty standard, adding these
	itemName = "xp";
	value = float(draftSchematic->getXpAmount());
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, true, ValuesMap::OVERRIDECOMBINE);
	itemName = "complexity";
	value = manufactureSchematic->getComplexity();
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, true, ValuesMap::OVERRIDECOMBINE);
	float modifier = calculateAssemblyValueModifier(assemblySuccess);
	int subtitleCounter = 0;

	for (int i = 0; i < draftSchematic->getResourceWeightCount(); ++i) {
		// Grab the first weight group
		Reference<ResourceWeight* > resourceWeight = draftSchematic->getResourceWeight(i);
		// Getting the title ex: expDamage
		String experimentalTitle = resourceWeight->getExperimentalTitle();
		// Getting the subtitle ex: minDamage
		String property = resourceWeight->getPropertyName();
		weightedSum = 0;
		craftingValues->addExperimentalProperty(experimentalTitle, property,
				resourceWeight->getMinValue(), resourceWeight->getMaxValue(),
				resourceWeight->getPrecision(), resourceWeight->isFiller(),
				resourceWeight->getCombineType());

		for (int ii = 0; ii < resourceWeight->getPropertyListSize(); ++ii) {
			// Based on the script we cycle through each exp group
			// Get the type from the type/weight
			int type = (resourceWeight->getTypeAndWeight(ii) >> 4);
			// Get the calculation percentage
			float percentage = resourceWeight->getPropertyPercentage(ii);
			// add to the weighted sum based on type and percentage
			weightedSum += getWeightedValue(manufactureSchematic, type) * percentage;
		}

		// > 0 ensures that we don't add things when there is NaN value
		if (weightedSum > 0) {

			// This is the formula for max experimenting percentages
			maxPercentage = ((weightedSum / 10.0f) * .01f);

			// Based on the weighted sum, we can get the initial %
			currentPercentage = getAssemblyPercentage(weightedSum) * modifier;
			craftingValues->setMaxPercentage(property, maxPercentage);
			craftingValues->setCurrentPercentage(property, currentPercentage);
			subtitleCounter++;
		}
	}

	craftingValues->recalculateValues(true);

	if (applyComponentStats(prototype,manufactureSchematic)) {
		craftingValues->recalculateValues(true);
	}

	if(draftSchematic->getIsMagic()) {
		prototype->setIsCraftedEnhancedItem(true);
		prototype->addMagicBit(false);
	}
}

void ResourceLabratory::experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult){

	float modifier, newValue;
	String title, subtitle, subtitlesTitle;
	title = craftingValues->getVisibleExperimentalPropertyTitle(rowEffected);
	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(i);
		if (subtitlesTitle == title) {
			subtitle = craftingValues->getExperimentalPropertySubtitle(i);
			modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);
			newValue = craftingValues->getCurrentPercentage(subtitle) + modifier;

			if (newValue > craftingValues->getMaxPercentage(subtitle))
				newValue = craftingValues->getMaxPercentage(subtitle);

			if (newValue < 0)
				newValue = 0;

			craftingValues->setCurrentPercentage(subtitle, newValue);
		}
	}
}
int ResourceLabratory::getCreationCount(ManufactureSchematic* manufactureSchematic) {
	return 1;
}

bool ResourceLabratory::applyComponentStats(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic) {

	if(manufactureSchematic == NULL || manufactureSchematic->getDraftSchematic() == NULL)
		return false;

	float max, min, currentvalue, propertyvalue;
	int precision;
	bool modified = false;
	bool hidden;
	String experimentalTitle, property;

	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();

	bool isYellow = false;

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		Reference<IngredientSlot* > ingredientSlot = manufactureSchematic->getSlot(i);
		Reference<DraftSlot* > draftSlot = draftSchematic->getDraftSlot(i);

		if(ingredientSlot == NULL || !ingredientSlot->isComponentSlot() || !ingredientSlot->isFull())
			continue;

		ComponentSlot* compSlot = cast<ComponentSlot*>(ingredientSlot.get());

		if(compSlot == NULL)
			continue;

		ManagedReference<TangibleObject*> tano = compSlot->getPrototype();

		if (tano == NULL || !tano->isComponent())
			continue;

		ManagedReference<Component*> component = cast<Component*>( tano.get());

		if (prototype->isWearableObject() && !prototype->isArmorObject()) {

			if (component->getObjectTemplate()->getObjectName() == "@craft_clothing_ingredients_n:reinforced_fiber_panels" || component->getObjectTemplate()->getObjectName() == "@craft_clothing_ingredients_n:synthetic_cloth"){

				for (int k = 0; k < component->getPropertyCount(); ++k) {
					const String property = component->getProperty(k);

					if (property == "" || property == "null") {
						continue;
					}

					String key = checkBioSkillMods(property);

					if (key == "") {
						continue;
					} else {
						currentvalue = component->getAttributeValue(property);
						precision = component->getAttributePrecision(property);
						int preciseValue = Math::getPrecision(currentvalue, precision);
						WearableObject* clothing = cast<WearableObject*>(prototype);
						VectorMap<String, int>* clothingMods = clothing->getWearableSkillMods();

						int existingValue = 0;
						if(clothingMods->contains(key)) {
							existingValue = clothingMods->get(key);
						}
						preciseValue += existingValue;
						if (preciseValue > 25)
							preciseValue = 25;
						clothing->addSkillMod(SkillModManager::WEARABLE, key, preciseValue);
						isYellow = true;
					}
				}
			}
		} else {

			for (int j = 0; j < component->getPropertyCount(); ++j) {
				property = component->getProperty(j);
				modified = true;

				if (craftingValues->hasProperty(property)) {
					max = craftingValues->getMaxValue(property);
					min = craftingValues->getMinValue(property);
					hidden = craftingValues->isHidden(property);
					currentvalue = craftingValues->getCurrentValue(property);
					propertyvalue = component->getAttributeValue(property) * draftSlot->getContribution();
					short combineType = craftingValues->getCombineType(property);

					switch(combineType) {
					case ValuesMap::LINEARCOMBINE:
						currentvalue += propertyvalue;
						min += propertyvalue;
						max += propertyvalue;

						craftingValues->setMinValue(property, min);
						craftingValues->setMaxValue(property, max);

						craftingValues->setCurrentValue(property, currentvalue);
						break;
					case ValuesMap::PERCENTAGECOMBINE:
						currentvalue += propertyvalue;
						min += propertyvalue;
						max += propertyvalue;

						craftingValues->setMinValue(property, min);
						craftingValues->setMaxValue(property, max);

						craftingValues->setCurrentPercentage(property, currentvalue);
						break;
					case ValuesMap::BITSETCOMBINE:
						currentvalue = (int)currentvalue | (int)propertyvalue;

						craftingValues->setCurrentValue(property , currentvalue);
						break;
					case ValuesMap::OVERRIDECOMBINE:
						// Do nothing because the values should override whatever is
						// on the component
						break;
					case ValuesMap::LIMITEDCOMBINE:
						currentvalue += propertyvalue;

						if (currentvalue < min)
							currentvalue = min;

						if (currentvalue > max)
							currentvalue = max;

						craftingValues->setCurrentValue(property, currentvalue);

						modified = false;
						break;
					default:
						break;
					}

				} else {

					currentvalue = component->getAttributeValue(property);
					precision = component->getAttributePrecision(property);
					experimentalTitle = component->getAttributeTitle(property);

					craftingValues->addExperimentalProperty(experimentalTitle, property,
						currentvalue, currentvalue, precision, component->getAttributeHidden(property), ValuesMap::LINEARCOMBINE);
					craftingValues->setCurrentPercentage(property, 0);
					craftingValues->setMaxPercentage(property, 0);
					craftingValues->setCurrentValue(property, currentvalue);
				}
			}
		}
	}

	if(isYellow) {
		prototype->setIsCraftedEnhancedItem(true);
		prototype->addMagicBit(false);
	}

	return modified;
}
String ResourceLabratory::checkBioSkillMods(const String& property) {

	for (int l = 0; l < bioMods.size(); ++l) {

		String key = bioMods.elementAt(l);
		String statname = "cat_skill_mod_bonus.@stat_n:" + key;

		if (property == statname) {
			return key;
		}
	}

	return "";
}
