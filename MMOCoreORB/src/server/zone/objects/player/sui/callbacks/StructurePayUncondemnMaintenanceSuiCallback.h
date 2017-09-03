/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_
#define STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/credit/CreditManager.h"

class StructurePayUncondemnMaintenanceSuiCallback : public SuiCallback {
public:
	StructurePayUncondemnMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:invalid_target"); // "Your original structure target is no longer valid. Aborting..."
			return;
		}

		StructureObject* structure = cast<StructureObject*>(obj.get());

		if (structure == NULL) {
			creature->sendSystemMessage("@player_structure:invalid_target"); // "Your original structure target is no longer valid. Aborting..."
			return;
		}

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		int uncondemnCost = -structure->getSurplusMaintenance();

		if (uncondemnCost < 0 || (creature->getBankCredits() < uncondemnCost)) {
			StringIdChatParameter params("@player_structure:structure_condemned_owner_no_credits"); // "This structure has been condemned by the order of the Empire. It currently requires %DI credits to uncondemn this structure. You do not have sufficient funds in your bank account. Add sufficient funds to your account and return to regain access to this structure."
			params.setDI(uncondemnCost);
			creature->sendSystemMessage(params);
			return;
		}

		ManagedReference<CreditObject*> creditObj = creature->getCreditObject();
		{
			Locker locker(creditObj);
			structure->payMaintenance(uncondemnCost, creditObj , false);
		}
		//Give the player 10 minutes to pay more maintenance before sending out new mails.
		structure->scheduleMaintenanceTask(10 * 60);

		if (structure->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject* >(structure);

			if (building != NULL) {
				//Remove ***** Condemned Structure ***** sign name.
				building->updateSignName(true);
			}
		}

		StringIdChatParameter message("@player_structure:structure_uncondemned"); // Your structure has been uncondemned. The Empire thanks you for your support.
		creature->sendSystemMessage(message);
	}
};

#endif /* STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_ */
