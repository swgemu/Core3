/*
 * VerifyPlayerNameCallback.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef VERIFYPLAYERNAMECALLBACK_H_
#define VERIFYPLAYERNAMECALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/packets/ui/VerifyPlayerNameResponseMessage.h"

class VerifyPlayerNameCallback : public MessageCallback {
	UnicodeString name;
	uint64 playerID;

public:
	VerifyPlayerNameCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}


	void parse(Message* message) {
		message->parseUnicode(name);
		playerID = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> playerClient = client->getPlayer();

		if (playerClient == NULL)
			return;

		CreatureObject* playerCreature = cast<CreatureObject*>( playerClient.get());

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		bool success = playerManager->existsName(name.toString());

		VerifyPlayerNameResponseMessage* vpnrm = new VerifyPlayerNameResponseMessage(success);
		playerCreature->sendMessage(vpnrm);
	}
};

#endif /* VERIFYPLAYERNAMECALLBACK_H_ */
