/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDPOWERTASK_H_
#define DROIDPOWERTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidPowerTask : public Task {

	ManagedWeakReference<DroidObject*> droid;

public:
	DroidPowerTask(DroidObject* droid) : Task() {
		this->droid = droid;
	}

	void run() {
		ManagedReference<DroidObject*> strongDroid = droid.get();

		if( strongDroid == NULL )
			return;

		Locker locker(strongDroid);

		strongDroid->removePendingTask("droid_power");

		// Check if droid is spawned
		if( strongDroid->getLocalZone() == NULL ){  // Not outdoors

			ManagedReference<SceneObject*> parent = strongDroid->getParent().get();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return;
			}
		}

		// Consume power if available
		if ( strongDroid->hasPower() ) {
			strongDroid->usePower(4);
			strongDroid->runModulePowerDrain();
		}

		strongDroid->addPendingTask("droid_power", this, 120000); // 2 min
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDPOWERTASK_H_*/
