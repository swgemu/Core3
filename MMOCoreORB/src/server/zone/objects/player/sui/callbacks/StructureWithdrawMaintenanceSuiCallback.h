
#ifndef STRUCTUREWITHDRAWMAINTENANCESUICALLBACK_H_
#define STRUCTUREWITHDRAWMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"


class StructureWithdrawMaintenanceSuiCallback : public SuiCallback {
public:
	StructureWithdrawMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		int amount = Integer::valueOf(args->get(0).toString());

		if (amount < 0)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL || !obj->isStructureObject())
			return;

		//Withdraw the maintenance
		StructureObject* structure = cast<StructureObject*>(obj.get());

		ManagedReference<Zone*> zone = structure->getZone();

		if (zone == NULL)
			return;

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		StructureManager::instance()->withdrawMaintenance(structure, creature, amount);
	}
};

#endif /* STRUCTUREWITHDRAWMAINTENANCESUICALLBACK_H_ */
