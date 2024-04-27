/*
 * ClientIdMessageCallback.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef CLIENTIDMESSAGECALLBACK_H_
#define CLIENTIDMESSAGECALLBACK_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/packets/MessageCallback.h"
#include "server/db/ServerDatabase.h"
#include "server/login/packets/ErrorMessage.h"
#include "server/login/account/Account.h"
#include "server/login/objects/CharacterList.h"
#include "server/login/account/AccountManager.h"

#include "ClientPermissionsMessage.h"

class ClientIdMessageCallback : public MessageCallback {
	uint32 gameBits{};
	uint32 dataLen;
	String sessionID;
	uint32 accountID;
	String version;

public:
	ClientIdMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server), dataLen(0), accountID(0) {
		setCustomTaskQueue("slowQueue");
	}

	void parse(Message* message) {
		gameBits = message->parseInt();
		dataLen = message->parseInt() - 4; //accountid embedded

		StringBuffer buf;

		for (uint32 i = 0; i < dataLen; ++i) {
			buf << static_cast<char>(message->parseByte());
		}

		sessionID = buf.toString();

		accountID = message->parseInt();
		version = message->parseAscii();
	}

	void run() {
		StringBuffer query;
		query << "SELECT session_id FROM sessions WHERE account_id = " << accountID;
		query << " AND  ip = '"<< client->getSession()->getIPAddress() <<"' AND expires > NOW();";

		UniqueReference<ResultSet*> result(ServerDatabase::instance()->executeQuery(query));

		if (result == nullptr || !result->next()) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Unable to obtain a valid session key from the server, please login again.", 0x0);
			client->sendMessage(errMsg);

			return;
		}

		// Get the Session Key the client is using
		String sessionKey = result->getString(0);

		/*
		info(true) << "got session id from db: " << sessionKey << endl
			<< "parsed session id in packet: " << sessionID << endl
			<< "Client Version: " << version << endl
			<< "gameBits: " << gameBits;
		*/

		// Set the result null
		result = nullptr;

		// Check client version
		String validClient = ConfigManager::instance()->getString("Core3.PlayerManager.ValidClientVersion", "20050408-18:00");

		if (!version.contains(validClient)) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "You are using an improper client version.", 0x0);
			client->sendMessage(errMsg);

			return;
		}

		// Invalid Session Key
		if (sessionKey != sessionID) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Your session key is invalid, or has expired. Please re-login", 0x0);
			client->sendMessage(errMsg);

			return;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		client->setSessionID(sessionID);
		client->setAccountID(accountID);

		auto account = AccountManager::getAccount(accountID, true);

		if (account == nullptr) {
			return;
		}

		// Lock the account object
		Locker alocker(account);

		AccountManager::expireSession(account, sessionID);
		client->resetCharacters();

		int galaxyID = zoneServer->getGalaxyID();

		Reference<CharacterList*> characters = account->getCharacterList();
		const GalaxyBanEntry* galaxyBan = account->getGalaxyBan(galaxyID);

		bool canConnect = true;

		if (galaxyBan != nullptr) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "You are banned from this galaxy.\n\nReason:" + galaxyBan->getBanReason(), 0x0);
			client->sendMessage(errMsg);

			canConnect = false;
		} else {
			for (int i = 0; i < characters->size(); ++i) {
				const CharacterListEntry* entry = &characters->get(i);

				if (!entry->isBanned()) {
					client->addCharacter(entry->getObjectID(), entry->getGalaxyID());
				} else {
					client->addBannedCharacter(entry->getObjectID(), entry->getGalaxyID());
				}
			}

			if (zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()) {
				canConnect = false;
			}
		}

		auto allowedChars = ConfigManager::instance()->getInt("Core3.PlayerCreationManager.MaxCharactersPerGalaxy", 10);
		bool canCreateCharacter = (client->getCharacterCount(galaxyID) < allowedChars);

		// Check if player has permission to create more characters
		auto permissionMessage = new ClientPermissionsMessage(canConnect, canCreateCharacter);
		client->sendMessage(permissionMessage);
	}

	inline uint32 getDataLen() const {
		return dataLen;
	}

	inline const String& getSessionID() const {
		return sessionID;
	}

	inline uint32 getAccountID() const {
		return accountID;
	}
};

#endif /* CLIENTIDMESSAGECALLBACK_H_ */
