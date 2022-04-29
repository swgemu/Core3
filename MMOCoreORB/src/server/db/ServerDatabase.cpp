/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ServerDatabase.h"

#include "conf/ConfigManager.h"
#include "MySqlDatabase.h"

Vector<Database*>* ServerDatabase::databases = nullptr;
AtomicInteger ServerDatabase::currentDB;

ServerDatabase::ServerDatabase(ConfigManager* configManager) {
	const String& dbHost = configManager->getDBHost();
	const String& dbUser = configManager->getDBUser();
	const String& dbPass = configManager->getDBPass();
	const String& dbName = configManager->getDBName();
	const int     dbPort = configManager->getDBPort();

	setLoggingName("ServerDatabase " + dbHost + ":" + String::valueOf(dbPort));

	databases = new Vector<Database*>();

	const static int DEFAULT_SERVERDATABASE_INSTANCES = configManager->getInt("Core3.DBInstances", 1);

	for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
		Database* db = new server::db::mysql::MySqlDatabase(String("MySqlDatabase" + String::valueOf(i)), dbHost);
		db->connect(dbName, dbUser, dbPass, dbPort);

		databases->add(db);
	}

	try {
		UniqueReference<ResultSet*> result(instance()->executeQuery("SELECT `schema_version` FROM `db_metadata`;"));

		if (result != nullptr && result->next())
			dbSchemaVersion = result->getInt(0);
	} catch (const Exception& e) {
		dbSchemaVersion = 1000;

		String createTable = "CREATE TABLE `db_metadata` AS SELECT 1000 as `schema_version`;";
		try {
			UniqueReference<ResultSet*> result(instance()->executeQuery(createTable));
		} catch (const Exception& e) {
			error("Failed to create db_metadata table, please manually create in mysql: " + createTable);
		}
	}

	updateDatabaseSchema();

	info(true) << "schema_version = " << dbSchemaVersion;
}

ServerDatabase::~ServerDatabase() {
	for (auto db : *databases) {
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
		UniqueReference<ResultSet*> result(instance()->executeQuery(alterSql));

		if (result != nullptr) {
			result = instance()->executeQuery(updateVersionSql);
			dbSchemaVersion = nextSchemaVersion;

			info(true) << "Upgraded mysql database schema to version " << dbSchemaVersion;
		}
	} catch (const Exception& e) {
		error(e.getMessage());
		error() << "Failed to update database schema, please manually execute: " << alterSql << " " << updateVersionSql;
	}
}

void ServerDatabase::updateDatabaseSchema() {
	alterDatabase(1001,
		"ALTER TABLE `account_ips`"
		" ADD COLUMN `galaxy_id` INT(5) DEFAULT -1 AFTER `account_id`,"
		" ADD COLUMN `online_count` INT(4) DEFAULT -1 AFTER `logout`;"
	);

	alterDatabase(1002,
		"CREATE TABLE `session_stats` ("
		"`timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP"
		",`ip` char(15) NOT NULL"
		",`galaxy_id` int(5) DEFAULT '-1'"
		",`account_id` int(10) unsigned NOT NULL"
		",`character_oid` bigint(20) NOT NULL"
		",`session_seconds` int(10) unsigned NOT NULL"
		",`delta_seconds` int(10) unsigned NOT NULL"
		",`delta_credits` int(11) NOT NULL"
		",`delta_skillpoints` int(3) NOT NULL"
		",`activity_xp` int(10) unsigned NOT NULL"
		",`activity_movement` int(5) unsigned NOT NULL"
		",`current_credits` int(11) unsigned NOT NULL"
		",`ip_account_count` int(2) unsigned NOT NULL"
		",`session_end` int(1) unsigned NOT NULL"
		",KEY `idx_timestamp` (`timestamp`)"
		",KEY `idx_ip` (`ip`)"
		",KEY `idx_galaxy_ip` (`galaxy_id`,`ip`,`account_id`,`character_oid`)"
		") ENGINE=MyISAM DEFAULT CHARSET=latin1;"
	);

	alterDatabase(1003,
		"ALTER TABLE `session_stats`"
		" ADD COLUMN `uptime` INT(11) DEFAULT '-1' AFTER `timestamp`;"
	);

	alterDatabase(1004,
		"ALTER TABLE `sessions`"
		" MODIFY `session_id` CHAR(255) NOT NULL;"
	);

	alterDatabase(1005,
		"CREATE TABLE `galaxy_access` ("
		"`account_id` int(10) NOT NULL DEFAULT '0'"
		",`galaxy_id` int(5) NOT NULL"
		",`expires` datetime DEFAULT NULL"
		",PRIMARY KEY (`account_id`,`galaxy_id`)"
		") ENGINE=MyISAM DEFAULT CHARSET=latin1;"
	);
}
