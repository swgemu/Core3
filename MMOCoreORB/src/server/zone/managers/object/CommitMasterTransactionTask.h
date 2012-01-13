/*
 * CommitMasterTransactionTask.h
 *
 *  Created on: Oct 15, 2010
 *      Author: oru
 */

#ifndef COMMITMASTERTRANSACTIONTASK_H_
#define COMMITMASTERTRANSACTIONTASK_H_

#include "engine/engine.h"
#include "server/db/ServerDatabase.h"
#include "server/ServerCore.h"

class CommitMasterTransactionTask : public Task {
	engine::db::berkley::Transaction* transaction;
	Vector<UpdateModifiedObjectsThread*>* threads;
	int numberOfThreads;
	bool startNew;
	int galaxyId;
	Reference<ResultSet*> charactersSaved;

public:
	CommitMasterTransactionTask(engine::db::berkley::Transaction* trans, Vector<UpdateModifiedObjectsThread*>* workers, int number, bool startNewUpdate, int galaxy, ResultSet* set) {
		transaction = trans;
		threads = workers;
		numberOfThreads = number;
		startNew = startNewUpdate;
		galaxyId = galaxy;
		charactersSaved = set;
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
							<< charactersSaved->getInt(2) << ", " << "\'" << charactersSaved->getString(3) << "\', "
							<< "\'" << charactersSaved->getString(4) << "\', " << charactersSaved->getInt(5) << ", "
							<< charactersSaved->getInt(6) << ", \'" << charactersSaved->getString(7) << "')";

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
};

#endif /* COMMITMASTERTRANSACTIONTASK_H_ */
