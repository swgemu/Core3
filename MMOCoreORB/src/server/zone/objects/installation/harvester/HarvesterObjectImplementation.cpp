/*
 * HarvesterObjectImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void HarvesterObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (!isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItem(122, 78, 3, "@harvester:manage");
	menuResponse->addRadialMenuItem(122, 77, 3, "@player_structure:management_power");
}

int HarvesterObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	/*case 122:
		sendPermissionListTo(player, "ADMIN");
		break;*/
	case 78:
		break;
	case 77:
		break;

	default:
		return InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}


float HarvesterObjectImplementation::getActualRate() {
	if (!isOperating())
		return 0.0f;

	ManagedReference<ResourceSpawn*> spawn = activeResource.get();

	if (spawn == NULL)
		return 0;

	return extractionRate * (spawn->getDensityAt(zone->getZoneID(), positionX, positionY) / 100.f);
}


float HarvesterObjectImplementation::getHopperSize() {
	float hopperSize = 0.0f;

	for (int i = 0; i < resourceHopper.size(); i++) {
		HopperEntry* entry = &resourceHopper.get(i);
		hopperSize += entry->getQuantity();
	}

	return hopperSize;
}
