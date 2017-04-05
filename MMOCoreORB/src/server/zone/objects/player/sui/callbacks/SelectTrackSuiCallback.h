/*
 * DroidPlaybackSuiCallback.h
 *
 */

#ifndef DROIDPLAYBACKSUICALLBACK_H
#define DROIDPLAYBACKSUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/DeleteTrackConfirmationSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class SelectTrackSuiCallback : public SuiCallback {
public:
	SelectTrackSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}
	/** droid and player should be locked by the ui start */
	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox())
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());
		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == NULL) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == NULL){
			return;
		}
		Locker crosslock(droid,player);
		auto module = droid->getModule("playback_module").castTo<DroidPlaybackModuleDataComponent*>();
		if(module == NULL) {
			return;
		}

		if (cancelPressed || index == -1) {
			return;
		}
		if (otherPressed) {
			// pop up are you sure dialog here, need delete confiration callback box.
			// make the confirmation UI
			ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::DROID_DELETE_TRACK);
			box->setCallback(new DeleteTrackConfirmationSuiCallback(player->getZoneServer(), module, index));
			box->setPromptTitle("@pet/droid_modules:playback_delete_title"); // Configure Effects
			box->setPromptText("@pet/droid_modules:playback_delete_prompt");
			box->setOkButton(true, "@ok");
			box->setCancelButton(true, "@cancel");
			box->setUsingObject(droid);
			player->getPlayerObject()->addSuiBox(box);
			player->sendMessage(box->generateMessage());
		} else {
			// if track is empty record
			if (module->trackEmpty(index)) {
				module->startRecordingSession(player,index);
			}
			else {
				module->playSong(player,index);
			}
		}
	}
};

#endif /* DROIDPLAYBACKSUICALLBACK_H */
