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

#include "managers/user/UserManager.h"
#include "managers/user/UserManagerImplementation.h"

#include "managers/player/PlayerManager.h"
#include "managers/player/PlayerManagerImplementation.h"

#include "managers/player/ProfessionManager.h"

#include "managers/crafting/CraftingManager.h"
#include "managers/crafting/CraftingManagerImplementation.h"

#include "managers/item/ItemManager.h"
#include "managers/item/ItemManagerImplementation.h"

#include "managers/combat/CombatManager.h"
#include "../chat/ChatManager.h"
#include "../chat/ChatManagerImplementation.h"

#include "managers/radial/RadialManager.h"
#include "managers/guild/GuildManager.h"
#include "managers/guild/GuildManagerImplementation.h"
#include "managers/group/GroupManager.h"

#include "managers/resource/ResourceManager.h"
#include "managers/resource/ResourceManagerImplementation.h"

#include "managers/loot/LootTableManager.h"
#include "managers/loot/LootTableManagerImplementation.h"

#include "managers/bazaar/BazaarManager.h"
#include "managers/bazaar/BazaarManagerImplementation.h"

#include "managers/bank/BankManager.h"
#include "managers/bank/BankManagerImplementation.h"

#include "managers/mission/MissionManager.h"
#include "managers/mission/MissionManagerImplementation.h"

#include "ZoneClientSession.h"
#include "ZoneClientSessionImplementation.h"

#include "ZoneServerImplementation.h"

#include "ZoneImplementation.h"

#include "../ServerCore.h"

ZoneServerImplementation::ZoneServerImplementation(int processingThreads) :
		DatagramServiceThread("ZoneServer"), ZoneServerServant() {
	name = "Core3";

	phandler = NULL;

	processor = NULL;
	procThreadCount = processingThreads;

	objectManager = new ObjectManager(this);

	totalSentPackets = 0;
	totalResentPackets = 0;

	currentPlayers = 0;
	maximumPlayers = 0;
	totalPlayers = 0;
	totalDeletedPlayers = 0;

	nextCreatureID = 0x10000000;
	nextCellID = 9995371; // last objectid in static objects // 0x00;

	setLogging(false);
	setLockName("ZoneServerLock");

	scheduler->setLogging(false);
}

ZoneServerImplementation::~ZoneServerImplementation() {
	if (phandler != NULL) {
		delete phandler;
		phandler = NULL;
	}

	if (processor != NULL) {
		delete processor;
		processor = NULL;
	}

	if (itemManager != NULL) {
		itemManager->finalize();
		itemManager = NULL;
	}

	if (bazaarManager != NULL) {
		bazaarManager->finalize();
		bazaarManager = NULL;
	}

	if (objectManager != NULL) {
		delete objectManager;
		objectManager = NULL;
	}

	if (userManager != NULL) {
		userManager->finalize();
		userManager = NULL;
	}

	if (playerManager != NULL) {
		playerManager->finalize();
		playerManager = NULL;
	}

	if (guildManager != NULL) {
		guildManager->finalize();
		guildManager = NULL;
	}

	if (resourceManager != NULL) {
		resourceManager->finalize();
		resourceManager = NULL;
	}

	if (lootTableManager != NULL) {
		lootTableManager->finalize();
		lootTableManager = NULL;
	}

	if (craftingManager != NULL) {
		craftingManager->finalize();
		craftingManager = NULL;
	}

	if (bankManager != NULL) {
		bankManager->finalize();
		bankManager = NULL;
	}

	if (chatManager != NULL) {
		chatManager->finalize();
		chatManager = NULL;
	}

	if (missionManager != NULL) {
		missionManager->finalize();
		missionManager = NULL;
	}

	for (int i = 0; i < 45; ++i) {
		Zone* zone = zones.get(i);
		zone->finalize();
	}

	zones.removeAll();
}

void ZoneServerImplementation::init() {
	processor = new ZoneProcessServerImplementation(_this, procThreadCount);
	processor->init();

	phandler = new BasePacketHandler("ZoneServer", processor->getMessageQueue());
	phandler->setLogging(false);

	info("initializing zones", true);

	for (int i = 0; i < 45; ++i) {
		Zone* zone = new Zone(_this, processor, i);
		zone->deploy("Zone", i);

		zone->startManagers();

		zones.add(zone);
	}

	userManager = NULL;
	itemManager = NULL;
	playerManager = NULL;
	guildManager = NULL;
	resourceManager = NULL;
	lootTableManager = NULL;
	bazaarManager = NULL;
	bankManager = NULL;
	chatManager = NULL;

	startManagers();

	startTimestamp = time(NULL);

	return;
}

void ZoneServerImplementation::startManagers() {
	info("loading managers..");

	userManager = new UserManager(_this);
	userManager->deploy("UserManager");

	itemManager = new ItemManager(_this, processor);
	itemManager->deploy("ItemManager");

	playerManager = new PlayerManager(itemManager, processor);
	playerManager->deploy("PlayerManager");

	guildManager = new GuildManager(_this);
	guildManager->deploy("GuildManager");

	guildManager->load();
	playerManager->setGuildManager(guildManager);

	resourceManager = new ResourceManager(_this, processor);
	resourceManager->deploy("ResourceManager");

	lootTableManager = new LootTableManager(_this, processor);
	lootTableManager->deploy("LootTableManager");

	craftingManager = new CraftingManager(_this, processor);
	craftingManager->deploy("CraftingManager");

	chatManager = new ChatManager(_this, 10000);
	chatManager->deploy("ChatManager");

	bazaarManager = new BazaarManager(_this, processor);
	bazaarManager->deploy("BazaarManager");

	bankManager = new BankManager(_this, processor);
	bankManager->deploy("BankManager");

	missionManager = new MissionManager(_this, processor);
	missionManager->deploy("MissionManager");
}

void ZoneServerImplementation::run() {
	scheduler->start();

	processor->start();

	receiveMessages();

	shutdown();
}

void ZoneServerImplementation::shutdown() {
	chatManager->broadcastMessage("Server is shutting down in 30 seconds..");
	Thread::sleep(10000);

	chatManager->broadcastMessage("Server is shutting down in 20 seconds..");
	Thread::sleep(10000);

	chatManager->broadcastMessage("Server is shutting down in 10 seconds..");
	Thread::sleep(10000);

	chatManager->broadcastMessage("Server is shutting down in 5 seconds..");
	Thread::sleep(5000);

	processor->stop();

	stopManagers();

	info("shutting down zones", true);

	for (int i = 0; i < 45; ++i) {
		Zone* zone = zones.get(i);
		zone->stopManagers();
	}

	scheduler->stop();

	printInfo(true);
}

void ZoneServerImplementation::stopManagers() {
	info("stopping managers..");

	/*if (playerManager != NULL)
		playerManager->stop();*/

	if (missionManager != NULL)
		missionManager->unloadManager();

	if (resourceManager != NULL)
		resourceManager->stop();

	info("managers stopped", true);
}

ServiceClient* ZoneServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	if (!userManager->checkUser(addr.getIPID()))
		return NULL;

	ZoneClientSession* client = new ZoneClientSession(this, sock, &addr);
	client->deploy("ZoneClientSession " + addr.getFullIPAddress());

	info("client connected from \'" + client->getAddress() + "\'");

	ZoneClientSessionImplementation* clientImpl = (ZoneClientSessionImplementation*) client->_getImplementation();
	return clientImpl;
}

void ZoneServerImplementation::handleMessage(ServiceClient* client, Packet* message) {
	ZoneClientSessionImplementation* zclient = (ZoneClientSessionImplementation*) client;

	try {
		/*if (zclient->simulatePacketLoss())
			return;*/

		if (zclient->isAvailable())
			phandler->handlePacket(zclient, message);

	} catch (PacketIndexOutOfBoundsException& e) {
		error(e.getMessage());

		error("incorrect packet - " + message->toString());
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (ArrayIndexOutOfBoundsException& e) {
		error(e.getMessage());
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

bool ZoneServerImplementation::handleError(ServiceClient* client, Exception& e) {
	ZoneClientSessionImplementation* zclient = (ZoneClientSessionImplementation*) client;
	zclient->setError();

	zclient->disconnect();

	return true;
}

void ZoneServerImplementation::addObject(SceneObject* obj, bool doLock) {
	try {
		lock(doLock);

		if (objectManager->add(obj) == NULL && obj->isPlayer()) {
			Player* player = (Player*) obj;

			chatManager->addPlayer(player);

			if (++currentPlayers > maximumPlayers)
				maximumPlayers = currentPlayers;

			++totalPlayers;
		}

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}
}

SceneObject* ZoneServerImplementation::getObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;

	try {
		lock(doLock);

		obj = objectManager->get(oid);

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

SceneObject* ZoneServerImplementation::removeObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;

	try {
		lock(doLock);

		obj = objectManager->remove(oid);
		if (obj == NULL) {
			unlock(doLock);
			return NULL;
		}

		if (obj->isPlayer()) {
			Player* player = (Player*) obj;
			String& name = player->getFirstName();

			chatManager->removePlayer(name);

			--currentPlayers;
		}

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

SceneObject* ZoneServerImplementation::removeObject(SceneObject* obj, bool doLock) {
	return removeObject(obj->getObjectID(), doLock);
}

bool ZoneServerImplementation::destroyObject(SceneObject* obj, bool doLock) {
	bool res = false;

	try {
		lock(doLock);

		res = objectManager->destroy(obj);

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return res;
}

SceneObject* ZoneServerImplementation::getCachedObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;

	try {
		lock(doLock);

		obj = objectManager->getCachedObject(oid);

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

SceneObject* ZoneServerImplementation::removeCachedObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;

	System::out << "removeCachedObject OID = " << oid << endl;
	try {
		lock(doLock);

		obj = objectManager->removeCachedObject(oid);

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

SceneObject* ZoneServerImplementation::removeCachedObject(SceneObject* obj, bool doLock) {
	return removeCachedObject(obj->getObjectID(), doLock);
}

bool ZoneServerImplementation::banUser(String& name, String& admin) {
	lock();

	bool result = userManager->banUserByName(name, admin);

	unlock();

	return result;
}

bool ZoneServerImplementation::kickUser(String& name, String& admin) {
	lock();

	bool result = userManager->kickUser(name, admin);

	unlock();

	return result;
}

void ZoneServerImplementation::changeUserCap(int amount) {
	lock();

	userManager->changeUserCap(amount);

	unlock();
}

void ZoneServerImplementation::addTotalSentPacket(int count) {
	lock();

	totalSentPackets += count;

	unlock();
}

void ZoneServerImplementation::addTotalResentPacket(int count) {
	lock();

	totalResentPackets += count;

	unlock();
}

int ZoneServerImplementation::getConnectionCount() {
	return currentPlayers;
}

void ZoneServerImplementation::printInfo(bool forcedLog) {
	lock();

	StringBuffer msg;
	msg << "MessageQueue - size = " << messageQueue.size();
	info(msg, forcedLog);

	StringBuffer msg2;
	msg2 << "Scheduler - size = " << scheduler->getQueueSize();
	info(msg2, forcedLog);

	float packetloss;
	if (totalSentPackets + totalSentPackets == 0)
		packetloss = 0.0f;
	else
		packetloss = (100 * totalResentPackets) / (totalResentPackets + totalSentPackets);

	StringBuffer msg3;
	msg3 << "sent packets = " << totalSentPackets << ", resent packets = "
		<< totalResentPackets << " [" << packetloss << "%]";
	info(msg3, forcedLog);

	StringBuffer msg4;
	msg4 << dec << currentPlayers << " users connected (" << maximumPlayers << " max, " << totalPlayers << " total, "
		 << totalDeletedPlayers << " deleted)";
	info(msg4, forcedLog);

	unlock();
}

void ZoneServerImplementation::printEvents() {
	lock();

	scheduler->printEvents();

	unlock();
}

uint64 ZoneServerImplementation::getNextCreatureID(bool doLock) {
	lock(doLock);

	uint64 nextID = (nextCreatureID += 0x10000);

	unlock(doLock);

	return nextID;
}

uint64 ZoneServerImplementation::getNextID(bool doLock) {
	lock(doLock);

	uint64 nextID = (nextCreatureID += 0x01);

	unlock(doLock);

	return nextID;
}

uint64 ZoneServerImplementation::getNextCellID(bool doLock) {
	lock(doLock);

	uint64 nextID = (nextCellID += 0x1);

	unlock(doLock);

	return nextID;
}
