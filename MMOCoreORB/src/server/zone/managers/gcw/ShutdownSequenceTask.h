/*
 * ShutdownSequenceTask.h
 *
 *  Created on: Feb 20, 2013
 *      Author: root
 */

#ifndef SHUTDOWNSEQUENCETASK_H_
#define SHUTDOWNSEQUENCETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/gcw/GCWManager.h"

class ShutdownSequenceTask : public Task {

	ManagedReference<BuildingObject*> buildingObject;
	ManagedReference<GCWManager*> gcwManager;
	ManagedReference<CreatureObject*> creature;
	bool bDestruction;

public:

	ShutdownSequenceTask(GCWManager* gcwMan, BuildingObject* building, CreatureObject* player, bool isDestruction) {
		gcwManager = gcwMan;
		buildingObject = building;
		bDestruction = isDestruction;
		creature = player;
	}

	void run() {

		if (buildingObject == NULL || gcwManager == NULL  )
			return;

		if(bDestruction)
			gcwManager->scheduleBaseDestruction(buildingObject, creature);
		else
			gcwManager->abortShutdownSequence(buildingObject, creature);

	}
};

#endif /* SHUTDOWNSEQUENCETASK_H_ */
