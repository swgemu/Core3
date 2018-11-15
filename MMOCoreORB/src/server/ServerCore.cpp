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

#include "server/zone/QuadTree.h"

#include "engine/core/MetricsManager.h"

ManagedReference<ZoneServer*> ServerCore::zoneServerRef = nullptr;
SortedVector<String> ServerCore::arguments;
bool ServerCore::truncateAllData = false;
ServerCore* ServerCore::instance = nullptr;

ServerCore::ServerCore(bool truncateDatabases, SortedVector<String>& args) :
		Core("log/core3.log"), Logger("Core") {
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

	configManager = ConfigManager::instance();
	metricsManager = MetricsManager::instance();

	features = nullptr;

	handleCmds = true;
}

class ZoneStatisticsTask: public Task {
	ManagedReference<ZoneServer*> zoneServer;

public:
	ZoneStatisticsTask(ZoneServer* server) {
		zoneServer = server;
	}

	void run() {
		zoneServer->printInfo();
	}
};

void ServerCore::finalizeContext() {
	Core::finalizeContext();

	server::db::mysql::MySqlDatabase::finalizeLibrary();
}

void ServerCore::initializeContext(int logLevel) {
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

	Core::initializeContext(logLevel);
}

void ServerCore::signalShutdown() {
	shutdownBlockMutex.lock();

	waitCondition.broadcast(&shutdownBlockMutex);

	shutdownBlockMutex.unlock();
}

void ServerCore::initialize() {
	info("starting up server..");

	processConfig();

	Logger::setGlobalFileLogger(configManager->getLogFile());
	Logger::setGlobalFileJson(configManager->getJsonLogOutput());
	Logger::setGlobalFileLoggerSync(configManager->getSyncLogOutput());
	Logger::setGlobalFileLogLevel(static_cast<Logger::LogLevel>(configManager->getLogFileLevel()));

	try {
		ObjectManager* objectManager = ObjectManager::instance();

		database = new ServerDatabase(configManager);

		mantisDatabase = new MantisDatabase(configManager);

		const String& orbaddr = configManager->getORBNamingDirectoryAddress();
		orb = DistributedObjectBroker::initialize(orbaddr,
				configManager->getORBNamingDirectoryPort());

		orb->setCustomObjectManager(objectManager);

		StringBuffer metricsMsg;
		metricsMsg << "MetricsServer: " << String::valueOf(configManager->shouldUseMetrics()) << " " << configManager->getMetricsHost() << " " << String::valueOf(configManager->getMetricsPort());
		info(metricsMsg, true);

		if (configManager->shouldUseMetrics()) {
			metricsManager->setGlobalPrefix(configManager->getMetricsPrefix());
			metricsManager->initializeStatsDConnection(
					configManager->getMetricsHost().toCharArray(),
					configManager->getMetricsPort());
		}

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
					String query = "SELECT port FROM galaxy WHERE galaxy_id = "
								   + String::valueOf(galaxyID);
					Reference < ResultSet * > result =
							database->instance()->executeQuery(query);

					if (result != nullptr && result->next()) {
						zonePort = result->getInt(0);
					}
				}

				database->instance()->executeStatement(
						"TRUNCATE TABLE sessions");

				database->instance()->executeStatement(
						"DELETE FROM characters_dirty WHERE galaxy_id = "
						+ String::valueOf(galaxyID));
			} catch (DatabaseException &e) {
				error(e.getMessage());

				exit(1);
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

		if (arguments.contains("playercleanup") && zoneServer != nullptr) {
			zoneServer->getPlayerManager()->cleanupCharacters();
		}

		if (arguments.contains("playercleanupstats") && zoneServer != nullptr) {
			zoneServer->getPlayerManager()->getCleanupCharacterCount();
		}

		if (arguments.contains("shutdown")) {
			handleCmds = false;
		}

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
	info("shutting down server..", true);

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

		playerManager->disconnectAllPlayers();

		int count = 0;
		while (zoneServer->getConnectionCount() > 0 && count < 20) {
			Thread::sleep(500);
			count++;
		}

		info("All players disconnected", true);
	}

	if (pingServer != nullptr) {
		pingServer->stop();
		delete pingServer;
		pingServer = nullptr;
	}

	if (webServer != nullptr) {
		webServer->stop();
		webServer = nullptr;
	}

	if (statusServer != nullptr) {
		statusServer->stop();
		delete statusServer;
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

	mysql_thread_end();
	server::db::mysql::MySqlDatabase::finalizeLibrary();

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

			System::out << "> ";

			char line[256];
			auto res = fgets(line, sizeof(line), stdin);

			if (!res)
				continue;

			fullCommand = line;
			fullCommand = fullCommand.replaceFirst("\n", "");

			StringTokenizer tokenizer(fullCommand);

			String command, arguments;

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(command);

			if (tokenizer.hasMoreTokens())
				tokenizer.finalToken(arguments);

			ZoneServer* zoneServer = zoneServerRef.getForUpdate();

			if (command == "exit") {
				if (zoneServer != nullptr) {
					ChatManager* chatManager = zoneServer->getChatManager();
					chatManager->broadcastGalaxy(nullptr,
							"Server is shutting down NOW!");
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

				if (loginServer != nullptr)
					loginServer->printInfo();

				if (zoneServer != nullptr)
					zoneServer->printInfo();

				if (pingServer != nullptr)
					pingServer->printInfo();
			} else if (command == "lock") {
				if (zoneServer != nullptr)
					zoneServer->setServerStateLocked();
			} else if (command == "unlock") {
				if (zoneServer != nullptr)
					zoneServer->setServerStateOnline();
			} else if (command == "icap") {
				if (zoneServer != nullptr)
					zoneServer->changeUserCap(50);
			} else if (command == "dcap") {
				if (zoneServer != nullptr)
					zoneServer->changeUserCap(-50);
			} else if (command == "fixQueue") {
				if (zoneServer != nullptr)
					zoneServer->fixScheduler();
			} else if (command == "save") {
				ObjectManager::instance()->createBackup();
				//ObjectDatabaseManager::instance()->checkpoint();
			} else if (command == "help") {
				System::out << "available commands:\n";
				System::out << "\texit, logQuadTree, info, lock, unlock, icap, dcap, fixQueue, save, chars, lookupcrc, rev, broadcast, shutdown.\n";
			} else if (command == "chars") {
				uint32 num = 0;

				try {
					num = UnsignedInteger::valueOf(arguments);
				} catch (Exception& e) {
					System::out << "invalid number of concurrent chars per account specified";
				}

				if (num != 0) {
					PlayerManager* pMan = zoneServer->getPlayerManager();
					pMan->setOnlineCharactersPerAccount(num);

					System::out << "changed max concurrent chars per account to: " << num << endl;
				}
			} else if (command == "lookupcrc") {
				uint32 crc = 0;
				try {
					crc = UnsignedInteger::valueOf(arguments);
				} catch (Exception& e) {
					System::out << "invalid crc number expected dec";
				}

				if (crc != 0) {
					String file = TemplateManager::instance()->getTemplateFile(
							crc);

					System::out << "result: " << file << endl;
				}

			} else if (command == "loglevel") {
				int level = 0;
				try {
					level = Integer::valueOf(arguments);
				} catch (Exception& e) {
					System::out << "invalid log level" << endl;
				}

				if (level >= Logger::NONE && level <= Logger::DEBUG) {
					Logger::setGlobalFileLogLevel(static_cast<Logger::LogLevel>(level));

					System::out << "log level changed to: " << level << endl;
				}
			} else if (command == "rev") {
				System::out << ConfigManager::instance()->getRevision() << endl;
			} else if (command == "broadcast") {
				ChatManager* chatManager = zoneServer->getChatManager();
				chatManager->broadcastGalaxy(nullptr, arguments);
			} else if (command == "shutdown") {
				int minutes = 1;

				try {
					minutes = UnsignedInteger::valueOf(arguments);
				} catch (Exception& e) {
					System::out << "invalid minutes number expected dec";
				}

				if (zoneServer != nullptr) {
					zoneServer->timedShutdown(minutes);

					shutdownBlockMutex.lock();

					waitCondition.wait(&shutdownBlockMutex);

					shutdownBlockMutex.unlock();
				}

				return;
			} else if ( command == "playercleanup" ) {

				if(zoneServerRef != nullptr){
					ZoneServer* server = zoneServerRef.get();

					if(server != nullptr)
						server->getPlayerManager()->cleanupCharacters();
				}

			} else if ( command == "playercleanupstats" ) {

				if(zoneServerRef != nullptr){

					ZoneServer* server = zoneServerRef.get();

					if(server != nullptr)
						server->getPlayerManager()->getCleanupCharacterCount();
				}

			} else if ( command == "test" ) {
				// get lua
				Lua* lua = DirectorManager::instance()->getLuaInstance();

				// create the lua function
				Reference<LuaFunction*> func = lua->createFunction("Tests", arguments, 0);
				func->callFunction();
			} else if ( command == "reloadscreenplays" ) {
				DirectorManager::instance()->reloadScreenPlays();
			} else if ( command == "clearstats" ) {
				Core::getTaskManager()->clearWorkersTaskStats();
#ifdef COLLECT_TASKSTATISTICS
			} else if (command == "statsd") {
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
			} else if (command == "samplerate") {
				try {
					int rate = UnsignedInteger::valueOf(arguments);

					Core::getTaskManager()->setStatsDTaskSampling(rate);

					System::out << "statsd sampling rate changed to " << rate << endl;
				} catch (Exception& e) {
					System::out << "invalid statsd sampling rate" << endl;
				}
			} else if (command == "sampleratedb") {
				try {
					int rate = UnsignedInteger::valueOf(arguments);

					Core::getTaskManager()->setStatsDBdbSamplingRate(rate);

					System::out << "statsd berkeley db sampling rate changed to " << rate << endl;
				} catch (Exception& e) {
					System::out << "invalid statsd sampling rate" << endl;
				}
#endif
			} else {
				System::out << "unknown command (" << command << ")\n";
			}
		} catch (SocketException& e) {
			System::out << "[ServerCore] " << e.getMessage();
		} catch (ArrayIndexOutOfBoundsException& e) {
			System::out << "[ServerCore] " << e.getMessage() << "\n";
		} catch (Exception& e) {
			System::out << "[ServerCore] unreported Exception caught\n";
		}

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
