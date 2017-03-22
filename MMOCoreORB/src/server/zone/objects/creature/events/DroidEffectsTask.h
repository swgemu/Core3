/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDEFFECTSTASK_H_
#define DROIDEFFECTSTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidEffectsModuleDataComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidEffectsTask : public Task, public Logger {

	ManagedReference<DroidEffectsModuleDataComponent*> module;

public:
	DroidEffectsTask(DroidEffectsModuleDataComponent* module) : Task() {
		this->module = module;
	}

	void run() {

		if( module == NULL || module->getDroidObject() == NULL ){
			return;
		}

		DroidObject* droid = module->getDroidObject();

		Locker locker(droid);

		// Check if module is still active
		if( !module->isActive() ){
			droid->removePendingTask("droid_effects");
			return;
		}

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedReference<SceneObject*> parent = droid->getParent().get();
			if( parent == NULL || !parent->isCellObject() ){ // Not indoors either
				droid->removePendingTask("droid_effects");
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			droid->removePendingTask("droid_effects");
			return;
		}


		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_effects");
			return;
		}

		// Play animation
		droid->playEffect( module->getCurrentAnimation() );

		// Reschedule task if next effect is valid
		uint64 delay = (uint64)module->getCurrentDelay() * 1000;
		if (delay > 0 && module->nextEffect()) {
			reschedule( delay );
		} else {
			droid->removePendingTask("droid_effects");
		}

	}

};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDEFFECTSTASK_H_*/
