/*
 * RespawnCreatureTask.h
 *
 *  Created on: 03/08/2010
 *      Author: victor
 */

#ifndef RESPAWNCREATURETASK_H_
#define RESPAWNCREATURETASK_H_

#include "../AiAgent.h"

class RespawnCreatureTask : public Task {
	ManagedReference<AiAgent*> creature;
	Zone* zone;
	int level;

public:
	RespawnCreatureTask(AiAgent* cr, Zone* zn, int level) {
		creature = cr;
		zone = zn;
		this->level = level;
	}

	void run() {
		Locker locker(creature);

		creature->respawn(zone, level);

		//creature->printReferenceHolders();

		/*PatrolPoint* homeLocation = creature->getHomeLocation();

		if (homeLocation->getPosit)*/
	}
};


#endif /* RESPAWNCREATURETASK_H_ */
