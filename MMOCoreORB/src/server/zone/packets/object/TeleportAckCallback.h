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
	}
};

#endif /* TELEPORTACKCALLBACK_H_ */
