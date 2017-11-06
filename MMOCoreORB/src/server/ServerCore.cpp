/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "ServerCore.h"

#include <type_traits>

#include "db/ServerDatabase.h"
#include "db/MantisDatabase.h"

#include "server/chat/ChatManager.h"
#include "server/login/LoginServer.h"
#include "features/Features.h"
#include "ping/PingServer.h"
#include "status/StatusServer.h"
#include "web/WebServer.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"

#include "engine/util/u3d/QuadTree.h"

#include "engine/core/MetricsManager.h"

ManagedReference<ZoneServer*> ServerCore::zoneServerRef = NULL;
SortedVector<String> ServerCore::arguments;
bool ServerCore::truncateAllData = false;
ServerCore* ServerCore::instance = NULL;

ServerCore::ServerCore(bool truncateDatabases, SortedVector<String>& args) :
		Core("log/core3.log"), Logger("Core") {
	orb = NULL;

	loginServer = NULL;
	zoneServerRef = NULL;
	statusServer = NULL;
	pingServer = NULL;
	webServer = NULL;
	database = NULL;
	mantisDatabase = NULL;

	truncateAllData = truncateDatabases;
	arguments = args;

	instance = this;

	configManager = ConfigManager::instance();
	metricsManager = MetricsManager::instance();

	features = NULL;

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

void ServerCore::signalShutdown() {
	shutdownBlockMutex.lock();

	waitCondition.broadcast(&shutdownBlockMutex);

	shutdownBlockMutex.unlock();
}

void ServerCore::initialize() {
	info("starting up server..");

	processConfig();

	Logger::setGlobalFileLogger(configManager->getLogFile());
	Logger::setGlobalFileLogLevel(static_cast<Logger::LogLevel>(configManager->getLogFileLevel()));

	try {
		ObjectManager* objectManager = ObjectManager::instance();

		database = new ServerDatabase(configManager);

		mantisDatabase = new MantisDatabase(configManager);

		const String& orbaddr = configManager->getORBNamingDirectoryAddress();
		orb = DistributedObjectBroker::initialize(orbaddr,
//				DistributedObjectBroker::NAMING_DIRECTORY_PORT);
				configManager->getORBNamingDirectoryPort());

		orb->setCustomObjectManager(objectManager);

		StringBuffer metricsMsg;
		metricsMsg << "METRICS: " << String::valueOf(configManager->shouldUseMetrics()) << " " << configManager->getMetricsHost() << " " << String::valueOf(configManager->getMetricsPort()) << endl;

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

		if (zoneServer != NULL) {
			int zonePort = configManager->getZoneServerPort();

			int zoneAllowedConnections =
					configManager->getZoneAllowedConnections();

			if (arguments.contains("deleteNavMeshes") && zoneServer != NULL) {
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

					if (result != NULL && result->next()) {
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

		if (statusServer != NULL) {
			int statusPort = configManager->getStatusPort();
			int statusAllowedConnections =
					configManager->getStatusAllowedConnections();

			statusServer->start(statusPort, statusAllowedConnections);
		}

		if (webServer != NULL) {
			webServer->start(configManager);
		}

		if (pingServer != NULL) {
			int pingPort = configManager->getPingPort();
			int pingAllowedConnections =
					configManager->getPingAllowedConnections();

			pingServer->start(pingPort, pingAllowedConnections);
		}

		if (loginServer != NULL) {
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

		info("initialized", true);
		
		if (arguments.contains("playercleanup") && zoneServer != NULL) {
			zoneServer->getPlayerManager()->cleanupCharacters();
		}

		if (arguments.contains("playercleanupstats") && zoneServer != NULL) {
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

	ObjectManager* objectManager = ObjectManager::instance();

	while (objectManager->isObjectUpdateInProcess())
		Thread::sleep(500);

	objectManager->cancelDeleteCharactersTask();
	objectManager->cancelUpdateModifiedObjectsTask();

	if (loginServer != NULL) {
		loginServer->stop();
		loginServer = NULL;
	}

	ZoneServer* zoneServer = zoneServerRef.get();

	if (zoneServer != NULL) {
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

	if (pingServer != NULL) {
		pingServer->stop();
		delete pingServer;
		pingServer = NULL;
	}

	if (webServer != NULL) {
		webServer->stop();
		webServer = NULL;
	}

	if (statusServer != NULL) {
		statusServer->stop();
		delete statusServer;
		statusServer = NULL;
	}

	NavMeshManager::instance()->stop();

	Thread::sleep(5000);

	objectManager->createBackup();

	while (objectManager->isObjectUpdateInProcess())
		Thread::sleep(500);

	info("database backup done", true);

	objectManager->cancelUpdateModifiedObjectsTask();

	if (zoneServer != NULL) {
		zoneServer->clearZones();
	}

	orb->shutdown();

	Core::shutdownTaskManager();

	if (zoneServer != NULL) {
		zoneServer->stop();
		zoneServer = NULL;
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

	configManager = NULL;
	metricsManager = NULL;

	if (database != NULL) {
		delete database;
		database = NULL;
	}

	if (mantisDatabase != NULL) {
		delete mantisDatabase;
		mantisDatabase = NULL;
	}

	if (features != NULL) {
		delete features;
		features = NULL;
	}

	mysql_thread_end();
	engine::db::mysql::MySqlDatabase::finalizeLibrary();

	NetworkInterface::finalize();

	Logger::closeGlobalFileLogger();

	orb->finalizeInstance();

	zoneServerRef = NULL;

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
				if (zoneServer != NULL) {
					ChatManager* chatManager = zoneServer->getChatManager();
					chatManager->broadcastGalaxy(NULL,
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

				if (loginServer != NULL)
					loginServer->printInfo();

				if (zoneServer != NULL)
					zoneServer->printInfo();

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
				chatManager->broadcastGalaxy(NULL, arguments);
			} else if (command == "shutdown") {
				int minutes = 1;

				try {
					minutes = UnsignedInteger::valueOf(arguments);
				} catch (Exception& e) {
					System::out << "invalid minutes number expected dec";
				}

				if (zoneServer != NULL) {
					zoneServer->timedShutdown(minutes);

					shutdownBlockMutex.lock();

					waitCondition.wait(&shutdownBlockMutex);

					shutdownBlockMutex.unlock();
				}

				return;
			} else if ( command == "playercleanup" ) {

				if(zoneServerRef != NULL){
					ZoneServer* server = zoneServerRef.get();

					if(server != NULL)
						server->getPlayerManager()->cleanupCharacters();
				}

			} else if ( command == "playercleanupstats" ) {

				if(zoneServerRef != NULL){

					ZoneServer* server = zoneServerRef.get();

					if(server != NULL)
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
