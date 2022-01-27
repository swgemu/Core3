/*
 * CheckWildContrabandScanTask.h
 *
 *  Created on: Aug 25, 2020
 *      Author: Loshult
 */

#ifndef CHECKWILDCONTRABANDSCANTASK_H_
#define CHECKWILDCONTRABANDSCANTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/Zone.h"

class CheckWildContrabandScanTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;

public:
	CheckWildContrabandScanTask(GCWManager* manager) {
		gcwManager = manager;
	}

	void run() {
		ManagedReference<GCWManager*> strongRef = gcwManager.get();

		if (strongRef == nullptr) {
			return;
		}

		ZoneServer* server = strongRef->getZone()->getZoneServer();

		if (server == nullptr || server->isServerShuttingDown())
			return;

		if (!server->isServerOnline()) {
			schedule(strongRef->getCrackdownScanInterval() * 10 + System::random(600000));
			return;
		}

		strongRef->performCheckWildContrabandScanTask();
	}
};

#endif /* CHECKWILDCONTRABANDSCANTASK_H_ */
