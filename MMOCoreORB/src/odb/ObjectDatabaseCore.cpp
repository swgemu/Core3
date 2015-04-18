/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/managers/object/ObjectManager.h"

#include "ObjectDatabaseCore.h"

ObjectDatabaseCore::ObjectDatabaseCore() : Core("log/odb3.log"), Logger("ObjectDatabaseCore") {
	setInfoLogLevel();
}

void ObjectDatabaseCore::initialize() {
	info("starting up ObjectDatabase..");

	DistributedObjectBroker* orb = DistributedObjectBroker::initialize("", 44440);

	orb->setCustomObjectManager(ObjectManager::instance());

}

void ObjectDatabaseCore::run() {
	info("initialized", true);
}

int main(int argc, char* argv[]) {
	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		StackTrace::setBinaryName("odb3");

		ObjectDatabaseCore core;

		core.start();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}
