/*
 * CheckGCWTask.h
 *
 *  Created on: Oct 24, 2012
 *      Author: root
 */

#ifndef CHECKGCWTASK_H_
#define CHECKGCWTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"

class CheckGCWTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;

public:
	CheckGCWTask(GCWManager* manager){
		gcwManager = manager;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		ManagedReference<GCWManager*> strongRef = gcwManager.get();

		if (strongRef == NULL){
			return;
		}

		ZoneServer* server = strongRef->getZone()->getZoneServer();

		if (server == NULL || server->isServerShuttingDown())
			return;

		strongRef->performGCWTasks(false);

	}
};




#endif /* CHECKGCWTASK_H_ */
