/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERCORE_H_
#define SERVERCORE_H_

#include "engine/engine.h"

namespace server {
	namespace zone{
		class ZoneServer;
	}
}

using namespace server::zone;

#include "server/login/LoginServer.h"

namespace conf {
	class ConfigManager;
}

using namespace conf;

class ServerDatabase;
class MantisDatabase;
class StatusServer;
class Features;
class PingServer;

namespace server {
 namespace web {
 	 class WebServer;
 }
}

namespace engine {
	namespace core {
		class MetricsManager;
	}
}

using namespace server::web;

class ServerCore : public Core, public Logger {
	ConfigManager* configManager;

	ServerDatabase* database;

	MantisDatabase* mantisDatabase;

	DistributedObjectBroker* orb;

	ManagedReference<server::login::LoginServer*> loginServer;

	StatusServer* statusServer;

	Features* features;

	PingServer* pingServer;

	WebServer* webServer;

	MetricsManager* metricsManager;

	Mutex shutdownBlockMutex;
	Condition waitCondition;

	static SortedVector<String> arguments;

	static ManagedReference<server::zone::ZoneServer*> zoneServerRef;

	static bool truncateAllData;

	static ServerCore* instance;

	bool handleCmds;

public:
	ServerCore(bool truncateDatabases, SortedVector<String>& args);

	void initialize();

	void run();

	void shutdown();

	void handleCommands();

	void processConfig();

	void signalShutdown();

	// getters
	static server::zone::ZoneServer* getZoneServer() {
		return zoneServerRef.get();
	}

	static bool truncateDatabases() {
		return truncateAllData;
	}

	static ServerCore* getInstance() {
		return instance;
	}

	static bool hasArgument(const String& arg) {
		return arguments.contains(arg);
	}

};

#endif /*SERVERCORE_H_*/
