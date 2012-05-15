/*
 * JtlShipListRequestCallback.h
 *
 *  Created on: 04/25/2011
 *      Author: crush
 */

#ifndef JTLSHIPLISTREQUESTCALLBACK_H_
#define JTLSHIPLISTREQUESTCALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
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
		ManagedReference<CreatureObject*> player = static_cast<CreatureObject*>(client->getPlayer());

		if (player == NULL)
			return;

		ManagedReference<SceneObject*> invokedObject = server->getZoneServer()->getObject(terminalObjectID);

		if (invokedObject == NULL)
			return;

		//This should be handled by the radial?
		if (!invokedObject->isInRange(player, 9.f)) {
			player->sendSystemMessage("You are too far out of range.");
			return;
		}

		JtlShipListResponse* resp = new JtlShipListResponse(player, invokedObject);
		player->sendMessage(resp);
	}
};


#endif /* JTLSHIPLISTREQUESTCALLBACK_H_ */
