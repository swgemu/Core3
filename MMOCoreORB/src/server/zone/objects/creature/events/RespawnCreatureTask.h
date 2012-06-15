/*
 * RespawnCreatureTask.h
 *
 *  Created on: 03/08/2010
 *      Author: victor
 */

#ifndef RESPAWNCREATURETASK_H_
#define RESPAWNCREATURETASK_H_

#include "../AiAgent.h"
#include "../ai/AiActor.h"

class RespawnCreatureTask : public Task {
	ManagedReference<AiAgent*> creature;
	ManagedReference<AiActor*> actor;
	Zone* zone;
	int level;

public:
	RespawnCreatureTask(AiAgent* cr, Zone* zn, int level) {
		creature = cr;
		zone = zn;
		this->level = level;
	}

	RespawnCreatureTask(AiActor* a, Zone* zn, int level) {
		actor = a;
		zone = zn;
		this->level = level;
	}

	void run() {
		System::out << "running respawn... \n";
		if (actor == NULL || zone == NULL)
			return;

		Locker locker(actor);

		System::out << "in respawn task \n";

		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return;

		System::out << "non-null host\n";

		Locker clocker(actor, host);

		actor->respawn(zone, level);
	}
};


#endif /* RESPAWNCREATURETASK_H_ */
