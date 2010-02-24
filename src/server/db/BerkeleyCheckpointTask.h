/*
 * BerkeleyCheckpointTask.h
 *
 *  Created on: 21/02/2010
 *      Author: victor
 */

#ifndef BERKELEYCHECKPOINTTASK_H_
#define BERKELEYCHECKPOINTTASK_H_

#include "engine/engine.h"
#include "ObjectDatabaseEnvironment.h"

class BerkeleyCheckpointTask : public Task {
	ObjectDatabaseEnvironment* environment;

public:
	BerkeleyCheckpointTask(ObjectDatabaseEnvironment* env) {
		environment = env;
	}

	void run() {
		environment->checkpoint();
	}
};


#endif /* BERKELEYCHECKPOINTTASK_H_ */
