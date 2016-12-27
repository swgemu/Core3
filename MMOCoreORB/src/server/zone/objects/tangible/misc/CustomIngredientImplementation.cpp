#include "server/zone/objects/tangible/misc/CustomIngredient.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void CustomIngredientImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	int average = 500;

	if (getServerObjectCRC() == 0x7D098ED) { // object/tangible/loot/quest/ardanium_ii.iff
		isBaseIngredient = true;
		addAttribute("res_potential_energy", getResourceValue(average));
		addAttribute("res_quality", getResourceValue(average));
	} else if (getServerObjectCRC() == 0x2C436272) { // object/tangible/loot/quest/wind_crystal.iff
		isBaseIngredient = true;
		addAttribute("res_potential_energy", getResourceValue(average));
	} else if (getServerObjectCRC() == 0x90B15BBB) { // object/tangible/loot/quest/ostrine.iff
		isBaseIngredient = true;
		addAttribute("res_malleability", getResourceValue(average));
		addAttribute("res_quality", getResourceValue(average));
	} else if (getServerObjectCRC() == 0x1F9CB9C1) { // object/tangible/loot/quest/endrine.iff
		isBaseIngredient = true;
		addAttribute("res_malleability", getResourceValue(average));
		addAttribute("res_quality", getResourceValue(average));
		addAttribute("res_toughness", getResourceValue(average));
	} else if (getServerObjectCRC() == 0x37EF3820) { // object/tangible/loot/quest/rudic.iff
		isBaseIngredient = true;
		addAttribute("res_conductivity", getResourceValue(average));
		addAttribute("res_decay_resist", getResourceValue(average));
		addAttribute("res_quality", getResourceValue(average));
		addAttribute("res_shock_resistance", getResourceValue(average));
	}

}

int CustomIngredientImplementation::getResourceValue(int average) {
	int randValue = (System::getMTRand()->randNorm(0, 1) * 50) + average;

	if (randValue > 1000)
		randValue = 1000;
	else if (randValue < 150)
		randValue = 150;

	return randValue;
}

void CustomIngredientImplementation::addAttribute(const String& attribute, int value) {
	objectAttributes.put(attribute, value);
}

int CustomIngredientImplementation::getAttributeAndValue(String& attribute,	int index) {
	if (index < objectAttributes.size()) {
		attribute = objectAttributes.elementAt(index).getKey();
		return objectAttributes.get(index);
	} else {
		return 0;
	}
}

int CustomIngredientImplementation::getValueOf(int stat) {

	String attribute = "";

	switch(stat) {
	case CraftingManager::CR:
		attribute = "res_cold_resist";
		break;
	case CraftingManager::CD:
		attribute = "res_conductivity";
		break;
	case CraftingManager::DR:
		attribute = "res_decay_resist";
		break;
	case CraftingManager::HR:
		attribute = "res_heat_resist";
		break;
	case CraftingManager::FL:
		attribute = "res_flavor";
		break;
	case CraftingManager::MA:
		attribute = "res_malleability";
		break;
	case CraftingManager::PE:
		attribute = "res_potential_energy";
		break;
	case CraftingManager::OQ:
		attribute = "res_quality";
		break;
	case CraftingManager::SR:
		attribute = "res_shock_resistance";
		break;
	case CraftingManager::UT:
		attribute = "res_toughness";
		break;
	default:
		return 0;
		break;
	}

	return getValueOf(attribute);
}

int CustomIngredientImplementation::getValueOf(const String& attribute) {
	if(objectAttributes.contains(attribute))
		return objectAttributes.get(attribute);

	return 0;
}

void CustomIngredientImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	for (int i = 0; i < objectAttributes.size(); ++i) {
		String attrib;
		int value = getAttributeAndValue(attrib, i);
		alm->insertAttribute(attrib, value);
	}
}

void CustomIngredientImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	if (isBaseIngredient)
		return;

	String attribute;
	float value;
	bool hidden;

	objectAttributes.removeAll();

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		attribute = values->getExperimentalPropertySubtitle(i);

		value = values->getCurrentValue(attribute);
		hidden = values->isHidden(attribute);

		if (!hidden)
			objectAttributes.put(attribute, value);
	}
}
