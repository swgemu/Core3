/*
 * AccepTransactionMessageCallback.h
 *
 *  Created on: 07/06/2010
 *      Author: victor
 */

#ifndef ACCEPTTRANSACTIONMESSAGECALLBACK_H_
#define ACCEPTTRANSACTIONMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"

class AcceptTransactionMessageCallback : public MessageCallback {


public:
	AcceptTransactionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		if (player == NULL)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->handleAcceptTransactionMessage(player);
	}

};



#endif /* ACCEPTRANSACTIONMESSAGECALLBACK_H_ */
