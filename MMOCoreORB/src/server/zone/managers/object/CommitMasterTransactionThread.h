/*
 * CommitMasterTransactionThread.h
 *
 *  Created on: 18/02/2012
 *      Author: victor
 */

#ifndef COMMITMASTERTRANSACTIONTHREAD_H_
#define COMMITMASTERTRANSACTIONTHREAD_H_

#include "engine/engine.h"

#include "server/db/ServerDatabase.h"
#include "server/ServerCore.h"

class UpdateModifiedObjectsThread;

class CommitMasterTransactionThread : public Thread, public Singleton<CommitMasterTransactionThread> {
	Mutex blockMutex;
	Condition waitCondition;

	engine::db::berkley::Transaction* transaction;
	Vector<UpdateModifiedObjectsThread*>* threads;
	int numberOfThreads;
	bool startNew;
	int galaxyId;
	Reference<ResultSet*> charactersSaved;

	bool doRun;

public:
	CommitMasterTransactionThread();

	void run();

	void startWatch(engine::db::berkley::Transaction* trans, Vector<UpdateModifiedObjectsThread*>* workers, int number, bool startNewUpdate, int galaxy, ResultSet* set);

	void commitData();
};

#endif /* COMMITMASTERTRANSACTIONTHREAD_H_ */
