/*
 * RemoveDroidStructureSuiCallback.h
 *
 *  Created on: 1/7/2015
 *      Author: Klivian
 */

#ifndef REMOVEDROIDSTRUCTURESUICALLBACK_H_
#define REMOVEDROIDSTRUCTURESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/tangible/components/droid/DroidMaintenanceModuleDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/SelectDroidEffectDelaySuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class RemoveDroidStructureSuiCallback : public SuiCallback, public Logger {

	ManagedReference<DroidMaintenanceModuleDataComponent*> module;

public:
	RemoveDroidStructureSuiCallback(ZoneServer* serv,
								    DroidMaintenanceModuleDataComponent* module) : SuiCallback(serv) {
		this->module = module;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if( !suiBox->isListBox() || module == NULL )
			return;

		if( cancelPressed )
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox );
		uint64 itemId = listBox->getMenuObjectID(index);

		Locker dlock( module->getDroidObject(), player );
		module->unassignStructure( itemId );

	}
};


#endif /* REMOVEDROIDSTRUCTURESUICALLBACK_H_ */
