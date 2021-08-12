#ifndef UPLINKTERMINALRESETTASK_H_
#define UPLINKTERMINALRESETTASK_H_

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"

class UplinkTerminalResetTask : public Task {
	ManagedReference<BuildingObject*> building;
	ManagedReference<GCWManager*> gcwManager;
	Reference<DestructibleBuildingDataComponent*> baseData;

public:
	UplinkTerminalResetTask(BuildingObject* base, GCWManager* gcwMan, DestructibleBuildingDataComponent* bData) {
		building = base;
		gcwManager = gcwMan;
		baseData = bData;
	}

	void run() {

		if (building == nullptr || gcwManager == nullptr || baseData == nullptr) {
			return;
		}

		if (gcwManager->isShutdownSequenceStarted(building) || gcwManager->isFacilityRebooting(building)) {
			reschedule(15 * 60 * 1000); // If base is rebooting or entered destruction sequence the task is rescheduled 15 Minutes
			return;
		}

		gcwManager->renewUplinkBand(building);
		baseData->setState(DestructibleBuildingDataComponent::VULNERABLE);
	}
};

#endif /* UPLINKTERMINALRESETTASK_H_ */