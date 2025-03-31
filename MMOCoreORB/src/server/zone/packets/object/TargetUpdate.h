/*
 * TargetUpdate.h
 *
 *  Created on: 10/08/2009
 *      Author: victor
 */

#ifndef TARGETUPDATE_H_
#define TARGETUPDATE_H_

#include "server/zone/objects/creature/CreatureObject.h"

class TargetUpdateCallback : public MessageCallback {
	int size;
	uint64 targetID;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	TargetUpdateCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		size(0), targetID(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		size = message->parseInt();
		targetID = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> object = client->getPlayer();

		if (object == nullptr) {
			return;
		}

		if (object->getTargetID() != targetID) {
			setPlayerTargetID(object);
		}

		if (object->isPilotingShip()) {
			setShipTargetID(object);
		}
	}
	
	void setPlayerTargetID(CreatureObject* object) {
		if (targetID != 0) {
			ManagedReference<SceneObject*> target = object->getZoneServer()->getObject(targetID);

			if (target != nullptr) {
				object->notifyObservers(ObserverEventType::PLAYERCHANGEDTARGET, target);
			} else {
				targetID = 0;
			}
		}

		object->setTargetID(targetID, true);
	}

	void setShipTargetID(CreatureObject* object) {
		auto root = object->getRootParent();

		if (root == nullptr || !root->isShipObject()) {
			return;
		}

		auto ship = root->asShipObject();

		if (ship == nullptr || ship->getShipTargetID() == targetID) {
			return;
		}
		
		Locker cLock(root, object);
		ship->setShipTargetID(targetID, true);
	}
};

#endif /* TARGETUPDATE_H_ */
