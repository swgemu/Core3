/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "ServerCore.h"

#include <type_traits>

#include "db/MySqlDatabase.h"
#include "db/ServerDatabase.h"
#include "db/MantisDatabase.h"

#include "server/chat/ChatManager.h"
#include "server/login/LoginServer.h"
#include "ping/PingServer.h"
#include "status/StatusServer.h"
#include "web/WebServer.h"
#include "web/RESTServer.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/frs/FrsManager.h"

#include "server/zone/QuadTree.h"

#include "engine/core/MetricsManager.h"

ManagedReference<ZoneServer*> ServerCore::zoneServerRef = nullptr;
SortedVector<String> ServerCore::arguments;
bool ServerCore::truncateAllData = false;
ServerCore* ServerCore::instance = nullptr;

ServerCore::ServerCore(bool truncateDatabases, const SortedVector<String>& args) :
		Core("log/core3.log", "core3engine", LogLevel::LOG), Logger("Core") {
	orb = nullptr;

	loginServer = nullptr;
	zoneServerRef = nullptr;
	statusServer = nullptr;
	pingServer = nullptr;
	webServer = nullptr;
	database = nullptr;
	mantisDatabase = nullptr;
	restServer = nullptr;

	truncateAllData = truncateDatabases;
	arguments = args;

	instance = this;

	setLogLevel(Logger::INFO);

	configManager = ConfigManager::instance();
	metricsManager = MetricsManager::instance();

	features = nullptr;

	handleCmds = true;

	initializeCoreContext();
}

void ServerCore::registerConsoleCommmands() {
	debug() << "registering console commands...";

	consoleCommands.setNoDuplicateInsertPlan();

	consoleCommands.put("exit", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr) {
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->broadcastGalaxy(nullptr,
					"Server is shutting down NOW!");
		}

		return SHUTDOWN;
	});

	consoleCommands.put("logQuadTree", [this](const String& arguments) -> CommandResult {
		QuadTree::setLogging(!QuadTree::doLog());

		return SUCCESS;
	});

	consoleCommands.put("info", [this](const String& arguments) -> CommandResult {
		//TaskManager::instance()->printInfo();

		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (loginServer != nullptr)
			loginServer->printInfo();

		if (zoneServer != nullptr)
			zoneServer->printInfo();

		if (pingServer != nullptr)
			pingServer->printInfo();

		return SUCCESS;
	});

	consoleCommands.put("lock", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr)
			zoneServer->setServerStateLocked();

		return SUCCESS;
	});

	consoleCommands.put("unlock", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr)
			zoneServer->setServerStateOnline();

		return SUCCESS;
	});

	consoleCommands.put("icap", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr)
			zoneServer->changeUserCap(50);

		return SUCCESS;
	});

	consoleCommands.put("dcap", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr)
			zoneServer->changeUserCap(-50);

		return SUCCESS;
	});

	consoleCommands.put("fixQueue", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr)
			zoneServer->fixScheduler();

		return SUCCESS;
	});

	consoleCommands.put("save", [this](const String& arguments) -> CommandResult {
		ObjectManager::instance()->createBackup();
		//ObjectDatabaseManager::instance()->checkpoint();

		return SUCCESS;
	});

	consoleCommands.put("help", [this](const String& arguments) -> CommandResult {
		System::out << "available commands: ";

		for (const auto& entry : consoleCommands) {
			System::out << entry.getKey() << "  ";
		}

		System::out << endl;

		return SUCCESS;
	});

	consoleCommands.put("chars", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();
		uint32 num = 0;

		try {
			num = UnsignedInteger::valueOf(arguments);
		} catch (const Exception& e) {
			System::out << "invalid noumber of concurrent chars per account specified" << endl;

			return ERROR;
		}

		if (num != 0) {
			PlayerManager* pMan = zoneServer->getPlayerManager();
			pMan->setOnlineCharactersPerAccount(num);

			System::out << "changed max concurrent chars per account to: " << num << endl;
		}

		return SUCCESS;
	});

	consoleCommands.put("lookupcrc", [this](const String& arguments) -> CommandResult {
		uint32 crc = 0;
		try {
			crc = UnsignedInteger::valueOf(arguments);
		} catch (const Exception& e) {
			System::out << "invalid crc number expected dec";

			return ERROR;
		}

		if (crc != 0) {
			String file = TemplateManager::instance()->getTemplateFile(
					crc);

			System::out << "result: " << file << endl;
		}

		return SUCCESS;
	});

	consoleCommands.put("loglevel", [this](const String& arguments) -> CommandResult {
		int level = 0;
		try {
			level = Integer::valueOf(arguments);
		} catch (const Exception& e) {
			System::out << "invalid log level" << endl;

			return ERROR;
		}

		if (level >= Logger::NONE && level <= Logger::DEBUG) {
			Logger::setGlobalFileLogLevel(static_cast<Logger::LogLevel>(level));

			System::out << "global log level changed to: " << level << endl;
		}

		return SUCCESS;
	});

	consoleCommands.put("rev", [this](const String& arguments) -> CommandResult {
		System::out << ConfigManager::instance()->getRevision() << endl;

		return SUCCESS;
	});

	consoleCommands.put("broadcast", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServer != nullptr) {
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->broadcastGalaxy(nullptr, arguments);
		}

		return SUCCESS;
	});

	consoleCommands.put("shutdown", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();
		int minutes = 1;

		try {
			minutes = UnsignedInteger::valueOf(arguments);
		} catch (const Exception& e) {
			System::out << "invalid minutes number expected dec" << endl;

			return ERROR;
		}

		if (zoneServer != nullptr) {
			zoneServer->timedShutdown(minutes);

			shutdownBlockMutex.lock();

			waitCondition.wait(&shutdownBlockMutex);

			shutdownBlockMutex.unlock();
		}

		return SHUTDOWN;
	});

	consoleCommands.put("playercleanup", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServerRef != nullptr) {
			ZoneServer* server = zoneServerRef.get();

			if (server != nullptr)
				server->getPlayerManager()->cleanupCharacters();
		}

		return SUCCESS;
	});

	consoleCommands.put("playercleanupstats", [this](const String& arguments) -> CommandResult {
		ZoneServer* zoneServer = zoneServerRef.getForUpdate();

		if (zoneServerRef != nullptr) {
			ZoneServer* server = zoneServerRef.get();

			if (server != nullptr)
				server->getPlayerManager()->getCleanupCharacterCount();
		}

		return SUCCESS;
	});

	consoleCommands.put("test", [this](const String& arguments) -> CommandResult {
		Lua* lua = DirectorManager::instance()->getLuaInstance();

		// create the lua function
		UniqueReference<LuaFunction*> func(lua->createFunction("Tests", arguments, 0));
		func->callFunction();

		return SUCCESS;
	});

	consoleCommands.put("reloadscreenplays", [this](const String& arguments) -> CommandResult {
		DirectorManager::instance()->reloadScreenPlays();

		return SUCCESS;
	});

	consoleCommands.put("reloadmanager", [this](const String& arguments) -> CommandResult {
		if (arguments == "name") {
			ZoneServer* server = zoneServerRef.get();

			if(server != nullptr)
				server->getNameManager()->loadConfigData(true);
		} else {
			System::out << "Invalid manager. Reloadable managers: name" << endl;
		}

		return SUCCESS;
	});

	consoleCommands.put("clearstats", [this](const String& arguments) -> CommandResult {
		Core::getTaskManager()->clearWorkersTaskStats();

		return SUCCESS;
	});

#ifdef COLLECT_TASKSTATISTICS
	consoleCommands.put("statsd", [this](const String& arguments) -> CommandResult {
		StringTokenizer argTokenizer(arguments);

		argTokenizer.setDelimiter(" ");

		String address;
		int port = 0;

		if (argTokenizer.hasMoreTokens())
			argTokenizer.getStringToken(address);

		if (argTokenizer.hasMoreTokens())
			port = argTokenizer.getIntToken();

		if (port) {
			MetricsManager::instance()->initializeStatsDConnection(address.toCharArray(), port);

			System::out << "metrics manager connection set to" << address << ":" << port << endl;
		} else {
			System::out << "invalid port or address" << endl;
		}

		return SUCCESS;
	});

	consoleCommands.put("samplerate", [this](const String& arguments) -> CommandResult {
		try {
			int rate = UnsignedInteger::valueOf(arguments);

			Core::getTaskManager()->setStatsDTaskSampling(rate);

			System::out << "statsd sampling rate changed to " << rate << endl;
		} catch (const Exception& e) {
			System::out << "invalid statsd sampling rate" << endl;

			return ERROR;
		}

		return SUCCESS;
	});

	consoleCommands.put("sampleratedb", [this](const String& arguments) -> CommandResult {
		try {
			int rate = UnsignedInteger::valueOf(arguments);

			Core::getTaskManager()->setStatsDBdbSamplingRate(rate);

			System::out << "statsd berkeley db sampling rate changed to " << rate << endl;
		} catch (const Exception& e) {
			System::out << "invalid statsd sampling rate" << endl;

			return ERROR;
		}

		return SUCCESS;
	});
#endif
	const auto pvpModeLambda = [this](const String& arguments) -> CommandResult {
		System::out << "PvpMode = " << ConfigManager::instance()->getPvpMode() << endl;

		return SUCCESS;
	};

	consoleCommands.put("getpvpmode", pvpModeLambda);
	consoleCommands.put("getpvp", pvpModeLambda);

	const auto setPvpModeLambda = [this](const String& arguments) -> CommandResult {
		int num;

		try {
			if (arguments == "on") {
				num = 1;
			} else if (arguments == "off") {
				num = 0;
			} else {
				num = UnsignedInteger::valueOf(arguments);
			}

			if (num == 1) {
				ConfigManager::instance()->setPvpMode(true);
			} else {
				ConfigManager::instance()->setPvpMode(false);
			}

			info(true) << "console set new PvpMode = " << ConfigManager::instance()->getPvpMode();
		} catch (const Exception& e) {
			System::out << "invalid PvpMode: (0=off; 1=on)" << endl;

			return ERROR;
		}

		return SUCCESS;
	};

	consoleCommands.put("setpvpmode", setPvpModeLambda);
	consoleCommands.put("setpvp", setPvpModeLambda);

	const auto dumpConfigLambda = [this](const String& arguments) -> CommandResult {
		ConfigManager::instance()->dumpConfig(arguments == "all" ? true : false);

		return SUCCESS;
	};

	consoleCommands.put("dumpcfg", dumpConfigLambda);
	consoleCommands.put("dumpconfig", dumpConfigLambda);

	consoleCommands.put("toggleModifiedObjectsDump", [this](const String& arguments) -> CommandResult {
		DOBObjectManager::setDumpLastModifiedTraces(!DOBObjectManager::getDumpLastModifiedTraces());

		System::out << "dump last modified traces set to " << DOBObjectManager::getDumpLastModifiedTraces();

		return SUCCESS;
	});

	debug() << "registered " << consoleCommands.size() << " console commands.";
}

ServerCore::~ServerCore() {
	finalizeContext();
}

class ZoneStatisticsTask: public Task {
	Reference<ZoneServer*> zoneServer;

public:
	ZoneStatisticsTask(ZoneServer* server) {
		zoneServer = server;
	}

	void run() {
		zoneServer->printInfo();
	}
};

void ServerCore::finalizeContext() {
	server::db::mysql::MySqlDatabase::finalizeLibrary();
}

void ServerCore::initializeCoreContext() {
	server::db::mysql::MySqlDatabase::initializeLibrary();

	class ThreadHook : public ThreadInitializer {
	public:
		void onThreadStart(Thread* thread) final {
			server::db::mysql::MySqlDatabase::onThreadStart();
		}

		void onThreadEnd(Thread* thread) final {
			server::db::mysql::MySqlDatabase::onThreadEnd();
		}
	};

	Thread::setThreadInitializer(new ThreadHook());
}

void ServerCore::signalShutdown() {
	shutdownBlockMutex.lock();

	waitCondition.broadcast(&shutdownBlockMutex);

	shutdownBlockMutex.unlock();
}

void ServerCore::initialize() {
	info(true) << "Server start, pid: "
		<< Thread::getProcessID() << ", time: " << Time().getFormattedTime();

	processConfig();

	Logger::setGlobalFileLogger(configManager->getLogFile());
	Logger::setGlobalFileJson(configManager->getJsonLogOutput());
	Logger::setGlobalFileLoggerSync(configManager->getSyncLogOutput());
	Logger::setGlobalFileLogLevel(static_cast<Logger::LogLevel>(configManager->getLogFileLevel()));

	registerConsoleCommmands();

	try {
		ObjectManager* objectManager = ObjectManager::instance();

		database = new ServerDatabase(configManager);

		mantisDatabase = new MantisDatabase(configManager);

		const String& orbaddr = configManager->getORBNamingDirectoryAddress();
		orb = DistributedObjectBroker::initialize(orbaddr,
				configManager->getORBNamingDirectoryPort());

		orb->setCustomObjectManager(objectManager);

		info() << "MetricsServer: " << configManager->shouldUseMetrics()
			<< " " << configManager->getMetricsHost() << " " << configManager->getMetricsPort();

		if (configManager->shouldUseMetrics()) {
			metricsManager->setGlobalPrefix(configManager->getMetricsPrefix());
			metricsManager->initializeStatsDConnection(
					configManager->getMetricsHost().toCharArray(),
					configManager->getMetricsPort());
		}

		if (configManager->getMakeLogin()) {
			loginServer = new LoginServer(configManager);
			loginServer->deploy("LoginServer");
			database->instance()->executeStatement("TRUNCATE TABLE sessions");
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

		NavMeshManager::instance()->initialize(configManager->getMaxNavMeshJobs(), zoneServer);

		if (zoneServer != nullptr) {
			int zonePort = configManager->getZoneServerPort();

			int zoneAllowedConnections =
					configManager->getZoneAllowedConnections();

			if (arguments.contains("deleteNavMeshes") && zoneServer != nullptr) {
				zoneServer->setShouldDeleteNavAreas(true);
			}

			ObjectDatabaseManager* dbManager =
					ObjectDatabaseManager::instance();
			dbManager->loadDatabases(truncateDatabases());

			int galaxyID = configManager->getZoneGalaxyID();

			try {
				if (zonePort == 0) {
					const String query = "SELECT port FROM galaxy WHERE galaxy_id = "
								   + String::valueOf(galaxyID);
					Reference < ResultSet * > result =
							database->instance()->executeQuery(query);

					if (result != nullptr && result->next()) {
						zonePort = result->getInt(0);
					}
				}

				database->instance()->executeStatement(
						"DELETE FROM characters_dirty WHERE galaxy_id = "
						+ String::valueOf(galaxyID));
			} catch (DatabaseException &e) {
				fatal(e.getMessage());
			}

			zoneServer->start(zonePort, zoneAllowedConnections);
		}

		if (statusServer != nullptr) {
			int statusPort = configManager->getStatusPort();
			int statusAllowedConnections =
					configManager->getStatusAllowedConnections();

			statusServer->start(statusPort, statusAllowedConnections);
		}

		if (webServer != nullptr) {
			webServer->start(configManager);
		}

		if (pingServer != nullptr) {
			int pingPort = configManager->getPingPort();
			int pingAllowedConnections =
					configManager->getPingAllowedConnections();

			pingServer->start(pingPort, pingAllowedConnections);
		}

		if (loginServer != nullptr) {
			int loginPort = configManager->getLoginPort();
			int loginAllowedConnections =
					configManager->getLoginAllowedConnections();

			loginServer->start(loginPort, loginAllowedConnections);
		}

#ifndef WITH_STM
		ObjectManager::instance()->scheduleUpdateToDatabase();
#else
		Task* statiscticsTask = new ZoneStatisticsTask(zoneServerRef);
		statiscticsTask->schedulePeriodic(10000, 10000);
#endif

		if (configManager->getRESTPort()) {
			restServer = new server::web3::RESTServer(configManager->getRESTPort());
			restServer->start();
		}

		info("initialized", true);

		System::flushStreams();

		if (arguments.contains("playercleanup") && zoneServer != nullptr) {
			zoneServer->getPlayerManager()->cleanupCharacters();
		}

		if (arguments.contains("playercleanupstats") && zoneServer != nullptr) {
			zoneServer->getPlayerManager()->getCleanupCharacterCount();
		}

		if (arguments.contains("shutdown")) {
			handleCmds = false;
		}

	} catch (const ServiceException& e) {
		shutdown();
	} catch (const DatabaseException& e) {
		fatal(e.getMessage());
	}
}

void ServerCore::run() {
	handleCommands();

	shutdown();
}

void ServerCore::shutdown() {
	info(true) << "shutting down server..";

	if (restServer) {
		restServer->stop();

		delete restServer;
		restServer = nullptr;
	}

	ObjectManager* objectManager = ObjectManager::instance();

	while (objectManager->isObjectUpdateInProcess())
		Thread::sleep(500);

	objectManager->cancelDeleteCharactersTask();
	objectManager->cancelUpdateModifiedObjectsTask();

	if (loginServer != nullptr) {
		loginServer->stop();
		loginServer = nullptr;
	}

	ZoneServer* zoneServer = zoneServerRef.get();

	if (zoneServer != nullptr) {
		zoneServer->setServerStateShuttingDown();

		Thread::sleep(2000);

		info("Disconnecting all players", true);

		PlayerManager* playerManager = zoneServer->getPlayerManager();

		playerManager->stopOnlinePlayerLogTask();
		playerManager->disconnectAllPlayers();

		int count = 0;
		while (zoneServer->getConnectionCount() > 0 && count < 20) {
			Thread::sleep(500);
			count++;
		}

		info("All players disconnected", true);

		auto frsManager = zoneServer->getFrsManager();

		if (frsManager != nullptr) {
			frsManager->cancelTasks();
		}
	}

	if (pingServer != nullptr) {
		pingServer->stop();
		pingServer = nullptr;
	}

	if (webServer != nullptr) {
		webServer->stop();
		webServer = nullptr;
	}

	if (statusServer != nullptr) {
		statusServer->stop();
		statusServer = nullptr;
	}

	NavMeshManager::instance()->stop();

	Thread::sleep(5000);

	objectManager->createBackup();

	while (objectManager->isObjectUpdateInProcess())
		Thread::sleep(500);

	info("database backup done", true);

	objectManager->cancelUpdateModifiedObjectsTask();

	if (zoneServer != nullptr) {
		zoneServer->clearZones();
	}

	orb->shutdown();

	Core::shutdownTaskManager();

	if (zoneServer != nullptr) {
		zoneServer->stop();
		zoneServer = nullptr;
	}

	DistributedObjectDirectory* dir = objectManager->getLocalObjectDirectory();

	HashTable<uint64, Reference<DistributedObject*> > tbl;
	auto objects = dir->getDistributedObjectMap();
	auto objectsIterator = objects->iterator();
	typedef std::remove_reference<decltype(*objects)>::type ObjectsMapType;

	while (objectsIterator.hasNext()) {
		ObjectsMapType::key_type key;
		ObjectsMapType::value_type value;

		objectsIterator.getNextKeyAndValue(key, value);

		tbl.put(key, value);
	}

	objectManager->finalizeInstance();

	configManager = nullptr;
	metricsManager = nullptr;

	if (database != nullptr) {
		delete database;
		database = nullptr;
	}

	if (mantisDatabase != nullptr) {
		delete mantisDatabase;
		mantisDatabase = nullptr;
	}

	if (features != nullptr) {
		delete features;
		features = nullptr;
	}

	NetworkInterface::finalize();

	Logger::closeGlobalFileLogger();

	orb->finalizeInstance();

	zoneServerRef = nullptr;

	info("server closed", true);
}

void ServerCore::handleCommands() {
	while (handleCmds) {

#ifdef WITH_STM
		Reference<Transaction*> transaction = TransactionalMemoryManager::instance()->startTransaction();
#endif

		try {
			String fullCommand;

			Thread::sleep(500);

			System::out << "> " << flush;

			char line[256];
			auto res = fgets(line, sizeof(line), stdin);

			if (!res)
				continue;

			fullCommand = line;
			fullCommand = fullCommand.trim();

			StringTokenizer tokenizer(fullCommand);

			String command, arguments;

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(command);

			if (tokenizer.hasMoreTokens())
				arguments = tokenizer.getRemainingString();

			auto it = consoleCommands.find(command);

			if (it != consoleCommands.npos) {
				int result = consoleCommands.get(it)(arguments);

				if (result == SHUTDOWN)
					return;
			} else {
				System::out << "unknown command (" << command << ")\n";
			}
		} catch (const SocketException& e) {
			error() << e.getMessage();
		} catch (const ArrayIndexOutOfBoundsException& e) {
			error() << e.getMessage();
		} catch (const Exception& e) {
			error() << "unreported Exception caught";
		}

		System::flushStreams();
#ifdef WITH_STM
		try {
			TransactionalMemoryManager::commitPureTransaction(transaction);
		} catch (const TransactionAbortedException& e) {
		}
#endif

	}

	Thread::sleep(10000);
}

void ServerCore::processConfig() {
	if (!configManager->loadConfigData())
		info("missing config file.. loading default values\n");

	//if (!features->loadFeatures())
	//info("Problem occurred trying to load features.lua");
}

int ServerCore::getSchemaVersion() {
	if (instance != nullptr && instance->database != nullptr)
		return instance->database->getSchemaVersion();

	return -1;
}
