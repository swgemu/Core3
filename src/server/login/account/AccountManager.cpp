/*
 * AccountManager.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#include "engine/engine.h"

#include "Account.h"
#include "AccountManager.h"
#include "server/login/LoginClient.h"
#include "server/login/LoginServer.h"
#include "server/login/objects/CharacterList.h"
#include "server/login/packets/AccountVersionMessage.h"
#include "server/login/packets/EnumerateCharacterId.h"
#include "server/login/packets/LoginClientToken.h"
#include "server/login/packets/LoginClusterStatus.h"
#include "server/login/packets/LoginEnumCluster.h"

AccountManager::AccountManager(LoginServer* loginserv) : Logger("AccountManager") {
	loginServer = loginserv;

	autoRegistration = true;
	requiredVersion = "";
	maxOnlineCharacters = 1;

	accountMap = new AccountMap();

	setLogging(false);
	setGlobalLogging(false);
}

AccountManager::~AccountManager() {
	if (accountMap != NULL) {
		delete accountMap;
		accountMap = NULL;
	}
}

void AccountManager::loginAccount(LoginClient* client, Message* packet) {
	String username, password, version;
	AccountVersionMessage::parse(packet, username, password, version);

	Database::escapeString(username);
	Database::escapeString(password);

	if (!isRequiredVersion(version)) {
		client->sendErrorMessage("Login Error", "The client you are attempting to connect with does not match that required by the server.");
		return;
	}

	ManagedReference<Account*> account = validateAccountCredentials(client, username, password);

	if (account == NULL)
		return;

	//TODO: This should probably be refactored at some point.
	uint32 sessionID = System::random();

	Message* lct = new LoginClientToken(account, sessionID);
	client->sendMessage(lct);

	StringBuffer query;
	query << "REPLACE INTO sessions (account_id, session_id) VALUES (" << account->getAccountID() << ", " << sessionID << ");";

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		client->info(e.getMessage(), true);
	}

	client->sendMessage(loginServer->getLoginEnumClusterMessage());
	client->sendMessage(loginServer->getLoginClusterStatusMessage());

	CharacterList characters(account->getAccountID());

	Message* eci = new EnumerateCharacterID(&characters);
	client->sendMessage(eci);
}


Account* AccountManager::validateAccountCredentials(LoginClient* client, const String& username, const String& password) {
	Account* account = NULL;

	StringBuffer query;
	query << "SELECT a.active, a.password, SHA1('" << password << "'), IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > NOW() LIMIT 1), 0), IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > NOW() LIMIT 1), ''), a.account_id, a.station_id, a.created, a.admin_level FROM accounts a WHERE a.username = '" << username << "' LIMIT 1;";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (result->next()) {
		bool active = result->getBoolean(0);

		//Check if the account has been disabled
		if (active) {
			//Check the password
			String passwordStored = result->getString(1);
			String passwordHashed = result->getString(2);

			if (passwordStored == passwordHashed) {
				//Check if they are banned
				Time banExpires(result->getUnsignedInt(3));

				if (banExpires.isPast()) {
					uint32 accountID = result->getUnsignedInt(5);
					uint32 stationID = result->getUnsignedInt(6);
					uint32 created = result->getUnsignedInt(7);
					uint32 adminLevel = result->getUnsignedInt(8);

					//Check if the account is already in memory
					account = getAccount(accountID);

					//Create a new account object, if it's not already loaded
					if (account == NULL)
						account = new Account(this, username, accountID, stationID);

					//Locker lock(this, account);

					//Update the account's information
					account->setTimeCreated(created);
					account->setAdminLevel(adminLevel);

					addAccount(account);

				} else {
					String banReason = result->getString(4);

					StringBuffer reason;
					reason << "Your account has been banned from the server by the administrators.\n\n";
					reason << "Time remaining: " << round(banExpires.miliDifference() / 1000.0f * -1.0f) << "\n";
					reason << "Reason: " << banReason;

					client->sendErrorMessage("Account Banned", reason.toString());
				}
			} else {
				client->sendErrorMessage("Wrong Password", "The password you entered was incorrect.");
			}
		} else {
			client->sendErrorMessage("Account Disabled", "The server administrators have disabled your account.");
		}
	} else {
		//The user name didn't exist, so we check if auto registration is enabled and create a new account
		if (isAutoRegistrationEnabled()) {
			account = createAccount(username, password);
		} else {
			client->sendErrorMessage("Login Error", "Automatic registration is currently disabled. Please contact the administrators of the server in order to get an authorized account.");
		}
	}

	delete result;
	result = NULL;

	return account;
}

Account* AccountManager::createAccount(const String& username, const String& password) {
	uint32 stationID = System::random();

	StringBuffer query;
	query << "INSERT INTO accounts (username, password, station_id) VALUES (";
	query << "'" << username << "',";
	query << "SHA1('" << password << "'),";
	query << stationID << ");";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query.toString());

	if (result == NULL)
		return NULL;

	uint32 accountID = result->getLastAffectedRow();

	Account* account = new Account(this, username, accountID, stationID);

	addAccount(account);

	return account;
}
