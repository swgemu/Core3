/*
 * MantisDatabase.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef MANTISDATABASE_H_
#define MANTISDATABASE_H_

#include "../conf/ConfigManager.h"

class MantisDatabase {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;

	static String tablePrefix;

public:
	MantisDatabase(ConfigManager* configManager) {
		const String& dbHost = configManager->getMantisHost();
		const String& dbUser = configManager->getMantisUser();
		const String& dbPass = configManager->getMantisPass();
		const String& dbName = configManager->getMantisName();
        tablePrefix = configManager->getMantisPrefix();
		const uint16& dbPort = configManager->getMantisPort();

        databases = new Vector<Database*>();

        for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
        	try {
        		Database* db = new engine::db::mysql::MySqlDatabase(String("MantisDatabase" + String::valueOf(i)), dbHost);
        		db->connect(dbName, dbUser, dbPass, dbPort);

        		databases->add(db);
        	} catch (const Exception& e) {

        	}
        }

	}

	const static int DEFAULT_SERVERDATABASE_INSTANCES = 1;

	~MantisDatabase() {
		while (!databases->isEmpty()) {
			Database* db = databases->remove(0);

			delete db;
		}

		delete databases;
		databases = NULL;
	}

	inline static Database* instance() {
		if (databases->size() == 0)
			return NULL;

		int i = currentDB.get() % databases->size();

		currentDB.increment();

		return databases->get(i);
	}

	static String& getTablePrefix() {
		return tablePrefix;
	}
};

#endif /* MANTISDATABASE_H_ */
