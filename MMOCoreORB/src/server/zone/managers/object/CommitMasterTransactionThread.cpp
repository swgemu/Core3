/*
 * CommitMasterTransactionThread.cpp
 *
 *  Created on: 18/02/2012
 *      Author: victor
 */

#include "UpdateModifiedObjectsThread.h"
#include "CommitMasterTransactionThread.h"

#include "ObjectManager.h"

CommitMasterTransactionThread::CommitMasterTransactionThread() {
	transaction = NULL;
	threads = NULL;

	doRun = true;
}

void CommitMasterTransactionThread::startWatch(engine::db::berkley::Transaction* trans, Vector<UpdateModifiedObjectsThread*>* workers, int number, bool startNewUpdate, int galaxy, ResultSet* set) {
	transaction = trans;
	threads = workers;
	numberOfThreads = number;
	startNew = startNewUpdate;
	galaxyId = galaxy;
	charactersSaved = set;

	blockMutex.lock();

	waitCondition.broadcast(&blockMutex);

	blockMutex.unlock();
}

void CommitMasterTransactionThread::run() {
	while (doRun) {
		blockMutex.lock();

		waitCondition.wait(&blockMutex);

		commitData();

		transaction = NULL;
		threads = NULL;

		charactersSaved = NULL;

		blockMutex.unlock();
	}
}

void CommitMasterTransactionThread::commitData() {
	for (int i = 0; i < numberOfThreads; ++i) {
		UpdateModifiedObjectsThread* worker = threads->get(i);

		while (!worker->hasFinishedCommiting()) {
			worker->signalMasterTransactionFinish();
			Thread::sleep(500);
		}
	}

	ObjectDatabaseManager::instance()->commitTransaction(transaction);
	ObjectDatabaseManager::instance()->checkpoint();

	if (charactersSaved != NULL) {
		try {
			StringBuffer query;
			query << "INSERT INTO characters (character_oid, account_id, galaxy_id, firstname, surname, race, gender, template) VALUES";

			StringBuffer deleteQuery;
			deleteQuery << "DELETE FROM characters_dirty WHERE ";

			bool first = true;

			int count = 0;

			while (charactersSaved->next()) {
				if (!first) {
					query << ",";
					deleteQuery << " OR ";
				}

				query << "(" << charactersSaved->getUnsignedLong(0) << ", " << charactersSaved->getInt(1) << ", "
						<< charactersSaved->getInt(2) << ", " << "\'" << String(charactersSaved->getString(3)).escapeString() << "\', "
						<< "\'" << String(charactersSaved->getString(4)).escapeString() << "\', " << charactersSaved->getInt(5) << ", "
						<< charactersSaved->getInt(6) << ", \'" << String(charactersSaved->getString(7)).escapeString() << "')";

				deleteQuery << "character_oid = " << charactersSaved->getUnsignedLong(0) << " AND galaxy_id = " << galaxyId;

				first = false;
				++count;
			}

			if (count > 0) {
				ServerDatabase::instance()->executeStatement(query.toString());
				ServerDatabase::instance()->executeStatement(deleteQuery.toString());
			}
		} catch (Exception& e) {
			System::out << e.getMessage();
		}
	}

	ObjectManager::instance()->info("master transaction commited", true);
	ObjectManager::instance()->finishObjectUpdate(startNew);
}
