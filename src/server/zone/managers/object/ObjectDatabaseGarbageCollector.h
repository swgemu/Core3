/*
 * ObjectDatabaseGarbageCollector.h
 *
 *  Created on: 13/11/2010
 *      Author: victor
 */

#ifndef OBJECTDATABASEGARBAGECOLLECTOR_H_
#define OBJECTDATABASEGARBAGECOLLECTOR_H_

#include "engine/engine.h"

class ObjectDatabaseGarbageCollector : public Task {
public:
	void run();
};


#endif /* OBJECTDATABASEGARBAGECOLLECTOR_H_ */
