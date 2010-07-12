/*
 * DespawnCreatureTask.h
 *
 *  Created on: 12/07/2010
 *      Author: victor
 */

#ifndef DESPAWNCREATURETASK_H_
#define DESPAWNCREATURETASK_H_

#include "../NonPlayerCreatureObject.h"

class DespawnCreatureTask : public Task {
	ManagedReference<NonPlayerCreatureObject*> creature;

public:
	DespawnCreatureTask(NonPlayerCreatureObject* cr) {
		creature = cr;
	}

	void run() {
		Locker locker(creature);

		creature->removeFromZone();

		//creature->printReferenceHolders();

		/*PatrolPoint* homeLocation = creature->getHomeLocation();

		if (homeLocation->getPosit)*/
	}
};


#endif /* DESPAWNCREATURETASK_H_ */
