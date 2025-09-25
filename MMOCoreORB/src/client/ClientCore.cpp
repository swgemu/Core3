/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "client/zone/Zone.h"
#include "client/zone/managers/object/ObjectManager.h"

#include "ClientCore.h"

#include "client/login/LoginSession.h"

ClientCore::ClientCore(int instances) : Core("log/core3client.log", "client3"), Logger("CoreClient") {
	ClientCore::instances = instances;

	// Load config and set log level
	Core::initializeProperties("Client3");
	int logLevel = Core::getIntProperty("Client3.LogLevel", 1);
	setLogLevel(static_cast<LogLevel>(logLevel));
}

void ClientCore::initialize() {
	info(true) << __PRETTY_FUNCTION__ << " start";
}

void ClientCore::run() {
	for (int i = 0; i < instances; ++i) {
		zones.add(nullptr);
	}

	info(true) << "initialized";

	if (!loginCharacter(0)) {
		info(true) << "Failed to login character.";
		return;
	}

	info(true) << "Waiting for zone connection...";

	Zone* zone = zones.get(0);
	if (zone != nullptr && zone->waitForSceneReady()) {
		info(true) << "Zone connection established and scene loaded!";
		info(true) << "Login flow test completed successfully!";
	} else {
		info(true) << "Timeout waiting for zone connection";
	}

	info(true) << "Shutting down...";

	for (int i = 0; i < instances; ++i) {
		logoutCharacter(i);
	}
}

bool ClientCore::loginCharacter(int index) {
	try {
		String username, password;

		// Get credentials from environment variables
		const char* envUser = getenv("CORE3_CLIENT_USERNAME");
		const char* envPass = getenv("CORE3_CLIENT_PASSWORD");

		if (envUser && envPass) {
			username = envUser;
			password = envPass;
			info(true) << "Logging in as: " << username;
		} else {
			info(true) << "ERROR: Please set CORE3_CLIENT_USERNAME and CORE3_CLIENT_PASSWORD environment variables";
			return false;
		}

		Zone* zone = zones.get(index);
		if (zone != nullptr)
			return false;

		Reference<LoginSession*> loginSession = new LoginSession(index, username, password);
		loginSession->run();

		auto numCharacters = loginSession->getCharacterListSize();

		if (numCharacters == 0) {
			info(true) << __FUNCTION__ << ": No characters found to login?";
			return false;
		}

		uint32 selectedCharacter = System::random(numCharacters - 1);

		const CharacterListEntry& character = loginSession->getCharacterByIndex(selectedCharacter);
		auto objid = character.getObjectID();
		auto galaxyId = character.getGalaxyID();

		info(true) << "Login[" << selectedCharacter << "]: " << character;

		uint32 acc = loginSession->getAccountID();
		const String& sessionID = loginSession->getSessionID();

		info(true) << "Login completed - Account: " << acc << ", Session: " << sessionID;

		auto& galaxy = loginSession->getGalaxy(galaxyId);

		info(true) << "Zone into " << galaxy;

		if (galaxy.getAddress().isEmpty()) {
			throw Exception("Invalid galaxy, missing IP address.");
		}

		zone = new Zone(index, objid, acc, sessionID, galaxy.getAddress(), galaxy.getPort());
		zone->start();
		zones.set(index, zone);
	} catch (Exception& e) {
		e.printMessage();
		return false;
	}

	return true;
}

void ClientCore::logoutCharacter(int index) {
	Zone* zone = zones.get(index);
	if (zone == nullptr || !zone->isStarted())
		return;

	info(true) << __FUNCTION__ << "(" << index << ")";

	zones.set(index, nullptr);

	zone->disconnect();

	delete zone;
}

void ClientCore::handleCommands() {
	// Disabled for now
}

int main(int argc, char* argv[]) {
	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		StackTrace::setBinaryName("core3client");

		int instances = 1;

		if (argc > 1)
			instances = Integer::valueOf(arguments.get(0));

		// Configure engine3
		Core::setProperty("TaskManager.defaultSchedulerThreads", "2");
		Core::setProperty("TaskManager.defaultIOSchedulers", "2");
		Core::setProperty("TaskManager.defaultWorkerQueues", "1");
		Core::setProperty("TaskManager.defaultWorkerThreadsPerQueue", "2");

		ClientCore core(instances);

		core.start();
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}
