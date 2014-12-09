/*
 * DroidPlaybackSuiCallback.h
 *
 */

#ifndef DROIDPLAYBACKSUICALLBACK_H
#define DROIDPLAYBACKSUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"

class SelectTrackSuiCallback : public SuiCallback {
public:
	SelectTrackSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox())
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());
		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL) {
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == NULL){
			return;
		}

		DroidPlaybackModuleDataComponent* module = cast<DroidPlaybackModuleDataComponent*>( droid->getModule("playback_module"));
		if(module == NULL) {
			return;
		}

		if (cancelPressed) {
			return;
		}
		if (otherPressed) {
			// pop up are you sure dialog here
			module->deleteTrack(index);
		} else {
			module->startRecordingSession(player,index);
		}
	}
};

#endif /* DROIDPLAYBACKSUICALLBACK_H */
