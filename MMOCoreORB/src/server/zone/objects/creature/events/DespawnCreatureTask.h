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
			// This early return used to destroy the weapons and skip notifyDespawn
			// entirely -- no observer drops, no herd unhook, no defender cleanup --
			// leaving every registration standing on an agent that had already left
			// the world. notifyDespawn tolerates a null zone (its self-respawn
			// schedule is guarded on a valid zone) and destroys the weapons itself
			// on both of its exits, including the npcTemplate == nullptr one.
			// A still-alive home lair gets CREATUREDESPAWNED first and may
			// legitimately respawn the agent (the lair owns its population
			// bookkeeping).
			agent->notifyDespawn(nullptr);

			return;
		}

		agent->destroyObjectFromWorld(false);
		agent->notifyDespawn(zone);
	}
};

#endif /* DESPAWNCREATURETASK_H_ */
