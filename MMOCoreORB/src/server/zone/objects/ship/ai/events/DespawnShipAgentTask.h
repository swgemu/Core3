/*
 * DespawnShipAgentTask.h
 *
 * Created on: 2024-10-25
 * Author: Hakry
 */

#ifndef DESPAWNSHIPAGENTTASK_H_
#define DESPAWNSHIPAGENTTASK_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/Zone.h"

class DespawnShipAgentTask : public Task {
	ManagedReference<ShipAiAgent*> shipAgent;

public:
	DespawnShipAgentTask(ShipAiAgent* agent) : Task(1000) {
		shipAgent = agent;
	}

	void run() {
		Locker locker(shipAgent);

		shipAgent->removePendingTask("despawn");

		shipAgent->destroyObjectFromWorld(false);
		shipAgent->notifyDespawn();
	}

	void schedule(uint64 delay = 0) {
		if (shipAgent != nullptr) {
			auto zone = shipAgent->getZone();

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

#endif /* DESPAWNSHIPAGENTTASK_H_ */
