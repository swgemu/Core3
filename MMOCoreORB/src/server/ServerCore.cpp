/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "ServerCore.h"

#include "db/ServerDatabase.h"

#include "db/MantisDatabase.h"

#include "chat/ChatManager.h"

#include "login/LoginServer.h"

#include "features/Features.h"

#include "ping/PingServer.h"

#include "status/StatusServer.h"

#include "web/WebServer.h"

#include "zone/ZoneServer.h"

#include "zone/managers/object/ObjectManager.h"

#include "zone/objects/creature/CreatureObject.h"

ManagedReference<ZoneServer*> ServerCore::zoneServerRef = NULL;

ServerCore::ServerCore() : Core("log/core3.log"), Logger("Core") {
	orb = NULL;

	loginServer = NULL;
	zoneServerRef = NULL;
	statusServer = NULL;
	pingServer = NULL;
	webServer = NULL;
	database = NULL;

	configManager = ConfigManager::instance();

	features = NULL;
}

class ZoneStatisticsTask : public Task {
	ManagedReference<ZoneServer*> zoneServer;

public:
	ZoneStatisticsTask(ZoneServer* server) {
		zoneServer = server;
	}

	void run() {
		zoneServer->printInfo(true);
	}
};

void ServerCore::initialize() {
	info("starting up server..");

	processConfig();

	try {
		database = new ServerDatabase(configManager);

		mantisDatabase = new MantisDatabase(configManager);

		String& orbaddr = configManager->getORBNamingDirectoryAddress();
		orb = DistributedObjectBroker::initialize(orbaddr, 44436);

		orb->setCustomObjectManager(ObjectManager::instance());

		if (configManager->getMakeLogin()) {
			loginServer = new LoginServer(configManager);
			loginServer->deploy("LoginServer");
		}

		if (configManager->getMakeZone()) {
			ZoneServer* zoneServer = new ZoneServer(configManager);
			zoneServer->deploy("ZoneServer");

			zoneServerRef = zoneServer;
		}

		if (configManager->getMakePing()) {
			pingServer = new PingServer();
		}

		if (configManager->getMakeStatus()) {
			statusServer = new StatusServer(configManager, zoneServerRef);
		}

		if (configManager->getMakeWeb()) {
			webServer = WebServer::instance();
		}

		ZoneServer* zoneServer = zoneServerRef.get();

		if (loginServer != NULL) {
			int loginPort = configManager->getLoginPort();
			int loginAllowedConnections = configManager->getLoginAllowedConnections();

			loginServer->start(loginPort, loginAllowedConnections);
		}

		if (zoneServer != NULL) {
			int zonePort = 44463;
			int zoneAllowedConnections = configManager->getZoneAllowedConnections();

			ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
			dbManager->loadDatabases();

			int galaxyID = configManager->getZoneGalaxyID();

			String query = "SELECT port FROM galaxy WHERE galaxy_id = " + String::valueOf(galaxyID);
			ResultSet* result = database->instance()->executeQuery(query);

			if (result != NULL && result->next()) {
				zonePort = result->getInt(0);
				delete result;
			}

			zoneServer->start(zonePort, zoneAllowedConnections);
		}

		if (statusServer != NULL) {
			int statusPort = configManager->getStatusPort();
			int statusAllowedConnections = configManager->getStatusAllowedConnections();

			statusServer->start(statusPort);
		}

		if (webServer != NULL) {
			webServer->start(configManager);
		}

		if (pingServer != NULL) {
			int pingPort = configManager->getPingPort();
			int pingAllowedConnections = configManager->getPingAllowedConnections();

			pingServer->start(pingPort, pingAllowedConnections);
		}

	#ifndef WITH_STM
		ObjectManager::instance()->scheduleUpdateToDatabase();
	#else
		Task* statiscticsTask = new ZoneStatisticsTask(zoneServerRef);
		statiscticsTask->schedulePeriodic(1000, 1000);
	#endif

		info("initialized", true);
	} catch (ServiceException& e) {
		shutdown();
	} catch (DatabaseException& e) {
		info(e.getMessage());

		exit(1);
	}
}

void ServerCore::run() {
	handleCommands();

	shutdown();
}

void ServerCore::shutdown() {
	info("shutting down server..");

	ObjectManager::instance()->cancelUpdateModifiedObjectsTask();
	ObjectDatabaseManager::instance()->checkpoint();

	info("database checkpoint done", true);

	if (statusServer != NULL) {
		statusServer->stop();

		delete statusServer;
		statusServer = NULL;
	}

	if (webServer != NULL) {
		webServer->stop();

		delete webServer;
		webServer = NULL;
	}

	ZoneServer* zoneServer = zoneServerRef.get();

	if (zoneServer != NULL) {
		zoneServer->stop();
		//zoneServer->finalize();

		zoneServer = NULL;
	}

	if (loginServer != NULL) {
		loginServer->stop();

		loginServer = NULL;
	}

	if (pingServer != NULL) {
		pingServer->stop();

		delete pingServer;
		pingServer = NULL;
	}

	if (features != NULL) {
		delete features;
		features = NULL;
	}

	if (database != NULL) {
		delete database;
		database = NULL;
	}

	if (mantisDatabase != NULL) {
		delete mantisDatabase;
		mantisDatabase = NULL;
	}

	zoneServerRef = NULL;

	info("server closed");

	//exit(1);
}

void ServerCore::handleCommands() {
	while (true) {
		try {
			String command;

			Thread::sleep(500);

			System::out << "> ";

			char line[256];
			fgets(line, sizeof(line), stdin);

			command = line;
			command = command.replaceFirst("\n", "");

			ZoneServer* zoneServer = zoneServerRef.getForUpdate();

			if (command == "exit") {
				if (zoneServer != NULL) {
					ChatManager* chatManager = zoneServer->getChatManager();
					chatManager->broadcastGalaxy(NULL, "Server is shutting down NOW!");
				}

				return;
			} else if (command == "dumpmem") {
				#ifdef DEBUG_MEMORY
					DumpUnfreed(TRUE);
				#endif
			} else if (command == "logQuadTree") {
				QuadTree::setLogging(!QuadTree::doLog());
			} else if (command == "info") {
				//TaskManager::instance()->printInfo();

				if (loginServer != NULL)
					loginServer->printInfo();

				if (zoneServer != NULL)
					zoneServer->printInfo(true);

				if (pingServer != NULL)
					pingServer->printInfo();
			} else if (command == "lock") {
				if (zoneServer != NULL)
					zoneServer->setServerStateLocked();
			} else if (command == "unlock") {
				if (zoneServer != NULL)
					zoneServer->setServerStateOnline();
			} else if (command == "icap") {
				if (zoneServer != NULL)
					zoneServer->changeUserCap(50);
			} else if (command == "dcap") {
				if (zoneServer != NULL)
					zoneServer->changeUserCap(-50);
			} else if (command == "fixQueue") {
				if (zoneServer != NULL)
					zoneServer->fixScheduler();
			} else if (command == "crash") {
				zoneServer = NULL;

				zoneServer->fixScheduler();
			} else if (command == "save") {
				ObjectManager::instance()->updateModifiedObjectsToDatabase(true);
				//ObjectDatabaseManager::instance()->checkpoint();
			} else if (command == "help") {
				System::out << "available commands:\n";
				System::out << "\texit, logQuadTree, info, icap, dcap, fixQueue, crash, about.\n";
			} else if (command == "about") {
				System::out << "Core3 Uber Edition. Ultyma pwns you.\n";
			} else
				System::out << "unknown command (" << command << ")\n";
		} catch (SocketException& e) {
			System::out << "[ServerCore] " << e.getMessage();
		} catch (ArrayIndexOutOfBoundsException& e) {
			System::out << "[ServerCore] " << e.getMessage() << "\n";
		} catch (Exception& e) {
			System::out << "[ServerCore] unreported Exception caught\n";
		}

	#ifdef WITH_STM
		try {
			TransactionalMemoryManager::commitPureTransaction();
		} catch (const TransactionAbortedException& e) {
		}
	#endif
	}
}

void ServerCore::processConfig() {
	if (!configManager->loadConfigData())
		info("missing config file.. loading default values\n");

	//if (!features->loadFeatures())
		//info("Problem occurred trying to load features.lua");
}
