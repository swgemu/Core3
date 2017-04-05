/*
 * SelectHarvestSuiCallback.h
 *
 */

#ifndef SELECTHARVESTSUICALLBACK_H_
#define SELECTHARVESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

class SelectHarvestSuiCallback : public SuiCallback {
public:
	SelectHarvestSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed != 0) {
			return;
		}

		if (args->size() < 1) {
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == NULL) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == NULL){
			return;
		}

		auto module = droid->getModule("harvest_module").castTo<DroidHarvestModuleDataComponent*>();
		if(module == NULL) {
			return;
		}

		Locker crosslock(droid,player);

		module->setHarvestInterest(player, index);
	}

};

#endif /* SELECTHARVESTSUICALLBACK_H_ */
