/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SampleResultsTask.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef SAMPLERESULTSTASK_H_
#define SAMPLERESULTSTASK_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerObject.h"

class ResourceSpawner;

class SampleResultsTask : public Task {

protected:
	ManagedReference<CreatureObject*> playerCreature;
	Reference<ResourceSpawner*> resourceSpawner;
	float density;
	String resname;

public:
	SampleResultsTask(ManagedReference<CreatureObject*> play, ResourceSpawner* spawner, float d, String rname) {
		playerCreature = play;
		resourceSpawner = spawner;
		density = d;
		resname = rname;
	}

	void run() {
		Locker locker(playerCreature);

		resourceSpawner->sendSampleResults(playerCreature, density, resname);
		playerCreature->removePendingTask("sampleresults");
	}


};

#endif /* SAMPLERESULTSTASK_H_ */
