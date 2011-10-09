/*
 * FactionRequestMessageCallback.h
 *
 *  Created on: Mar 18, 2011
 *      Author: crush
 */

#ifndef FACTIONREQUESTMESSAGECALLBACK_H_
#define FACTIONREQUESTMESSAGECALLBACK_H_

#include "engine/engine.h"
#include "FactionResponseMessage.h"


class FactionRequestMessageCallback : public MessageCallback {
public:
	FactionRequestMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
	}

	void run() {
		CreatureObject* object = cast<CreatureObject*>( client->getPlayer());

		if (object == NULL)
			return;

		Locker _locker(object);

		ManagedReference<PlayerObject*> ghost = object->getPlayerObject();

		FactionResponseMessage* frm = new FactionResponseMessage(ghost->getFactionStandingList());
		object->sendMessage(frm);
	}
};

#endif /* FACTIONREQUESTMESSAGECALLBACK_H_ */
