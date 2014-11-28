/*
 * SelectDroidEffectSuiCallback.h
 *
 *  Created on: 11/28/2014
 *      Author: Klivian
 */

#ifndef SELECTDROIDEFFECTSUICALLBACK_H_
#define SELECTDROIDEFFECTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/tangible/components/droid/DroidEffectsModuleDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class SelectDroidEffectSuiCallback : public SuiCallback, public Logger {

	ManagedReference<DroidEffectsModuleDataComponent*> module;
	int slotIndex;

public:
	SelectDroidEffectSuiCallback(ZoneServer* serv, DroidEffectsModuleDataComponent* module, int slotIndex) :
		SuiCallback(serv) {
		this->module = module;
		this->slotIndex = slotIndex;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		info( "SelectDroidEffectSuiCallback::run", true );

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( !suiBox->isListBox() || playerManager == NULL )
			return;

		if( cancelPressed ){
			return;
		}

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());
		info( "index=" + String::valueOf(index), true);

		SuiListBox* listBox = cast<SuiListBox*>( suiBox );
		String effectName = listBox->getMenuItemName(index);
		info( "effectName=" + effectName, true );

		// If empty slot is configured, remove the configured effect
		if( effectName.contains( "empty_slot" ) ){
			module->setEffect( effectName, -1, slotIndex );
		}
		// Otherwise prompt for delay
		else{
			//TODO Prompt for delay
			module->setEffect( effectName, 10, slotIndex );
		}

	}
};


#endif /* SELECTDROIDEFFECTSUICALLBACK_H_ */
