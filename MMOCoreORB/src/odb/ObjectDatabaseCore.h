/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTDATABASECORE_H_
#define OBJECTDATABASECORE_H_

#include <ostream>
#include <utility>

#include "engine/engine.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "system/util/SynchronizedHashTable.h"
#include "server/db/ServerDatabase.h"

class ParsedObjectsHashTable : protected HashTable<uint64, int> {
public:
	ParsedObjectsHashTable() : HashTable<uint64, int>(1000000) {
		setNullValue(0);
	}

	int put(uint64 key, int val) {
		Locker locker(&guard);

		return HashTable<uint64, int>::put(key, val);
	}

	int size() {
		return HashTable<uint64, int>::size();
	}

protected:
	int hash(const uint64& keyValue) const {
		uint64 key = keyValue;

		key = (~key) + (key << 18);
		key =   key  ^ (key >> 31);
		key = key * 21;
		key = key ^ (key >> 11);
		key = key + (key << 6);
		key = key ^ (key >> 22);
		return (int) key;
	}

	Mutex guard;
};

class ServerDatabase;

class ODB3WorkerData {
public:
	uint64 oid;
	ObjectInputStream* data;

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}
};

class ObjectDatabaseCore : public Core, public Logger {
protected:
	Reference<ObjectManager*> objectManager;
	Vector<String> arguments;
	UniqueReference<ServerDatabase*> mysql;

	static ParsedObjectsHashTable parsedObjects;
	static AtomicInteger dbReadCount;
	static AtomicInteger dbReadNotFoundCount;
	static AtomicInteger pushedObjects;
	static AtomicInteger backPushedObjects;
	static Logger staticLogger;
	static SynchronizedVectorMap<String, int> adminList;
	static AtomicLong creoReadSize;
	static AtomicLong compressedCreoReadSize;
	static AtomicLong ghostReadSize;
	static AtomicLong globalDBReadSize;

	static AtomicLong creoCompactSize;
	static AtomicLong ghostCompactSize;

public:
	ObjectDatabaseCore(Vector<String> arguments, const char* engine);

	void initialize();

	void run();

	void dumpObjectToJSON(uint64_t oid);
	void dumpDatabaseToJSON(const String& database);

	static VectorMap<uint64, String> loadPlayers(int galaxyID);

	void showHelp();
	void dumpPlayers();

	static void showStats(uint32 previousCount, int deltaMs);

	static ObjectDatabase* getDatabase(uint64_t objectID);

	static int getJSONString(uint64 oid, ObjectDatabase* database, std::ostream& writeStream);
	static UniqueReference<DistributedObjectPOD*> getJSONString(uint64 oid, ObjectInputStream& objectData, std::ostream& returnData);
	//static std::function<void()> getReadTestTask(const Vector<ODB3WorkerData>& currentObjects, ObjectDatabase* database, const String& fileName, int maxWriterThreads, int dispatcher);

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

	static void dispatchTask(const Vector<uint64>& currentObjects, ObjectDatabase* database, const String& fileName, int maxWriterThreads, int dispatcher);
	static void dispatchWorkerTask(const Vector<ODB3WorkerData>& currentObjects, ObjectDatabase* database, const String& fileName, int maxWriterThreads, int dispatcher);
	static void startBackIteratorTask(ObjectDatabase* database, const String& fileName, int writerThreads);
	static void startBackIteratorTask2(ObjectDatabase* database, const String& fileName, int writerThreads);
	static void dispatchPlayerTask(const Vector<VectorMapEntry<String, uint64>>& currentObjects, const String& fileName);
};

#endif /*OBJECTDATABASECORE_H_*/
