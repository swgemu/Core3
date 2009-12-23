/*
 * ObjectDatabaseEnvironment.h
 *
 *  Created on: 11/11/2009
 *      Author: victor
 */

#ifndef OBJECTDATABASEENVIRONMENT_H_
#define OBJECTDATABASEENVIRONMENT_H_

#include "engine/engine.h"
#include "ObjectDatabase.h"

class ObjectDatabaseEnvironment : public Logger, public Singleton<ObjectDatabaseEnvironment>, public Mutex {
	DbEnv* databaseEnvironment;

	VectorMap<uint16, ObjectDatabase*> databases;

	ObjectDatabase* databaseDirectory;

	uint32 dbEnvironmentFlags;

private:
	void openEnvironment();
	void closeEnvironment();

	void loadDatabases();

public:
	ObjectDatabaseEnvironment();
	~ObjectDatabaseEnvironment();

	void closeDatabases();

	static int isAlive(DbEnv* dbenv, pid_t pid, db_threadid_t tid, u_int32_t flags);

	/**
	 * Loads or creates a database in this environment
	 * @param name name of the database
	 * @param create create if no database exists with specified uniqueID/name pair
	 * @param uniqueID if not specified, uniqueID will be set to name.hashCode()
	 */
	ObjectDatabase* loadDatabase(const String& name, bool create, uint16 uniqueID = 0xFFFF);

	inline ObjectDatabase* getDatabase(uint16 id) {
		Locker _locker(this);

		return databases.get(id);
	}

	inline ObjectDatabase* getDatabase(int idx) {
		Locker _locker(this);

		return databases.get(idx);
	}

	inline ObjectDatabase* getDatabase(const String& name) {
		Locker _locker(this);

		return databases.get((uint16)name.hashCode());
	}

	void getDatabaseName(uint16 tableID, String& name);

	inline int getDatabaseCount() {
		return databases.size();
	}

	inline DbEnv* getBerkeleyEnvironment() {
		return databaseEnvironment;
	}

};


#endif /* OBJECTDATABASEENVIRONMENT_H_ */
