/*
 * ClearThreatStateTask.h
 *
 *  Created on: 1/22/2012
 *      Author: Kyle
 */

#ifndef CLEARTHREATSTATETASK_H_
#define CLEARTHREATSTATETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class ClearThreatStateTask : public Task {
	ManagedReference<TangibleObject*> self;
	ManagedReference<CreatureObject*> target;
	uint64 state;
public:
	ClearThreatStateTask(TangibleObject* me, CreatureObject* tar, uint64 st) {
		self = me;
		target = tar;
		state = st;
	}

	void run() {
		Locker locker(self);
		ThreatMap* threatMap = self->getThreatMap();
		threatMap->clearThreatState(target, state);
	}
};

#endif /* CLEARTHREATSTATETASK_H_ */
