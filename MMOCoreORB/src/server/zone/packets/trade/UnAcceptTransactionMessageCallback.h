/*
 * UnAcceptTransactionMessageCallback.h
 *
 *  Created on: 07/06/2010
 *      Author: victor
 */

#ifndef UNACCEPTTRANSACTIONMESSAGECALLBACK_H_
#define UNACCEPTTRANSACTIONMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"

class UnAcceptTransactionMessageCallback : public MessageCallback {


public:
	UnAcceptTransactionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		ManagedReference<SceneObject*> scene = client->getPlayer();

		if (scene == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>(scene.get());

		if (player == NULL)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->handleUnAcceptTransactionMessage(player);
	}

};


#endif /* UNUnAcceptTransactionMessageCallback_H_ */
