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
#include "server/login/account/Account.h"
#include "server/login/objects/CharacterList.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "ClientPermissionsMessage.h"

class ClientIDMessageCallback : public MessageCallback {
	uint32 dataLen;
	uint32 sessionID;
	uint32 accountID;

public:
	ClientIDMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->shiftOffset(4);

		dataLen = message->parseInt();

		//Get session key
		sessionID = message->parseInt();

		//Shift to end of session key, beginning of accountID:
		//pack->shiftOffset(dataLen - 4);

		//Get accountID
		accountID = message->parseInt();
	}

	void run() {
		client->setSessionID(sessionID);
		client->setAccountID(accountID);

		StringBuffer query;
		query << "SELECT session_id FROM sessions WHERE account_id = " << accountID;
		query << " AND  ip = '"<< client->getSession()->getIPAddress() <<"' AND expires > NOW();";

		//System::out << query.toString() << endl;

		Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery(query);

		if (result != NULL && result->next()) {
			uint32 sesskey = result->getUnsignedInt(0);

			result = NULL;

			if (sesskey == sessionID) {

				StringBuffer delQuery;
				delQuery << "DELETE FROM sessions WHERE account_id = " << accountID << ";";

				try {
					ServerDatabase::instance()->executeStatement(delQuery);
				} catch (DatabaseException& e) {
					client->info(e.getMessage(), true);
				}
				//Session was found
				//We need to check how many characters this account has online already.
				//We also need to store a reference to the Account object on the zoneSessionClient.

				/*ManagedReference<Account*> account = server->getZoneServer()->getAccount(accountID);
				System::out << "account found: " << account->getUsername() << endl;*/



				//if (!account->hasMaxOnlineCharacters()) {
					//client->setAccount(account);
					//account->addZoneSession(client);

					ManagedReference<Account*> account = server->getPlayerManager()->getAccount(accountID);
					if (account == NULL)
						return;

					client->resetCharacters();

					CharacterList* characters = account->getCharacterList();

					for(int i = 0; i < characters->size(); ++i) {
						CharacterListEntry* entry = &characters->get(i);
						GalaxyBanEntry* galaxyBan = account->getGalaxyBan(entry->getGalaxyName());
						if(!entry->isBanned() && galaxyBan == NULL)
							client->addCharacter(entry->getObjectID());
					}

					BaseMessage* cpm = new ClientPermissionsMessage();
					client->sendMessage(cpm);

					return;

					//return;
				//} else {
					//ErrorMessage* errMsg = new ErrorMessage("Login Error", "You already have the maximum number of characters logged in to this account.", 0x0);
					//client->sendMessage(errMsg);
					//return;
				//}
			}
		}

		ErrorMessage* errMsg = new ErrorMessage("Login Error", "Your session key is invalid, or has expired. Please re-login", 0x0);
		client->sendMessage(errMsg);

	}

	inline uint32 getDataLen() {
		return dataLen;
	}

	inline uint32 getSessionID() {
		return sessionID;
	}

	inline uint32 getAccountID() {
		return accountID;
	}
};


#endif /* CLIENTIDMESSAGECALLBACK_H_ */
