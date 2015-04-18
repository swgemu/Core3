/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BURSTRUNNOTIFYAVAILABLEEVENT_H_
#define BURSTRUNNOTIFYAVAILABLEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class BurstRunNotifyAvailableEvent : public Task {
	ManagedWeakReference<CreatureObject*> creo;

public:
	BurstRunNotifyAvailableEvent(CreatureObject* cr) : Task() {
		creo = cr;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = creo.get();

		if (creature == NULL)
			return;

		Locker locker(creature);

		creature->removePendingTask("burst_run_notify");
		creature->sendSystemMessage("@combat_effects:burst_run_not_tired"); //"You are no longer tired.";
	}

};

#endif /*BURSTRUNNOTIFYAVAILABLEEVENT_H_*/
