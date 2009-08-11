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
#include "db/ForumsDatabase.h"

#include "login/LoginServer.h"

#include "features/Features.h"

#include "ping/PingServer.h"

//#include "status/StatusServer.h"

#include "zone/ZoneServer.h"

#include "zone/managers/object/ObjectManager.h"

#include "zone/objects/creature/CreatureObject.h"


ZoneServer* ServerCore::zoneServer = NULL;

ServerCore::ServerCore() : Core("log/core3.log"), Logger("Core") {
	orb = NULL;

	loginServer = NULL;
	zoneServer = NULL;
	//statusServer = NULL;
	pingServer = NULL;
	forumDatabase = NULL;
	database = NULL;

	features = NULL;
}

void ServerCore::init() {
	info("starting up server..");

	processConfig();

	try {

		database = new ServerDatabase(&configManager);

		if (configManager.getUseVBIngeration() == 1)
			forumDatabase = new ForumsDatabase(&configManager);

		if (configManager.getMakeZone()) {
			String& orbaddr = configManager.getORBNamingDirectoryAddress();
			orb = DistributedObjectBroker::initialize(orbaddr);
		}

		if (configManager.getMakeLogin()) {
			loginServer = new LoginServer(&configManager);
		}

		if (configManager.getMakeZone()) {
			zoneServer = new ZoneServer(configManager.getZoneProcessingThreads(), configManager.getZoneGalaxyID());
			zoneServer->deploy("ZoneServer");
		}

		/*if (configManager.getMakeStatus()) {
			statusServer = new StatusServer(&configManager, zoneServer);
		}*/

		if (configManager.getMakePing()) {
			pingServer = new PingServer();
		}

	} catch (ServiceException& e) {
		shutdown();
	} catch (DatabaseException& e) {
		info(e.getMessage());

		exit(1);
	}
}

void ServerCore::run() {
	if (loginServer != NULL) {
		int loginPort = configManager.getLoginPort();
		int loginAllowedConnections = configManager.getLoginAllowedConnections();

		loginServer->start(loginPort, loginAllowedConnections);
	}

	if (zoneServer != NULL) {
		int zoneAllowedConnections = configManager.getZoneAllowedConnections();

		zoneServer->start(44463, zoneAllowedConnections);
	}

	/*if (statusServer != NULL) {
		int statusPort = configManager.getStatusPort();
		int statusAllowedConnections = configManager.getStatusAllowedConnections();

		statusServer->start(statusPort);
	}*/

	if (pingServer != NULL) {
		int pingPort = configManager.getPingPort();
		int pingAllowedConnections = configManager.getPingAllowedConnections();

		pingServer->start(pingPort, pingAllowedConnections);
	}

	info("initialized", true);

	handleCommands();

	shutdown();
}

void ServerCore::shutdown() {
	info("shutting down server..");

	/*if (statusServer != NULL) {
		statusServer->stop();

		delete statusServer;
		statusServer = NULL;
	}*/

	if (zoneServer != NULL) {
		zoneServer->stop();
		zoneServer->finalize();

		zoneServer = NULL;
	}

	if (loginServer != NULL) {
		loginServer->stop();

		delete loginServer;
		loginServer = NULL;
	}

	if (pingServer != NULL) {
		pingServer->stop();

		delete pingServer;
		pingServer = NULL;
	}

	if (database != NULL) {
		delete database;
		database = NULL;
	}

	if (forumDatabase != NULL) {
		delete forumDatabase;
		forumDatabase = NULL;
	}

	if (features != NULL) {
		delete features;
		features = NULL;
	}

	DistributedObjectBroker::finalize();

	info("server closed");
}

void ServerCore::handleCommands() {
	while (true) {
		try {
			String command;

			Thread::sleep(500);

			System::out << "> ";

			char line[4096];
			gets(line);

			command = line;

			if (command == "exit") {
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

				/*SceneObject* object = ObjectManager::instance()->createObject(0xA4ADAAE6);
				String data;
				object->serialize(data);
				System::out << data << "\n";
				object->deSerialize(data);
				data = "";
				object->serialize(data);
				System::out << data;
				object->finalize();*/
				/*String name;
				object->getFullObjectName(name);

				System::out << "objectCRC : " << name << "\n";*/

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
		} catch (...) {
			System::out << "[ServerCore] unreported Exception caught\n";
		}
	}
}

void ServerCore::processConfig() {
	if (!configManager.loadConfigData())
		info("missing config file.. loading default values\n");

	//if (!features->loadFeatures())
		//info("Problem occurred trying to load features.lua");
}
