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

#include "ZoneServer.h"

#include "ZoneClientSession.h"

#include "Zone.h"

#include "../db/ServerDatabase.h"

#include "server/login/LoginServer.h"
#include "server/login/account/Account.h"

#include "server/conf/ConfigManager.h"

#include "managers/object/ObjectManager.h"
#include "managers/stringid/StringIdManager.h"
#include "managers/objectcontroller/ObjectController.h"
#include "managers/player/PlayerManager.h"
#include "managers/radial/RadialManager.h"
#include "managers/resource/ResourceManager.h"
#include "managers/crafting/CraftingManager.h"
#include "managers/loot/LootManager.h"
#include "managers/skill/SkillManager.h"
#include "managers/auction/AuctionManager.h"
#include "managers/minigames/FishingManager.h"
#include "managers/minigames/GamblingManager.h"
#include "managers/minigames/ForageManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "managers/creature/CreatureTemplateManager.h"
#include "managers/guild/GuildManager.h"
#include "managers/creature/CreatureManager.h"
#include "managers/faction/FactionManager.h"
#include "managers/director/DirectorManager.h"
#include "managers/city/CityManager.h"

#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/variables/Skill.h"

#include "tre3/TreeDirectory.h"

#include "ZoneProcessServer.h"
#include "ZonePacketHandler.h"
#include "ZoneHandler.h"

#include "ZoneLoadManagersTask.h"
#include "ShutdownTask.h"

ZoneServerImplementation::ZoneServerImplementation(ConfigManager* config) :
		ManagedServiceImplementation(), Logger("ZoneServer") {

	configManager = config;

	galaxyID = config->getZoneGalaxyID();
	galaxyName = "Core3";

	processor = NULL;
	
	
	serverCap = 3000;

	phandler = NULL;

	datagramService = new DatagramServiceThread("ZoneServer");
	datagramService->setLogging(false);
	datagramService->setLockName("ZoneServerLock");

	objectManager = NULL;
	playerManager = NULL;
	chatManager = NULL;
	radialManager = NULL;
	resourceManager = NULL;
	craftingManager = NULL;
	lootManager = NULL;

	stringIdManager = NULL;
	creatureTemplateManager = NULL;
	guildManager = NULL;
	cityManager = NULL;

	totalSentPackets = 0;
	totalResentPackets = 0;

	currentPlayers = 0;
	maximumPlayers = 0;
	totalPlayers = 0;
	totalDeletedPlayers = 0;

	serverState = OFFLINE;

	setLogging(true);
}

void ZoneServerImplementation::initializeTransientMembers() {
	phandler = NULL;

	objectManager = NULL;

	ManagedObjectImplementation::initializeTransientMembers();
}

void ZoneServerImplementation::loadGalaxyName() {
	try {
		String query = "SELECT name FROM galaxy WHERE galaxy_id = " + String::valueOf(galaxyID);

		Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery(query);

		if (result->next())
			galaxyName = result->getString(0);

	} catch (DatabaseException& e) {
		info(e.getMessage());
	}

	setLoggingName("ZoneServer " + galaxyName);

	loadLoginMessage();
}

void ZoneServerImplementation::initialize() {
	serverState = LOADING;

	loadGalaxyName();

	processor = new ZoneProcessServer(_this.get());
	processor->deploy("ZoneProcessServer");
	processor->initialize();

	zones = new VectorMap<String, ManagedReference<Zone*> >();

	objectManager = ObjectManager::instance();
	objectManager->setZoneProcessor(processor);
	objectManager->updateObjectVersion();

	stringIdManager = StringIdManager::instance();

	creatureTemplateManager = CreatureTemplateManager::instance();
	creatureTemplateManager->loadTemplates();

	phandler = new BasePacketHandler("ZoneServer", zoneHandler);
	phandler->setLogging(false);

	info("Initializing chat manager...", true);

	chatManager = new ChatManager(_this.get(), 10000);
	chatManager->deploy("ChatManager");
	chatManager->initiateRooms();

	playerManager = new PlayerManager(_this.get(), processor);
	playerManager->deploy("PlayerManager");

	chatManager->setPlayerManager(playerManager);

	craftingManager = new CraftingManager();
	craftingManager->deploy("CraftingManager");
	craftingManager->setZoneProcessor(processor);
	craftingManager->initialize();

	lootManager = new LootManager(craftingManager, objectManager, _this.get());
	lootManager->deploy("LootManager");
	lootManager->initialize();

	resourceManager = new ResourceManager(_this.get(), processor, objectManager);
	resourceManager->deploy("ResourceManager");

	cityManager = new CityManager(_this.get());
	cityManager->deploy("CityManager");
	cityManager->loadLuaConfig();

	auctionManager = new AuctionManager(_this.get());
	auctionManager->deploy();

	missionManager = new MissionManager(_this.get(), processor);
	missionManager->deploy("MissionManager");

	startZones();

	startManagers();

	serverState = LOCKED;
	//serverState = ONLINE; //Test Center does not need to apply this change, but would be convenient for Dev Servers.

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	return;
}

void ZoneServerImplementation::startZones() {
	info("Loading zones.");

	SortedVector<String>* enabledZones = configManager->getEnabledZones();

	for (int i = 0; i < enabledZones->size(); ++i) {
		String zoneName = enabledZones->get(i);

		info("Loading zone " + zoneName + ".");

		Zone* zone = new Zone(processor, zoneName);
		zone->createContainerComponent();
		zone->initializePrivateData();
		zone->deploy("Zone " + zoneName);

		zones->put(zoneName, zone);
	}

	resourceManager->initialize();

	for (int i = 0; i < zones->size(); ++i) {
		Zone* zone = zones->get(i);

		if (zone != NULL)
			zone->startManagers();
	}
}

void ZoneServerImplementation::startManagers() {
	info("loading managers..");

	radialManager = new RadialManager(_this.get());
	radialManager->deploy("RadialManager");

	guildManager = new GuildManager(_this.get(), processor);
	guildManager->deploy("GuildManager");
	guildManager->setChatManager(chatManager);
	guildManager->loadGuilds();

	//Loads the FactionManager LUA Config.
	FactionManager::instance()->loadData();

	cityManager->loadCityRegions();

	//start global screne plays
	DirectorManager::instance()->startGlobalScreenPlays();

	auctionManager->initialize();
}

void ZoneServerImplementation::start(int p, int mconn) {
	zoneHandler = new ZoneHandler(_this.get());

	datagramService->setHandler(zoneHandler);

	datagramService->start(p, mconn);

	/*datagramService->join();

	shutdown();*/
}

void ZoneServerImplementation::stop() {
	datagramService->stop();
	//datagramService->setHandler(NULL);
}

void ZoneServerImplementation::timedShutdown(int minutes) {
	Reference<Task*> task = new ShutdownTask(_this.get(), minutes);
	task->schedule(60 * 1000);

	String str = "Server will shutdown in " + String::valueOf(minutes) + " minutes";
	Logger::console.info(str, true);

	getChatManager()->broadcastGalaxy(NULL, str);
}

void ZoneServerImplementation::shutdown() {
	//datagramService->setHandler(NULL);

	stopManagers();

	info("shutting down zones", true);

	for (int i = 0; i < 45; ++i) {
		ManagedReference<Zone*> zone = zones->get(i);

		if (zone != NULL) {
			zone->stopManagers();
			//info("zone references " + String::valueOf(zone->getReferenceCount()), true);
		}
	}

	zones->removeAll();

	info("zones shut down", true);

	printInfo();

	info("shut down complete", true);
}

void ZoneServerImplementation::stopManagers() {
	info("stopping managers..");

	if (resourceManager != NULL) {
		resourceManager->stop();
		resourceManager = NULL;
	}

	playerManager = NULL;
	chatManager = NULL;
	radialManager = NULL;
	craftingManager = NULL;
	lootManager = NULL;
	auctionManager = NULL;
	missionManager = NULL;
	guildManager = NULL;
	cityManager = NULL;

	info("managers stopped", true);
}

ZoneClientSession* ZoneServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	/*if (!userManager->checkUser(addr.getIPID()))
		return NULL;*/

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

	String address = session->getAddress();

	//info("client connected from \'" + address + "\'");

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

	ZoneClientSession* client = zoneHandler->getClientSession(message->getClient());

	Task* task = zonePacketHandler->generateMessageTask(client, message);

	if (task != NULL) {
		Core::getTaskManager()->executeTask(task, ((MessageCallback*)task)->getTaskQueue());
	}

	delete message;
}

bool ZoneServerImplementation::handleError(ZoneClientSession* client, Exception& e) {
	client->getSession()->setError();

	client->disconnect();

	return true;
}

SceneObject* ZoneServerImplementation::getObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;

	try {
		//lock(doLock); ObjectManager has its own mutex

		DistributedObject* distributedObject = Core::getObjectBroker()->lookUp(oid);

		if (distributedObject != NULL) {
			obj = dynamic_cast<SceneObject*>(distributedObject); // only for debug purposes

			if (obj == NULL) {
				error("trying to lookup object that is not an SceneObject");
				StackTrace::printStackTrace();
			}
		}

		//unlock(doLock);
	} catch (Exception& e) {
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

SceneObject* ZoneServerImplementation::createObject(uint32 templateCRC, int persistenceLevel, uint64 oid) {
	SceneObject* obj = NULL;

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

SceneObject* ZoneServerImplementation::createClientObject(uint32 templateCRC, uint64 oid) {
	SceneObject* obj = NULL;

	try {
		//lock(); ObjectManager has its own mutex

		obj = objectManager->createObject(templateCRC, 1, "clientobjects", oid);
		obj->setClientObject(true);

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

void ZoneServerImplementation::addTotalSentPacket(int count) {
//	lock();

	totalSentPackets += count;

//	unlock();
}

void ZoneServerImplementation::addTotalResentPacket(int count) {
	//lock();

	totalResentPackets += count;

	//unlock();
}

int ZoneServerImplementation::getConnectionCount() {
	return currentPlayers;
}

void ZoneServerImplementation::printInfo() {
	lock();

	StringBuffer msg;
	msg << Core::getTaskManager()->getInfo(false) << endl;;
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

	int totalCreatures = 0;

	for (int i = 0; i < zones->size(); ++i) {
		ManagedReference<Zone*> zone = zones->get(i);

		if (zone != NULL) {
			CreatureManager* manager = zone->getCreatureManager();

			if (manager != NULL) {
				totalCreatures += manager->getSpawnedRandomCreatures();
				//creatureEvents += manager->creatureEventsSize();
			}
		}
	}

//	msg << dec << totalCreatures << " random creatures spawned" << endl;
	msg << dec << playerManager->getOnlineZoneClientMap()->getDistinctIps() << " total distinct ips connected";
#endif

	unlock();

	info(msg.toString(), true);
}

String ZoneServerImplementation::getInfo() {
	lock();

	StringBuffer msg;
	msg << Core::getTaskManager()->getInfo(false) << endl;;
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

	int totalCreatures = 0;

	for (int i = 0; i < zones->size(); ++i) {
		ManagedReference<Zone*> zone = zones->get(i);

		if (zone != NULL) {
			CreatureManager* manager = zone->getCreatureManager();

			if (manager != NULL) {
				totalCreatures += manager->getSpawnedRandomCreatures();
				//creatureEvents += manager->creatureEventsSize();
			}
		}
	}

	msg << dec << totalCreatures << " random creatures spawned" << endl;
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
	Locker locker(_this.get());

	serverState = LOCKED;

	StringBuffer msg;
	msg << dec << "server locked";
	info(msg, true);
}

void ZoneServerImplementation::setServerStateOnline() {
	Locker locker(_this.get());

	serverState = ONLINE;

	StringBuffer msg;
	msg << dec << "server unlocked";
	info(msg, true);
}

String ZoneServerImplementation::getLoginMessage() {
	return loginMessage;
}

void ZoneServerImplementation::loadLoginMessage() {
	Locker locker(_this.get());

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
		file = NULL;
		reader = NULL;
	}

	loginMessage += "\nRevision=";
	loginMessage += ConfigManager::instance()->getRevision();
}

void ZoneServerImplementation::changeLoginMessage(const String& motd) {
	Locker locker(_this.get());

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
		file = NULL;
		writer = NULL;
	}

	loginMessage = finalMOTD;
}

/*Account* ZoneServerImplementation::getAccount(uint32 accountID) {

	ManagedReference<LoginServer*> loginServer = cast<LoginServer*>(DistributedObjectBroker::instance()->lookUp("LoginServer"));
	if(loginServer == NULL)
		return NULL;

	return loginServer->getAccount(accountID);
}*/
