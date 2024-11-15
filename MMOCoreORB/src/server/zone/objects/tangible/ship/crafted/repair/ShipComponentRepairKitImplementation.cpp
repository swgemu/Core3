/*
 * ShipComponentRepairKitImplementation.cpp
 *
 *  Created on: 2024-11-15
 *  Author: Hakry
 */

#include "server/zone/objects/tangible/ship/crafted/repair/ShipComponentRepairKit.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"


void ShipComponentRepairKitImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* player) {
	TangibleObjectImplementation::fillAttributeList(msg, player);

	msg->insertAttribute("repaircharges", repairCharges);
}

void ShipComponentRepairKitImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);

	repairCharges = values->getCurrentValue("repaircharges");
}
