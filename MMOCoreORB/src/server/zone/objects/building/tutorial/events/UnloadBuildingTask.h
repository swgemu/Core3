/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef UNLOADBUILDINGTASK_H_
#define UNLOADBUILDINGTASK_H_

#include "server/zone/objects/building/tutorial/TutorialBuildingObject.h"

namespace server {
namespace zone {
namespace objects {
namespace building {
namespace tutorial {
namespace events {

class UnloadBuildingTask: public Task {
	ManagedWeakReference<TutorialBuildingObject*> building;

public:
	UnloadBuildingTask(TutorialBuildingObject* bo) :
		Task() {
		building = bo;
	}

	void run() {
		ManagedReference<TutorialBuildingObject*> blg = building.get();

		if (blg == NULL)
			return;

		Locker _locker(blg);

		try {
			blg->clearUnloadEvent();

			blg->destroyObjectFromWorld(true);
		} catch (Exception& e) {
			blg->error("unreported exception caught in UnloadBuildingTask::run");

			blg->clearUnloadEvent();
		}
	}

};

}
}
}
}
}
}

#endif /*UNLOADBUILDINGTASK_H_*/
