/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/ZoneServer.h"

#include "server/zone/ZoneClientSession.h"

#include "server/zone/Zone.h"
#include "server/zone/GroundZone.h"
#include "server/zone/SpaceZone.h"

#include "server/db/ServerDatabase.h"

#include "conf/ConfigManager.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/radial/RadialManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/managers/space/SpaceAiMap.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/ship/ShipAgentTemplateManager.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/frs/FrsManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/ship/ShipManager.h"

#include "server/zone/ZoneProcessServer.h"
#include "ZonePacketHandler.h"
#include "ZoneHandler.h"

#include "SpaceZoneLoadManagersTask.h"
#include "ZoneLoadManagersTask.h"
#include "ShutdownTask.h"

ZoneServerImplementation::ZoneServerImplementation(ConfigManager* config) :
		ManagedServiceImplementation(), Logger("ZoneServer") {

	configManager = config;

	galaxyID = config->getZoneGalaxyID();
	galaxyName = "Core3";

	processor = nullptr;


	serverCap = 3000;

	phandler = nullptr;

	datagramService = new DatagramServiceThread("ZoneServer");
	datagramService->setLogging(false);
	datagramService->setLockName("ZoneServerLock");

	objectManager = nullptr;
	playerManager = nullptr;
	chatManager = nullptr;
	radialManager = nullptr;
	resourceManager = nullptr;
	craftingManager = nullptr;
	lootManager = nullptr;

	stringIdManager = nullptr;
	creatureTemplateManager = nullptr;
	shipAgentTemplateManager = nullptr;
	guildManager = nullptr;
	cityManager = nullptr;
	petManager = nullptr;

	totalSentPackets = 0;
	totalResentPackets = 0;

	currentPlayers = 0;
	maximumPlayers = 0;
	totalPlayers = 0;
	totalDeletedPlayers = 0;

	serverState = OFFLINE;
	deleteNavAreas = false;

	setLogLevel(Logger::INFO);
}

void ZoneServerImplementation::initializeTransientMembers() {
	phandler = nullptr;

	objectManager = nullptr;

	deleteNavAreas = false;

	ManagedObjectImplementation::initializeTransientMembers();
}

void ZoneServerImplementation::loadGalaxyName() {
	try {
		const String query = "SELECT name FROM galaxy WHERE galaxy_id = " + String::valueOf(galaxyID);

		UniqueReference<ResultSet*> result(ServerDatabase::instance()->executeQuery(query));

		if (result->next())
			galaxyName = result->getString(0);

	} catch (const DatabaseException& e) {
		fatal(e.getMessage());
	}

	setLoggingName("ZoneServer " + galaxyName);

	loadLoginMessage();
}

void ZoneServerImplementation::initialize() {
	serverState = LOADING;

	loadGalaxyName();

	processor = new ZoneProcessServer(_this.getReferenceUnsafeStaticCast());
	processor->deploy("ZoneProcessServer");
	processor->initialize();

	zones = new VectorMap<String, ManagedReference<GroundZone*> >();
	spaceZones = new VectorMap<String, ManagedReference<SpaceZone*> >();

	objectManager = ObjectManager::instance();
	objectManager->setZoneProcessor(processor);
	objectManager->updateObjectVersion();

	stringIdManager = StringIdManager::instance();

	reactionManager = new ReactionManager(_this.getReferenceUnsafeStaticCast());
	reactionManager->loadLuaConfig();

	creatureTemplateManager = CreatureTemplateManager::instance();
	creatureTemplateManager->loadTemplates();

	shipAgentTemplateManager = ShipAgentTemplateManager::instance();
	shipAgentTemplateManager->loadTemplates();
	shipAgentTemplateManager->loadSpacePatrolPoints();

	AiMap::instance()->loadTemplates();
	SpaceAiMap::instance()->loadTemplates();

	dnaManager = DnaManager::instance();
	dnaManager->loadSampleData();

	phandler = new BasePacketHandler("ZoneServer", zoneHandler);
	phandler->setLogging(false);

	info("Initializing chat manager...", true);

	chatManager = new ChatManager(_this.getReferenceUnsafeStaticCast(), 10000);
	chatManager->deploy("ChatManager");
	chatManager->initiateRooms();

	playerManager = new PlayerManager(_this.getReferenceUnsafeStaticCast(), processor, true);
	playerManager->deploy("PlayerManager");

	chatManager->setPlayerManager(playerManager);

	craftingManager = new CraftingManager();
	craftingManager->deploy("CraftingManager");
	craftingManager->setZoneProcessor(processor);
	craftingManager->initialize();

	lootManager = new LootManager(craftingManager, objectManager, _this.getReferenceUnsafeStaticCast());
	lootManager->deploy("LootManager");
	lootManager->initialize();

	resourceManager = new ResourceManager(_this.getReferenceUnsafeStaticCast(), processor);
	resourceManager->deploy("ResourceManager");

	cityManager = new CityManager(_this.getReferenceUnsafeStaticCast());
	cityManager->deploy("CityManager");
	cityManager->loadLuaConfig();

	auctionManager = new AuctionManager(_this.getReferenceUnsafeStaticCast());
	auctionManager->deploy();

	missionManager = new MissionManager(_this.getReferenceUnsafeStaticCast(), processor);
	missionManager->deploy("MissionManager");

	petManager = new PetManager(_this.getReferenceUnsafeStaticCast());
	petManager->initialize();

	// Load ship data
	ShipManager::instance()->initialize();

	startGroundZones();
	startSpaceZones();

	startManagers();

	//serverState = LOCKED;
	serverState = ONLINE; //Test Center does not need to apply this change, but would be convenient for Dev Servers.

	ObjectDatabaseManager::instance()->commitLocalTransaction();
}

void ZoneServerImplementation::startGroundZones() {
	info(true) << "Loading Ground Zones...";

	auto enabledZones = configManager->getEnabledZones();

	StructureManager* structureManager = StructureManager::instance();
	structureManager->setZoneServer(_this.getReferenceUnsafeStaticCast());

	int totalZones = enabledZones.size();

	info(true) << "Total Enabled Ground Zones: " << totalZones;

	for (int i = 0; i < totalZones; ++i) {
		String zoneName = enabledZones.get(i);

		if (zoneName.toLowerCase().contains("space")) {
			error() << "Attempting to load Space Zone as a Ground Zone -- Zone: " << zoneName;
			continue;
		}

		GroundZone* zone = new GroundZone(processor, zoneName);
		zone->createContainerComponent();
		zone->initializePrivateData();
		zone->deploy("GroundZone " + zoneName);

		String displayName = zoneName.subString(0,1).toUpperCase() + zoneName.subString(1);

		info(true) << "Ground Zone: " + displayName + " deployed.";

		zones->put(zoneName, zone);
	}

	resourceManager->initialize();

	for (int i = 0; i < zones->size(); ++i) {
		GroundZone* zone = zones->get(i);

		if (zone != nullptr) {
			ZoneLoadManagersTask* task = new ZoneLoadManagersTask(_this.getReferenceUnsafeStaticCast(), zone);
			task->execute();
		}
	}

	for (int i = 0; i < zones->size(); ++i) {
		GroundZone* zone = zones->get(i);

		if (zone != nullptr) {
			while (!zone->hasManagersStarted())
				Thread::sleep(500);
		}
	}
}

void ZoneServerImplementation::startSpaceZones() {
	info(true) << "Loading Space Zones...";

	auto enabledSpaceZones = configManager->getEnabledSpaceZones();

	int totalZones = enabledSpaceZones.size();

	info(true) << "Total Enabled Space Zones: " << totalZones;

	for (int i = 0; i < totalZones; ++i) {
		String zoneName = enabledSpaceZones.get(i);

		SpaceZone* spaceZone = new SpaceZone(processor, zoneName);

		spaceZone->createContainerComponent();
		spaceZone->initializePrivateData();
		spaceZone->deploy("SpaceZone " + zoneName);

		info(true) << "Space Zone: " + zoneName + " deployed.";

		spaceZones->put(zoneName, spaceZone);
	}

	for (int i = 0; i < spaceZones->size(); ++i) {
		SpaceZone* zone = spaceZones->get(i);

		if (zone != nullptr) {
			SpaceZoneLoadManagersTask* task = new SpaceZoneLoadManagersTask(_this.getReferenceUnsafeStaticCast(), zone);
			task->execute();
		}
	}

	for (int i = 0; i < spaceZones->size(); ++i) {
		SpaceZone* spaceZone = spaceZones->get(i);

		if (spaceZone != nullptr) {
			while (!spaceZone->hasManagersStarted())
				Thread::sleep(500);
		}
	}
}

void ZoneServerImplementation::startManagers() {
	info(true) << "ZoneServerImplementation -- Starting Managers...";

	radialManager = new RadialManager(_this.getReferenceUnsafeStaticCast());
	radialManager->deploy("RadialManager");

	guildManager = new GuildManager(_this.getReferenceUnsafeStaticCast(), processor);
	guildManager->deploy("GuildManager");
	guildManager->setChatManager(chatManager);
	guildManager->loadLuaConfig();
	guildManager->loadGuilds();

	chatManager->initiatePlanetRooms();
	chatManager->loadPersistentRooms();

	//Loads the FactionManager LUA Config.
	FactionManager::instance()->loadData();

	//Start global screen plays
	DirectorManager::instance()->loadPersistentEvents();
	DirectorManager::instance()->loadPersistentStatus();
	DirectorManager::instance()->startGlobalScreenPlays();

	cityManager->loadCityRegions();

	for (int i = 0; i < zones->size(); ++i) {
		Zone* zone = zones->get(i);

		if (zone != nullptr) {
			zone->updateCityRegions();
		}
	}

	auctionManager->initialize();

	frsManager = new FrsManager(_this.getReferenceUnsafeStaticCast());
	frsManager->initialize();

	info(true) << "ZoneServerImplementation -- Managers Started.";
}

void ZoneServerImplementation::start(int p, int mconn) {
	zoneHandler = new ZoneHandler(_this.getReferenceUnsafeStaticCast());

	datagramService->setHandler(zoneHandler);

	datagramService->start(p, mconn);

	/*datagramService->join();

	shutdown();*/
}

void ZoneServerImplementation::stop() {
	datagramService->stop();

	shutdown();
}

void ZoneServerImplementation::timedShutdown(int minutes, int flags) {
	Reference<Task*> task = new ShutdownTask(_this.getReferenceUnsafeStaticCast(), minutes, flags);

	if (minutes <= 0) {
		task->execute();
	} else {
		task->schedule(60 * 1000);

		StringBuffer shutdownMsg;

		shutdownMsg << "You will be disconnected in ";

		if (minutes > 1) {
			shutdownMsg << minutes << " minutes ";
		} else {
			shutdownMsg << minutes << " minute ";
		}

		shutdownMsg << "so the server can perform a final save before shutting down. Please find a safe place to logout.";

		Logger::console.info(shutdownMsg.toString(), true);

		getChatManager()->broadcastGalaxy(nullptr, shutdownMsg.toString());
	}
}

void ZoneServerImplementation::shutdown() {
	//datagramService->setHandler(nullptr);

	stopManagers();

	info("Shutting Down Ground Zones", true);

	for (int i = 0; i < zones->size(); ++i) {
		ManagedReference<GroundZone*> zone = zones->get(i);

		if (zone != nullptr) {
			zone->stopManagers();

			debug() << "zone references " << zone->getReferenceCount();
		}
	}

	zones->removeAll();

	info("Ground Zones Shut Down", true);

	info("Shutting Down Space Zones", true);

	for (int i = 0; i < spaceZones->size(); ++i) {
		ManagedReference<SpaceZone*> spaceZone = spaceZones->get(i);

		if (spaceZone != nullptr) {
			spaceZone->stopManagers();

			debug() << "zone references " << spaceZone->getReferenceCount();
		}
	}

	spaceZones->removeAll();

	info("Space Zones Shut Down", true);

	printInfo();

	datagramService = nullptr;

	info("shut down complete", true);
}

void ZoneServerImplementation::stopManagers() {
	info(true) << "ZoneServerImplementation -- Stopping Managers...";

	missionManager = nullptr;
	radialManager = nullptr;
	auctionManager = nullptr;
	petManager = nullptr;
	reactionManager = nullptr;

	if (frsManager != nullptr) {
		frsManager->stop();
		frsManager = nullptr;
	}

	creatureTemplateManager = nullptr;
	shipAgentTemplateManager = nullptr;

	dnaManager = nullptr;
	stringIdManager = nullptr;
	zoneHandler = nullptr;
	configManager = nullptr;
	phandler = nullptr;

	if (guildManager != nullptr) {
		guildManager->stop();
		guildManager = nullptr;
	}

	if (cityManager != nullptr) {
		cityManager->stop();
		cityManager = nullptr;
	}

	if (chatManager != nullptr) {
		chatManager->stop();
		chatManager = nullptr;
	}

	if (resourceManager != nullptr) {
		resourceManager->stop();
		resourceManager = nullptr;
	}

	if (craftingManager != nullptr) {
		craftingManager->stop();
		craftingManager = nullptr;
	}

	if (lootManager != nullptr) {
		lootManager->stop();
		lootManager = nullptr;
	}

	if (playerManager != nullptr) {
		playerManager->finalize();
		playerManager = nullptr;
	}

	if (processor != nullptr) {
		processor->stop();
		processor = nullptr;
	}

	if (objectManager != nullptr) {
		objectManager->shutdown();
		objectManager = nullptr;
	}

	ShipManager::instance()->stop();

	info(true) << "ZoneServerImplementation -- Managers Stopped";
}

void ZoneServerImplementation::clearZones() {
	info("clearing all zones..", true);
	// Clear Ground Zones
	for (int i = 0; i < zones->size(); ++i) {
		ManagedReference<GroundZone*> zone = zones->get(i);

		if (zone != nullptr) {
			Core::getTaskManager()->executeTask([=] () {
				zone->clearZone();
			}, "ClearZoneLambda");
		}
	}

	for (int i = 0; i < zones->size(); ++i) {
		GroundZone* zone = zones->get(i);

		if (zone != nullptr) {
			while (!zone->isZoneCleared())
				Thread::sleep(500);
		}
	}

	info("Ground zones cleared...", true);

	//Clear Space Zones
	for (int i = 0; i < spaceZones->size(); ++i) {
		ManagedReference<SpaceZone*> szone = spaceZones->get(i);

		if (szone != nullptr) {
			Core::getTaskManager()->executeTask([=] () {
				szone->clearZone();
			}, "ClearZoneLambda");
		}
	}

	for (int i = 0; i < spaceZones->size(); ++i) {
		SpaceZone* szone = spaceZones->get(i);

		if (szone != nullptr) {
			while (!szone->isZoneCleared())
				Thread::sleep(500);
		}
	}

	info("Space zones cleared...", true);
}

Zone* ZoneServerImplementation::getZone(const String& zoneName) const {
	if (zoneName.beginsWith("space")) {
		return spaceZones->get(zoneName);
	}

	return zones->get(zoneName);
}

ZoneClientSession* ZoneServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	/*if (!userManager->checkUser(addr.getIPID()))
		return nullptr;*/

	BaseClientProxy* session = new BaseClientProxy(sock, addr);

	StringBuffer loggingname;
	loggingname << "ZoneClientSession " << addr.getFullIPAddress();

	session->setLoggingName(loggingname.toString());
	session->setLogging(false);

	session->init(datagramService);

	ZoneClientSession* client = new ZoneClientSession(session);
	//clients arent undeployed instantly so we get already deployed clients
	//client->deploy("ZoneClientSession " + addr.getFullIPAddress());
	//client->deploy();

	const auto& address = session->getAddress();

	debug() << "client connected from \'" << address << "\'";

	return client;
}

void ZoneServerImplementation::handleMessage(ZoneClientSession* client, Packet* message) {
	try {
		/*if (zclient->simulatePacketLoss())
			return;*/

		if (client->getSession()->isAvailable())
			phandler->handlePacket(client->getSession(), message);

	} catch (PacketIndexOutOfBoundsException& e) {
		error(e.getMessage());

		error("incorrect packet - " + message->toStringData());
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (ArrayIndexOutOfBoundsException& e) {
		error(e.getMessage());
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

void ZoneServerImplementation::processMessage(Message* message) {
	ZonePacketHandler* zonePacketHandler = processor->getPacketHandler();

	auto client = zoneHandler->getClientSession(message->getClient());

	// move generateMessageTask to the client task at some point
	Task* task = zonePacketHandler->generateMessageTask(client, message);

	if (task != nullptr) {
		if (client != nullptr) {
			client->executeOrderedTask(task);
		} else {
			auto taskManager = Core::getTaskManager();

			if (taskManager) {
				taskManager->executeTask(task);
			} else {
				delete task;
			}
		}
	}

	delete message;
}

bool ZoneServerImplementation::handleError(ZoneClientSession* client, Exception& e) {
	client->getSession()->setError();

	client->disconnect();

	return true;
}

Reference<SceneObject*> ZoneServerImplementation::getObject(uint64 oid, bool doLock) {
	Reference<SceneObject*> obj = nullptr;

	if (isServerShuttingDown())
		return obj;

	try {
		//lock(doLock); ObjectManager has its own mutex

		Reference<DistributedObject*> distributedObject = Core::getObjectBroker()->lookUp(oid);

		if (distributedObject != nullptr) {
			obj = dynamic_cast<SceneObject*>(distributedObject.get()); // only for debug purposes

			if (obj == nullptr) {
				error("trying to lookup object that is not an SceneObject");
				StackTrace::printStackTrace();
			}
		}

		//unlock(doLock);
	} catch (const Exception& e) {
		//unlock(doLock);
		error(e.getMessage());
		e.printStackTrace();
	}

	return obj;
}

void ZoneServerImplementation::updateObjectToDatabase(SceneObject* object) {
	objectManager->updatePersistentObject(object);
}

void ZoneServerImplementation::updateObjectToStaticDatabase(SceneObject* object) {
	objectManager->updatePersistentObject(object);
}

Reference<SceneObject*> ZoneServerImplementation::createObject(uint32 templateCRC, const String& dbname, int persistenceLevel ){
	Reference<SceneObject*> obj = nullptr;

	try {
		//lock(); ObjectManager has its own mutex

		obj = objectManager->createObject(templateCRC, persistenceLevel, dbname, 0);

		//unlock();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		//unlock();
	}

	return obj;
}

Reference<SceneObject*> ZoneServerImplementation::createObject(uint32 templateCRC, int persistenceLevel, uint64 oid) {
	Reference<SceneObject*> obj = nullptr;

	try {
		//lock(); ObjectManager has its own mutex

		obj = objectManager->createObject(templateCRC, persistenceLevel, "sceneobjects", oid);

		//unlock();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		//unlock();
	}

	return obj;
}

Reference<SceneObject*> ZoneServerImplementation::createClientObject(uint32 templateCRC, uint64 oid) {
	Reference<SceneObject*> obj = nullptr;

	try {
		//lock(); ObjectManager has its own mutex

		obj = objectManager->createObject(templateCRC, 1, "clientobjects", oid, false);
		obj->setClientObject(true);
		obj->initializeTransientMembers();

		//unlock();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		//unlock();
	}

	return obj;
}

void ZoneServerImplementation::destroyObjectFromDatabase(uint64 objectID) {
	objectManager->destroyObjectFromDatabase(objectID);
}

void ZoneServerImplementation::changeUserCap(int amount) {
	lock();

	serverCap += amount;
	//userManager->changeUserCap(amount);

	info("server cap changed to " + String::valueOf(serverCap), true);

	unlock();
}

void ZoneServerImplementation::addTotalSentPacket(unsigned int count) {
//	lock();

	totalSentPackets += count;

//	unlock();
}

void ZoneServerImplementation::addTotalResentPacket(unsigned int count) {
	//lock();

	totalResentPackets += count;

	//unlock();
}

int ZoneServerImplementation::getConnectionCount() {
	return currentPlayers;
}

void ZoneServerImplementation::printInfo() {
	lock();

	TaskManager* taskMgr = Core::getTaskManager();
	StringBuffer msg;

	if (taskMgr != nullptr)
		msg << taskMgr->getInfo(false) << endl;
	//msg << "MessageQueue - size = " << processor->getMessageQueue()->size() << endl;

	float packetloss;
	if (totalSentPackets + totalSentPackets == 0)
		packetloss = 0.0f;
	else
		packetloss = (100 * totalResentPackets) / (totalResentPackets + totalSentPackets);

#ifndef WITH_STM
	msg << "sent packets = " << totalSentPackets << ", resent packets = "
		<< totalResentPackets << " [" << packetloss << "%]" << endl;
#endif

	msg << dec << currentPlayers << " users connected (" << maximumPlayers << " max, " << totalPlayers << " total, "
		 << totalDeletedPlayers << " deleted)" << endl;

#ifndef WITH_STM
	msg << ObjectManager::instance()->getInfo() << endl;

	if (playerManager != nullptr)
		msg << dec << playerManager->getOnlineZoneClientMap()->getDistinctIps() << " total distinct ips connected";
#endif

	unlock();

	info(msg.toString(), true);
}

String ZoneServerImplementation::getInfo() {
	lock();

	StringBuffer msg;
	msg << Core::getTaskManager()->getInfo(false) << endl;
	//msg << "MessageQueue - size = " << processor->getMessageQueue()->size() << endl;

	float packetloss;
	if (totalSentPackets + totalSentPackets == 0)
		packetloss = 0.0f;
	else
		packetloss = (100 * totalResentPackets) / (totalResentPackets + totalSentPackets);

#ifndef WITH_STM
	msg << "sent packets = " << totalSentPackets << ", resent packets = "
		<< totalResentPackets << " [" << packetloss << "%]" << endl;
#endif

	msg << dec << currentPlayers << " users connected (" << maximumPlayers << " max, " << totalPlayers << " total, "
		 << totalDeletedPlayers << " deleted)" << endl;

#ifndef WITH_STM
	msg << ObjectManager::instance()->getInfo() << endl;
#endif

	unlock();

	return msg.toString();
}

void ZoneServerImplementation::printEvents() {
	lock();

	//scheduler->printEvents();

	unlock();
}

void ZoneServerImplementation::increaseOnlinePlayers() {
	currentPlayers.increment();

	if (currentPlayers > maximumPlayers)
		maximumPlayers = currentPlayers;

	totalPlayers.increment();
}

void ZoneServerImplementation::decreaseOnlinePlayers() {
	currentPlayers.decrement();
}

void ZoneServerImplementation::increaseTotalDeletedPlayers() {
	totalDeletedPlayers.increment();
}

void ZoneServerImplementation::lock(bool doLock) {
#ifdef WITH_STM
	if (doLock && !datagramService->tryLock())
		throw TransactionAbortedException();
#else
	datagramService->lock(doLock);
#endif
}

void ZoneServerImplementation::unlock(bool doLock) {
	datagramService->unlock(doLock);
}

void ZoneServerImplementation::setServerStateLocked() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	serverState = LOCKED;

	StringBuffer msg;
	msg << dec << "server locked";
	info(msg, true);
}

void ZoneServerImplementation::setServerStateOnline() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	serverState = ONLINE;

	StringBuffer msg;
	msg << dec << "server unlocked";
	info(msg, true);
}

void ZoneServerImplementation::setServerStateShuttingDown() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	serverState = SHUTTINGDOWN;

	StringBuffer msg;
	msg << dec << "server shutting down";
	info(msg, true);
}

String ZoneServerImplementation::getLoginMessage() const {
	return loginMessage;
}

void ZoneServerImplementation::loadLoginMessage() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	File* file;
	FileReader* reader;

	try {
		file = new File("conf/motd.txt");
		reader = new FileReader(file);

		String line;
		while(reader->readLine(line)) {
			loginMessage += line;
		}

		reader->close();
	} catch (FileNotFoundException& e) {
		file = nullptr;
		reader = nullptr;
	}

	loginMessage += "\nLatest Commits:\n";
	loginMessage += ConfigManager::instance()->getRevision();

	delete reader;
	delete file;
}

void ZoneServerImplementation::changeLoginMessage(const String& motd) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	File* file;
	FileWriter* writer;

	String finalMOTD = "";

	try {
		file = new File("conf/motd.txt");
		writer = new FileWriter(file);

		for(int i = 0; i < motd.length(); i++) {
			if(i+1 < motd.length()) {
				char currentLetter = motd.charAt(i);
				char nextLetter = motd.charAt(i+1);
				if(currentLetter == '\\' && nextLetter == 'n') {
					finalMOTD += "\n";
					i++;
				} else {
					finalMOTD += currentLetter;
				}
			} else {
				finalMOTD += motd.charAt(i);
			}
		}

		writer->write(finalMOTD);

		writer->close();
	} catch (FileNotFoundException& e) {
		file = nullptr;
		writer = nullptr;
	}

	loginMessage = finalMOTD;

	delete writer;
	delete file;
}
