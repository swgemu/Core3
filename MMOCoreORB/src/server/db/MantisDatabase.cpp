/*
 * MantisDatabase.cpp
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */


#include "MantisDatabase.h"

#include "conf/ConfigManager.h"

Vector<Database*>* MantisDatabase::databases = nullptr;
AtomicInteger MantisDatabase::currentDB;
String MantisDatabase::tablePrefix;

MantisDatabase::MantisDatabase(ConfigManager* configManager) {
	const String& dbHost = configManager->getMantisHost();
	const String& dbUser = configManager->getMantisUser();
	const String& dbPass = configManager->getMantisPass();
	const String& dbName = configManager->getMantisName();
	tablePrefix = configManager->getMantisPrefix();
	const uint16& dbPort = configManager->getMantisPort();

	databases = new Vector<Database*>();

	if (dbHost.isEmpty())
		return;

	for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
		try {
			Database* db = new engine::db::mysql::MySqlDatabase(String("MantisDatabase" + String::valueOf(i)), dbHost);
			db->connect(dbName, dbUser, dbPass, dbPort);

			databases->add(db);
		} catch (const Exception& e) {
			Logger::console.error(e.getMessage());
		}
	}
}

MantisDatabase::~MantisDatabase() {
	while (!databases->isEmpty()) {
		Database* db = databases->remove(0);

		delete db;
	}

	delete databases;
	databases = nullptr;
}
