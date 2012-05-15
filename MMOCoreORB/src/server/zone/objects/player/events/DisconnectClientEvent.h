/*
 * DisconnectClientEvent.h
 *
 *  Created on: Oct 14, 2010
 *      Author: oru
 */

#ifndef DISCONNECTCLIENTEVENT_H_
#define DISCONNECTCLIENTEVENT_H_

#include "server/zone/objects/player/PlayerObject.h"

class DisconnectClientEvent : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<ZoneClientSession*> client;
	int eventType;

public:
	const static int DISCONNECT = 1;
	const static int LOGOUT = 2;
	const static int SETLINKDEAD = 3;

public:
	DisconnectClientEvent(CreatureObject* pl, ZoneClientSession* cl, int type) : Task() {
		player = pl;
		client = cl;
		eventType = type;
	}

	void run() {
		if (player == NULL || client == NULL)
			return;

		Locker _locker(player);

		PlayerObject* ghost = player->getPlayerObject();

		switch (eventType) {
		case DISCONNECT:
			ghost->disconnect(false, true);
			break;
		case LOGOUT:
			ghost->logout(true);
			break;
		case SETLINKDEAD:
			ghost->setLinkDead();
			break;
		}
	}


};


#endif /* DISCONNECTCLIENTEVENT_H_ */
