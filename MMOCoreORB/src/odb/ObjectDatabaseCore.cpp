/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/managers/object/ObjectManager.h"

#include "ObjectDatabaseCore.h"

ObjectDatabaseCore::ObjectDatabaseCore(Vector<String> arguments) : Core("log/odb3.log", LogLevel::LOG),
	Logger("ObjectDatabaseCore"), arguments(std::move(arguments)) {

	setLogLevel(LogLevel::LOG);
}

void ObjectDatabaseCore::initialize() {
	info("starting up ObjectDatabase..");

	Core::MANAGED_REFERENCE_LOAD = false;

	objectManager = new ObjectManager(false); //initialize databases but not the templates

	//DistributedObjectBroker* orb = DistributedObjectBroker::initialize("", 44230);
	//orb->setCustomObjectManager(new ObjectManager(false));
}

bool ObjectDatabaseCore::getJSONString(uint64 oid, ObjectDatabase* database, String& returnData) {
	ObjectInputStream objectData(1024);

	if (!database->getData(oid, &objectData)) {
		String className;

		if (Serializable::getVariable<String>(STRING_HASHCODE("_className"), &className, &objectData)) {
			UniqueReference<DistributedObjectPOD*> pod(Core::getObjectBroker()->createObjectPOD(className));

			if (pod == nullptr) {
				Logger::console.error("could not create pod object for class name " + className);

				return false;
			}

			pod->readObject(&objectData);

			nlohmann::json j;
			pod->writeJSON(j);

			nlohmann::json thisObject;
			thisObject[String::valueOf(oid).toCharArray()] = j;

			std::stringstream fullStream;
			fullStream << thisObject.dump() << "\n";

			returnData = fullStream.str().c_str();

			return true;
		}
	}

	return false;
}

void ObjectDatabaseCore::dispatchTask(const Vector<uint64>& currentObjects, AtomicInteger& pushedObjects, ObjectDatabase* database) {
	Core::getTaskManager()->executeTask([currentObjects, &pushedObjects, database]() {
			for (const auto& oid : currentObjects) {
				pushedObjects.decrement();

				String jsonString;

				if (getJSONString(oid, database, jsonString)) {
					std::cout << jsonString.toCharArray();
				}
			}
	}, "DumpJSONTask", "ODBThreads");
}

void ObjectDatabaseCore::dumpDatabaseToJSON(const String& databaseName) {
	auto databases = ObjectDatabaseManager::instance();
	auto database = databases->loadObjectDatabase(databaseName, false);

	if (!database) {
		error("invalid database " + databaseName);

		showHelp();

		return;
	}

	Core::getTaskManager()->initializeCustomQueue("ODBThreads", getIntArgument(2, 4));

	ObjectDatabaseIterator iterator(database);
	uint64 oid = 0;

	AtomicInteger pushedObjects = 0;

	Vector<uint64> currentObjects;
	constexpr static const int objectsPerTask = 5;

	while (iterator.getNextKey(oid)) {
		currentObjects.emplace(oid);

		if (currentObjects.size() >= objectsPerTask) {
			pushedObjects.add(currentObjects.size());

			dispatchTask(currentObjects, pushedObjects, database);

			currentObjects.removeAll(100, 100);
		}
	}

	if (currentObjects.size()) {
		pushedObjects.add(currentObjects.size());

		dispatchTask(currentObjects, pushedObjects, database);
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

	String json;
	if (getJSONString(objectID, database, json)) {
		std::cout << json.toCharArray();
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

		StackTrace::setBinaryName("odb3");

		ObjectDatabaseCore core(std::move(arguments));

		core.start();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}
