/*
 * CommitMasterTransactionTask.h
 *
 *  Created on: Oct 15, 2010
 *      Author: oru
 */

#ifndef COMMITMASTERTRANSACTIONTASK_H_
#define COMMITMASTERTRANSACTIONTASK_H_

#include "engine/engine.h"

class CommitMasterTransactionTask : public Task {
	engine::db::berkley::Transaction* transaction;
	Vector<UpdateModifiedObjectsThread*>* threads;
	int numberOfThreads;
	bool startNew;

public:
	CommitMasterTransactionTask(engine::db::berkley::Transaction* trans, Vector<UpdateModifiedObjectsThread*>* workers, int number, bool startNewUpdate) {
		transaction = trans;
		threads = workers;
		numberOfThreads = number;
		startNew = startNewUpdate;
	}

	void run() {
		for (int i = 0; i < numberOfThreads; ++i) {
			UpdateModifiedObjectsThread* worker = threads->get(i);

			if (!worker->hasFinishedCommiting()) {
				worker->signalMasterTransactionFinish();
				schedule(500);
				return;
			}
		}

		ObjectDatabaseManager::instance()->commitTransaction(transaction);
		ObjectManager::instance()->info("master transaction commited", true);
		ObjectManager::instance()->finishObjectUpdate(startNew);
	}
};

#endif /* COMMITMASTERTRANSACTIONTASK_H_ */
