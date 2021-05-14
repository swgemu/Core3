/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDPLAYBACKEVENT_H_
#define DROIDPLAYBACKEVENT_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidPlaybackEvent : public Task {

	Reference<DroidPlaybackModuleDataComponent*> module;
	ManagedReference<CreatureObject*> player;
	int action;
	int performanceIndex;
public:
	const static uint8 SET_TRACK = 0;
	const static uint8 CHANGE_SONG = 1;
	const static uint8 STOP_PLAYING = 2;

	DroidPlaybackEvent(DroidPlaybackModuleDataComponent* module,CreatureObject* player, int perfIndex, int action) : Task() {
		this->module = module;
		this->action = action;
		this->performanceIndex = perfIndex;
		this->player = player;
	}

	void run() {
		if (module == nullptr)
			return;

		DroidObject* droid = module->getDroidObject();

		if (droid == nullptr)
			return;

		Locker locker(droid);

		if (droid->getLocalZone() == nullptr) {  // Not outdoors
			ManagedReference<SceneObject*> parent = droid->getParent().get();

			if (parent == nullptr || !parent->isCellObject()) { // Not indoors either
				module->deactivate();
				droid->removePendingTask("droid_playback_event");
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			module->deactivate();
			droid->removePendingTask("droid_playback_event");
			return;
		}


		// Droid must have power
		if (!droid->hasPower()) {
			module->deactivate();
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_playback_event");
			return;
		}

		Locker plock(player);
		Locker crossLock(droid,player);

		if (action == SET_TRACK)
			module->setTrack(player, performanceIndex);
		if (action == CHANGE_SONG)
			module->songChanged(player);
		if (action == STOP_PLAYING)
			module->songStopped(player);

	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDPLAYBACKEVENT_H_*/
