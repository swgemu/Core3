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
	int size;
	uint64 target;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	TargetUpdateCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		size = message->parseInt();
		target = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> object = (CreatureObject*) client->getPlayer();

		if (object == NULL)
			return;

		//object->info("received target update");

		object->setTargetID(target, true);

		ManagedReference<SceneObject*> scene = object->getZoneServer()->getObject(target);

		if (scene != NULL)
			object->notifyObservers(ObserverEventType::PLAYERCHANGEDTARGET, scene);
	}
};



#endif /* TARGETUPDATE_H_ */
