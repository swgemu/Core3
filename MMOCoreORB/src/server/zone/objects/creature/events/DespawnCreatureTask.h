/*
 * DespawnCreatureTask.h
 *
 *  Created on: 12/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATURETASK_H_
#define DESPAWNCREATURETASK_H_

#include "../AiAgent.h"
#include "../ai/AiActor.h"

class DespawnCreatureTask : public Task {
	ManagedReference<AiAgent*> creature;
	ManagedReference<AiActor*> actor;

public:
	DespawnCreatureTask(AiAgent* cr) {
		creature = cr;
	}

	DespawnCreatureTask(AiActor* a) {
		actor = a;
	}

	void run() {
		if (actor == NULL)
			return;

		Locker _locker(actor);

		Zone* zone = actor->getZone();

		actor->removePendingTask("despawn");

		if (zone == NULL)
			return;

		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return;

		Locker clocker(actor, host);

		host->destroyObjectFromWorld(false);
		actor->destroyObjectFromWorld(false);

		actor->notifyDespawn(zone);
	}
};


#endif /* DESPAWNCREATURETASK_H_ */
