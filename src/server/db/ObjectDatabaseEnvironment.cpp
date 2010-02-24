/*
 * ObjectDatabaseEnvironmentNEW.cpp
 *
 *  Created on: 20/02/2010
 *      Author: victor
 */


#include "ObjectDatabaseEnvironment.h"
#include "BerkeleyCheckpointTask.h"

ObjectDatabaseEnvironment::ObjectDatabaseEnvironment() : Logger("ObjectDatabaseEnvironment") {

	setGlobalLogging(true);
	setLogging(false);

	databases.setNullValue(NULL);
	databases.setNoDuplicateInsertPlan();

	nameDirectory.setNullValue(-1);
	nameDirectory.setNoDuplicateInsertPlan();

	databaseDirectory = NULL;

	checkpointTask = new BerkeleyCheckpointTask(this);

	lastTableID = 0;

	openEnvironment();
	loadDatabases();
	checkpoint();
}

ObjectDatabaseEnvironment::~ObjectDatabaseEnvironment() {
	closeDatabases();

	delete databaseDirectory;
	databaseDirectory = NULL;

	closeEnvironment();

	delete databaseEnvironment;
	databaseEnvironment = NULL;

	checkpointTask->cancel();

	info("closed", true);
}

void ObjectDatabaseEnvironment::checkpoint() {
	databaseEnvironment->checkpoint();

	checkpointTask->schedule(CHECKPOINTTIME);
}

void ObjectDatabaseEnvironment::openEnvironment() {
	EnvironmentConfig config;
	config.setAllowCreate(true);
	config.setInitializeLocking(true);
	config.setInitializeLogging(true);
	config.setLogAutoRemove(true);
	config.setThreaded(true);
	config.setThreadCount(50);
	config.setTransactional(true);
	config.setInitializeCache(true);
	config.setMaxLogFileSize(100000); // 100mb

	try {
		databaseEnvironment = new Environment("databases", config);

		if (databaseEnvironment->failCheck() != 0) {
			error("Database environment crashed and cant continue, please run db_recover in the databases folder");
			exit(1);
		}

	} catch (Exception& e) {
		error("Error opening environment...");
		error(e.getMessage());
		exit(1);
	} catch (...) {
		error("unreported exception caught while trying to open berkeley environment ");
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
		nameDirectory.put(dbName, tableID);

		if (tableID > lastTableID)
			lastTableID = tableID;

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
		uniqueID = getDatabaseID(name);

	ObjectDatabase* db = databases.get(uniqueID);

	if (db != NULL)
		return db;

	if (db == NULL && !create)
		return NULL;

	if (uniqueID == 0xFFFF)
		uniqueID = ++lastTableID;

	db = new ObjectDatabase(this, String(name + ".db"));

	StringBuffer msg;
	msg << "trying to create database " << name << " with id 0x" << hex << uniqueID;
	info(msg.toString(), true);

	ObjectOutputStream nameData(20);

	String nm = name;
	nm.toBinaryStream(&nameData);

	databaseDirectory->putData((uint64)uniqueID, &nameData);

	databases.put(uniqueID, db);
	nameDirectory.put(name, uniqueID);

	return db;
}

void ObjectDatabaseEnvironment::closeEnvironment() {
	try {

		int ret = databaseEnvironment->close();

		if (ret != 0) {
			error("Error closing environment: ");
		}

	} catch (Exception &e) {
		error("Error closing environment: ");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught while trying to close environment");
	}
}

void ObjectDatabaseEnvironment::getDatabaseName(uint16 tableID, String& name) {
	ObjectDatabase* db = getDatabase(tableID);

	db->getDatabaseName(name);
}
