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

		ManagedReference<DroidObject*> strongDroidRef = droid;
		ManagedReference<CreatureObject*> strongOwnerRef = owner;

		if( strongDroidRef == NULL || strongOwnerRef == NULL )
			return;

		Locker locker(strongDroidRef);

		strongDroidRef->removePendingTask("droid_skill_mod");

		// Check if droid is spawned
		if( strongDroidRef->getLocalZone() == NULL ){  // Not outdoors
			ManagedReference<SceneObject*> parent = strongDroidRef->getParent().get();
			if( parent == NULL || !parent->isCellObject() ){ // Not indoors either
				return;
			}
		}

		Locker crossLocker(strongOwnerRef, strongDroidRef);

		//refresh the skill mods if qualifying.
		strongDroidRef->unloadSkillMods(strongOwnerRef);

		//various sources list 15m as the cut-off for all droid skill mods.
		//verify that it is in range, has power, not dead, and not incapped
		if ( strongOwnerRef->isInRange(strongDroidRef, 15) && !strongDroidRef->isDead() && !strongDroidRef->isIncapacitated() && strongDroidRef->hasPower() )
			strongDroidRef->loadSkillMods(strongOwnerRef);

		strongDroidRef->addPendingTask("droid_skill_mod", this, 3000); // 3 sec
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDSKILLMODTASK_H_*/
