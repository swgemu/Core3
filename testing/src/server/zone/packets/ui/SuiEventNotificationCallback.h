/*
 * SuiEventNotificationCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef SUIEVENTNOTIFICATIONCALLBACK_H_
#define SUIEVENTNOTIFICATIONCALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/managers/sui/SuiManager.h"

class SuiEventNotificationCallback : public MessageCallback {
	uint32 opcode;
	uint32 cancel;
	uint32 unk1;
	uint32 unk2;
	UnicodeString value;
	UnicodeString value2;

public:
	SuiEventNotificationCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}


	void parse(Message* message) {
		opcode = message->parseInt();

		cancel = message->parseInt();
		unk1 = message->parseInt();
		unk2 = message->parseInt();

		if (unk2 != 0)
			message->parseUnicode(value);
		if (unk2 > 1)
			message->parseUnicode(value2);
	}

	void run() {
		ManagedReference<SceneObject> playerClient = client->getPlayer();
		if (playerClient == NULL)
			return;

		PlayerCreature* playerCreature = (PlayerCreature*) playerClient.get();

		server->getSuiManager()->handleSuiEventNotification(opcode, playerCreature, cancel, value.toString(), value2.toString());

	}
};


#endif /* SUIEVENTNOTIFICATIONCALLBACK_H_ */
