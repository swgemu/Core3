/*
 * RepairVehicleSuiCallback.h
 *
 *  Created on: Dec 6, 2010
 *      Author: crush
 */

#ifndef REPAIRVEHICLESUICALLBACK_H_
#define REPAIRVEHICLESUICALLBACK_H_


#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"

class RepairVehicleSuiCallback : public SuiCallback {
public:
	RepairVehicleSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> obj = listBox->getUsingObject();

		if (obj == NULL || !obj->isVehicleObject())
			return;

		VehicleObject* vehicle = cast<VehicleObject*>( obj.get());

		Locker _lock(vehicle, player);

		if (!vehicle->checkInRangeGarage() && !player->getPlayerObject()->isPrivileged()) {
			player->sendSystemMessage("@pet/pet_menu:repair_unrecognized_garages"); //Your vehicle does not recognize any local garages. Try again in a garage repair zone.
			return;
		}

		int repairCost = vehicle->calculateRepairCost(player);
		int totalFunds = player->getBankCredits();
		int tax = 0;

		ManagedReference<CityRegion*> city =vehicle->getCityRegion();
		if(city != NULL && city->getGarageTax() > 0){
			tax = repairCost * city->getGarageTax() / 100;
			repairCost += tax;
		}

		if (repairCost > totalFunds) {
			player->sendSystemMessage("@pet/pet_menu:lacking_funds_prefix " + String::valueOf(repairCost - totalFunds) + " @pet/pet_menu:lacking_funds_suffix"); //You lack the additional  credits required to repair your vehicle.
			return;
		}

		player->setBankCredits(totalFunds - repairCost, true);

		StringIdChatParameter params("@base_player:prose_pay_success_no_target"); //You successfully make a payment of %DI credits.
		params.setDI(repairCost);
		player->sendSystemMessage(params);

		vehicle->healDamage(player, 0, vehicle->getConditionDamage(), true);

		String vehicleName = vehicle->getDisplayedName();

		if (vehicleName.beginsWith("(disabled)"))
			vehicle->setCustomObjectName(vehicleName.subString(11), true);

		if( city != NULL && tax > 0){

			_lock.release();
			Locker clocker(city, player);
			city->addToCityTreasury(tax);
		}

	}
};

#endif /* REPAIRVEHICLESUICALLBACK_H_ */
