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

	ManagedReference<DroidObject*> droid;
	ManagedReference<CreatureObject*> owner;

public:
	DroidSkillModTask(DroidObject* droid, CreatureObject* owner) : Task() {
		this->droid = droid;
		this->owner = owner;
	}

	void run() {

		if( droid == NULL )
			return;

		Locker locker(droid);

		droid->removePendingTask("droid_skill_mod");

		// Check if droid is spawned
		if( droid->getLocalZone() == NULL ){  // Not outdoors
			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return;
			}
		}

		//refresh the skill mods if qualifying.
		droid->unloadSkillMods(owner);

		//various sources list 15m as the cut-off for all droid skill mods.
		//verify that it is in range, not dead, and not incapped
		if ( owner->isInRange(droid, 15) && !droid->isDead() && !droid->isIncapacitated() )
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
