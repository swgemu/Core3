/*
 * StructurePayMaintenanceSuiCallback.h
 *
 *  Created on: Aug 16, 2011
 *      Author: cRush
 */

#ifndef STRUCTUREPAYMAINTENANCESUICALLBACK_H_
#define STRUCTUREPAYMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"


class StructurePayMaintenanceSuiCallback : public SuiCallback {
public:
	StructurePayMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isTransferBox() || cancelPressed || args->size() < 2)
			return;

		int amount = Integer::valueOf(args->get(1).toString());

		if (amount < 0)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:invalid_target"); // "Your original structure target is no longer valid. Aborting..."
			return;
		}

		//Deposit/Withdraw the maintenance
		StructureObject* structure = cast<StructureObject*>(obj.get());

		ManagedReference<Zone*> zone = structure->getZone();

		if (zone == NULL)
			return;

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		StructureManager::instance()->payMaintenance(structure, creature, amount);
	}
};

#endif /* STRUCTUREPAYMAINTENANCESUICALLBACK_H_ */
