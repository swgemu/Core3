/*
 * ObjectDatabase.h
 *
 *  Created on: Sep 26, 2009
 *      Author: theanswer
 */

#ifndef OBJECTDATABASE_H_
#define OBJECTDATABASE_H_

#include "engine/engine.h"

#include "db_cxx.h"

class ObjectDatabase : public Logger {
	DbEnv* databaseEnvironment;
	Db* objectsDatabase;

	uint32 dbEnvironmentFlags;
	uint32 dbFlags;

private:
	void closeDatabase();
	void openDatabase();

	void openEnvironment();
	void closeEnvironment();

public:
	ObjectDatabase();
	~ObjectDatabase();

	static int isAlive(DbEnv* dbenv, pid_t pid, db_threadid_t tid, u_int32_t flags);

	int getData(uint64 objKey, ObjectInputStream* objectData);
	int putData(uint64 objKey, ObjectOutputStream* stream, bool syncToDisk = false);

	int sync();

	inline Db* getDatabaseHandle() {
		return objectsDatabase;
	}

};

class ObjectDatabaseIterator : public Logger {
	Dbc* cursor;
	Db* databaseHandle;

	Dbt key, data;

public:
	ObjectDatabaseIterator(ObjectDatabase* database);
	ObjectDatabaseIterator(Db* databaseHandle);
	~ObjectDatabaseIterator();

	void resetIterator();

	bool getNextKeyAndValue(uint64& key, ObjectInputStream* data);
	bool getNextValue(ObjectInputStream* data);
	bool getNextKey(uint64& key);

	inline void closeCursor() {
		if (cursor != NULL)
			cursor->close();

		cursor = NULL;
	}

};

#endif /* OBJECTDATABASE_H_ */
