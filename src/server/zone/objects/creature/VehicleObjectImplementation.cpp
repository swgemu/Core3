/*
 * VehicleObjectImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "VehicleObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/building/BuildingObject.h"


void VehicleObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	info("checking linked creature", true);

	if (linkedCreature != player)
		return;

	info("adding radial items", true);

	menuResponse->addRadialMenuItem(205, 1, "@pet/pet_menu:menu_enter_exit");
	menuResponse->addRadialMenuItem(61, 3, "");


	//TODO:Remove this when garages are functioning
	if (checkInRangeGarage())
		menuResponse->addRadialMenuItem(62, 3, "Repair");

}

bool VehicleObjectImplementation::checkInRangeGarage() {
	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

		if (scno == this)
			continue;

		if (scno->isBuildingObject()) {
			BuildingObjectImplementation* building = (BuildingObjectImplementation*) scno;

			if (building->isStaticGarage() && building->isInRange(_this, 15))
				return true;
		}
	}

	return false;
}


int VehicleObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 61 && linkedCreature == player) {
		unlock();

		controlDevice->storeObject(player);

		wlock(player);
	}

	return 0;
}
