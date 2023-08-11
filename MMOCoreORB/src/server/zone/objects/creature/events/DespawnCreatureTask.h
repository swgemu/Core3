/*
 * DespawnCreatureTask.h
 *
 *  Created on: 12/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATURETASK_H_
#define DESPAWNCREATURETASK_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/Zone.h"

class DespawnCreatureTask : public Task {
	ManagedReference<AiAgent*> agent;

public:
	DespawnCreatureTask(AiAgent* creature) {
		agent = creature;

		auto zone = creature->getZone();

		if (zone != nullptr) {
			setCustomTaskQueue(zone->getZoneName());
		}
	}

	void run() {
		Locker locker(agent);

		Zone* zone = agent->getZone();

		agent->removePendingTask("despawn");

		if (zone == nullptr) {
			agent->destroyAllWeapons();

			return;
		}

		agent->destroyObjectFromWorld(false);
		agent->notifyDespawn(zone);
	}
};

#endif /* DESPAWNCREATURETASK_H_ */
