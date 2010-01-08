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

class ObjectDatabaseEnvironment;

class ObjectDatabase : public Logger {
	Db* objectsDatabase;
	DbEnv* environment;

	String databaseFileName;
	uint32 dbFlags;

private:
	void closeDatabase();
	void openDatabase();

	ObjectDatabase() {
	}

public:
	ObjectDatabase(ObjectDatabaseEnvironment* dbEnv, const String& dbFileName);
	~ObjectDatabase();

	int getData(uint64 objKey, ObjectInputStream* objectData);
	int putData(uint64 objKey, ObjectOutputStream* stream, bool syncToDisk = false);
	int deleteData(uint64 objKey);

	int sync();

	inline Db* getDatabaseHandle() {
		return objectsDatabase;
	}

	inline void getDatabaseName(String& name) {
		name = databaseFileName.replaceFirst(".db", "");
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

class ObjectDatabaseTransaction {

};

#endif /* OBJECTDATABASE_H_ */
