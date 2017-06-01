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

		strongRef->processRankMaintenance();
	}
};

}
}
}
}

#endif /* RANKMAINTENANCETASK_H_ */
