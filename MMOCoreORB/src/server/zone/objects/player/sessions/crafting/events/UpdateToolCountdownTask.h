
/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATETOOLCOUNTDOWNTASK_H_
#define UPDATETOOLCOUNTDOWNTASK_H_

class UpdateToolCountdownTask : public Task {
	ManagedWeakReference<TangibleObject* > craftTool;
	ManagedWeakReference<CreatureObject* > player;
	int timeLeft;

public:
	UpdateToolCountdownTask(CreatureObject* pl, TangibleObject* tool, int time) : Task() {
		craftTool = tool;
		player = pl;
		timeLeft = time;
	}

	void run() {
		try {
			ManagedReference<TangibleObject* > craftingTool = craftTool.get();
			ManagedReference<CreatureObject* > crafter = player.get();

			if (craftingTool == NULL || crafter == NULL)
				return;

			Locker locker(crafter);

			Locker clocker(craftingTool, crafter);

			craftingTool->setCountdownTimer(timeLeft, true);

		} catch (Exception& e) {
			System::out << "Unreported exception caught in UpdateToolCountdownEvent::activate\n";
		}
	}
};

#endif /*UPDATETOOLCOUNTDOWNTASK_H_*/
