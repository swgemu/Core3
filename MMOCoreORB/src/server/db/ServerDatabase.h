/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDATABASE_H_
#define SERVERDATABASE_H_

#include "../conf/ConfigManager.h"

class ServerDatabase {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;

public:
	ServerDatabase(ConfigManager* configManager) {
		const String& dbHost = configManager->getDBHost();
        const String& dbUser = configManager->getDBUser();
        const String& dbPass = configManager->getDBPass();
        const String& dbName = configManager->getDBName();
        const uint16& dbPort = configManager->getDBPort();

        databases = new Vector<Database*>();

        for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
        	Database* db = new engine::db::mysql::MySqlDatabase(String("ServerDatabase" + String::valueOf(i)), dbHost);
        	db->connect(dbName, dbUser, dbPass, dbPort);

        	databases->add(db);
        }

	}

	const static int DEFAULT_SERVERDATABASE_INSTANCES = 8;

	~ServerDatabase() {
		while (!databases->isEmpty()) {
			Database* db = databases->remove(0);

			delete db;
		}

		delete databases;
		databases = NULL;
	}

	inline static Database* instance() {
		if (databases == NULL)
			throw DatabaseException("No Server Database initiated");

		int i = currentDB.get() % databases->size();

		currentDB.increment();

		return databases->get(i);
	}
};

#endif /*SERVERDATABASE_H_*/
