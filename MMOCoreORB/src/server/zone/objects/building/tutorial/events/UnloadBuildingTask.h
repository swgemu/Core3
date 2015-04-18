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
	ManagedReference<TutorialBuildingObject*> building;

public:
	UnloadBuildingTask(TutorialBuildingObject* bo) :
		Task() {
		building = bo;
	}

	void run() {
		Locker _locker(building);

		try {
			building->clearUnloadEvent();

			building->destroyObjectFromWorld(true);
		} catch (Exception& e) {
			building->error("unreported exception caught in UnloadBuildingTask::run");

			building->clearUnloadEvent();
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
