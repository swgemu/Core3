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
#include "server/ServerCore.h"

AccountManager::AccountManager(LoginServer* loginserv) : Logger("AccountManager") {
	loginServer = loginserv;

	autoRegistration = true;
	requiredVersion = "";
	maxOnlineCharacters = 1;

	setLogging(false);
	setGlobalLogging(false);

	if (ServerCore::truncateDatabases()) {
		try {
			String query = "TRUNCATE TABLE characters";

			Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

			info("characters table truncated", true);
		} catch (Exception& e) {
			error(e.getMessage());
		}
	}
}

AccountManager::~AccountManager() {

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

	uint32 accountID = account->getAccountID();

	client->setAccountID(accountID);

	String ip = client->getSession()->getAddress().getIPAddress();

	StringBuffer sessionQuery;
	sessionQuery << "REPLACE INTO sessions (account_id, session_id, ip, expires) VALUES (";
	sessionQuery << accountID << ", " << sessionID << ", '" << ip << "' , ADDTIME(NOW(), '00:15'));";

	StringBuffer logQuery;
	logQuery << "INSERT INTO account_log (account_id, ip_address, timestamp) VALUES (" << accountID << ", '" << ip << "', NOW());";

	try {
		ServerDatabase::instance()->executeStatement(sessionQuery);
		ServerDatabase::instance()->executeStatement(logQuery);
	} catch (DatabaseException& e) {
		client->info(e.getMessage(), true);
	}

	client->sendMessage(loginServer->getLoginEnumClusterMessage());
	client->sendMessage(loginServer->getLoginClusterStatusMessage());

	Message* eci = new EnumerateCharacterID(account->getCharacterList());
	client->sendMessage(eci);
}


Account* AccountManager::validateAccountCredentials(LoginClient* client, const String& username, const String& password) {

	StringBuffer query;
	query << "SELECT a.account_id, a.username, a.password, a.salt, IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.username = '" << username << "' LIMIT 1;";

	String passwordStored;
	Account* account = getAccount(query.toString(), passwordStored);

	if(account == NULL) {

		//The user name didn't exist, so we check if auto registration is enabled and create a new account
		if (isAutoRegistrationEnabled() && client != NULL) {
			account = createAccount(username, password, passwordStored);
		} else {
			if(client != NULL)
				client->sendErrorMessage("Login Error", "Automatic registration is currently disabled. Please contact the administrators of the server in order to get an authorized account.");
			return NULL;
		}
	}

	if(!account->isActive()) {

		if(client != NULL)
			client->sendErrorMessage("Account Disabled", "The server administrators have disabled your account.");

		return NULL;
	}

	//Check hash version
	String passwordHashed;
	if(account->getSalt() == "") {
		passwordHashed = Crypto::SHA1Hash(password);
	} else {
		passwordHashed = Crypto::SHA256Hash(dbSecret + password + account->getSalt());
	}

	if (passwordStored != passwordHashed) {

		if(client != NULL)
			client->sendErrorMessage("Wrong Password", "The password you entered was incorrect.");

		return NULL;
	}
	//update hash if unsalted
	if(account->getSalt() == "")
		updateHash(username, password);

	//Check if they are banned
	if(account->isBanned()) {

		StringBuffer reason;
		reason << "Your account has been banned from the server by the administrators.\n\n";
		reason << "Time remaining: " << round(((account->getBanExpires() - time(0)) / 60.0f) / 60.f) << " Minutes\n";
		reason << "Reason: " << account->getBanReason();

		if(client != NULL)
			client->sendErrorMessage("Account Banned", reason.toString());

		return NULL;
	}

	return account;
}

void AccountManager::updateHash(const String& username, const String& password) {
	String salt = Crypto::randomSalt();
	String hash = Crypto::SHA256Hash(dbSecret + password + salt);

	StringBuffer query;
	query << "UPDATE accounts SET password = '" << hash << "', ";
	query << "salt = '" << salt << "' ";
	query << "WHERE username = '" << username << "';";

	try {
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}
}

Account* AccountManager::createAccount(const String& username, const String& password, String& passwordStored) {

	uint32 stationID = System::random();

	String salt = Crypto::randomSalt();
	String hash = Crypto::SHA256Hash(dbSecret + password + salt);

	StringBuffer query;
	query << "INSERT INTO accounts (username, password, station_id, salt) VALUES (";
	query << "'" << username << "',";
	query << "'" << hash << "',";
	query << stationID << ",";
	query << "'" << salt << "');";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query.toString());

	if (result == NULL)
		return NULL;

	uint32 accountID = result->getLastAffectedRow();

	return getAccount(accountID, passwordStored);
}

Account* AccountManager::getAccount(uint32 accountID) {
	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	String passwordStored;
	return getAccount(query.toString(), passwordStored);
}

Account* AccountManager::getAccount(uint32 accountID, String& passwordStored) {
	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	return getAccount(query.toString(), passwordStored);
}

Account* AccountManager::getAccount(String query, String& passwordStored) {

	Account* account = NULL;

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (result->next()) {

		account = new Account(this);

		account->setActive(result->getBoolean(0));
		account->setUsername(result->getString(1));
		passwordStored = result->getString(2);
		account->setSalt(result->getString(3));

		account->setBanExpires(result->getUnsignedInt(4));
		account->setBanReason(result->getString(5));

		account->setAccountID(result->getUnsignedInt(6));
		account->setStationID(result->getUnsignedInt(7));

		account->setTimeCreated(result->getUnsignedInt(8));
		account->setAdminLevel(result->getInt(9));
	}
	delete result;
	result = NULL;

	return account;
}
