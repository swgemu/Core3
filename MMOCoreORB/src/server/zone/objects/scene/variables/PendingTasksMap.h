/*
 * PendingTasksMap.h
 *
 *  Created on: 04/05/2010
 *      Author: victor
 */

#ifndef PENDINGTASKSMAP_H_
#define PENDINGTASKSMAP_H_

#include "engine/engine.h"

class PendingTasksMap : public VectorMap<String, Reference<Task*> > {
public:
	PendingTasksMap() : VectorMap<String, Reference<Task*> >(1, 1) {

	}

	PendingTasksMap(const PendingTasksMap& p) : VectorMap<String, Reference<Task*> >(p) {

	}
};


#endif /* PENDINGTASKSMAP_H_ */
