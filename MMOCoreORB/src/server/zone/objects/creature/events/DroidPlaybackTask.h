/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDPOWERTASK_H_
#define DROIDPOWERTASK_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidPlaybackTask : public Task {

	ManagedReference<DroidPlaybackModuleDataComponent*> module;
	bool playing;
public:
	DroidPlaybackTask(DroidPlaybackModuleDataComponent* module) : Task() {
		this->module = module;
		playing = false;
	}

	void run() {
		if (module == NULL)
			return;

		DroidObject* droid = module->getDroidObject();
		if (droid == NULL)
			return;

		Locker locker(droid);

		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				module->deactivate();
				droid->removePendingTask("droid_playback");
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			module->deactivate();
			droid->removePendingTask("droid_playback");
			return;
		}


		// Droid must have power
		if( !droid->hasPower() ){
			module->deactivate();
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_playback");
			return;
		}


		String performance = module->getCurrentTrack();
		int instrument = module->getCurrentInstrument();
		if (instrument == -1) {
			module->deactivate();
			return;
		}
		if (performance.length() == 0) {
			module->deactivate();
			return;
		}

		if (!playing) {
			DroidObject* droid = module->getDroidObject();
			// we fire off the performance piece and let it run
			droid->setPerformanceAnimation(performance, false);
			droid->setPerformanceCounter(0, false);
			droid->setInstrumentID(instrument, false);
			// broadcast the song
			CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(droid);
			dcreo6->updatePerformanceAnimation(performance);
			dcreo6->updatePerformanceCounter(0);
			dcreo6->updateInstrumentID(instrument);
			dcreo6->close();
			droid->broadcastMessage(dcreo6, true);
			playing = true;
		}
		// recheck every 30 seconds for power ont he droid
		droid->addPendingTask("droid_playback",this,30000);
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDPOWERTASK_H_*/
