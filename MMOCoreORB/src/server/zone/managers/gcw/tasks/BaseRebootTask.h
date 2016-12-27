#ifndef BASEREBOOTTASK_H_
#define BASEREBOOTTASK_H_

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

		StringIdChatParameter restartMessage;
		restartMessage.setStringId("@faction/faction_hq/faction_hq_response:terminal_response08"); // FACILITY RESTART: RELOADING PRIMARY FACILITY SYSTEMS
		gcwManager->broadcastBuilding(buildingObject, restartMessage);
	}
};

#endif /* BASEREBOOTTASK_H_ */
