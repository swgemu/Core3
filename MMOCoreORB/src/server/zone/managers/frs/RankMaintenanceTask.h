#ifndef RANKMAINTENANCETASK_H_
#define RANKMAINTENANCETASK_H_

#include "server/zone/managers/frs/FrsManager.h"

namespace server {
namespace zone {
namespace managers {
namespace frs {

class RankMaintenanceTask: public Task {
	ManagedWeakReference<FrsManager*> frsManager;

public:
	RankMaintenanceTask(FrsManager* frs) {
		frsManager = frs;
	}

	void run() {
		ManagedReference<FrsManager*> strongRef = frsManager.get();

		if (strongRef == NULL)
			return;

		strongRef->updateLastMaintenance();

		Vector<uint64> playerList = strongRef->getFullPlayerList();

		if (playerList.size() == 0) {
			reschedule(strongRef->getMaintenanceInterval());
			return;
		}

		int numTasks = 20;
		int playersPerTask = playerList.size() / numTasks;

		for (int i = 0; i < numTasks; i++) {
			int numPlayers = playersPerTask;

			if (i == numTasks - 1)
				numPlayers += playerList.size() % numTasks;

			Vector<uint> taskList;

			for (int j = 0; j < numPlayers; j++)
				taskList.add(playerList.get(i * playersPerTask + j));

			Core::getTaskManager()->scheduleTask([taskList, strongRef]{
				for (int i = 0; i < taskList.size(); i++) {
					ManagedReference<CreatureObject*> player = strongRef->getZoneServer()->getObject(taskList.get(i)).castTo<CreatureObject*>();

					if (player != NULL)
						strongRef->deductMaintenanceXp(player);
				}
			}, "frsMaintenanceTask", ((i % 5) + 1) * 1000);
		}

		reschedule(strongRef->getMaintenanceInterval());
	}
};

}
}
}
}

#endif /* RANKMAINTENANCETASK_H_ */
