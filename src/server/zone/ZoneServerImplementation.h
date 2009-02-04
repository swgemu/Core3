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

#ifndef ZONESERVERIMPLEMENTATION_H_
#define ZONESERVERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "ZoneProcessServerImplementation.h"

#include "ZonePacketHandler.h"

#include "Zone.h"

#include "managers/object/ObjectManager.h"

class SceneObject;

class UserManager;

class PlayerManager;
class CraftingManager;
class ItemManager;
class GuildManager;

class ChatManager;

class ResourceManager;
class MissionManager;
class LootTableManager;

class BazaarManager;
class BankManager;

#include "ZoneServer.h"

class ZoneServerImplementation : public DatagramServiceThread, public ZoneServerServant {
	BasePacketHandler* phandler;

	ZoneProcessServerImplementation* processor;
	int procThreadCount;

	Vector<Zone*> zones;

	ObjectManager* objectManager;

	UserManager* userManager;
	PlayerManager* playerManager;
	CraftingManager* craftingManager;
	ItemManager* itemManager;
	ChatManager* chatManager;
	GuildManager* guildManager;

	ResourceManager* resourceManager;

	LootTableManager* lootTableManager;

	MissionManager* missionManager;

	BazaarManager* bazaarManager;
	BankManager* bankManager;

	int totalSentPackets;
	int totalResentPackets;

	int currentPlayers, maximumPlayers;
	int totalPlayers, totalDeletedPlayers;

	time_t startTimestamp;

	uint64 nextCreatureID;
	uint64 nextCellID;

	int serverState;

	String name;
	String messageoftheDay;

public:
	const static int OFFLINE = 0;
	const static int LOADING = 1;
	const static int ONLINE = 2;
	const static int LOCKED = 3;

public:
	ZoneServerImplementation(int processingThreads);

	~ZoneServerImplementation();

	void init();

	void run();

	void shutdown();

	void startManagers();

	void stopManagers();

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr);

	void handleMessage(ServiceClient* client, Packet* message);

	bool handleError(ServiceClient* client, Exception& e);

	// object methods
	void addObject(SceneObject* obj, bool doLock = true);

	SceneObject* getObject(uint64 oid, bool doLock = true);

	SceneObject* removeObject(uint64 oid, bool doLock = true);
	SceneObject* removeObject(SceneObject* obj, bool doLock = true);

	bool destroyObject(SceneObject* obj, bool doLock = true);

	SceneObject* getCachedObject(uint64 oid, bool doLock = true);

	SceneObject* removeCachedObject(uint64 oid, bool doLock = true);
	SceneObject* removeCachedObject(SceneObject* obj, bool doLock = true);

	// server methods
	void addTotalSentPacket(int count);
	void addTotalResentPacket(int count);

	void printInfo(bool forcedLog = true);
	void printEvents();

	void fixScheduler() {
		scheduler->fixQueue();
	}

	// user control methods
	bool banUser(String& name, String& admin);

	bool kickUser(String& name, String& admin);

	void changeUserCap(int amount = 50);

	int getConnectionCount();

	inline void increaseTotalDeletedPlayers() {
		lock();

		++totalDeletedPlayers;

		unlock();
	}

	// setters and getters

	inline String& getServerName() {
		return name;
	}

	inline PlayerManager* getPlayerManager() {
		return playerManager;
	}

	inline UserManager* getUserManager() {
		return userManager;
	}

	inline CraftingManager* getCraftingManager() {
		return craftingManager;
	}

	inline ItemManager* getItemManager() {
		return itemManager;
	}

	inline ChatManager* getChatManager() {
		return chatManager;
	}

	inline GuildManager* getGuildManager() {
		return guildManager;
	}

	inline BankManager* getBankManager() {
		return bankManager;
	}

	inline ResourceManager* getResourceManager() {
		return resourceManager;
	}

	inline LootTableManager* getLootTableManager() {
		return lootTableManager;
	}

	inline BazaarManager* getBazaarManager() {
		return bazaarManager;
	}

	inline MissionManager* getMissionManager() {
		return missionManager;
	}

	inline CreatureManager* getCreatureManager(int zone) {
		return (zones.get(zone))->getCreatureManager();
	}

	inline bool isServerLocked() {
		return serverState == LOCKED;
	}

	inline bool isServerOnline() {
		return serverState == ONLINE;
	}

	inline bool isServerOffline() {
		return serverState == OFFLINE;
	}

	inline bool isServerLoading() {
		return serverState == LOADING;
	}

	inline int getServerState() {
		return serverState;
	}

	inline Zone* getZone(int index) {
		return zones.get(index);
	}

	inline int getMaxPlayers() {
		return maximumPlayers;
	}

	inline int getTotalPlayers() {
		return totalPlayers;
	}

	inline int getDeletedPlayers() {
		return totalDeletedPlayers;
	}

	inline time_t getStartTimestamp() {
		return startTimestamp;
	}

	uint64 getNextCreatureID(bool doLock = true);
	uint64 getNextID(bool doLock = true);
	uint64 getNextCellID(bool doLock = true);

	//setters

	inline void setServerState(int state) {
		lock();

		serverState = state;

		unlock();
	}

	inline void setServerStateLocked() {
		lock();

		serverState = LOCKED;

		StringBuffer msg;
		msg << dec << "server locked";
		info(msg, true);

		unlock();
	}

	inline void setServerStateOnline() {
		lock();

		serverState = ONLINE;

		StringBuffer msg;
		msg << dec << "server unlocked";
		info(msg, true);

		unlock();
	}

	inline void loadMessageoftheDay() {
		File* file;
		FileReader* reader;

		try {
			file = new File("motd.txt");
			reader = new FileReader(file);
		} catch (FileNotFoundException& e) {
			file = NULL;
			reader = NULL;
		}

		String line;
		while(reader->readLine(line)) {
			messageoftheDay += line;
		}

		reader->close();
	}

	inline String& getMessageoftheDay() {
		return messageoftheDay;
	}
};

#endif /*ZONESERVERIMPLEMENTATION_H_*/
