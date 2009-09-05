/*
 * LoginClient.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef LOGINCLIENT_H_
#define LOGINCLIENT_H_

#include "engine/engine.h"

class LoginClient : public BaseClient {
	MessageQueue messageQueue;

	bool doRun;
	bool disconnecting;

	Vector<uint64> characterObjectIds;
	uint32 selectedCharacter;

	uint32 accountID;

public:
	LoginClient(const String& addr, int port);

	~LoginClient();

	void runLoginClient();

	void sendMessage(Message* msg) {
		BaseClient::sendPacket((BasePacket*) msg);
	}

	void sendMessage(StandaloneBaseMessage* msg) {
		BaseClient::sendPacket((BasePacket*) msg);
	}

	//void disconnect(bool doLock = true);

	void addCharacter(uint64 objectID) {
		characterObjectIds.add(objectID);
	}

	void setSelectedCharacter(uint32 id) {
		selectedCharacter = id;
	}

	void setAccountID(uint32 id) {
		accountID = id;
	}

	uint32 getAccountID() {
		return accountID;
	}

	uint32 getSelectedCharacter() {
		return selectedCharacter;
	}

	uint64 getCharacterObjectID(uint32 id) {
		return characterObjectIds.get(id);
	}

	void stopParsingPackets() {
		doRun = false;
	}

	/*void setZone(Zone* zone) {
		LoginClient::zone = zone;
	}

	void setPlayer(Player* p) {
		player = p;
	}

	void setKey(uint32 key) {
		LoginClient::key = key;
	}

	Player* getPlayer() {
		return player;
	}

	uint32 getKey(){
		return key;
	}*/
};


#endif /* LOGINCLIENT_H_ */
