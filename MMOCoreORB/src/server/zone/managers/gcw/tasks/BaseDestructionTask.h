/*
 * BaseDestructionTask.h
 *
 *  Created on: Nov 2, 2012
 *      Author: root
 */

#ifndef BASEDESTRUCTIONTASK_H_
#define BASEDESTRUCTIONTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"

class BaseDestructionTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;
	ManagedWeakReference<BuildingObject*> buildingObject;
	int countDown;
public:
	BaseDestructionTask(GCWManager* manager, BuildingObject* building) {
		gcwManager = manager;
		buildingObject = building;
		countDown = manager->getDestructionTimer() / 60;
	}

	void run() {
		countDown--;
		ManagedReference<GCWManager*> strongRef = gcwManager.get();
		ManagedReference<BuildingObject*> building = buildingObject.get();
		if (strongRef == NULL){
			return;
		}

		strongRef->doBaseDestruction(building);

	}

	int getCountdown(){
		return countDown;
	}
};

#endif /* BASEDESTRUCTIONTASK_H_ */
