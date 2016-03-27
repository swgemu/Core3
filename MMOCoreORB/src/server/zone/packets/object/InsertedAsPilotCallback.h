/*
 * InsertedAsPilotCallback.h
 *
 *  Created on: Sep 5, 2011
 *      Author: theanswer
 */

#ifndef INSERTEDASPILOTCALLBACK_H_
#define INSERTEDASPILOTCALLBACK_H_

#include "server/zone/objects/player/PlayerObject.h"

class InsertedAsPilotCallback : public MessageCallback {
	uint32 movementCounter;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	InsertedAsPilotCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		movementCounter(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		movementCounter = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != NULL)
			ghost->setTeleporting(false);
	}
};


#endif /* INSERTEDASPILOTCALLBACK_H_ */
