/*
 * SuiEventNotificationCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef SUIEVENTNOTIFICATIONCALLBACK_H_
#define SUIEVENTNOTIFICATIONCALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/sui/SuiManager.h"

class SuiEventNotificationCallback : public MessageCallback {
	uint32 pageId;
	uint32 eventIndex;
	uint32 listSize1;
	uint32 listSize2;
	Vector<UnicodeString> arguments;

public:
	SuiEventNotificationCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), pageId(0), eventIndex(0), listSize1(0), listSize2(0) {

	}


	void parse(Message* message) {
		pageId = message->parseInt();

		eventIndex = message->parseInt();
		listSize1 = message->parseInt();
		listSize2 = message->parseInt();

		for (int i = 0; i < listSize1; ++i) {
			UnicodeString arg;
			message->parseUnicode(arg);
			arguments.add(arg);
		}
	}

	void run() {
		ManagedReference<CreatureObject*> playerCreature = client->getPlayer();

		if (playerCreature == NULL)
			return;

		server->getSuiManager()->handleSuiEventNotification(pageId, playerCreature, eventIndex, &arguments);
	}
};


#endif /* SUIEVENTNOTIFICATIONCALLBACK_H_ */
