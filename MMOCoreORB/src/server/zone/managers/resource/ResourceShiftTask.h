/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceShiftTask.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCESHIFTTASK_H_
#define RESOURCESHIFTTASK_H_

class ResourceShiftTask : public Task {
	ManagedReference<ResourceManager* > resourceManager;

public:
	ResourceShiftTask(ManagedReference<ResourceManager* >  resMan) {
		resourceManager = resMan;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		ZoneServer* server = resourceManager->getZoneServer();

		if (server == NULL || server->isServerShuttingDown())
			return;

		resourceManager->shiftResources();
	}
};

#endif /* RESOURCESHIFTTASK_H_ */
