/*
 * ClientIDMessageCallback.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef CLIENTIDMESSAGECALLBACK_H_
#define CLIENTIDMESSAGECALLBACK_H_

#include "../MessageCallback.h"

#include "ClientPermissionsMessage.h"



class ClientIDMessageCallback : public MessageCallback {
	uint32 dataLen;
	uint32 sessionKey;
	uint32 accountId;

public:
	ClientIDMessageCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->shiftOffset(4);

		dataLen = message->parseInt();

		//Get session key
		sessionKey = message->parseInt();

		//Shift to end of session key, beginning of accountId:
		//pack->shiftOffset(dataLen - 4);

		//Get accountId
		accountId = message->parseInt();
	}

	void run() {
		client->setSessionKey(sessionKey);
		client->setAccountID(accountId);

		BaseMessage* cpm = new ClientPermissionsMessage();
		client->sendMessage(cpm);
	}

	inline uint32 getDataLen() {
		return dataLen;
	}

	inline uint32 getSessionKey() {
		return sessionKey;
	}

	inline uint32 getAccountId() {
		return accountId;
	}
};


#endif /* CLIENTIDMESSAGECALLBACK_H_ */
