/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDPOWERTASK_H_
#define DROIDPOWERTASK_H_

#include "server/zone/objects/creature/DroidObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidPowerTask : public Task {

	ManagedReference<DroidObject*> droid;

public:
	DroidPowerTask(DroidObject* droid) : Task() {
		this->droid = droid;
	}

	void run() {

		if( droid == NULL )
			return;

		Locker locker(droid);

		droid->removePendingTask("droid_power");

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return;
			}
		}

		// Consume power if available
		if ( droid->hasPower() ) {
			droid->usePower(4);
			droid->runModulePowerDrain();
		}

		reschedule( 120000 ); // 2 min
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDPOWERTASK_H_*/
