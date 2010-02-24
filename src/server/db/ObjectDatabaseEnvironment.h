/*
 * ObjectDatabaseEnvironmentNEW.h
 *
 *  Created on: 20/02/2010
 *      Author: victor
 */

#ifndef OBJECTDATABASEENVIRONMENTNEW_H_
#define OBJECTDATABASEENVIRONMENTNEW_H_


#include "engine/engine.h"
#include "ObjectDatabase.h"

class BerkeleyCheckpointTask;

class ObjectDatabaseEnvironment : public Logger, public Singleton<ObjectDatabaseEnvironment>, public Mutex {
	Environment* databaseEnvironment;

	VectorMap<uint16, ObjectDatabase*> databases;
	VectorMap<String, uint16> nameDirectory;

	ObjectDatabase* databaseDirectory;

	uint32 dbEnvironmentFlags;

	uint16 lastTableID;

	Reference<BerkeleyCheckpointTask*> checkpointTask;
	uint32 checkpointTime;

public:
	const static int CHECKPOINTTIME = 1800000; //msec

private:
	void openEnvironment();
	void closeEnvironment();

	void loadDatabases();

public:
	ObjectDatabaseEnvironment();
	~ObjectDatabaseEnvironment();

	void closeDatabases();

	/**
	 * Loads or creates a database in this environment
	 * @param name name of the database
	 * @param create create if no database exists with specified uniqueID/name pair
	 * @param uniqueID if not specified, uniqueID will be set to name.hashCode()
	 */
	ObjectDatabase* loadDatabase(const String& name, bool create, uint16 uniqueID = 0xFFFF);

	void checkpoint();

	void getDatabaseName(uint16 tableID, String& name);

	inline ObjectDatabase* getDatabase(uint16 id) {
		//Locker _locker(this);

		return databases.get(id);
	}

	inline ObjectDatabase* getDatabase(int idx) {
		//Locker _locker(this);

		return databases.get(idx);
	}

	inline uint16 getDatabaseID(const String& name) {
		//Locker _locker(this);

		return nameDirectory.get(name);
	}

	inline int getDatabaseCount() {
		return databases.size();
	}

	inline Environment* getBerkeleyEnvironment() {
		return databaseEnvironment;
	}

};

#endif /* OBJECTDATABASEENVIRONMENTNEW_H_ */
