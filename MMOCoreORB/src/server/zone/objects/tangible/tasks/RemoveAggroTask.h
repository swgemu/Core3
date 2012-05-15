/*
 * RemoveAggroTask.h
 *
 *  Created on: 1/22/2012
 *      Author: Kyle
 */

#ifndef REMOVEAGGROTASK_H_
#define REMOVEAGGROTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class RemoveAggroTask : public Task {
	ManagedReference<TangibleObject*> self;
	ManagedReference<CreatureObject*> target;
	int value;
public:
	RemoveAggroTask(TangibleObject* me, CreatureObject* cr, int va) {
		self = me;
		target = cr;
		value = va;
	}

	void run() {
		Locker locker(self);
		ThreatMap* threatMap = self->getThreatMap();
		threatMap->removeAggro(target, value);
	}
};

#endif /* REMOVEAGGROTASK_H_ */
