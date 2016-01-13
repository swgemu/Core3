/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALLOPNOTIFYAVAILABLEEVENT_H_
#define GALLOPNOTIFYAVAILABLEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class GallopNotifyAvailableEvent : public Task {
	ManagedWeakReference<CreatureObject*> creo;

public:
	GallopNotifyAvailableEvent(CreatureObject* cr) : Task() {
		creo = cr;
	}

	void run() {
		ManagedReference<CreatureObject*> mount = creo.get();

		if (mount == NULL)
			return;

		Locker locker(mount);

		mount->removePendingTask("gallop_notify");

		ManagedReference<CreatureObject*> owner = mount->getLinkedCreature().get();

		if (owner != NULL)
			owner->sendSystemMessage("@combat_effects:mount_not_tired"); // Your mount is no longer winded.
	}

};

#endif /*GALLOPNOTIFYAVAILABLEEVENT_H_*/
