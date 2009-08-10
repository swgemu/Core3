/*
 * TargetUpdate.h
 *
 *  Created on: 10/08/2009
 *      Author: victor
 */

#ifndef TARGETUPDATE_H_
#define TARGETUPDATE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class TargetUpdateCallback : public MessageCallback {
	uint64 target;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	TargetUpdateCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		target = message->parseLong();
	}

	void run() {
		CreatureObject* object = (CreatureObject*) client->getPlayer();

		object->info("received target update");

		object->setTargetID(target, true);
	}
};



#endif /* TARGETUPDATE_H_ */
