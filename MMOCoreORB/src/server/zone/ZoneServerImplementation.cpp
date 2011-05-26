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
#include "managers/professions/ProfessionManager.h"
#include "managers/auction/AuctionManager.h"
#include "managers/minigames/FishingManager.h"
#include "managers/minigames/GamblingManager.h"
#include "managers/minigames/ForageManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "managers/creature/CreatureTemplateManager.h"
#include "managers/guild/GuildManager.h"
#include "managers/creature/CreatureManager.h"
#include "managers/faction/FactionManager.h"

#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/professions/SkillBox.h"

#include "tre3/TreeDirectory.h"

#include "ZoneProcessServer.h"
#include "ZonePacketHandler.h"
#include "ZoneHandler.h"

#include "ZoneLoadManagersTask.h"

ZoneServerImplementation::ZoneServerImplementation(ConfigManager* config) :
		ManagedServiceImplementation(), Logger("ZoneServer") {

	configManager = config;

	galaxyID = config->getZoneGalaxyID();
	galaxyName = "Core3";

	processor = NULL;

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
	fishingManager = NULL;
	gamblingManager = NULL;
	forageManager = NULL;
	stringIdManager = NULL;
	creatureTemplateManager = NULL;
	guildManager = NULL;

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
}

void ZoneServerImplementation::initialize() {
	serverState = LOADING;

	loadGalaxyName();

	processor = new ZoneProcessServer(_this);
	processor->deploy("ZoneProcessServer");
	processor->initialize();

	objectManager = ObjectManager::instance();
	objectManager->setZoneProcessor(processor);
	objectManager->updateObjectVersion();

	stringIdManager = StringIdManager::instance();

	creatureTemplateManager = CreatureTemplateManager::instance();
	creatureTemplateManager->loadTemplates();

	phandler = new BasePacketHandler("ZoneServer", zoneHandler);
	phandler->setLogging(false);

	info("Initializing chat manager...", true);

	chatManager = new ChatManager(_this, 10000);
	chatManager->deploy("ChatManager");
	chatManager->initiateRooms();

	playerManager = new PlayerManager(_this, processor);
	playerManager->deploy("PlayerManager");

	chatManager->setPlayerManager(playerManager);

	craftingManager = new CraftingManager();
	craftingManager->deploy("CraftingManager");
	craftingManager->setZoneProcessor(processor);
	craftingManager->initialize();

	startZones();

	startManagers();

	//serverState = LOCKED;
	serverState = ONLINE; //Test Center does not need to apply this change, but would be convenient for Dev Servers.

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
		zone->initializePrivateData();
		zone->_setObjectID(~0 - i);
		zone->deploy("Zone " + zoneName);

		zones.put(zoneName, zone);

		zone->startManagers();
	}
}

void ZoneServerImplementation::startManagers() {
	info("loading managers..");

	resourceManager = new ResourceManager(_this, processor, objectManager);
	resourceManager->deploy("ResourceManager");
	resourceManager->initialize();

	auctionManager = new AuctionManager(_this);
	auctionManager->deploy();
	auctionManager->initialize();

	missionManager = new MissionManager(_this, processor);
	missionManager->deploy("MissionManager");

	radialManager = new RadialManager(_this);
	radialManager->deploy("RadialManager");

	fishingManager = new FishingManager(_this);
	fishingManager->deploy();

	gamblingManager = new GamblingManager(_this);
	gamblingManager->deploy();

	forageManager = new ForageManager(_this);
	forageManager->deploy();

	lootManager = new LootManager(craftingManager);
	lootManager->deploy("LootManager");
	lootManager->setZoneProcessor(processor);
	lootManager->initialize();

	guildManager = new GuildManager(_this, processor);
	guildManager->deploy("GuildManager");
	guildManager->setChatManager(chatManager);
	guildManager->loadGuilds();

	//Loads the FactionManager LUA Config.
	FactionManager::instance()->loadLuaConfig();

}

void ZoneServerImplementation::start(int p, int mconn) {
	zoneHandler = new ZoneHandler(_this);

	datagramService->setHandler(zoneHandler);

	datagramService->start(p, mconn);

	/*datagramService->join();

	shutdown();*/
}

void ZoneServerImplementation::stop() {
	datagramService->stop();
	datagramService->setHandler(NULL);
}

void ZoneServerImplementation::shutdown() {
	//datagramService->setHandler(NULL);

	stopManagers();

	info("shutting down zones", true);

	for (int i = 0; i < 45; ++i) {
		Zone* zone = zones.get(i);

		if (zone != NULL) {
			zone->stopManagers();
			//info("zone references " + String::valueOf(zone->getReferenceCount()), true);
		}
	}

	zones.removeAll();

	info("zones shut down", true);

	printInfo(true);

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
	fishingManager = NULL;
	guildManager = NULL;

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
	client->deploy();

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

	if (task != NULL)
		Core::getTaskManager()->executeTask(task);

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

	//userManager->changeUserCap(amount);

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

void ZoneServerImplementation::printInfo(bool forcedLog) {
	lock();

	Core::getTaskManager()->printInfo();

	/*StringBuffer msg;
	msg << "MessageQueue - size = " << processor->getMessageQueue()->size();
	info(msg, forcedLog);*/

	float packetloss;
	if (totalSentPackets + totalSentPackets == 0)
		packetloss = 0.0f;
	else
		packetloss = (100 * totalResentPackets) / (totalResentPackets + totalSentPackets);

#ifndef WITH_STM
	StringBuffer msg3;
	msg3 << "sent packets = " << totalSentPackets << ", resent packets = "
		<< totalResentPackets << " [" << packetloss << "%]";
	info(msg3, forcedLog);
#endif

	StringBuffer msg4;
	msg4 << dec << currentPlayers << " users connected (" << maximumPlayers << " max, " << totalPlayers << " total, "
		 << totalDeletedPlayers << " deleted)";
	info(msg4, forcedLog);

#ifndef WITH_STM
	ObjectManager::instance()->printInfo();

	int totalCreatures = 0;

	for (int i = 0; i < zones.size(); ++i) {
		Zone* zone = zones.get(i);

		if (zone != NULL) {
			CreatureManager* manager = zone->getCreatureManager();

			if (manager != NULL) {
				totalCreatures += manager->getSpawnedRandomCreatures();
				//creatureEvents += manager->creatureEventsSize();
			}
		}
	}

	StringBuffer msg5;
	msg5 << dec << totalCreatures << " random creatures spawned";
	info(msg5, forcedLog);
#endif

	unlock();
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
	Locker locker(_this);

	serverState = LOCKED;

	StringBuffer msg;
	msg << dec << "server locked";
	info(msg, true);
}

void ZoneServerImplementation::setServerStateOnline() {
	Locker locker(_this);

	serverState = ONLINE;

	StringBuffer msg;
	msg << dec << "server unlocked";
	info(msg, true);
}

String ZoneServerImplementation::getMessageoftheDay() {
	return messageoftheDay;
}

void ZoneServerImplementation::loadMessageoftheDay() {
	Locker locker(_this);

	File* file;
	FileReader* reader;

	try {
		file = new File("conf/motd.txt");
		reader = new FileReader(file);

		String line;
		while(reader->readLine(line)) {
			messageoftheDay += line;
		}

		reader->close();
	} catch (FileNotFoundException& e) {
		file = NULL;
		reader = NULL;
	}
}

void ZoneServerImplementation::changeMessageoftheDay(const String& newMOTD) {
	Locker locker(_this);

	File* file;
	FileWriter* writer;

	String finalMOTD = "";

	try {
		file = new File("conf/motd.txt");
		writer = new FileWriter(file);

		for(int i = 0; i < newMOTD.length(); i++) {
			if(i+1 < newMOTD.length()) {
				char currentLetter = newMOTD.charAt(i);
				char nextLetter = newMOTD.charAt(i+1);
				if(currentLetter == '\\' && nextLetter == 'n') {
					finalMOTD += "\n";
					i++;
				} else {
					finalMOTD += currentLetter;
				}
			} else {
				finalMOTD += newMOTD.charAt(i);
			}
		}

		writer->write(finalMOTD);

		writer->close();
	} catch (FileNotFoundException& e) {
		file = NULL;
		writer = NULL;
	}

	messageoftheDay = finalMOTD;
}

Account* ZoneServerImplementation::getAccount(uint32 accountID) {
	/*ManagedReference<LoginServer*> loginServer = (LoginServer*) Core::getObjectBroker()->lookUp("LoginServer");

	if (loginServer == NULL)
		return NULL;

	return loginServer->getAccount(accountID);*/

	return NULL;
}
