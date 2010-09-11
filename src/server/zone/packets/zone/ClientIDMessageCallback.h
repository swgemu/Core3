/*
 * ClientIDMessageCallback.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef CLIENTIDMESSAGECALLBACK_H_
#define CLIENTIDMESSAGECALLBACK_H_

#include "../MessageCallback.h"
#include "../../../db/ServerDatabase.h"
#include "../../../login/packets/ErrorMessage.h"
#include "server/zone/managers/account/AccountManager.h"

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

		StringBuffer query;
		query << "SELECT session_id FROM sessions WHERE account_id = " << accountId << ";";

		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (result != NULL && result->next()) {
			uint32 sesskey = result->getUnsignedInt(0);

			if (sesskey == sessionKey) {
				//Session was found
				//We need to check how many characters this account has online already.
				//We also need to store a reference to the Account object on the zoneSessionClient.

				AccountManager* accountManager = server->getZoneServer()->getAccountManager();
				accountManager->registerSession(client);

				BaseMessage* cpm = new ClientPermissionsMessage();
				client->sendMessage(cpm);

				return;
			}
		}

		ErrorMessage* errMsg = new ErrorMessage("Login Error", "Your session key is invalid, or has expired. Please restart your client.", 0x0);
		client->sendMessage(errMsg);
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
