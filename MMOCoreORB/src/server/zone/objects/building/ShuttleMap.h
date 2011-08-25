/*
 * ShuttleMap.h
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#ifndef SHUTTLEMAP_H_
#define SHUTTLEMAP_H_

#include "server/zone/objects/building/tasks/ShuttleDepartureTask.h"
#include "engine/engine.h"

class ShuttleMap : public VectorMap<uint64, Reference<ShuttleDepartureTask*> > {
public:
	ShuttleMap() : VectorMap<uint64, Reference<ShuttleDepartureTask*> >() {
		setNoDuplicateInsertPlan();
		setNullValue(NULL);
	}
};

#endif /* SHUTTLEMAP_H_ */
