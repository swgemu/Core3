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

#include "StatusServer.h"

#include "../zone/managers/item/ItemManager.h"

StatusServer::StatusServer(ConfigManager * conf, ZoneServer * server)
	: Thread(), Logger("StatusServer") {
	zoneServer = server;
	configManager = conf;

	setLogging(false);
}

StatusServer::~StatusServer() {
	obj->finalize();
}

void StatusServer::init() {
	timestamp = time(NULL);
	lastStatus = true;

	if (zoneServer != NULL) {
		oid = zoneServer->getItemManager()->getNextStaticObjectID();
		obj = new Attachment(oid, 1);
	}
}

Packet * StatusServer::getStatusXMLPacket() {
	Packet * p = new Packet();

	stringstream ss;
	ss << "<?xml version=\"1.0\" standalone=\"yes\"?>" << endl;
	ss << "<zoneServer>" << endl;
	if(lastStatus = testZone()) {
		ss << "<name>" << zoneServer->getServerName() << "</name>";
		ss << "<status>up</status>" << endl;
		ss << "<users>" << endl;
		ss << "<connected>" << zoneServer->getConnectionCount() << "</connected>" << endl;
		ss << "<max>" << zoneServer->getMaxPlayers() << "</max>" << endl;
		ss << "<total>" << zoneServer->getTotalPlayers() << "</total>" << endl;
		ss << "<deleted>" << zoneServer->getDeletedPlayers() << "</deleted>" << endl;
		ss << "</users>" << endl;
		ss << "<uptime>" << time(NULL) - zoneServer->getStartTimestamp() << "</uptime>" << endl;
	} else
		ss << "<status>down</status>";
	ss << "<timestamp>" << timestamp << "</timestamp>" << endl;
	ss << "</zoneServer>" << endl;


	string xml = ss.str();

	p->insertStream(xml.c_str(), xml.length());

	return p;
}

bool StatusServer::testZone() {

	if(zoneServer == NULL)
		return false;

	if (time(NULL) - timestamp < configManager->getStatusInterval()) {
		return lastStatus;
	}

	timestamp = time(NULL);

	try {
		zoneServer->addObject(obj);
		return (zoneServer->removeObject(oid) == obj);
	} catch (...) {
		return false;
	}
}

void StatusServer::run() {
	TCPServerSocket * socket = NULL;

	try {
		init();

		socket = new TCPServerSocket(new SocketAddress(configManager->getStatusPort()));

		socket->listen(configManager->getStatusAllowedConnections());
	} catch (Exception& e) {
		error("failed to initialize");
		error(e.getMessage());
		return;
	} catch (...) {
		error("failed to initialize");
		return;
	}

	info("initialized", true);

	while (true) {
		try {
			Socket * s = socket->accept();
			s->send(getStatusXMLPacket());
			s->close();

			delete(s);
		} catch (SocketException& e) {
			info("socket exception caught");
			info(e.getMessage());
		} catch (...) {
			info("unreported exception caught");
		}

		sleep(1);
	}
}
