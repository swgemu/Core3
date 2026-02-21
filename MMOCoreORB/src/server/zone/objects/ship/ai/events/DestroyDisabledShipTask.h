/*
 * DestroyDisabledShipTask.h
 *
 * Created on: 2026-02-21
 * Author: Hakry
 */

#ifndef DESTROYDISABLEDSHIPTASK_H_
#define DESTROYDISABLEDSHIPTASK_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/events/DestroyShipTask.h"
#include "server/zone/Zone.h"

class DestroyDisabledShipTask : public Task {
	ManagedWeakReference<ShipAiAgent*> shipAgent;

public:
	DestroyDisabledShipTask(ShipAiAgent* agent) : Task(1000) {
		shipAgent = agent;
	}

	void run() {
		ManagedReference<ShipAiAgent*> strongAgent = shipAgent.get();

		if (strongAgent == nullptr) {
			return;
		}

		Locker locker(strongAgent);

		strongAgent->removePendingTask("destroy_disabled");

		if (strongAgent->isShipDestroyed()) {
			// strongAgent->info(true) << "DestroyDisabledShipTask -- ship already destroyed, skipping";
			return;
		}

		if (!strongAgent->isShipDisabled()) {
			// strongAgent->info(true) << "DestroyDisabledShipTask -- ship no longer disabled, skipping";
			return;
		}

		// strongAgent->info(true) << "DestroyDisabledShipTask -- destroying disabled ship: " << strongAgent->getDisplayedName();

		auto destroyTask = new DestroyShipTask(strongAgent);

		if (destroyTask == nullptr) {
			strongAgent->destroyObjectFromWorld(true);
		} else {
			destroyTask->execute();
		}

		Core::getTaskManager()->scheduleTask([strongAgent] () {
			if (strongAgent == nullptr) {
				return;
			}

			Locker lock(strongAgent);

			strongAgent->notifyObjectDestructionObservers(nullptr, 0, true);
		}, "notifyShipDestroyLambda", 200);
	}

	void schedule(uint64 delay = 0) {
		ManagedReference<ShipAiAgent*> strongAgent = shipAgent.get();

		if (strongAgent != nullptr) {
			auto zone = strongAgent->getZone();

			if (zone != nullptr) {
				setCustomTaskQueue(zone->getZoneName());
			}
		}

		try {
			Task::schedule(delay);
		} catch (...) {
		}
	}
};

#endif /* DESTROYDISABLEDSHIPTASK_H_ */
