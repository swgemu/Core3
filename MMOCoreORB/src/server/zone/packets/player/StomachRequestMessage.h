/*
 * StomachRequestMessage.h
 *
 *  Created on: 02/02/2010
 *      Author: victor
 */

#ifndef STOMACHREQUESTMESSAGE_H_
#define STOMACHREQUESTMESSAGE_H_

#include "../MessageCallback.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"

class StomachRequestMessageCallback : public MessageCallback {
public:
	StomachRequestMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(client->getPlayer().get().get());

		if (player == NULL)
			return;

		Reference<PlayerObject*> playerObject = player->getSlottedObject("ghost").castTo<PlayerObject*>();

		PlayerObjectDeltaMessage9* delta = new  PlayerObjectDeltaMessage9(playerObject);
		delta->updateStomachFilling();
		delta->close();

		client->sendMessage(delta);
	}

};


#endif /* STOMACHREQUESTMESSAGE_H_ */
