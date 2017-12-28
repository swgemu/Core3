/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONECLIENT_H_
#define ZONECLIENT_H_

#include <stddef.h>

#include "client/zone/objects/player/PlayerCreature.h"
#include "engine/service/MessageQueue.h"
#include "engine/service/ServiceHandler.h"
#include "engine/service/proto/BaseClient.h"
#include "engine/service/proto/BasePacket.h"
#include "engine/service/proto/StandaloneBaseMessage.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"

class Zone;
class ZonePacketHandler;
namespace engine {
namespace service {
class Message;
class ServiceClient;
namespace proto {
class BasePacketHandler;
}  // namespace proto
}  // namespace service
}  // namespace engine
namespace sys {
namespace lang {
class Exception;
}  // namespace lang
namespace net {
class Packet;
class Socket;
class SocketAddress;
}  // namespace net
}  // namespace sys

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
