/*
 * ClearClientEvent.h
 *
 *  Created on: Feb 14, 2010
 *      Author: oru
 */

#ifndef CLEARCLIENTEVENT_H_
#define CLEARCLIENTEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class ClearClientEvent : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<ZoneClientSession*> client;

public:
	ClearClientEvent(CreatureObject* pl, ZoneClientSession* cl) : Task() {
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
