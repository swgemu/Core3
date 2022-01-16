/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERCORE_H_
#define SERVERCORE_H_

#include "engine/engine.h"
#include "system/lang/Function.h"
#include "system/io/Pipe.h"

#include "server/features/Features.h"

#include "server/login/LoginServer.h"
#ifdef WITH_SESSION_API
#include "server/login/SessionAPIClient.h"
#endif // WITH_SESSION_API
#include "server/ping/PingServer.h"

namespace server {
	namespace zone {
		class ZoneServer;
	}
}

namespace conf {
	class ConfigManager;
}

class ServerDatabase;
class MantisDatabase;
class StatusServer;

#ifdef WITH_REST_API
namespace server {
 namespace web3 {
 	class RESTServer;
 }
}
#endif // WITH_REST_API

namespace engine {
	namespace core {
		class MetricsManager;
	}
}

class ServerCore : public Core, public Logger {
	Pipe consoleCommandPipe;
	conf::ConfigManager* configManager;
	ServerDatabase* database;
	MantisDatabase* mantisDatabase;
	DistributedObjectBroker* orb;
	Reference<server::login::LoginServer*> loginServer;
	Reference<StatusServer*> statusServer;
	server::features::Features* features;
	Reference<PingServer*> pingServer;
	MetricsManager* metricsManager;
#ifdef WITH_REST_API
	server::web3::RESTServer* restServer;
#endif // WITH_REST_API
#ifdef WITH_SESSION_API
	Reference<server::login::SessionAPIClient*> sessionAPIClient;
#endif // WITH_SESSION_API

	Mutex shutdownBlockMutex;
	Condition waitCondition;

public:
	enum CommandResult {
		SUCCESS = 0,
		ERROR = 1,
		SHUTDOWN,
		NOTFOUND
	};

	enum ShutdownFlags {
		DEFAULT   = 0,
		FAST      = 1<<1,
		DUMP_JSON = 1<<2,
	};

private:
	ShutdownFlags nextShutdownFlags = ShutdownFlags::DEFAULT;

	using CommandFunctionType = Function<CommandResult(const String & arguments)>;

	VectorMap<String, CommandFunctionType> consoleCommands;

	bool handleCmds;

	static SortedVector<String> arguments;
	static ManagedReference<server::zone::ZoneServer*> zoneServerRef;
	static bool truncateAllData;
	static ServerCore* instance;

	void registerConsoleCommmands();
	CommandResult processConsoleCommand(const String& commandString);

public:
	ServerCore(bool truncateDatabases, const SortedVector<String>& args);
	~ServerCore();

	void initialize() override;
	void initializeCoreContext();

	void finalizeContext() override;

	void run() override;

	void shutdown();
	void queueConsoleCommand(const String& commandString);
	void handleCommands();
	void processConfig();
	void signalShutdown(ShutdownFlags flags = ShutdownFlags::DEFAULT);

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

	static Logger& logger() {
		return *instance;
	}

	static bool hasArgument(const String& arg) {
		return arguments.contains(arg);
	}

	static int getSchemaVersion();
};

#endif /*SERVERCORE_H_*/
