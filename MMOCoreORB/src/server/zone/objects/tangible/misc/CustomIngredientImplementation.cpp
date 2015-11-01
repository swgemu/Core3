#include "server/zone/objects/tangible/misc/CustomIngredient.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

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
