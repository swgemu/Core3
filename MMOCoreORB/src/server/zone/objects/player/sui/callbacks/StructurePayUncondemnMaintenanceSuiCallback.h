/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_
#define STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class StructurePayUncondemnMaintenanceSuiCallback : public SuiCallback {
public:
	StructurePayUncondemnMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isStructureObject()) {
			return; //TODO: What message should be shown here?
		}

		StructureObject* structure = cast<StructureObject*>(obj.get());

		if (structure == NULL) {
			return; //TODO: What message should be shown here?
		}

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		int uncondemnCost = -structure->getSurplusMaintenance();

		if (uncondemnCost < 0 || (creature->getBankCredits() + creature->getCashCredits() < uncondemnCost)) {
			//TODO: add error message;
			return;
		}

		structure->payMaintenance(uncondemnCost, creature, false);

		//Give the player 10 minutes to pay more maintenance before sending out new mails.
		structure->scheduleMaintenanceTask(10 * 60);

		if (structure->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject* >(structure);

			if (building != NULL) {
				//Remove ***** Condemned Structure ***** sign name.
				building->updateSignName(true);
			}
		}

		StringIdChatParameter message("@player_structure:structure_uncondemned");
		creature->sendSystemMessage(message);
	}
};

#endif /* STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_ */
