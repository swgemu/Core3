/*
 * LoadStimpackSuiCallback.h
 *
 */

#ifndef LOADSTIMPACKSUICALLBACK_H_
#define LOADSTIMPACKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/DroidObject.h"

class SelectHarvestSuiCallback : public SuiCallback {
public:
	SelectHarvestSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if (!suiBox->isListBox() || cancelPressed != 0) {
			return;
		}

		if (args->size() < 1) {
			player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == NULL){
			return;
		}

		DroidHarvestModuleDataComponent* module = cast<DroidHarvestModuleDataComponent*>( droid->getModule("harvest_module"));
		if(module == NULL) {
			return;
		}

		Locker crosslock(droid,player);

		module->setHarvestInterest(player, index);
	}

};

#endif /* LOADSTIMPACKSUICALLBACK_H_ */
