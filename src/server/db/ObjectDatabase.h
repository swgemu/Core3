/*
 * ObjectDatabaseNEW.h
 *
 *  Created on: 19/02/2010
 *      Author: victor
 */

#ifndef OBJECTDATABASENEW_H_
#define OBJECTDATABASENEW_H_

#include "engine/engine.h"

using namespace engine::db::berkley;

class ObjectDatabaseEnvironment;

class ObjectDatabase : public Logger {
	BerkeleyDatabase* objectsDatabase;
	Environment* environment;

	String databaseFileName;

private:
	const static int DEADLOCK_MAX_RETRIES = 20;

	void closeDatabase();
	void openDatabase();

	ObjectDatabase() {
	}

public:
	ObjectDatabase(ObjectDatabaseEnvironment* dbEnv, const String& dbFileName);
	~ObjectDatabase();

	int getData(uint64 objKey, ObjectInputStream* objectData);
	int putData(uint64 objKey, ObjectOutputStream* stream);
	int deleteData(uint64 objKey);

	int sync();

	inline BerkeleyDatabase* getDatabaseHandle() {
		return objectsDatabase;
	}

	inline void getDatabaseName(String& name) {
		name = databaseFileName.replaceFirst(".db", "");
	}

};

class ObjectDatabaseIterator : public Logger {
	Cursor* cursor;
	BerkeleyDatabase* databaseHandle;

	DatabaseEntry key, data;

public:
	ObjectDatabaseIterator(ObjectDatabase* database);
	ObjectDatabaseIterator(BerkeleyDatabase* databaseHandle);
	~ObjectDatabaseIterator();

	void resetIterator();

	bool getNextKeyAndValue(uint64& key, ObjectInputStream* data);
	bool getNextValue(ObjectInputStream* data);
	bool getNextKey(uint64& key);

	inline void closeCursor() {
		if (cursor != NULL) {
			cursor->close();

			delete cursor;
		}

		cursor = NULL;
	}

};


#endif /* OBJECTDATABASENEW_H_ */
