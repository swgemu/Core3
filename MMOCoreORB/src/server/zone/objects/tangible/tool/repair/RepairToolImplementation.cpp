/*
 * RepairToolImplementation.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/tangible/tool/repair/RepairTool.h"

#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void RepairToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
}

void RepairToolImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(msg, object);
	msg->insertAttribute("quality", Math::getPrecision(quality, 1));
}

void RepairToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	quality = values->getCurrentValue("quality");
}
