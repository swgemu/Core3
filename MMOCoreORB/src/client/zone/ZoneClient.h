/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONECLIENT_H_
#define ZONECLIENT_H_

#include "client/zone/objects/player/PlayerCreature.h"

class Zone;
class ZonePacketHandler;

class ZoneClient : public ServiceHandler {
	Reference<BaseClient*> client;

	Zone* zone;
	SpaceZone* spaceZone;

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

	//void disconnect(bool doLock = true);

	void setZone(Zone* zone) {
		ZoneClient::zone = zone;
		ZoneClient::spaceZone = nullptr;
	}

	void setZone(SpaceZone* zone) {
		ZoneClient::spaceZone = zone;
		ZoneClient::zone = nullptr;
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

	SpaceZone* getSpaceZone() {
		return spaceZone;
	}

	uint32 getKey(){
		return key;
	}

	uint32 getAccountID() {
		return accountID;
	}

};

#endif /* ZONECLIENT_H_ */
