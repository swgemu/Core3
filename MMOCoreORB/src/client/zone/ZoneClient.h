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

#ifndef ZONECLIENT_H_
#define ZONECLIENT_H_

#include "engine/engine.h"
#include "objects/player/PlayerCreature.h"

class Zone;
class ZonePacketHandler;

class ZoneClient : public ServiceHandler {
	Reference<BaseClient*> client;

	Zone* zone;

	Reference<PlayerCreature*> player;

	uint32 key;
	uint32 accountID;

	//bool doRun;
	//bool disconnecting;

	BasePacketHandler* basePacketHandler;
	ZonePacketHandler* zonePacketHandler;

	MessageQueue messageQueue;

public:
	ZoneClient(int port);

	~ZoneClient();

	void initialize();

	bool connect() {
		return client->connect();
	}

	void disconnect() {
		client->disconnect();


		client->info("disconnected" , true);
	}

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
		return NULL;
	}

	bool deleteConnection(ServiceClient* client) {
		return false;
	}

	void handleMessage(ServiceClient* client, Packet* message);

	void processMessage(Message* message);

	bool handleError(ServiceClient* client, Exception& e) {
		return true;
	}

	void sendMessage(Message* msg) {
		client->sendPacket((BasePacket*) msg);
	}

	void sendMessage(StandaloneBaseMessage* msg) {
		client->sendPacket((BasePacket*) msg);

	#ifdef WITH_STM
		//TransactionalMemoryManager::commitPureTransaction();
	#endif
	}

	bool hasMessages() {
		return !messageQueue.isEmpty();
	}

	Message* getMessage() {
		return messageQueue.pop();
	}

	//void disconnect(bool doLock = true);

	void setZone(Zone* zone) {
		ZoneClient::zone = zone;
	}

	void setAccountID(uint32 id) {
		accountID = id;
	}

	void setPlayer(PlayerCreature* p) {
		player = p;
	}

	void setKey(uint32 key) {
		ZoneClient::key = key;
	}

	BaseClient* getClient() {
		return client;
	}

	PlayerCreature* getPlayer() {
		return player;
	}

	Zone* getZone() {
		return zone;
	}

	uint32 getKey(){
		return key;
	}

	uint32 getAccountID() {
		return accountID;
	}

};

#endif /* ZONECLIENT_H_ */
