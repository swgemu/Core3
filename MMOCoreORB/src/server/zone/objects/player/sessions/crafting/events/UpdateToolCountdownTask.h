
/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATETOOLCOUNTDOWNTASK_H_
#define UPDATETOOLCOUNTDOWNTASK_H_


#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"

class UpdateToolCountdownTask : public Task {
	ManagedReference<TangibleObject* > craftingTool;
	ManagedReference<CreatureObject* > crafter;
	int timeLeft;

public:
	UpdateToolCountdownTask(CreatureObject* pl, TangibleObject* tool, int time) : Task() {
		craftingTool = tool;
		crafter = pl;
		timeLeft = time;
	}

	void run() {
		try {
			Locker locker(crafter);

			Locker clocker(craftingTool, crafter);

			craftingTool->setCountdownTimer(timeLeft, true);

		} catch (Exception& e) {
			System::out << "Unreported exception caught in UpdateToolCountdownEvent::activate\n";
		}
	}
};

#endif /*UPDATETOOLCOUNTDOWNTASK_H_*/
