/*
 * TeleportAckCallback.h
 *
 *  Created on: 27/11/2010
 *      Author: victor
 */

#ifndef TELEPORTACKCALLBACK_H_
#define TELEPORTACKCALLBACK_H_


class TeleportAckCallback : public MessageCallback {
	uint32 unknown;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	TeleportAckCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		unknown = message->parseInt();
		//missionObjectID = message->parseLong();
	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		player->setTeleporting(false);
	}
};

#endif /* TELEPORTACKCALLBACK_H_ */
