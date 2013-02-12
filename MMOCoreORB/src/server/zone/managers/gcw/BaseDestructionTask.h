/*
 * BaseDestructionTask.h
 *
 *  Created on: Nov 2, 2012
 *      Author: root
 */

#ifndef BASEDESTRUCTIONTASK_H_
#define BASEDESTRUCTIONTASK_H_

#include "engine/engine.h"
#include "GCWManager.h"

class BaseDestructionTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;
	ManagedWeakReference<BuildingObject*> buildingObject;
	int countDown;
public:
	BaseDestructionTask(GCWManager* manager, BuildingObject* building){
		gcwManager = manager;
		buildingObject = building;
		countDown = GCWManagerImplementation::destructionTimer / 60;
	}

	void run() {
		Logger::Logger tlog("DTASK");
		tlog.info("BaseDestruction task execution", true);
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
