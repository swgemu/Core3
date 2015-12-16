/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDSKILLMODTASK_H_
#define DROIDSKILLMODTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidSkillModTask : public Task {

	ManagedWeakReference<DroidObject*> droid;
	ManagedWeakReference<CreatureObject*> owner;

public:
	DroidSkillModTask(DroidObject* droid, CreatureObject* owner) : Task() {
		this->droid = droid;
		this->owner = owner;
	}

	void run() {

		if( this->droid == NULL || this->owner == NULL )
			return;

		ManagedReference<DroidObject*> droid = this->droid;
		ManagedReference<CreatureObject*> owner = this->owner;

		Locker locker(droid);

		droid->removePendingTask("droid_skill_mod");

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors
			ManagedReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return;
			}
		}

		Locker crossLocker(owner, droid);

		//refresh the skill mods if qualifying.
		droid->unloadSkillMods(owner);

		//various sources list 15m as the cut-off for all droid skill mods.
		//verify that it is in range, has power, not dead, and not incapped
		if ( owner->isInRange(droid, 15) && !droid->isDead() && !droid->isIncapacitated() && droid->hasPower() )
			droid->loadSkillMods(owner);

		reschedule( 3000 ); // 3 sec

	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDSKILLMODTASK_H_*/
