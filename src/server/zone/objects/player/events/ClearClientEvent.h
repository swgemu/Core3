/*
 * ClearClientEvent.h
 *
 *  Created on: Feb 14, 2010
 *      Author: oru
 */

#ifndef CLEARCLIENTEVENT_H_
#define CLEARCLIENTEVENT_H_

#include "../PlayerCreature.h"

class ClearClientEvent : public Task {
	ManagedReference<PlayerCreature*> player;
	ManagedReference<ZoneClientSession*> client;

public:
	ClearClientEvent(PlayerCreature* pl, ZoneClientSession* cl) : Task() {
		player = pl;
		client = cl;
	}

	void run() {
		if (player == NULL || client == NULL)
			return;

		Locker _locker(player);

		if (player->getClient() == client)
			player->setClient(NULL);
	}


};


#endif /* CLEARCLIENTEVENT_H_ */
