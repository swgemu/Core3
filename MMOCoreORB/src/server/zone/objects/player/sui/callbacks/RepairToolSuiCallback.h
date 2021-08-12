/*
 * RepairToolSuiCallback.h
 *
 *  Created on: Oct 19, 2019
 *      Author: rafalski
 */

#ifndef REPAIRTOOLSUICALLBACK_H_
#define REPAIRTOOLSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/VehicleObject.h"

class RepairToolSuiCallback : public SuiCallback {
public:
	RepairToolSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> obj = listBox->getUsingObject().get();

		if (obj == nullptr || !obj->isRepairTool() )
			return;

		RepairTool* repairTool = cast<RepairTool*>( obj.get());

		if (repairTool == nullptr )
			return;

		int index = Integer::valueOf(args->get(0).toString());

		ManagedReference<TangibleObject*> itemToRepair =
				server->getObject(listBox->getMenuObjectID(index)).castTo<TangibleObject*>();

		if (itemToRepair == nullptr )
			return;
                
		Locker _lock(repairTool, player);
			itemToRepair->repair(player, repairTool);
	}
};

#endif /* REPAIRTOOLSUICALLBACK_H_ */
