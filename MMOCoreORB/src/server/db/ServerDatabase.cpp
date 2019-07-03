/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ServerDatabase.h"

#include "conf/ConfigManager.h"
#include "MySqlDatabase.h"

Vector<Database*>* ServerDatabase::databases = NULL;
AtomicInteger ServerDatabase::currentDB;

ServerDatabase::ServerDatabase(ConfigManager* configManager) {
	setLoggingName("ServerDatabase");

	const String& dbHost = configManager->getDBHost();
	const String& dbUser = configManager->getDBUser();
	const String& dbPass = configManager->getDBPass();
	const String& dbName = configManager->getDBName();
	const int     dbPort = configManager->getDBPort();

	databases = new Vector<Database*>();

	for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
		Database* db = new server::db::mysql::MySqlDatabase(String("ServerDatabase" + String::valueOf(i)), dbHost);
		db->connect(dbName, dbUser, dbPass, dbPort);

		databases->add(db);
	}

	try {
		Reference<ResultSet*> result = instance()->executeQuery("SELECT `schema_version` FROM `db_metadata`;");

		if (result != nullptr && result->next())
			dbSchemaVersion = result->getInt(0);
	} catch (Exception& e) {
		dbSchemaVersion = 1000;

		String createTable = "CREATE TABLE `db_metadata` AS SELECT 1000 as `schema_version`;";
		try {
			Reference<ResultSet*> result = instance()->executeQuery(createTable);
			updateDatabaseSchema();
		} catch (Exception& e) {
			error("Failed to create db_metadata table, please manually create in mysql: " + createTable);
		}
	}

	info("schema_version = " + String::valueOf(dbSchemaVersion), true);
}

ServerDatabase::~ServerDatabase() {
	while (!databases->isEmpty()) {
		Database* db = databases->remove(0);

		delete db;
	}

	delete databases;
	databases = nullptr;
}

void ServerDatabase::alterDatabase(int nextSchemaVersion, const String& alterSql) {
	if (dbSchemaVersion >= nextSchemaVersion)
		return;

	String updateVersionSql = "UPDATE `db_metadata` SET `schema_version` = " + String::valueOf(nextSchemaVersion);

	try {
		Reference<ResultSet*> result = instance()->executeQuery(alterSql);

		if (result != nullptr) {
			result = instance()->executeQuery(updateVersionSql);
			dbSchemaVersion = nextSchemaVersion;
			info("Upgraded mysql database schema to version " + String::valueOf(dbSchemaVersion), true);
		}
	} catch (Exception& e) {
		error(e.getMessage());
		error("Failed to update database schema, please manually execute: " + alterSql + "; " + updateVersionSql);
	}
}

void ServerDatabase::updateDatabaseSchema() {
	alterDatabase(1001,
		"ALTER TABLE `account_ips`"
		" ADD COLUMN `galaxy_id` INT(5) DEFAULT -1 AFTER `account_id`,"
		" ADD COLUMN `online_count` INT(4) DEFAULT -1 AFTER `logout`;"
	);
}
