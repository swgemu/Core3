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
	uint32 unk;


	ObjectControllerMessageCallback* objectControllerMain;
public:
	InsertedAsPilotCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		unk = message->parseInt();

	}

	void run() {
		ManagedReference<CreatureObject*> object = cast<CreatureObject*>(client->getPlayer());

		if (object == NULL)
			return;

		PlayerObject* ghost = object->getPlayerObject();

		if (ghost != NULL)
			ghost->setTeleporting(false);

	}
};


#endif /* INSERTEDASPILOTCALLBACK_H_ */
