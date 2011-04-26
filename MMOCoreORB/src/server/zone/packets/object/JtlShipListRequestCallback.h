/*
 * JtlShipListRequestCallback.h
 *
 *  Created on: 04/25/2011
 *      Author: crush
 */

#ifndef JTLSHIPLISTREQUESTCALLBACK_H_
#define JTLSHIPLISTREQUESTCALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/JtlShipListResponse.h"

class JtlShipListRequestCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	uint64 terminalObjectID;

public:
	JtlShipListRequestCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;

	}

	void parse(Message* message) {
		message->shiftOffset(4);
		terminalObjectID = message->parseLong();
	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		if (player == NULL)
			return;

		JtlShipListResponse* resp = new JtlShipListResponse(player, terminalObjectID);
		player->sendMessage(resp);
	}
};


#endif /* JTLSHIPLISTREQUESTCALLBACK_H_ */
