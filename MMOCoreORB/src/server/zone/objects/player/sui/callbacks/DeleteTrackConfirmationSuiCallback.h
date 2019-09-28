/*
 * DroidPlaybackSuiCallback.h
 *
 */

#ifndef DELETETRACKCONFIRMATIONSUICALLBACK_H
#define DELETETRACKCONFIRMATIONSUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class DeleteTrackConfirmationSuiCallback : public SuiCallback {
public:
	Reference<DroidPlaybackModuleDataComponent*> module;
	int track;
	DeleteTrackConfirmationSuiCallback(ZoneServer* server, DroidPlaybackModuleDataComponent* m, int index)
		: SuiCallback(server) {
		track = index;
		module = m;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox())
			return;

		SuiMessageBox* listBox = cast<SuiMessageBox*>( suiBox);
		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == nullptr) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == nullptr){
			return;
		}
		// should be locked before hand

		if(module == nullptr) {
			return;
		}

		if (cancelPressed) {
			return;
		}
		Locker crosslock(droid,player);
		module->deleteTrack(player,track);
	}
};

#endif /* DELETETRACKCONFIRMATIONSUICALLBACK_H */
