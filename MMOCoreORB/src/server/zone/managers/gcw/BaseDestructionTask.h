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
public:
	BaseDestructionTask(GCWManager* manager, BuildingObject* building){
		gcwManager = manager;
		buildingObject = building;
	}

	void run() {
		Logger::Logger tlog("DTASK");
		tlog.info("BaseDestruction task execution", true);
		ManagedReference<GCWManager*> strongRef = gcwManager.get();
		ManagedReference<BuildingObject*> building = buildingObject.get();
		if (strongRef == NULL){
			return;
		}

		strongRef->doBaseDestruction(building);

	}
};



#endif /* BASEDESTRUCTIONTASK_H_ */
