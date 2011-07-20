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
	uint32 listSize1;
	uint32 listSize2;
	Vector<UnicodeString> arguments;

public:
	SuiEventNotificationCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}


	void parse(Message* message) {
		opcode = message->parseInt();

		cancel = message->parseInt();
		listSize1 = message->parseInt();
		listSize2 = message->parseInt();

		for (int i = 0; i < listSize1; ++i) {
			UnicodeString arg;
			message->parseUnicode(arg);
			arguments.add(arg);
		}
	}

	void run() {
		ManagedReference<SceneObject*> playerClient = client->getPlayer();

		if (playerClient == NULL)
			return;

		CreatureObject* playerCreature = (CreatureObject*) playerClient.get();

		server->getSuiManager()->handleSuiEventNotification(opcode, playerCreature, cancel, &arguments);
	}
};


#endif /* SUIEVENTNOTIFICATIONCALLBACK_H_ */
