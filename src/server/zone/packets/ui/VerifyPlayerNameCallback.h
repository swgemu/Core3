/*
 * VerifyPlayerNameCallback.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef VERIFYPLAYERNAMECALLBACK_H_
#define VERIFYPLAYERNAMECALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/packets/ui/VerifyPlayerNameResponseMessage.h"

class VerifyPlayerNameCallback : public MessageCallback {
	UnicodeString name;
	int counter;
	int unknown;

public:
	VerifyPlayerNameCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}


	void parse(Message* message) {
		message->parseUnicode(name);
		counter = message->parseInt();
		unknown = message->parseInt();
	}

	void run() {
		ManagedReference<SceneObject*> playerClient = client->getPlayer();

		if (playerClient == NULL)
			return;

		PlayerCreature* playerCreature = (PlayerCreature*) playerClient.get();

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		uint64 objectID = playerManager->getObjectID(name.toString());

		bool success = objectID > 0;

		VerifyPlayerNameResponseMessage* vpnrm = new VerifyPlayerNameResponseMessage(success, counter);
		playerCreature->sendMessage(vpnrm);
	}
};

#endif /* VERIFYPLAYERNAMECALLBACK_H_ */
