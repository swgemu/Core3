/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef STATUSSERVER_H_
#define STATUSSERVER_H_

#include "conf/ConfigManager.h"
#include "engine/engine.h"
#include "engine/service/StreamServiceThread.h"
#include "server/zone/ZoneServer.h"
#include "system/lang/Time.h"

class StatusHandler;
namespace conf {
class ConfigManager;
}  // namespace conf
namespace engine {
namespace service {
class ServiceClient;
}  // namespace service
}  // namespace engine
namespace server {
namespace zone {
class ZoneServer;
}  // namespace zone
}  // namespace server
namespace sys {
namespace net {
class Packet;
class Socket;
class SocketAddress;
}  // namespace net
}  // namespace sys

class StatusServer: public StreamServiceThread {
	ZoneServer* zoneServer;
	StatusHandler* statusHandler;

	ConfigManager* configManager;

	unsigned int statusInterval;

	Time timestamp;
	bool lastStatus;

public:
	StatusServer(ConfigManager* conf, ZoneServer * server);

	~StatusServer();

	void init();

	void run();

	void shutdown();

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr);

	Packet* getStatusXMLPacket();

	bool testZone();
};

#endif /* STATUSSERVER_H_ */
