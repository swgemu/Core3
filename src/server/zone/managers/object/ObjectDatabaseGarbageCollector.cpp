/*
 * ObjectDatabaseGarbageCollector.cpp
 *
 *  Created on: 13/11/2010
 *      Author: victor
 */

#include "ObjectDatabaseGarbageCollector.h"

void ObjectDatabaseGarbageCollector::run() {
	/*for (int i = 0; i < databaseManager->getTotalDatabaseCount(); ++i) {
		LocalDatabase* database = databaseManager->getDatabase(i);

		if (!database->isObjectDatabase())
			continue;

		ObjectDatabase* db = (ObjectDatabase*) database;

		String dbName;
		db->getDatabaseName(dbName);

		ObjectDatabaseIterator iterator(db);

		while (iterator.getNextKey(objectID)) {
			objectID = objectID & nullify;

			if (objectID > maxObjectID)
				maxObjectID = objectID;
		}
	}
*/
}
