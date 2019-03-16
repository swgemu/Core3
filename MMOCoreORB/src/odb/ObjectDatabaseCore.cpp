/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/managers/object/ObjectManager.h"

#include "ObjectDatabaseCore.h"
#include <fstream>

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

bool ObjectDatabaseCore::getJSONString(uint64 oid, ObjectDatabase* database, std::ostream& returnData) {
	static bool reportError = Core::getIntProperty("ODB3.reportParsingErrors", 1);

	ObjectInputStream objectData(1024);

	if (!database->getData(oid, &objectData)) {
		String className;

		if (Serializable::getVariable<String>(STRING_HASHCODE("_className"), &className, &objectData)) {
			UniqueReference<DistributedObjectPOD*> pod(Core::getObjectBroker()->createObjectPOD(className));

			if (pod == nullptr) {
				if (reportError)
					Logger::console.error("could not create pod object for class name " + className);

				return false;
			}

			try {
				pod->readObject(&objectData);

				nlohmann::json j;
				pod->writeJSON(j);

				nlohmann::json thisObject;
				thisObject[String::valueOf(oid).toCharArray()] = j;

				returnData << thisObject.dump();
			} catch (Exception& e) {
				if (reportError)
					Logger::console.error("parsing data for object 0x:" + String::hexvalueOf(oid) + " " + e.getMessage());

				return false;
			}

			return true;
		}
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

void ObjectDatabaseCore::dispatchTask(const Vector<uint64>& currentObjects, AtomicInteger& pushedObjects, ObjectDatabase* database, int maxWriterThreads) {
	const static String fileName = getArgument(3, database->getDatabaseFileName() + ".json");

	static AtomicInteger taskCount;

	int writerThread = taskCount.increment() % maxWriterThreads;
	const String file = fileName + String::valueOf(writerThread);

	Core::getTaskManager()->executeTask([currentObjects, &pushedObjects, database, file, writerThread]() {
			std::stringstream* buffer(new std::stringstream());
			int count = 0;

			for (const auto& oid : currentObjects) {
				pushedObjects.decrement();

				if (getJSONString(oid, database, *buffer)) {
					*buffer << "\n";

					++count;
				}
			}

			if (count) {
				dispatchWriterTask(buffer, file, writerThread);
			} else {
				delete buffer;
			}
	}, "DumpJSONTask", "ODBReaderThreads");
}

void ObjectDatabaseCore::dumpDatabaseToJSON(const String& databaseName) {
	auto databases = ObjectDatabaseManager::instance();
	auto database = databases->loadObjectDatabase(databaseName, false);

	if (!database) {
		error("invalid database " + databaseName);

		showHelp();

		return;
	}

	int readerThreads = getIntArgument(2, 4);
	int writerThreads = readerThreads / 2 + 1;

	Core::getTaskManager()->initializeCustomQueue("ODBReaderThreads", readerThreads);

	for (int i = 0; i < writerThreads; ++i) {
		Core::getTaskManager()->initializeCustomQueue("Writer" + String::valueOf(i), 1);
	}

	ObjectDatabaseIterator iterator(database);
	uint64 oid = 0;

	AtomicInteger pushedObjects = 0;

	Vector<uint64> currentObjects;
	constexpr static const int objectsPerTask = 15;

	while (iterator.getNextKey(oid)) {
		currentObjects.emplace(oid);

		if (currentObjects.size() >= objectsPerTask) {
			pushedObjects.add(currentObjects.size());

			dispatchTask(currentObjects, pushedObjects, database, writerThreads);

			currentObjects.removeAll(100, 100);
		}
	}

	if (currentObjects.size()) {
		pushedObjects.add(currentObjects.size());

		dispatchTask(currentObjects, pushedObjects, database, writerThreads);
	}

	while (pushedObjects > 0) {
		Thread::sleep(100);
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
		"\todb3 dumpdb <database> <threads> \n"
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
