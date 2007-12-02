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

#include "managers/item/ItemManager.h"
#include "managers/item/ItemManagerImplementation.h"

#include "managers/combat/CombatManager.h"
#include "../chat/ChatManager.h"
#include "../chat/ChatManagerImplementation.h"

#include "managers/radial/RadialManager.h"
#include "managers/guild/GuildManager.h"
#include "managers/guild/GuildManagerImplementation.h"
#include "managers/group/GroupManager.h"

#include "ZoneClient.h"
#include "ZoneClientImplementation.h"

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
	
	nextCreatureID = 0x10000000;

	setLogging(false);
	setLockName("ZoneServerLock");
	
	scheduler->setLogging(false);
}

void ZoneServerImplementation::startManagers() {
	info("loading managers..");
	
	UserManagerImplementation* userImpl = new UserManagerImplementation(_this);
	userManager = (UserManager*) ObjectRequestBroker::instance()->deploy("UserManager", userImpl);
	
	ItemManagerImplementation* itemImpl = new ItemManagerImplementation(_this);
	itemManager = (ItemManager*) ObjectRequestBroker::instance()->deploy("ItemManager", itemImpl);

	PlayerManagerImplementation* playerImpl = new PlayerManagerImplementation(itemManager, processor);
	playerManager = (PlayerManager*) ObjectRequestBroker::instance()->deploy("PlayerManager", playerImpl);
	
	GuildManagerImplementation* guildImpl = new GuildManagerImplementation(_this);
	guildManager = (GuildManager*) ObjectRequestBroker::instance()->deploy("GuildManager", guildImpl);
	guildManager->load();
	playerManager->setGuildManager(guildManager);

	ChatManagerImplementation* chatImpl = new ChatManagerImplementation(_this, 10000);
	chatManager = (ChatManager*) ObjectRequestBroker::instance()->deploy("ChatManager", chatImpl);
}

ZoneServerImplementation::~ZoneServerImplementation() {
	if (phandler != NULL)
		delete phandler; 

	/*if (processors != NULL)
		delete processors;*/

	/*delete chatManager;
	delete combatManager;

	delete playerManager;
	delete professionManager;*/
	//delete userManager;
			
	delete objectManager; 
}

void ZoneServerImplementation::init() {
	processor = new ZoneProcessServerImplementation(_this, procThreadCount);
	processor->init();
	processor->start();
	
	phandler = new BasePacketHandler("ZoneServer", processor->getMessageQueue());
	phandler->setLogging(false);
	
	info("initializing zones", true);
	
	for (int i = 0; i < 50; ++i) {
		ZoneImplementation* zoneImpl = new ZoneImplementation(_this, processor, i);
		
		stringstream Name;
		Name << "Zone" << i;
		
		Zone* zne = (Zone*) ObjectRequestBroker::instance()->deploy(Name.str(), zoneImpl);
		zne->startManagers();
		
		zones.add(zne);
	}
	
	startManagers();

	return;
}

void ZoneServerImplementation::run() {
	scheduler->start();
	
	receiveMessages();
}

void ZoneServerImplementation::shutdown() {
	chatManager->broadcastMessage("Server is shutting down in 10 seconds..");
	
	Thread::sleepMili(10000);
	
	stop();
	
	processor->stop();

	printInfo(true);
		
	scheduler->stop();
}

ServiceClient* ZoneServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	if (!userManager->checkUser(addr.getIPID()))
		return NULL;
			
	ZoneClientImplementation* client = new ZoneClientImplementation(this, sock, addr);

	/*string ip = fromAddr.getFullIPAddress();
	if (ip.substr(0, 14) == "89.132.121.190")
		client->setPacketLoss(25);*/
	
	client->deploy("ZoneClient", addr.getNetworkID());
						
	info("client connected from \'" + client->getAddress() + "\'");
	
	return client;
}

void ZoneServerImplementation::handleMessage(ServiceClient* client, Packet* message) {
	ZoneClientImplementation* zclient = (ZoneClientImplementation*) client;
	
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
	ZoneClientImplementation* zclient = (ZoneClientImplementation*) client;
	zclient->setError();

	zclient->disconnect();

	return true;
}

void ZoneServerImplementation::addObject(SceneObject* obj, bool doLock) {
	try {
		lock(doLock);
		
		objectManager->add(obj);
		
		if (obj->isPlayer()) {
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
			string& name = player->getFirstName();

			chatManager->removePlayer(name);
			
			--currentPlayers;
		}

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

SceneObject* ZoneServerImplementation::removeCachedObject(uint64 oid, bool doLock) {
	SceneObject* obj = NULL;
	
	try {
		lock(doLock);

		obj = objectManager->removeCachedObject(oid);

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}

	return obj;
}

bool ZoneServerImplementation::banUser(string& name, string& admin) {
	lock();

	bool result = userManager->banUserByName(name, admin);

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
		
	stringstream msg;
	msg << "MessageQueue - size = " << messageQueue.size();
	info(msg, forcedLog);
		
	stringstream msg2;
	msg2 << "Scheduler - size = " << scheduler->getQueueSize();
	info(msg2, forcedLog);

	float packetloss;
	if (totalSentPackets + totalSentPackets == 0)
		packetloss = 0.0f;
	else
		packetloss = (100 * totalResentPackets) / (totalResentPackets + totalSentPackets);
		
	stringstream msg3;
	msg3 << "sent packets = " << totalSentPackets << ", resent packets = " 
		<< totalResentPackets << " [" << packetloss << "%]";
	info(msg3, forcedLog);

	stringstream msg4;
	msg4 << dec << currentPlayers << " users connected (" << maximumPlayers << " max, " << totalPlayers << " total)";
	info(msg4, forcedLog);
		
	unlock();
}

void ZoneServerImplementation::printEvents() {
	lock();

	scheduler->printEvents();
		
	unlock();
}

