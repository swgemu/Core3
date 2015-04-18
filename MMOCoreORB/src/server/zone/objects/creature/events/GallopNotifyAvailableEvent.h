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
		ManagedReference<CreatureObject*> creature = creo.get();

		if (creature == NULL)
			return;

		Locker locker(creature);

		creature->removePendingTask("gallop_notify");
		creature->sendSystemMessage("@combat_effects:mount_not_tired"); // Your mount is no longer winded.
	}

};

#endif /*GALLOPNOTIFYAVAILABLEEVENT_H_*/
