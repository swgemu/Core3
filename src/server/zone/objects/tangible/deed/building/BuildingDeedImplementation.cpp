/*
 * BuildingDeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include "BuildingDeed.h"
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"

void BuildingDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("BuildingDeed");
}

int BuildingDeedImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	String actionName = "placestructuremode";
	player->executeObjectControllerAction(actionName.hashCode(), getObjectID(), "");

	return 0;
}

void BuildingDeedImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	DeedImplementation::fillAttributeList(alm, object);

	TemplateManager* templateManager = TemplateManager::instance();

	uint32 buioCRC = generatedObjectTemplate.hashCode();

	SharedBuildingObjectTemplate* buildingTemplate = dynamic_cast<SharedBuildingObjectTemplate*>(templateManager->getTemplate(buioCRC));

	if (buildingTemplate == NULL)
		return;

	//Base Maintenance Rate
	int baseMaintenanceRate = buildingTemplate->getBaseMaintenanceRate();

	if (baseMaintenanceRate > 0)
		alm->insertAttribute("examine_maintenance_rate", String::valueOf(baseMaintenanceRate) + " / hour"); //Base Maintenance Rate

	if (surplusMaintenance > 0)
		alm->insertAttribute("examine_maintenance", String::valueOf(surplusMaintenance)); //Surplus Maintenance

	for (int i = 0; i < 10; ++i) {
		if (buildingTemplate->isAllowedZone(i)) {
			StringBuffer planetName;
			planetName << "@planet_n:" << zone->getZoneName();
			alm->insertAttribute("examine_scene", planetName.toString()); //Can Be Built On
		}
	}
}
