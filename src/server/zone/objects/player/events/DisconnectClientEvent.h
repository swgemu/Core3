/*
 * DisconnectClientEvent.h
 *
 *  Created on: Oct 14, 2010
 *      Author: oru
 */

#ifndef DISCONNECTCLIENTEVENT_H_
#define DISCONNECTCLIENTEVENT_H_

class DisconnectClientEvent : public Task {
	ManagedReference<PlayerCreature*> player;
	ManagedReference<ZoneClientSession*> client;
	int eventType;

public:
	const static int DISCONNECT = 1;
	const static int LOGOUT = 2;
	const static int SETLINKDEAD = 3;

public:
	DisconnectClientEvent(PlayerCreature* pl, ZoneClientSession* cl, int type) : Task() {
		player = pl;
		client = cl;
		eventType = type;
	}

	void run() {
		if (player == NULL || client == NULL)
			return;

		Locker _locker(player);

		switch (eventType) {
		case DISCONNECT:
			player->disconnect(false, true);
			break;
		case LOGOUT:
			player->logout(true);
			break;
		case SETLINKDEAD:
			player->setLinkDead();
			break;
		}
	}


};


#endif /* DISCONNECTCLIENTEVENT_H_ */
