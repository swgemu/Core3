/*
 * StructureManageMaintenanceSuiCallback.h
 *
 *  Created on: Aug 16, 2011
 *      Author: crush
 */

#ifndef STRUCTUREMANAGEMAINTENANCESUICALLBACK_H_
#define STRUCTUREMANAGEMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class StructureManageMaintenanceSuiCallback : public SuiCallback {
public:
	StructureManageMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isTransferBox() || cancelPressed)
			return;

		uint32 received = Integer::valueOf(args->get(0).toString());
		uint32 transferred = Integer::valueOf(args->get(1).toString());

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isStructureObject())
			return; //TODO: What message should be shown here?

		//Deposit/Withdraw the maintenance
		StructureObject* structure = cast<StructureObject*>( obj.get());

		Locker _lock(structure, creature);

		//No wrap around in the maintenance pool.
		if (structure->getSurplusMaintenance() + (int)transferred < structure->getSurplusMaintenance()) {
			return; //TODO: Find a suitable message for this.
		}

		// Ensure that the creature has the credits that will be transferred.
		if (creature->getCashCredits() < transferred) {
			StringIdChatParameter stringId("player_structure", "insufficient_funds");
			creature->sendSystemMessage(stringId);
			return;
		}

		creature->substractCashCredits(transferred);
		structure->addMaintenance(transferred);
		structure->scheduleMaintenanceExpirationEvent();
	}
};

#endif /* STRUCTUREMANAGEMAINTENANCESUICALLBACK_H_ */
