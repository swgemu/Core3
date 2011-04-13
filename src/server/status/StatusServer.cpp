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
#include "StatusHandler.h"
//#include "../zone/managers/item/ItemManager.h"

StatusServer::StatusServer(ConfigManager* conf, ZoneServer* server)
		: StreamServiceThread("StatusServer") {
	zoneServer = server;
	configManager = conf;
	statusHandler = new StatusHandler(this);

	statusInterval = configManager->getStatusInterval();

	setLogging(false);
}

StatusServer::~StatusServer() {
	//obj->finalize();
}

void StatusServer::init() {
	timestamp.updateToCurrentTime();
	lastStatus = true;

	setHandler(statusHandler);

	if (zoneServer != NULL) {
		//oid = zoneServer->getItemManager()->getNextStaticObjectID();
		//obj = new Attachment(oid, 0, "", "", 1);
	}

	info("initialized", true);
}

void StatusServer::run() {
	acceptConnections();

	shutdown();
}

void StatusServer::shutdown() {
}

ServiceClient* StatusServer::createConnection(Socket* sock, SocketAddress& addr) {
	Packet* pack = getStatusXMLPacket();

	sock->send(pack);

	sock->close();
	delete sock;

	delete pack;

	Thread::sleep(100);

	return NULL;
}

Packet* StatusServer::getStatusXMLPacket() {
	Packet* pack = new Packet();

	timestamp.updateToCurrentTime();

	StringBuffer str;
	str << "<?xml version=\"1.0\" standalone=\"yes\"?>" << endl;
	str << "<zoneServer>" << endl;

	if ((lastStatus = testZone())) {
		str << "<name>" << zoneServer->getServerName() << "</name>" << endl;
		str << "<status>up</status>" << endl;
		str << "<users>" << endl;
		str << "<connected>" << zoneServer->getConnectionCount() << "</connected>" << endl;
		str << "<max>" << zoneServer->getMaxPlayers() << "</max>" << endl;
		str << "<total>" << zoneServer->getTotalPlayers() << "</total>" << endl;
		str << "<deleted>" << zoneServer->getDeletedPlayers() << "</deleted>" << endl;
		str << "</users>" << endl;
		str << "<uptime>" << zoneServer->getStartTimestamp()->miliDifference(timestamp) / 1000 << "</uptime>" << endl;
	} else
		str << "<status>down</status>";

	str << "<timestamp>" << timestamp.getMiliTime() << "</timestamp>" << endl;
	str << "</zoneServer>" << endl;

	String xml = str.toString();
	pack->insertStream(xml.toCharArray(), xml.length());

	return pack;
}

bool StatusServer::testZone() {
	if (zoneServer == NULL)
		return false;

	if (-timestamp.miliDifference() < statusInterval) {
		return lastStatus;
	}

	timestamp.updateToCurrentTime();

	/*try {
		zoneServer->addObject(obj);

		return zoneServer->removeObject(oid) == obj;
	} catch (...) {
		return false;
	}*/

	return true;
}
