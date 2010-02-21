/*
 * ObjectDatabaseNEW.cpp
 *
 *  Created on: 18/02/2010
 *      Author: victor
 */

#include "ObjectDatabase.h"
#include "ObjectDatabaseEnvironment.h"


ObjectDatabase::ObjectDatabase(ObjectDatabaseEnvironment* dbEnv, const String& dbFileName) {
	environment = dbEnv->getBerkeleyEnvironment();

	setLoggingName("ObjectDatabase " + dbFileName);
	setGlobalLogging(true);
	setLogging(false);

	databaseFileName = dbFileName;

	openDatabase();

	//setFileLogger("log/berkeley.log");

}

ObjectDatabase::~ObjectDatabase() {
	closeDatabase();

	delete objectsDatabase;
	objectsDatabase = NULL;
}

void ObjectDatabase::openDatabase() {
	DatabaseConfig config;
	config.setThreaded(true);
	config.setTransactional(true);
	config.setAllowCreate(true);
	config.setType(DatabaseType::HASH);

	try {

		objectsDatabase = environment->openDatabase(NULL, databaseFileName, "", config);

	} catch (Exception& e) {
		error(e.getMessage());
		exit(1);
	}
}

void ObjectDatabase::closeDatabase() {
	try {

		objectsDatabase->close(true);

		info("database closed", true);

	} catch (Exception &e) {
		error("Error closing database (" + databaseFileName + "):");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

int ObjectDatabase::getData(uint64 objKey, ObjectInputStream* objectData) {
	int ret = 0;

	DatabaseEntry key, data;

	key.setData(&objKey, sizeof(uint64));

	int i = 0;

	do {
		ret = objectsDatabase->get(NULL, &key, &data);

		if (ret == DB_LOCK_DEADLOCK)
			info("deadlock detected in ObjectDatabse::get.. retrying", true);

		++i;
	} while (ret == DB_LOCK_DEADLOCK && i < DEADLOCK_MAX_RETRIES);

	if (ret == 0) {
		objectData->writeStream((const char*) data.getData(), data.getSize());

		objectData->reset();
	} else if (ret != DB_NOTFOUND) {
		error("error in ObjectDatabase::getData ret " + String::valueOf(ret));

		throw DatabaseException("error in ObjectDatabase::getData ret " + String(db_strerror(ret)));
	}

	return ret;
}


int ObjectDatabase::putData(uint64 objKey, ObjectOutputStream* objectData) {
	int ret = -1;

	DatabaseEntry key, data;
	key.setData(&objKey, sizeof(uint64));
	data.setData(objectData->getBuffer(), objectData->size());

	int i = 0;

	Transaction* transaction = NULL;

	do {
		transaction = environment->beginTransaction(NULL);

		ret = objectsDatabase->put(transaction, &key, &data);

		if (ret == DB_LOCK_DEADLOCK) {
			info("deadlock detected in ObjectDatabse::get.. retrying", true);

			transaction->abort();
		}

		++i;
	} while (ret == DB_LOCK_DEADLOCK && i < DEADLOCK_MAX_RETRIES);

	if (ret != 0) {
		error("error in ObjectDatabase::putData :" + String::valueOf(ret));

		transaction->abort();

		exit(1);
	}

	if (transaction->commitNoSync() != 0) {
		error("error commiting transaction in ObjectDatabase::putData :" + String::valueOf(ret));
		exit(1);
	}

	return ret;
}

int ObjectDatabase::deleteData(uint64 objKey) {
	int ret = -1;

	DatabaseEntry key;
	key.setData(&objKey, sizeof(uint64));


	int i = 0;

	do {

		ret = objectsDatabase->del(NULL, &key);

		++i;
	} while (ret == DB_LOCK_DEADLOCK && i < DEADLOCK_MAX_RETRIES);

	return ret;
}

int ObjectDatabase::sync() {
	objectsDatabase->sync();

	return 0;
}

ObjectDatabaseIterator::ObjectDatabaseIterator(ObjectDatabase* database) : Logger("ObjectDatabaseIterator") {
	databaseHandle = database->getDatabaseHandle();
	cursor = databaseHandle->openCursor(NULL);

	data.setReuseBuffer(true);
	key.setReuseBuffer(true);
}

ObjectDatabaseIterator::ObjectDatabaseIterator(BerkeleyDatabase* dbHandle) : Logger("ObjectDatabaseIterator") {
	databaseHandle = dbHandle;
	cursor = databaseHandle->openCursor(NULL);

	data.setReuseBuffer(true);
	key.setReuseBuffer(true);
}

ObjectDatabaseIterator::~ObjectDatabaseIterator() {
	closeCursor();
}

void ObjectDatabaseIterator::resetIterator() {
	if (cursor != NULL) {
		cursor->close();
		delete cursor;
	}

	cursor = databaseHandle->openCursor(NULL);
}

bool ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, ObjectInputStream* data) {
	try {
		if (cursor->getNext(&this->key, &this->data) != 0)
			return false;

		key = *(uint64*) (this->key.getData());
		data->writeStream((char*)this->data.getData(), this->data.getSize());

		data->reset();

	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextValue(ObjectInputStream* data) {
	try {
		if (cursor->getNext(&this->key, &this->data) != 0)
			return false;

		data->writeStream((char*)this->data.getData(), this->data.getSize());

		data->reset();

	} catch(Exception &e) {
		error("Error in ObjectDatabaseIterator::getNextValue(String& data)");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextValue(String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextKey(uint64& key) {
	try {
		if (cursor->getNext(&this->key, &this->data) != 0)
			return false;

		key =  *(uint64*)(this->key.getData());

	}  catch(Exception &e) {
		error("Error in ObjectDatabaseIterator::getNextKey");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught  in ObjectDatabaseIterator::getNextKey(uint64& key) ");
	}

	return true;
}
