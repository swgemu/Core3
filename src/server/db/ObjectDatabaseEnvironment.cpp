/*
 * ObjectDatabaseEnvironment.cpp
 *
 *  Created on: 11/11/2009
 *      Author: victor
 */

#include "ObjectDatabaseEnvironment.h"

ObjectDatabaseEnvironment::ObjectDatabaseEnvironment() : Logger("ObjectDatabaseEnvironment") {
	databaseEnvironment = new DbEnv(0);

	dbEnvironmentFlags = DB_CREATE | DB_THREAD | DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_TXN | DB_INIT_MPOOL;

	setGlobalLogging(true);
	setLogging(false);

	databases.setNullValue(NULL);
	databases.setNoDuplicateInsertPlan();

	databaseDirectory = NULL;

	openEnvironment();

	loadDatabases();
}


ObjectDatabaseEnvironment::~ObjectDatabaseEnvironment() {
	closeDatabases();

	delete databaseDirectory;
	databaseDirectory = NULL;

	closeEnvironment();

	delete databaseEnvironment;
	databaseEnvironment = NULL;

	info("closed", true);
}

void ObjectDatabaseEnvironment::openEnvironment() {
	try {

		databaseEnvironment->set_thread_count(50);

		int ret = databaseEnvironment->open("databases", dbEnvironmentFlags, 0);

		databaseEnvironment->set_isalive(isAlive);

		databaseEnvironment->log_set_config(DB_LOG_AUTO_REMOVE, 1); // delete unnecesary log files

		if (ret != 0)
			error("Trying to open environment error: " + String::valueOf(ret));

		if (databaseEnvironment->failchk(0) != 0) {
			error("Database environment crashed and cant continue, please run db_recover in the databases folder");
			exit(1);
		}

	} catch(DbException &e) {
		error("Error opening environment... please run db_recover in the database folder");
		error(e.what());
		exit(1);
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

void ObjectDatabaseEnvironment::loadDatabases() {
	databaseDirectory = new ObjectDatabase(this, "databases.db");

	ObjectDatabaseIterator iterator(databaseDirectory);

	uint64 tableID;
	ObjectInputStream tableName(20);

	while (iterator.getNextKeyAndValue(tableID, &tableName)) {
		String dbName;
		dbName.parseFromBinaryStream(&tableName);

		ObjectDatabase* db = new ObjectDatabase(this, String(dbName + ".db"));

		StringBuffer msg;
		msg << "loading database:" << dbName << " with id 0x" << hex << (uint16)tableID;
		info(msg.toString(), true);

		databases.put((uint16)tableID, db);

		tableName.reset();
	}
}

void ObjectDatabaseEnvironment::closeDatabases() {
	while (databases.size() > 0) {
		ObjectDatabase* db = databases.remove(0).getValue();

		delete db;
	}

	delete databaseDirectory;
	databaseDirectory = NULL;
}

ObjectDatabase* ObjectDatabaseEnvironment::loadDatabase(const String& name, bool create, uint16 uniqueID) {
	Locker _locker(this);

	if (uniqueID == 0xFFFF)
		uniqueID = (uint16)name.hashCode();

	ObjectDatabase* db = databases.get(uniqueID);

	if (db != NULL)
		return db;

	if (db == NULL && !create)
		return NULL;

	db = new ObjectDatabase(this, String(name + ".db"));

	StringBuffer msg;
	msg << "trying to create database " << name << " with id 0x" << hex << uniqueID;
	info(msg.toString(), true);

	ObjectOutputStream nameData(20);

	String nm = name;
	nm.toBinaryStream(&nameData);

	databaseDirectory->putData((uint64)uniqueID, &nameData, true);

	databases.put(uniqueID, db);

	return db;
}

void ObjectDatabaseEnvironment::closeEnvironment() {
	try {

		databaseEnvironment->close(0);

	} catch (DbException &e) {
		error("Error closing environment: ");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to close environment");
	}
}


int ObjectDatabaseEnvironment::isAlive(DbEnv* dbenv, pid_t pid, db_threadid_t tid, u_int32_t flags) {
	if (pid != Thread::getProcessID())
		return 0;

	return 1; // still running
}

void ObjectDatabaseEnvironment::getDatabaseName(uint16 tableID, String& name) {
	ObjectDatabase* db = getDatabase(tableID);

	db->getDatabaseName(name);
}
