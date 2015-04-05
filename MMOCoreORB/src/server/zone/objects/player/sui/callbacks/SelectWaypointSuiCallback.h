/*
 * SelectDroidEffectSuiCallback.h
 *
 *  Created on: 11/28/2014
 *      Author: Klivian
 */

#ifndef SELECTWAYPOINTEFFECTSUICALLBACK_H_
#define SELECTWAYPOINTEFFECTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/tangible/components/droid/DroidMerchantModuleDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/PlayerObject.h"

class SelectWaypointSuiCallback : public SuiCallback, public Logger {

	ManagedReference<DroidMerchantModuleDataComponent*> module;
	int slotIndex;

public:
	SelectWaypointSuiCallback(ZoneServer* serv,DroidMerchantModuleDataComponent* module) : SuiCallback(serv), module(module), slotIndex(0) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if( !suiBox->isListBox() || module == NULL )
			return;

		if( cancelPressed ){
			return;
		}

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox );
		ManagedReference<WaypointObject*> waypoint = server->getObject(listBox->getMenuObjectID(index)).castTo<WaypointObject*>();
		// If empty slot is configured, remove the configured effect
		if( waypoint != NULL ){
			Locker dlock( module->getDroidObject(), player );
			module->setWaypoint(waypoint);
			player->sendSystemMessage("@pet/droid_modules:waypoint_set");
		}
	}
};


#endif /* SELECTDROIDEFFECTSUICALLBACK_H_ */
