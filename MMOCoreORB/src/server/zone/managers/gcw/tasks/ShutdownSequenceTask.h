/*
 * ShutdownSequenceTask.h
 *
 *  Created on: Feb 20, 2013
 *      Author: root
 */

#ifndef SHUTDOWNSEQUENCETASK_H_
#define SHUTDOWNSEQUENCETASK_H_

#include "server/zone/managers/gcw/GCWManager.h"

class ShutdownSequenceTask : public Task {

	ManagedReference<BuildingObject*> buildingObject;
	ManagedReference<GCWManager*> gcwManager;
	ManagedReference<CreatureObject*> creature;
	ManagedReference<SceneObject*> hqTerminal;
	bool bDestruction;

public:

	ShutdownSequenceTask(GCWManager* gcwMan, BuildingObject* building, CreatureObject* player, SceneObject* term, bool isDestruction) {
		gcwManager = gcwMan;
		buildingObject = building;
		bDestruction = isDestruction;
		creature = player;
		hqTerminal = term;
	}

	void run() {

		if (buildingObject == NULL || gcwManager == NULL  )
			return;

		if(bDestruction)
			gcwManager->scheduleBaseDestruction(buildingObject, creature);
		else
			gcwManager->startAbortSequenceDelay(buildingObject, creature, hqTerminal);

	}
};

#endif /* SHUTDOWNSEQUENCETASK_H_ */
