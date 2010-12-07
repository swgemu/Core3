/*
 * RepairVehicleCallback.h
 *
 *  Created on: Dec 6, 2010
 *      Author: crush
 */

#ifndef REPAIRVEHICLECALLBACK_H_
#define REPAIRVEHICLECALLBACK_H_


#include "server/zone/objects/player/sui/SuiMessageCallback.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"

class RepairVehicleCallback : public SuiMessageCallback {
public:
	RepairVehicleCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = (SuiListBox*) suiBox;

		ManagedReference<SceneObject*> obj = listBox->getUsingObject();

		if (obj == NULL || !obj->isVehicleObject())
			return;

		VehicleObject* vehicle = (VehicleObject*) obj.get();

		Locker _lock(vehicle, player);

		int repairCost = vehicle->calculateRepairCost(player);
		int totalFunds = player->getBankCredits();

		if (repairCost > totalFunds) {
			player->sendSystemMessage("@pet/pet_menu:lacking_funds_prefix " + String::valueOf(repairCost - totalFunds) + " @pet/pet_menu:lacking_funds_suffix"); //You lack the additional  credits required to repair your vehicle.
			return;
		}

		player->setBankCredits(totalFunds - repairCost, true);

		StringIdChatParameter params("@base_player:prose_pay_success_no_target"); //You successfully make a payment of %DI credits.
		params.setDI(repairCost);
		player->sendSystemMessage(params);

		vehicle->healDamage(player, 0, vehicle->getConditionDamage(), true);
	}
};

#endif /* REPAIRVEHICLECALLBACK_H_ */
