/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDPOWERTASK_H_
#define DROIDPOWERTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/managers/skill/SkillManager.h"

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

			ManagedReference<SceneObject*> parent = droid->getParent().get();
			if( parent == NULL || !parent->isCellObject() ){ // Not indoors either
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
		SkillManager* skillManager = droid->getZoneServer()->getSkillManager();
		if (skillManager == NULL)
			return;

		PerformanceManager* performanceManager = skillManager->getPerformanceManager();
		if (performanceManager == NULL)
			return;

		String instrumentAnimation;
		int instrid = performanceManager->getInstrumentId(performance);
		instrid += performanceManager->getInstrumentAnimation(instrument, instrumentAnimation);
		if (!playing) {
			droid->setPosture(CreaturePosture::SKILLANIMATING);
			// we fire off the performance piece and let it run
			droid->setPerformanceAnimation(instrumentAnimation, false);
			droid->setPerformanceCounter(0, false);
			droid->setInstrumentID(instrid, false);
			// broadcast the song
			CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(droid);
			dcreo6->updatePerformanceAnimation(instrumentAnimation);
			dcreo6->updatePerformanceCounter(0);
			dcreo6->updateInstrumentID(instrid);
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
