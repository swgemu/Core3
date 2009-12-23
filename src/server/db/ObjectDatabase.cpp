/*
 * ObjectDatabase.cpp
 *
 *  Created on: Sep 27, 2009
 *      Author: theanswer
 */

#include "ObjectDatabase.h"
#include "ObjectDatabaseEnvironment.h"

ObjectDatabase::ObjectDatabase(ObjectDatabaseEnvironment* dbEnv, const String& dbFileName) {
	DbEnv* env = NULL;

	if (dbEnv != NULL)
		env = dbEnv->getBerkeleyEnvironment();

	objectsDatabase = new Db(env, 0);

	dbFlags = DB_CREATE | DB_THREAD;

	databaseFileName = dbFileName;

	setLoggingName("ObjectDatabase " + dbFileName);
	setGlobalLogging(true);
	setLogging(false);

	openDatabase();

	//setFileLogger("log/berkeley.log");

}

ObjectDatabase::~ObjectDatabase() {
	closeDatabase();

	delete objectsDatabase;
	objectsDatabase = NULL;
}

void ObjectDatabase::openDatabase() {
	try {
		//berkeley->set_error_stream(&System::out);

		int ret = objectsDatabase->open(NULL, databaseFileName, NULL, DB_HASH, dbFlags, 0);

		if (ret != 0) {
			error("Trying to open database error:" + String::valueOf(ret));
		} else
			info("opened object database", true);

	} catch(DbException &e) {
		error("Error opening database (" + databaseFileName + "): " );
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

void ObjectDatabase::closeDatabase() {
	try {

		objectsDatabase->close(0);

		info("database closed", true);

	} catch (DbException &e) {
		error("Error closing database (" + databaseFileName + "):");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

int ObjectDatabase::getData(uint64 objKey, ObjectInputStream* objectData) {
	int ret = 0;

	try {
		Dbt key, data;

		key.set_data(&objKey);
		key.set_size(sizeof(uint64));

		data.set_flags(DB_DBT_MALLOC);

		ret = objectsDatabase->get(NULL, &key, &data, 0);

		if (ret != 0) {
			if (ret != DB_NOTFOUND)
				error("Trying to get database (" + databaseFileName + ") error:" + String::valueOf(ret));

			return ret;
		}

		objectData->writeStream((const char*) data.get_data(), data.get_size());

		objectData->reset();

		free(data.get_data());

		info("retrieved data of size " + String::valueOf(objectData->size()));
	} catch(DbException &e) {
		error("Error in getData");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to get data from berkeley DB ");
	}

	return ret;
}

int ObjectDatabase::putData(uint64 objKey, ObjectOutputStream* objectData, bool syncToDisk) {
	int ret = -1;

	try {
		Dbt key(&objKey, sizeof(uint64));
		Dbt data((void*)objectData->getBuffer(), objectData->size());

		StringBuffer msg;
		msg << "saving oid 0x" << hex << objKey;
		info(msg.toString(), true);

		ret = objectsDatabase->put(NULL, &key, &data, 0);

		if (ret != 0)
			error("Trying to open database (" + databaseFileName + ") error:" + String::valueOf(ret));

		if (syncToDisk)
			objectsDatabase->sync(0);

	} catch(DbException &e) {
		error("Error in putData");
		error(e.what());
	} catch (...) {
		error("unreported exception caught while trying to put data into berkeley DB ");
	}

	return ret;
}

int ObjectDatabase::deleteData(uint64 objKey) {
	int ret = -1;

	Dbt key(&objKey, sizeof(uint64));

	try {

		ret = objectsDatabase->del(NULL, &key, 0);

	} catch(DbException &e) {
		error("Error in deleteData");
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

bool ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, ObjectInputStream* data) {
	try {
		if (cursor->get(&this->key, &this->data, DB_NEXT) != 0)
			return false;

		key = *(uint64*) (this->key.get_data());
		data->writeStream((char*)this->data.get_data(), this->data.get_size());

		data->reset();

	}  catch(DbException &e) {
		error("Error in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
		error(e.what());
	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextValue(ObjectInputStream* data) {
	try {
		if (cursor->get(&this->key, &this->data, DB_NEXT) != 0)
			return false;

		data->writeStream((char*)this->data.get_data(), this->data.get_size());

		data->reset();

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
