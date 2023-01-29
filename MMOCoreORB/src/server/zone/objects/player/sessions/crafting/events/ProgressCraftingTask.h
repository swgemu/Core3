
/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PROGRESSCRAFTINGTASK_H_
#define PROGRESSCRAFTINGTASK_H_

class ProgressCraftingTask : public Task {
	ManagedWeakReference<TangibleObject*> craftTool;
	ManagedWeakReference<CreatureObject*> player;

public:
	ProgressCraftingTask(CreatureObject* pl, TangibleObject* tool, int time) : Task() {
		craftTool = tool;
		player = pl;
	}

	void run() {
		try {
			ManagedReference<TangibleObject* > craftingTool = craftTool.get();
			ManagedReference<CreatureObject* > crafter = player.get();

			if (craftingTool == nullptr || crafter == nullptr)
				return;

		} catch (Exception& e) {
			System::out << "Unreported exception caught in UpdateToolCountdownEvent::activate\n";
		}
	}
};

#endif /*PROGRESSCRAFTINGTASK_H_*/
