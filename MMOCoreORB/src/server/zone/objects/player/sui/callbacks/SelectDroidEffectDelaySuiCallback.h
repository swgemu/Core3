/*
 * SelectDroidEffectDelaySuiCallback.h
 *
 *  Created on: November 30, 2014
 *      Author: Klivian
 */

#ifndef SELECTDROIDEFFECTDELAYSUICALLBACK_H_
#define SELECTDROIDEFFECTDELAYSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/droid/DroidEffectsModuleDataComponent.h"


class SelectDroidEffectDelaySuiCallback : public SuiCallback, public Logger {

	ManagedReference<DroidEffectsModuleDataComponent*> module;
	String effectName;
	int slotIndex;

public:
	SelectDroidEffectDelaySuiCallback(ZoneServer* serv, DroidEffectsModuleDataComponent* module, String effectName, int slotIndex) : SuiCallback(serv) {
		this->module = module;
		this->effectName = effectName;
		this->slotIndex = slotIndex;
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1 || module == NULL)
			return;

		try {
			int delay = Integer::valueOf(args->get(0).toString());

			if(delay > 3 && delay <= 60){

				Locker dlock( module->getDroidObject(), player );
				module->setEffect( effectName, delay, slotIndex );
				player->sendSystemMessage("Effect successfully configured in slot " + String::valueOf(slotIndex+1));
			}
			else{
				player->sendSystemMessage("@pet/droid_modules:invalid_delay_time"); // "The delay must be at least 3 seconds and no longer than 60 seconds"
			}
		} catch(Exception& e) {
			player->sendSystemMessage("@pet/droid_modules:invalid_delay_time"); // "The delay must be at least 3 seconds and no longer than 60 seconds"
		}

	}
};

#endif /* SELECTDROIDEFFECTDELAYSUICALLBACK_H_ */
