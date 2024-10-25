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
	DespawnShipAgentTask(ShipAiAgent* agent) {
		shipAgent = agent;

		auto zone = agent->getZone();

		if (zone != nullptr) {
			setCustomTaskQueue(zone->getZoneName());
		}
	}

	void run() {
		Locker locker(shipAgent);

		shipAgent->removePendingTask("despawn");

		shipAgent->destroyObjectFromWorld(false);
		shipAgent->notifyDespawn();
	}
};

#endif /* DESPAWNSHIPAGENTTASK_H_ */
