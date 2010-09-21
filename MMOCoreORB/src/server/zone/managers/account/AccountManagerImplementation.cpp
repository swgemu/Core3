/*
 * AccountManagerImplementation.cpp
 *
 *  Created on: Sep 11, 2010
 *      Author: crush
 */

#include "AccountManager.h"
#include "ZoneAccount.h"
#include "server/zone/ZoneClientSession.h"

/*
AccountManagerImplementation::~AccountManagerImplementation() {
	for (int i = 0; i < accountMap.size(); ++i) {
		ZoneAccount* account = accountMap.get(i);

		if (account == NULL)
			continue;

		delete account;
		account = NULL;
	}

	accountMap.removeAll();
}*/

void AccountManagerImplementation::registerSession(ZoneClientSession* client) {
	uint32 accountid = client->getAccountID();

	ZoneAccount* account = accountMap.get(accountid);

	//If the account isnt in the map, then we need to create it before registering the session with it.
	if (account == NULL) {
		account = new ZoneAccount(accountid);
		accountMap.put(accountid, account);
	}

	account->addSession(client);

	info("Registered session with account map. Account now has " + String::valueOf(account->getSessionCount()) + " total sessions.");
}

void AccountManagerImplementation::unregisterSession(ZoneClientSession* client) {
	uint32 accountid = client->getAccountID();

	ZoneAccount* account = accountMap.get(accountid);

	if (account == NULL)
		return;

	account->removeSession(client);

	info("Unregistered session with account map. Account now has " + String::valueOf(account->getSessionCount()) + " total sessions.");

	//If the account has no more sessions associated with it, drop it from the map.
	if (account->getSessionCount() < 1 && accountMap.drop(accountid))
		delete account;
}

int AccountManagerImplementation::getTotalOnlineCharacters(uint32 accountid) {
	ZoneAccount* account = accountMap.get(accountid);

	if (account == NULL)
		return 0;

	return account->getSessionCount();
}
