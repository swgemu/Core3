/*
 * CreateTicketMessageCallback.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef CREATETICKETMESSAGECALLBACK_H_
#define CREATETICKETMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/packets/ui/VerifyPlayerNameResponseMessage.h"

class CreateTicketMessageCallback : public MessageCallback {

public:
	CreateTicketMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {
	}


	void parse(Message* message) {
		System::out << message->toStringData() << endl;
	}

	void run() {
		ManagedReference<SceneObject*> playerClient = client->getPlayer();

		if (playerClient == NULL)
			return;

		PlayerCreature* playerCreature = (PlayerCreature*) playerClient.get();
	}
};

#endif /* CREATETICKETMESSAGECALLBACK_H_ */
