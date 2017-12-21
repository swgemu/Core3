/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDATABASE_H_
#define SERVERDATABASE_H_

#include "engine/engine.h"

namespace conf {
	class ConfigManager;
}

class ServerDatabase {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;

public:
	ServerDatabase(conf::ConfigManager* configManager);
	~ServerDatabase();

	const static int DEFAULT_SERVERDATABASE_INSTANCES = 8;

	inline static Database* instance() {
		if (databases == nullptr)
			throw DatabaseException("No Server Database initiated");

		int i = currentDB.get() % databases->size();

		currentDB.increment();

		return databases->get(i);
	}
};

#endif /*SERVERDATABASE_H_*/
