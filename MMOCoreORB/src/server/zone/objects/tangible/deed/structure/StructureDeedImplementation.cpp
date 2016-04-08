/*
 * StructureDeedImplementation.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: xyborn
 */

#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "templates/tangible/StructureDeedTemplate.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/components/ComponentManager.h"

void StructureDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	StructureDeedTemplate* templ = dynamic_cast<StructureDeedTemplate*>(templateObject.get());

	if (templ != NULL)
		placeStructureComponent = ComponentManager::instance()->getComponent<PlaceStructureComponent*>(templ->getStructurePlacementComponent());

	setLoggingName("StructureDeed");
}

int StructureDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 20) {

		if (!isASubChildOf(player))
			return 0;

		player->executeObjectControllerAction(STRING_HASHCODE("placestructuremode"), getObjectID(), "");

		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

void StructureDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	TemplateManager* templateManager = TemplateManager::instance();

	uint32 structureCRC = generatedObjectTemplate.hashCode();

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureCRC));

	if (structureTemplate == NULL)
		return;

	//Base Maintenance Rate
	int baseMaintenanceRate = structureTemplate->getBaseMaintenanceRate();
	int basePowerRate = structureTemplate->getBasePowerRate();

	if (baseMaintenanceRate > 0)
		alm->insertAttribute("examine_maintenance_rate", String::valueOf(baseMaintenanceRate) + " / hour"); //Base Maintenance Rate

	if (surplusMaintenance > 0)
		alm->insertAttribute("examine_maintenance", String::valueOf(surplusMaintenance)); //Surplus Maintenance

	if (surplusPower > 0)
		alm->insertAttribute("examine_power", String::valueOf(surplusPower)); //Surplus Power

	if (hopperSizeMax > 0)
		alm->insertAttribute("examine_hoppersize", String::valueOf((int)hopperSizeMax));

	if (extractionRate > 0)
		alm->insertAttribute("examine_extractionrate", String::valueOf(Math::getPrecision(extractionRate, 2)));

	for (int i = 0; i < structureTemplate->getTotalAllowedZones(); ++i) {
		String zoneName = structureTemplate->getAllowedZone(i);

		if (zoneName.isEmpty())
			continue;

		alm->insertAttribute("examine_scene", "@planet_n:" + zoneName); //Can Be Built On
	}
}

void StructureDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate){
	setExtractionRate(values->getCurrentValue("extractrate"));
	setHopperSize(values->getCurrentValue("hoppersize"));
}
