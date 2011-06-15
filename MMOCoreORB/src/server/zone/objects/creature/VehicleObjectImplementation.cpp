/*
 * VehicleObjectImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "VehicleObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/building/city/CityHallObject.h"


void VehicleObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (!player->getPlayerObject()->isPrivileged() && linkedCreature != player)
		return;

	menuResponse->addRadialMenuItem(205, 1, "@pet/pet_menu:menu_enter_exit");
	menuResponse->addRadialMenuItem(61, 3, "");

	if (player->getPlayerObject()->isPrivileged() || (checkInRangeGarage() && !isDestroyed()))
		menuResponse->addRadialMenuItem(62, 3, "@pet/pet_menu:menu_repair_vehicle"); //Repair Vehicle
}

void VehicleObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::insertToZone(zone);

	//inflictDamage(_this, 0, System::random(50), true);
}

bool VehicleObjectImplementation::checkInRangeGarage() {
	if (getZone() == NULL)
		return false;

	ManagedReference<StructureManager*> structureManager = getZone()->getStructureManager();

	if (structureManager == NULL)
		return false;

	ManagedReference<SceneObject*> garage = structureManager->getInRangeParkingGarage(_this);

	if (garage == NULL)
		return false;

	return true;
}


int VehicleObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 61 && linkedCreature == player) {
		unlock();

		controlDevice->storeObject(player);

		wlock(player);
	} else if (selectedID == 62) {
		repairVehicle(player);
	}

	return 0;
}

void VehicleObjectImplementation::repairVehicle(PlayerCreature* player) {
	if (!player->getPlayerObject()->isPrivileged()) {
		//Need to check if they are city banned.
		/*
		ManagedReference<ActiveArea*> activeArea = getActiveRegion();

		if (activeArea != NULL && activeArea->isRegion()) {
			Region* region = (Region*) activeArea.get();

			ManagedReference<CityHallObject*> cityHall = region->getCityHall();

			if (cityHall != NULL && cityHall->isBanned(player->getObjectID())) {
				player->sendSystemMessage("@city/city:garage_banned"); //You are city banned and cannot use this garage.
				return;
			}
		}*/

		if (getConditionDamage() == 0) {
			player->sendSystemMessage("@pet/pet_menu:undamaged_vehicle"); //The targeted vehicle does not require any repairs at the moment.
			return;
		}

		if (isDestroyed()) {
			player->sendSystemMessage("@pet/pet_menu:cannot_repair_disabled"); //You may not repair a disabled vehicle.
			return;
		}

		if (!checkInRangeGarage()) {
			player->sendSystemMessage("@pet/pet_menu:repair_unrecognized_garages"); //Your vehicle does not recognize any local garages. Try again in a garage repair zone.
			return;
		}
	}

	sendRepairConfirmTo(player);
}

void VehicleObjectImplementation::sendRepairConfirmTo(PlayerCreature* player) {
	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::GARAGE_REPAIR);
	listbox->setPromptTitle("@pet/pet_menu:confirm_repairs_t"); //Confirm Vehicle Repairs
	listbox->setPromptText("@pet/pet_menu:vehicle_repair_d"); //You have chosen to repair your vehicle. Please review the listed details and confirm your selection.
	listbox->setUsingObject(_this);
	listbox->setCancelButton(true, "@cancel");

	int repairCost = calculateRepairCost(player);
	int totalFunds = player->getBankCredits();

	listbox->addMenuItem("@pet/pet_menu:vehicle_prompt " + getObjectName()->getDisplayedName()); //Vehicle:
	listbox->addMenuItem("@pet/pet_menu:repair_cost_prompt " + String::valueOf(repairCost)); //Repair Cost:
	listbox->addMenuItem("@pet/pet_menu:total_funds_prompt " + String::valueOf(totalFunds)); //Total Funds Available:

	player->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}

int VehicleObjectImplementation::calculateRepairCost(PlayerCreature* player) {
	if (player->getPlayerObject()->isPrivileged())
		return 0;

	//TODO: Implement city taxes.
	float cityTax = 1.0f;

	int repairCost = (int) (getConditionDamage() * 5.0f * cityTax);

	return repairCost;
}

int VehicleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	return TangibleObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}

int VehicleObjectImplementation::healDamage(TangibleObject* healer, int damageType, int damage, bool notifyClient) {
	return TangibleObjectImplementation::healDamage(healer, damageType, damage, notifyClient);
}

int VehicleObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	unlock();

	if (linkedCreature != NULL) {
		try {
			if (attacker != _this) {
				Locker clocker(linkedCreature, attacker);

				linkedCreature->executeObjectControllerAction(String("dismount").hashCode());
			} else {
				Locker locker(linkedCreature);

				linkedCreature->executeObjectControllerAction(String("dismount").hashCode());
			}


		} catch (Exception& e) {
		}
	}

	if (attacker != _this)
		wlock(attacker);
	else
		wlock();

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

