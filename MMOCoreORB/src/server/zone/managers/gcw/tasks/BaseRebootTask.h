#ifndef BASEREBOOTTASK_H_
#define BASEREBOOTTASK_H_

#include "engine/engine.h"
#include "server/zone/managers/gcw/GCWManager.h"

class BaseRebootTask : public Task {
	ManagedReference<BuildingObject*> buildingObject;
	ManagedReference<GCWManager*> gcwManager;
	ManagedReference<DestructibleBuildingDataComponent*> baseData;

public:
	BaseRebootTask(GCWManager* gcwMan, BuildingObject* building, DestructibleBuildingDataComponent* data) {
		gcwManager = gcwMan;
		buildingObject = building;
		baseData = data;
	}

	void run() {
		if (gcwManager == NULL || buildingObject == NULL || baseData == NULL)
			return;

		Locker block(buildingObject);

		baseData->setState(DestructibleBuildingDataComponent::OVERLOADED);
	}
};

#endif /* BASEREBOOTTASK_H_ */
