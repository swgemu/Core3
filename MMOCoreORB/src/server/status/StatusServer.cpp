/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "StatusServer.h"
#include "StatusHandler.h"

StatusServer::StatusServer(ConfigManager* conf, ZoneServer* server)
		: StreamServiceThread("StatusServer") {
	zoneServer = server;
	configManager = conf;
	statusHandler = new StatusHandler(this);

	lastStatus = true;

	statusInterval = configManager->getStatusInterval();

	signal(SIGPIPE, SIG_IGN);
	
	setLogging(false);
}

StatusServer::~StatusServer() {
	delete statusHandler;
}

void StatusServer::init() {
	timestamp.updateToCurrentTime();
	lastStatus = true;

	setHandler(statusHandler);

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

	try {
		sock->send(pack);
	} catch (...) {
	}

	sock->close();
	delete sock;

	delete pack;

	Thread::sleep(100);

	return NULL;
}

Packet* StatusServer::getStatusXMLPacket() {
	Packet* pack = new Packet();

	StringBuffer str;
	str << "<?xml version=\"1.0\" standalone=\"yes\"?>" << endl;
	str << "<zoneServer>" << endl;

	if ((lastStatus = testZone())) {
		str << "<name>" << zoneServer->getGalaxyName() << "</name>" << endl;
		str << "<status>up</status>" << endl;
		str << "<users>" << endl;
		str << "<connected>" << zoneServer->getConnectionCount() << "</connected>" << endl;
		str << "<cap>" << zoneServer->getServerCap() << "</cap>" << endl;
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

	if (timestamp.miliDifference() < (statusInterval * 1000)) {
		return lastStatus;
	}

	timestamp.updateToCurrentTime();

	return true;
}
