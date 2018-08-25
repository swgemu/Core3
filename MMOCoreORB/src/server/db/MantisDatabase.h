/*
 * MantisDatabase.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef MANTISDATABASE_H_
#define MANTISDATABASE_H_

#include "engine/engine.h"

namespace conf {
	class ConfigManager;
}

class MantisDatabase {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;

	static String tablePrefix;

public:
	const static int DEFAULT_SERVERDATABASE_INSTANCES = 1;

	MantisDatabase(conf::ConfigManager* configManager);
	~MantisDatabase();

	inline static Database* instance() {
		if (databases->size() == 0)
			return nullptr;

		int i = currentDB.get() % databases->size();

		currentDB.increment();

		return databases->get(i);
	}

	static const String& getTablePrefix() {
		return tablePrefix;
	}
};

#endif /* MANTISDATABASE_H_ */
