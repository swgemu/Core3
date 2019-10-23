/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDATABASE_H_
#define SERVERDATABASE_H_

#include "engine/engine.h"

namespace conf {
	class ConfigManager;
}

class ServerDatabase : public Logger {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;
	int dbSchemaVersion;

public:
	ServerDatabase(conf::ConfigManager* configManager);
	~ServerDatabase();

	inline static Database* instance() {
		if (databases == nullptr)
			throw DatabaseException("No Server Database initiated");

		int i = currentDB.postIncrement() % databases->size();

		return databases->get(i);
	}

	inline int getSchemaVersion() const {
		return dbSchemaVersion;
	}
private:
	void alterDatabase(int nextVersion, const String& alterSql);
	void updateDatabaseSchema();
};

#endif /*SERVERDATABASE_H_*/
