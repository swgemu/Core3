/*
 * PendingTasksMap.h
 *
 *  Created on: 04/05/2010
 *      Author: victor
 */

#ifndef PENDINGTASKSMAP_H_
#define PENDINGTASKSMAP_H_

#include "engine/engine.h"

#include "system/util/SynchronizedVectorMap.h"

class PendingTasksMap : public SynchronizedVectorMap<String, Reference<Task*> > {
public:
	PendingTasksMap() : SynchronizedVectorMap<String, Reference<Task*> >(1, 1) {

	}

	PendingTasksMap(const PendingTasksMap& p) : SynchronizedVectorMap<String, Reference<Task*> >(p) {

	}
};


#endif /* PENDINGTASKSMAP_H_ */
