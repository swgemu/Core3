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

#include "server/zone/objects/transaction/TransactionLog.h"

class ResourceSpawner;

class SampleResultsTask : public Task {

protected:
	ManagedReference<CreatureObject*> playerCreature;
	Reference<const ResourceSpawner*> resourceSpawner;
	float density;
	String resname;

public:
	SampleResultsTask(ManagedReference<CreatureObject*> play, const ResourceSpawner* spawner, float d, String rname) {
		playerCreature = play;
		resourceSpawner = spawner;
		density = d;
		resname = rname;
	}

	void run() {
		Locker locker(playerCreature);

		TransactionLog trx(TrxCode::HARVESTED, playerCreature);
		resourceSpawner->sendSampleResults(trx, playerCreature, density, resname);
		playerCreature->removePendingTask("sampleresults");
		trx.commit();
	}

};

#endif /* SAMPLERESULTSTASK_H_ */
