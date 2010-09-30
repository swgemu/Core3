/*
 * Account.cpp
 *
 *  Created on: Sep 5, 2010
 *      Author: crush
 */

#include "../LoginClient.h"
#include "../LoginServer.h"
#include "Account.h"

void Account::login(LoginClient* client, LoginServer* loginServer) {
	if (accountID == 0)
		return;

	uint32 sessionKey = System::random();

	Message* lct = new LoginClientToken(username, sessionKey, accountID, stationID);
	client->sendMessage(lct);

	StringBuffer query;
	query << "REPLACE INTO `sessions` (`account_id`, `session_id`) VALUES (" << accountID << ", " << sessionKey << ");";

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		client->info(e.getMessage(), true);
	}

	client->sendMessage(loginServer->getLoginEnumClusterMessage());
	client->sendMessage(loginServer->getLoginClusterStatusMessage());

	CharacterList characters(accountID);

	Message* eci = new EnumerateCharacterID(&characters);
	client->sendMessage(eci);

	sendErrorMessageTo(client, "OR TEST", "This is a temporary OR test");
}


void Account::sendBanMessageTo(LoginClient* client, uint32 banID) {
	StringBuffer query, msg;
	query << "SELECT UNIX_TIMESTAMP(`expires`) - UNIX_TIMESTAMP(NOW()), reason FROM account_bans WHERE `ban_id` = " << banID << " LIMIT 1;";

	msg << "Your account has been banned.";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (result != NULL && result->next()) {
		int seconds = result->getInt(0);
		String reason = result->getString(1);

		msg << "\nYou have " << seconds << " seconds remaining before your ban expires.\n\nReason: " << reason;
	}

	sendErrorMessageTo(client, "Account Banned", msg.toString());

	delete result;
}

bool Account::create(ConfigManager* configManager, LoginClient* client) {
	if (configManager->getAutoReg() == 0) {
		sendErrorMessageTo(client, "Login Error", "Automatic account registration has been disabled.\n\nPlease contact the server administrators to create an account on this server.");
		return false;
	}

	//Generate a random StationID
	//TODO: We could use this to associate an LPE profile or SWGEmu global id with the account object.
	stationID = System::random();

	StringBuffer query;
	query << "INSERT INTO accounts (`username`, `password`, `station_id`) VALUES "
		  << "('" << username << "', SHA1('" << password << "'), " << stationID << ");";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		accountID = (uint32) result->getLastAffectedRow();
	} catch (DatabaseException& e) {
		//Account already exists?
		client->info(e.getMessage(), true);
	}

	delete result;

	//Account created and ready for login.
	return true;
}

bool Account::validate(ConfigManager* configManager, LoginClient* client) {
	StringBuffer query;
	query << "SELECT account_id, station_id, active, ban_id, password, SHA1('" << password << "') FROM accounts WHERE username = '" << username << "' LIMIT 1;";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (result == NULL) {
		sendErrorMessageTo(client, "Server Error", "The server has encountered an error and is not accepting logins at this time.\n\nPlease try again later.");
		return false;
	}

	if (result->next()) {
		accountID = result->getUnsignedInt(0);
		stationID = result->getUnsignedInt(1);

		bool active = result->getBoolean(2);

		//If the account has been disabled.
		if (!active) {
			sendErrorMessageTo(client, "Login Error", "Your account has been disabled by the server administrators.");
			return false;
		}

		uint32 banID = result->getUnsignedInt(3);

		//If the character is banned.
		if (banID > 0) {
			sendBanMessageTo(client, banID);
			delete result;
			return false;
		}

		String passwordHash = result->getString(4);
		String enteredPassword = result->getString(5);

		if (passwordHash != enteredPassword) {
			delete result,

			client->sendMessage(new ErrorMessage("Password Error", "Incorrect password entered.", 0));
			return false;
		}

	} else {
		delete result;
		//The account couldn't be found, so we attempt to create one.
		return create(configManager, client);
	}

	delete result;

	return true;
}
