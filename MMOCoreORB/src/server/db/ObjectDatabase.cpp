/*
 * ObjectDatabase.cpp
 *
 *  Created on: Sep 27, 2009
 *      Author: theanswer
 */

#include "ObjectDatabase.h"

ObjectDatabase::ObjectDatabase() : Logger("ObjectDatabase") {
	databaseEnvironment = new DbEnv(0);
	objectsDatabase = new Db(databaseEnvironment, 0);

	dbFlags = DB_CREATE | DB_THREAD;
	dbEnvironmentFlags = DB_CREATE | DB_THREAD | DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_TXN | DB_INIT_MPOOL;

	openEnvironment();
	openDatabase();

	//setFileLogger("log/berkeley.log");

}

ObjectDatabase::~ObjectDatabase() {
	closeDatabase();
	closeEnvironment();

	delete objectsDatabase;
	objectsDatabase = NULL;

	delete databaseEnvironment;
	objectsDatabase = NULL;
}

int ObjectDatabase::isAlive(DbEnv* dbenv, pid_t pid, db_threadid_t tid, u_int32_t flags) {

	return 1; // still running
}

void ObjectDatabase::openEnvironment() {
	try {

		int ret = databaseEnvironment->open("databases", dbEnvironmentFlags, 0);

		//databaseEnvironment->set_isalive(isAlive);

		if (ret != 0)
			error("Trying to open environment error: " + String::valueOf(ret));

		/*if (databaseEnvironment->failchk(0) != 0) we need to implement isAlive
			error("Database environment crashed and cant continue, please run db_recovery");*/

	} catch(DbException &e) {
		error("Error opening environment... please run db_recovery");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

void ObjectDatabase::closeEnvironment() {
	try {

		databaseEnvironment->close(0);

	} catch (DbException &e) {
		error("Error closing environment: ");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to close environment");
	}
}


void ObjectDatabase::openDatabase() {
	try {
		//berkeley->set_error_stream(&System::out);

		int ret = objectsDatabase->open(NULL, "objects.db", NULL, DB_HASH, dbFlags, 0);

		if (ret != 0) {
			error("Trying to open database error:" + String::valueOf(ret));
		} else
			info("opened objects database", true);

	} catch(DbException &e) {
		error("Error opening database: " );
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

void ObjectDatabase::closeDatabase() {
	try {

		objectsDatabase->close(0);

	} catch (DbException &e) {
		error("Error closing database: ");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

int ObjectDatabase::getData(uint64 objKey, String& objectData) {
	int ret = 0;

	try {
		Dbt key, data;

		key.set_data(&objKey);
		key.set_size(sizeof(uint64));

		data.set_flags(DB_DBT_MALLOC);

		ret = objectsDatabase->get(NULL, &key, &data, 0);

		if (ret != 0) {
			if (ret != DB_NOTFOUND)
				error("Trying to get database error:" + String::valueOf(ret));

			return ret;
		}

		objectData = (char*) data.get_data();

		free(data.get_data());

		info("retreived data of size" + String::valueOf(objectData.length()), true);
	} catch(DbException &e) {
		error("Error in getData");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to get data from berkeley DB ");
	}

	return ret;
}

int ObjectDatabase::putData(uint64 objKey, const String& objectData) {
	int ret = -1;

	try {
		Dbt key(&objKey, sizeof(uint64));
		Dbt data((void*)objectData.toCharArray(), objectData.length() + 1);

		ret = objectsDatabase->put(NULL, &key, &data, 0);

		if (ret != 0)
			error("Trying to open database error:" + String::valueOf(ret));

	} catch(DbException &e) {
		error("Error in putData");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to put data into berkeley DB ");
	}

	return ret;
}

int ObjectDatabase::sync() {
	int ret = -1;

	try {

		ret = objectsDatabase->sync(0);

	} catch(DbException &e) {
		error("Error in putData");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to put data into berkeley DB ");
	}

	return ret;
}

ObjectDatabaseIterator::ObjectDatabaseIterator(ObjectDatabase* database) : Logger("ObjectDatabaseIterator") {
	databaseHandle = database->getDatabaseHandle();
	databaseHandle->cursor(NULL, &cursor, 0);

	data.set_flags(DB_DBT_REALLOC);
	key.set_flags(DB_DBT_REALLOC);
}

ObjectDatabaseIterator::ObjectDatabaseIterator(Db* dbHandle) : Logger("ObjectDatabaseIterator") {
	databaseHandle = dbHandle;
	databaseHandle->cursor(NULL, &cursor, 0);

	data.set_flags(DB_DBT_REALLOC);
	key.set_flags(DB_DBT_REALLOC);
}

ObjectDatabaseIterator::~ObjectDatabaseIterator() {
	closeCursor();

	free(data.get_data());
	free(key.get_data());
}

void ObjectDatabaseIterator::resetIterator() {
	if (cursor != NULL)
		cursor->close();

	databaseHandle->cursor(NULL, &cursor, 0);
}

bool ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data) {
	try {
		if (cursor->get(&this->key, &this->data, DB_NEXT) != 0)
			return false;

		key = *(uint64*) (this->key.get_data());
		data = (char*) ObjectDatabaseIterator::data.get_data();

	}  catch(DbException &e) {
		error("Error in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
		error(e.what());
	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextValue(String& data) {
	try {
		if (cursor->get(&this->key, &this->data, DB_NEXT) != 0)
			return false;

		data = (char*) this->data.get_data();

	}  catch(DbException &e) {
		error("Error in ObjectDatabaseIterator::getNextValue(String& data)");
		error(e.what());
	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextValue(String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextKey(uint64& key) {
	try {
		if (cursor->get(&this->key, &this->data, DB_NEXT) != 0)
			return false;

		key =  *(uint64*)(this->key.get_data());

	}  catch(DbException &e) {
		error("Error in ObjectDatabaseIterator::getNextKey");
		error(e.what());
	} catch (...) {
		error("unreported exception caught  in ObjectDatabaseIterator::getNextKey(uint64& key) ");
	}

	return true;
}
