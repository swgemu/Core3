/*
 * VerifyTradeMessageCallback.h
 *
 *  Created on: 07/06/2010
 *      Author: victor
 */

#ifndef VERIFYTRADEMESSAGECALLBACK_H_
#define VERIFYTRADEMESSAGECALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"

class VerifyTradeMessageCallback : public MessageCallback {


public:
	VerifyTradeMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->handleVerifyTradeMessage(player);
	}

};


#endif /* VERIFYTRADEMESSAGECALLBACK_H_ */
