/*
 * MantisDatabase.cpp
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#include "MySqlDatabase.h"
#include "MantisDatabase.h"

#include "conf/ConfigManager.h"

UniqueReference<ArrayList<UniqueReference<Database*> >* > MantisDatabase::databases;
AtomicInteger MantisDatabase::currentDB;
String MantisDatabase::tablePrefix;

MantisDatabase::MantisDatabase(ConfigManager* configManager) {
	const String& dbHost = configManager->getMantisHost();
	const String& dbUser = configManager->getMantisUser();
	const String& dbPass = configManager->getMantisPass();
	const String& dbName = configManager->getMantisName();
	tablePrefix = configManager->getMantisPrefix();
	const int     dbPort = configManager->getMantisPort();

	databases = new ArrayList<UniqueReference<Database*>>();

	if (dbHost.isEmpty())
		return;

	for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
		Database* db = nullptr;

		try {
			db = new server::db::mysql::MySqlDatabase(String("MantisDatabase" + String::valueOf(i)), dbHost);
			db->connect(dbName, dbUser, dbPass, dbPort);

			databases->emplace(db);
		} catch (const Exception& e) {
			Logger::console.error(e.getMessage());

			delete db;
			db = nullptr;
		}
	}
}

MantisDatabase::~MantisDatabase() {
}
