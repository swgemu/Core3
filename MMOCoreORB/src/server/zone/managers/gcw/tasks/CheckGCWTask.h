/*
 * CheckGCWTask.h
 *
 *  Created on: Oct 24, 2012
 *      Author: root
 */

#ifndef CHECKGCWTASK_H_
#define CHECKGCWTASK_H_
#include "engine/engine.h"
#include "server/zone/managers/gcw/GCWManager.h"

namespace server {
namespace zone {
namespace managers {
namespace gcw {
namespace tasks {

class CheckGCWTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;

public:
	CheckGCWTask(GCWManager* manager) {
		gcwManager = manager;
	}

	void run() {
		ManagedReference<GCWManager*> strongRef = gcwManager.get();

		if (strongRef == NULL) {
			return;
		}

		strongRef->performGCWTasks();

	}
};

}
}
}
}
}

using namespace server::zone::managers::gcw::tasks;

#endif /* CHECKGCWTASK_H_ */
