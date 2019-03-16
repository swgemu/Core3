/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTDATABASECORE_H_
#define OBJECTDATABASECORE_H_

#include "engine/engine.h"
#include "server/zone/managers/object/ObjectManager.h"

class ObjectDatabaseCore : public Core, public Logger {
protected:
	Reference<ObjectManager*> objectManager;
	Vector<String> arguments;

public:
	ObjectDatabaseCore(Vector<String> arguments);

	void initialize();

	void run();

	void dumpDatabaseToJSON(const String& database);
	void dumpObjectToJSON(uint64_t oid);

	void showHelp();

	static ObjectDatabase* getDatabase(uint64_t objectID);

	static bool getJSONString(uint64 oid, ObjectDatabase* database, String& returnData);

	uint64_t getLongArgument(int index, uint64_t defaultValue = 0) const {
		if (index >= arguments.size()) {
			return defaultValue;
		}

		return UnsignedLong::valueOf(arguments.get(index));
	}

	int getIntArgument(int index, int defaultValue = 0) const {
		if (index >= arguments.size()) {
			return defaultValue;
		}

		return Integer::valueOf(arguments.get(index));
	}

	const String& getArgument(int index, const String& defaultValue = "") const {
		if (index >= arguments.size()) {
			return defaultValue;
		}

		return arguments.get(index);
	}

	void dispatchTask(const Vector<uint64>& currentObjects, AtomicInteger& pushedObjects, ObjectDatabase* database);
};

#endif /*OBJECTDATABASECORE_H_*/
