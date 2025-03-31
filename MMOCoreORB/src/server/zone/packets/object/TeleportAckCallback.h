/*
 * TeleportAckCallback.h
 *
 *  Created on: 27/11/2010
 *      Author: victor
 */

#ifndef TELEPORTACKCALLBACK_H_
#define TELEPORTACKCALLBACK_H_

class TeleportAckCallback : public MessageCallback {
	uint32 movementCounter;
	ObjectControllerMessageCallback* objectControllerMain;

public:
	TeleportAckCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), movementCounter(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		movementCounter = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr) {
			return;
		}

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		ghost->setTeleporting(false);

		if (player->isPilotingShip()) {
			setHyperspacing(player);
		}
	}

	void setHyperspacing(CreatureObject* player) {
		auto root = player->getRootParent();

		if (root == nullptr || !root->isShipObject()) {
			return;
		}

		auto ship = root->asShipObject();

		if (ship == nullptr || !ship->isHyperspacing()) {
			return;
		}

		Locker lock(root, player);
		ship->setHyperspacing(false);
	}
};

#endif /* TELEPORTACKCALLBACK_H_ */
