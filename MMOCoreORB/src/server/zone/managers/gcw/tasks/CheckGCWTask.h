/*
 * CheckGCWTask.h
 *
 *  Created on: Oct 24, 2012
 *      Author: root
 */

#ifndef CHECKGCWTASK_H_
#define CHECKGCWTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/Zone.h"

class CheckGCWTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;

public:
	CheckGCWTask(GCWManager* manager){
		gcwManager = manager;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		ManagedReference<GCWManager*> strongRef = gcwManager.get();

		if (strongRef == nullptr){
			return;
		}

		ZoneServer* server = strongRef->getZone()->getZoneServer();

		if (server == nullptr || server->isServerShuttingDown())
			return;

		if (!server->isServerOnline()) {
			schedule((60 + System::random(30)) * 1000);
			return;
		}

		strongRef->performGCWTasks();
	}
};

#endif /* CHECKGCWTASK_H_ */
