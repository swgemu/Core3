/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ServerDatabase.h"

#include "conf/ConfigManager.h"

Vector<Database*>* ServerDatabase::databases = NULL;
AtomicInteger ServerDatabase::currentDB;

ServerDatabase::ServerDatabase(ConfigManager* configManager) {
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

ServerDatabase::~ServerDatabase() {
	while (!databases->isEmpty()) {
		Database* db = databases->remove(0);

		delete db;
	}

	delete databases;
	databases = nullptr;
}
