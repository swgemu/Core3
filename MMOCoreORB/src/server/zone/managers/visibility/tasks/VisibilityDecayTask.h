/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VISIBILITYDECAYTASK_H_
#define VISIBILITYDECAYTASK_H_

#include "server/zone/managers/visibility/VisibilityManager.h"

namespace server {
namespace zone {
namespace managers {
namespace visibility {
namespace tasks {

class VisibilityDecayTask : public Task {
public:
	VisibilityDecayTask() : Task() {
	}

	void run() {
		VisibilityManager::instance()->performVisiblityDecay();
		reschedule(VisibilityManager::instance()->getVisDecayTickRate() * 1000);
	}
};

}
}
}
}
}

using namespace server::zone::managers::visibility::tasks;

#endif /* VISIBILITYDECAYTASK_H_ */
