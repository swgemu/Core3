/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/managers/object/ObjectManager.h"

#include "ObjectDatabaseCore.h"
#include <fstream>
#include <thread>

AtomicInteger ObjectDatabaseCore::dbReadCount;
AtomicInteger ObjectDatabaseCore::dbReadNotFoundCount;
ParsedObjectsHashTable ObjectDatabaseCore::parsedObjects;
AtomicInteger ObjectDatabaseCore::pushedObjects;
AtomicInteger ObjectDatabaseCore::backPushedObjects;
Logger ObjectDatabaseCore::staticLogger("ObjectDatabaseCore");

ObjectDatabaseCore::ObjectDatabaseCore(Vector<String> arguments, const char* engine) : Core("log/odb3.log", engine, LogLevel::LOG),
	Logger("ObjectDatabaseCore"), arguments(std::move(arguments)) {

	setLogLevel(LogLevel::LOG);
}

void ObjectDatabaseCore::initialize() {
	info("starting up ObjectDatabase..");

	Core::initializeProperties("ODB3");

	Core::MANAGED_REFERENCE_LOAD = false;

	objectManager = new ObjectManager(false); //initialize databases but not the templates

	//DistributedObjectBroker* orb = DistributedObjectBroker::initialize("", 44230);
	//orb->setCustomObjectManager(new ObjectManager(false));
}

bool ObjectDatabaseCore::getJSONString(uint64 oid, ObjectInputStream& objectData, std::ostream& returnData) {
	static bool reportError = Core::getIntProperty("ODB3.reportParsingErrors", 1);
	String className;

	if (!Serializable::getVariable<String>(STRING_HASHCODE("_className"), &className, &objectData)) {
		return false;
	}

	UniqueReference<DistributedObjectPOD*> pod(Core::getObjectBroker()->createObjectPOD(className));

	if (pod == nullptr) {
		if (reportError)
			staticLogger.error("could not create pod object for class name " + className);

		return false;
	}

	try {
		pod->readObject(&objectData);

		nlohmann::json j;
		pod->writeJSON(j);

		nlohmann::json thisObject;
		thisObject[String::valueOf(oid).toCharArray()] = j;

		returnData << thisObject.dump();
	} catch (const Exception& e) {
		if (reportError)
			staticLogger.error("parsing data for object 0x:" + String::hexvalueOf(oid) + " " + e.getMessage());

		return false;
	} catch (const std::exception& e) {
		if (reportError)
			staticLogger.error("parsing data for object 0x:" + String::hexvalueOf(oid) + " " + e.what());

		return false;
	} catch (...) {
		if (reportError)
			staticLogger.error("parsing data for object 0x:" + String::hexvalueOf(oid));


		return false;
	}

	return true;

}

bool ObjectDatabaseCore::getJSONString(uint64 oid, ObjectDatabase* database, std::ostream& returnData) {
	static bool reportError = Core::getIntProperty("ODB3.reportParsingErrors", 1);

	try {
		ObjectInputStream objectData(1024);

		if (database->getDataNoTx(oid, &objectData)) {
			dbReadNotFoundCount.increment();
			return false;
		}

		ObjectDatabaseCore::dbReadCount.increment();

		return getJSONString(oid, objectData, returnData);
	} catch (...) {
		if (reportError)
			staticLogger.error("parsing data for object 0x:" + String::hexvalueOf(oid));
	}

	return false;
}

void dispatchWriterTask(std::stringstream* data, const String& fileName, int writerThread) {
	 Core::getTaskManager()->executeTask([data, fileName]() {
		UniqueReference<std::stringstream*> guard(data);

		std::ofstream jsonFile(fileName.toCharArray(), std::fstream::out | std::fstream::app);

		jsonFile << data->str();

		jsonFile.close();
	 }, "WriteJSONTask", ("Writer" + String::valueOf(writerThread)).toCharArray());
}

void ObjectDatabaseCore::dispatchTask(const Vector<uint64>& currentObjects, ObjectDatabase* database, const String& fileName, int maxWriterThreads, int dispatcher) {
	static AtomicInteger taskCount;
	int writerThread = taskCount.increment() % maxWriterThreads;

	Core::getTaskManager()->executeTask([fileName, dispatcher, currentObjects, database, writerThread]() {
			const String file = fileName + String::valueOf(writerThread);
			std::stringstream* buffer(new std::stringstream());
			int count = 0;

			for (const auto& oid : currentObjects) {
				try {
					if (getJSONString(oid, database, *buffer)) {
						*buffer << "\n";

						++count;
					}
				} catch (...) {
				}

				if (dispatcher == 2) {
					backPushedObjects.decrement();
				} else {
					pushedObjects.decrement();
				}
			}

			if (count) {
				dispatchWriterTask(buffer, file, writerThread);
			} else {
				delete buffer;
			}
	}, "DumpJSONTask", "ODBReaderThreads");
}

void ObjectDatabaseCore::showStats(uint32 previousCount, int deltaMs) {
	auto currentCount = dbReadCount.get(std::memory_order_seq_cst);

	StringBuffer buff;
	buff << "total db read count: " << currentCount << " speed: " << (currentCount - previousCount)
		<< " reads in " << deltaMs / 1000 << "s front queued: " << pushedObjects.get(std::memory_order_seq_cst)
		<< " back queued: " << backPushedObjects.get(std::memory_order_seq_cst);
	staticLogger.info(buff, true);
}

void ObjectDatabaseCore::startBackIteratorTask(ObjectDatabase* database, const String& fileName, int writerThreads) {
	if (Core::getIntProperty("ODB3.enableBackIterator", 1) == 0)
		return;

	staticLogger.info("back iterator2 enabled", true);

	berkley::CursorConfig config;
	config.setReadUncommitted(true);

	auto taskManager = Core::getTaskManager();

	//back iterator
	taskManager->executeTask([database, writerThreads, fileName, config]() mutable {
		ObjectDatabaseIterator iterator(database, config);
		uint64 oid = 0;

		Vector<uint64> currentObjects;
		int pushedCount = 0;

		static const int objectsPerTask = Core::getIntProperty("ODB3.objectsPerTask", 15);

		if (!iterator.getLastKey(oid)) {
			return; //no last key
		}

		ObjectInputStream data;

		if (!iterator.getSearchKey(oid, &data)) {
			staticLogger.error("false search key");

			return;
		}

		if (parsedObjects.put(oid, 2)) {
			return;
		}

		currentObjects.add(oid);

		while (iterator.getPrevKey(oid)) {
			if (parsedObjects.put(oid, 2)) {
				break;
			}

			currentObjects.add(oid);

			if (currentObjects.size() >= objectsPerTask) {
				backPushedObjects.add(currentObjects.size());
				pushedCount += (currentObjects.size());

				dispatchTask(currentObjects, database, fileName, writerThreads, 2);

				currentObjects.removeRange(0, currentObjects.size());
			}
		}

		if (currentObjects.size()) {
			backPushedObjects.add(currentObjects.size());
			pushedCount += (currentObjects.size());

			dispatchTask(currentObjects, database, fileName, writerThreads, 2);
		}

		staticLogger.info("back iterator finished dispatching " + String::valueOf(pushedCount) + " tasks", true);
	}, "BackIteratorTask", "BackIteratorThread");
}

void ObjectDatabaseCore::dispatchWorkerTask(const Vector<ODB3WorkerData>& currentObjects, ObjectDatabase* database, const String& fileName, int maxWriterThreads, int dispatcher) {
	static AtomicInteger taskCount;
	int writerThread = taskCount.increment() % maxWriterThreads;

	Core::getTaskManager()->executeTask([fileName, dispatcher, currentObjects, database, writerThread]() {
			const String file = fileName + String::valueOf(writerThread);
			std::stringstream* buffer(new std::stringstream());
			int count = 0;

			for (const auto& entry : currentObjects) {
				try {

					if (database->hasCompressionEnabled()) {
						ObjectInputStream uncompressed(entry.data->size() * 2);

						LocalDatabase::uncompress(entry.data->begin(), entry.data->size(), &uncompressed);

						uncompressed.reset();

						if (getJSONString(entry.oid, uncompressed, *buffer)) {
						*buffer << "\n";

						++count;
						}
					} else {
						if (getJSONString(entry.oid, *entry.data, *buffer)) {
							*buffer << "\n";

							++count;
						}
					}
				} catch (...) {
				}

				delete entry.data;

				pushedObjects.decrement();
				dbReadCount.increment();
			}

			if (count) {
				dispatchWriterTask(buffer, file, writerThread);
			} else {
				delete buffer;
			}
	}, "DumpJSONTask", "ODBReaderThreads");
}

void ObjectDatabaseCore::dumpDatabaseVersion2(const String& databaseName) {
	auto databaseManager  = ObjectDatabaseManager::instance();
	auto database = databaseManager->loadObjectDatabase(databaseName, false);

	if (!database) {
		error("invalid database " + databaseName);

		showHelp();

		return;
	}

	info("starting version 2 reader", true);

	int readerThreads = getIntArgument(2, 4);
	int writerThreads = readerThreads / 2 + 1;

	auto taskManager = Core::getTaskManager();

	taskManager->initializeCustomQueue("ODBReaderThreads", readerThreads);
	taskManager->initializeCustomQueue("BackIteratorThread", 1);

	for (int i = 0; i < writerThreads; ++i) {
		Core::getTaskManager()->initializeCustomQueue("Writer" + String::valueOf(i), 1);
	}


	const String fileName = getArgument(3, database->getDatabaseFileName() + ".json");

	berkley::CursorConfig config;
	config.setReadUncommitted(true);

	//forward iterator
	ObjectDatabaseIterator iterator(database, config);
	uint64 oid = 0;

	Vector<ODB3WorkerData> currentObjects;
	static const int objectsPerTask = Core::getIntProperty("ODB3.objectsPerTask", 15);

	Time lastStatsShow;
	lastStatsShow.updateToCurrentTime();
	uint32 previousCount = dbReadCount.get();
	int pushedCount = 0;

	//5MB buffer
	int buffersize = Core::getIntProperty("ODB3.bulkBuffer", 5 * 1024 * 1024); //5MB
	ArrayList<char> buffer(buffersize, buffersize / 2);

	berkley::DatabaseEntry dataEntry;
	dataEntry.setData(buffer.begin(), buffersize);

	size_t retklen, retdlen;
	unsigned char *retkey, *retdata;
	void *p;

	int queryRes = 0;

	do {
		if (queryRes == DB_BUFFER_SMALL) {
			staticLogger.info("resizing bulk buffer to " + String::valueOf(buffersize * 2), true);

			buffersize *= 2;

			buffer.removeAll(buffersize, 5);
			dataEntry.setData(buffer.begin(), buffersize);
		}

		queryRes = iterator.getNextKeyAndValueMultiple(dataEntry);

		if (!queryRes) {
			for (DB_MULTIPLE_INIT(p, dataEntry.getDBT());;) {
				DB_MULTIPLE_KEY_NEXT(p,
						dataEntry.getDBT(), retkey, retklen, retdata, retdlen);
				if (p == NULL)
					break;

				ObjectInputStream* data = new ObjectInputStream(retdlen);
				data->writeStream((const char*)retdata, retdlen);

				oid = *reinterpret_cast<uint64*>(retkey);

				ODB3WorkerData val;
				val.oid = oid;
				val.data = data;

				currentObjects.emplace(val);

				if (currentObjects.size() >= objectsPerTask) {
					pushedObjects.add(currentObjects.size());
					pushedCount += (currentObjects.size());

					dispatchWorkerTask(currentObjects, database, fileName, writerThreads, 1);

					currentObjects.removeRange(0, currentObjects.size());

					auto diff = lastStatsShow.miliDifference();

					if (diff > 1000) {
						showStats(previousCount, diff);

						lastStatsShow.updateToCurrentTime();
						previousCount = dbReadCount.get();
					}
				}
			}
		}
	} while (queryRes == 0 || queryRes == DB_BUFFER_SMALL);

	if (queryRes) {
		staticLogger.info("iterator finished with result: " + String::valueOf(queryRes) + db_strerror(queryRes), true);
	}

	if (currentObjects.size()) {
		pushedObjects.add(currentObjects.size());
		pushedCount += (currentObjects.size());

		dispatchWorkerTask(currentObjects, database, fileName, writerThreads, 1);
	}

	staticLogger.info("iterator finished dispatching " + String::valueOf(pushedCount) + " tasks", true);

	while (pushedObjects.get(std::memory_order_seq_cst)) {
		Thread::sleep(500);

		auto diff = lastStatsShow.miliDifference();

		if (diff > 1000) {
			showStats(previousCount, diff);

			lastStatsShow.updateToCurrentTime();
			previousCount = dbReadCount.get();
		}
	}
}

void ObjectDatabaseCore::dumpDatabaseToJSON(const String& databaseName) {
	if (Core::getIntProperty("ODB3.version", 0) == 2) {
		dumpDatabaseVersion2(databaseName);

		return;
	}

	auto databaseManager  = ObjectDatabaseManager::instance();
	auto database = databaseManager->loadObjectDatabase(databaseName, false);

	if (!database) {
		error("invalid database " + databaseName);

		showHelp();

		return;
	}

	int readerThreads = getIntArgument(2, 4);
	int writerThreads = readerThreads / 2 + 1;

	auto taskManager = Core::getTaskManager();

	taskManager->initializeCustomQueue("ODBReaderThreads", readerThreads);
	taskManager->initializeCustomQueue("BackIteratorThread", 1);

	for (int i = 0; i < writerThreads; ++i) {
		Core::getTaskManager()->initializeCustomQueue("Writer" + String::valueOf(i), 1);
	}

	berkley::CursorConfig config;
	config.setReadUncommitted(true);

	const String fileName = getArgument(3, database->getDatabaseFileName() + ".json");
	startBackIteratorTask(database, fileName, writerThreads);

	//forward iterator
	ObjectDatabaseIterator iterator(database, config);
	uint64 oid = 0;

	Vector<uint64> currentObjects;
	static const int objectsPerTask = Core::getIntProperty("ODB3.objectsPerTask", 15);

	Time lastStatsShow;
	lastStatsShow.updateToCurrentTime();
	uint32 previousCount = dbReadCount.get();
	int pushedCount = 0;

	const bool backIteratorEnabled = Core::getIntProperty("ODB3.enableBackIterator", 1);

	while (iterator.getNextKey(oid)) {
		if (backIteratorEnabled && this->parsedObjects.put(oid, 1)) {
			break;
		}

		currentObjects.add(oid);

		if (currentObjects.size() >= objectsPerTask) {
			pushedObjects.add(currentObjects.size());
			pushedCount += (currentObjects.size());

			dispatchTask(currentObjects,  database, fileName, writerThreads, 1);

			currentObjects.removeRange(0, currentObjects.size());

			auto diff = lastStatsShow.miliDifference();

			if (diff > 1000) {
				showStats(previousCount, diff);

				lastStatsShow.updateToCurrentTime();
				previousCount = dbReadCount.get();
			}
		}
	}

	if (currentObjects.size()) {
		pushedObjects.add(currentObjects.size());
		pushedCount += (currentObjects.size());

		dispatchTask(currentObjects, database, fileName, writerThreads, 1);
	}

	staticLogger.info("front iterator finished dispatching " + String::valueOf(pushedCount) + " tasks", true);

	while (backPushedObjects.get(std::memory_order_seq_cst) && pushedObjects.get(std::memory_order_seq_cst)) {
		Thread::sleep(100);

		auto diff = lastStatsShow.miliDifference();

		if (diff > 1000) {
			showStats(previousCount, diff);

			lastStatsShow.updateToCurrentTime();
			previousCount = dbReadCount.get();
		}
	}
}

ObjectDatabase* ObjectDatabaseCore::getDatabase(uint64_t objectID) {
	auto databaseManager = ObjectDatabaseManager::instance();
	uint16 tableID = (uint16)(objectID >> 48);

	LocalDatabase* db = databaseManager->getDatabase(tableID);

	if (db == NULL || !db->isObjectDatabase())
		return NULL;

	ObjectDatabase* database = static_cast<ObjectDatabase*>( db);

	return database;
}

void ObjectDatabaseCore::dumpObjectToJSON(uint64_t objectID) {
	ObjectDatabase* database = getDatabase(objectID);

	if (!database) {
		error("cant map object id to database");

		showHelp();

		return;
	}

	std::stringstream json;
	if (getJSONString(objectID, database, json)) {
		std::cout << json.str() << std::endl;
	}
}

void ObjectDatabaseCore::showHelp() {
	info("Arguments: \n"
		"\todb3 dumpdb <database> <threads> <filename>\n"
		"\todb3 dumpobj <objectid>\n"
		, true);
}

void ObjectDatabaseCore::run() {
	info("initialized");

	const String& operation = getArgument(0, "none");

	if (operation == "dumpdb") {
		dumpDatabaseToJSON(getArgument(1));
	} else if (operation == "dumpobj") {
		dumpObjectToJSON(getLongArgument(1));
	} else {
		showHelp();
	}
}

int main(int argc, char* argv[]) {
	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		ObjectDatabaseCore core(std::move(arguments), "odb3");

		core.start();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}
