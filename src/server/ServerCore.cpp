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

#include "zone/ZoneServerImplementation.h"

#include "zone/objects.h"

#include "zone/managers/combat/CombatManager.h"
#include "zone/managers/player/ProfessionManager.h"
#include "zone/managers/radial/RadialManager.h"
#include "zone/managers/group/GroupManager.h"

ServerCore::ServerCore() : Logger("Core") {
	orb = NULL;

	lserv = NULL;
	zserv = NULL;
}

void ServerCore::init() {
	info("starting up server..");

	processConfig();
	
	try {
		database = new ServerDatabase(&configManager);
		
		if (configManager.getMakeZone()) {
			string& orbaddr = configManager.getORBNamingDirectoryAddress();
			orb = ObjectRequestBroker::initialize(orbaddr);
		}
		
		if (configManager.getMakeLogin()) {		
			lserv = new LoginServer();
		}

		if (configManager.getMakeZone()) {
			zserv = new ZoneServerImplementation(configManager.getZoneProcessingThreads());
			orb->deploy("ZoneServer", zserv);
		}
	} catch (ServiceException& e) {
		shutdown();
	} catch (DatabaseException& e) {
		info(e.getMessage());
		
		exit(1);
	}
}

void ServerCore::run() {
	if (lserv != NULL) {
		int loginPort = configManager.getLoginPort(); 
		int loginAllowedConnections = configManager.getLoginAllowedConnections();

		lserv->start(loginPort, loginAllowedConnections);
	}
	
	if (zserv != NULL) {
		int zoneAllowedConnections = configManager.getZoneAllowedConnections(); 

		zserv->start(44463, zoneAllowedConnections);
	}
	
	info("initialized", true);
	
	handleCommands();
	
	shutdown();
}

void ServerCore::shutdown() {
	info("shutting down server..");

	if (zserv != NULL) {
		zserv->stop();
		
		zserv = NULL;
	}
	
	if (lserv != NULL) {
		lserv->stop();
		
		delete lserv;
		lserv = NULL;
	}
	
	ObjectRequestBroker::finalize();
	
	delete database;
	
	info("server closed");
}

void ServerCore::handleCommands() {
	while (true) {
		try {
			string command;
	
			Thread::sleepMili(500);
		
			cout << "> ";
			cin >> command;
		
			if (command == "exit") {
				return;
			} else if (command == "dumpmem") {
				#ifdef DEBUG_MEMORY	
					DumpUnfreed(TRUE);
				#endif
			} else if (command == "logQuadTree") {
				QuadTree::setLogging(!QuadTree::doLog());
			} else if (command == "info") {
				if (lserv != NULL)
					lserv->printInfo();
					
				if (zserv != NULL)
					zserv->printInfo();
			} else if (command == "icap") {
				if (zserv != NULL)
					zserv->changeUserCap();
			} else if (command == "dcap") {
				if (zserv != NULL)
					zserv->changeUserCap(-50);
			} else if (command == "fixQueue") {
				if (zserv != NULL)
					zserv->fixScheduler();
			} else if (command == "crash") {
				zserv = NULL;
				
				zserv->fixScheduler();
			} else if (command == "help") { 
				cout << "available commands:\n"; 
				cout << "\texit, logQuadTree, info, icap, dcap, fixQueue, crash, about.\n"; 			
			} else if (command == "about") {
				cout << "Core3 Uber Edition. Ultyma pwns you.\n";
			} else
				cout << "unknown command (" << command << ")\n";
		} catch (SocketException& e) {
			cout << "[ServerCore] " << e.getMessage();
		} catch (ArrayIndexOutOfBoundsException& e) {
			cout << "[ServerCore] " << e.getMessage() << "\n";
		} catch (...) {
			cout << "[ServerCore] unreported Exception caught\n";
		}
	}
}

void ServerCore::processConfig() {
	if (!configManager.loadConfigData())
		info("missing config file.. loading default values\n");
}
