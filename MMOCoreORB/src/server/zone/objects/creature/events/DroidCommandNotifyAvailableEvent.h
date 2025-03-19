/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDCOMMANDNOTIFYAVAILABLEEVENT_H_
#define DROIDCOMMANDNOTIFYAVAILABLEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class DroidCommandNotifyAvailableEvent : public Task {
	ManagedWeakReference<CreatureObject*> creo;

public:
	DroidCommandNotifyAvailableEvent(CreatureObject* cr) : Task() {
		creo = cr;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = creo.get();

		if (creature == nullptr)
			return;

		Locker locker(creature);

		creature->removePendingTask("droid_command_notify");
		creature->sendSystemMessage("@space/space_interaction:droid_delay_ready"); //Droid command completed. Ready for new command.
	}

};

#endif /*DROIDCOMMANDNOTIFYAVAILABLEEVENT_H_*/
