/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONECLIENT_H_
#define ZONECLIENT_H_

#include "client/zone/objects/player/PlayerCreature.h"
#include "client/zone/ZonePacketHandler.h"

class Zone;
class ZonePacketHandler;

class ZoneClient : public ServiceHandler {
	Reference<BaseClient*> client;

	Zone* zone;

	Reference<PlayerCreature*> player;

	uint32 accountID;

	BasePacketHandler* basePacketHandler;
	ZonePacketHandler* zonePacketHandler;

	MessageQueue messageQueue;

public:
	ZoneClient(const String& address, int port);

	~ZoneClient();

	void initialize();

	bool connect() {
		return client->connect();
	}

	void disconnect() {
		if (zonePacketHandler != nullptr) {
			client->info(true) << "disconnecting after " << zonePacketHandler->getPacketCount() << " packets.";
		}

		client->disconnect();

		client->info(true) << "disconnected";
	}

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
		return nullptr;
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

	void setZone(Zone* zone) {
		ZoneClient::zone = zone;
	}

	void setAccountID(uint32 id) {
		accountID = id;
	}

	void setPlayer(PlayerCreature* p) {
		player = p;
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

	uint32 getAccountID() {
		return accountID;
	}
};

#endif /* ZONECLIENT_H_ */
