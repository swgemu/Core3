/*
 * LoadStimpackSuiCallback.h
 *
 */

#ifndef LOADSTIMPACKSUICALLBACK_H_
#define LOADSTIMPACKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

class LoadStimpackSuiCallback : public SuiCallback {
public:
	LoadStimpackSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed != 0) {
			return;
		}

		if (args->size() < 1) {
			player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<StimPack*> stimpack = server->getObject(listBox->getMenuObjectID(index)).castTo<StimPack*>();
		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();
		if(stimpack == NULL) {
			player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
			return;
		}
		if (object == NULL) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == NULL){
			return;
		}

		auto module = droid->getModule("stimpack_module").castTo<DroidStimpackModuleDataComponent*>();
		if(module == NULL) {
			return;
		}

		Locker locker(player);
		Locker clocker(player, droid);

		if (stimpack->isRangedStimPack()) {
			player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
			return;
		}
		module->handleInsertStimpack(player, stimpack);
	}

};

#endif /* LOADSTIMPACKSUICALLBACK_H_ */
