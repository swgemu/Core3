/*
 * ZoneAccount.h
 *
 *  Created on: Sep 5, 2010
 *      Author: crush
 */

#ifndef ZONEACCOUNT_H_
#define ZONEACCOUNT_H_

#include "engine/engine.h"
#include "../../ZoneClientSession.h"

class ZoneAccount {
	//sessionId, zoneClient
	VectorMap<uint32, ManagedReference<ZoneClientSession*> > zoneClients;
	uint32 accountID;

public:
	ZoneAccount(uint32 accountid) {
		accountID = accountid;

		zoneClients.setNullValue(0);
		zoneClients.setNoDuplicateInsertPlan();
	}

	inline void addSession(ZoneClientSession* client) {
		if (zoneClients.contains(client->getSessionKey()))
			return;

		zoneClients.put(client->getSessionKey(), client);
	}

	inline void removeSession(ZoneClientSession* client) {
		zoneClients.drop(client->getSessionKey());
	}

	/**
	 * Returns the number of sessions that are online and associated with this account.
	 */
	inline int getSessionCount() {
		return zoneClients.size();
	}

	inline void setAccountID(uint32 accountid) {
		accountID = accountid;
	}

	inline uint32 getAccountID() {
		return accountID;
	}
};

#endif /* ZONEACCOUNT_H_ */
