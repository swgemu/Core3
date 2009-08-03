/*
 * ObjectMenuRequest.h
 *
 *  Created on: 03/08/2009
 *      Author: victor
 */

#include "ObjectControllerMessage.h"
#include "ObjectMenuResponse.h"

class ObjectMenuRequestCallback : public MessageCallback {
	int size;
	uint64 objectID;
	uint64 playerID;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	ObjectMenuRequestCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		size = message->parseInt();

		objectID = message->parseInt();
		playerID = message->parseInt();

		int size = pack->parseInt();

		ObjectMenuResponse* omr = new ObjectMenuResponse(player, objectid, 0);

		for (int i = 0; i < size; i++) {
			uint8 index = pack->parseByte();
			uint8 parentid = pack->parseByte();
			uint8 radialid = pack->parseByte();
			uint8 callback = pack->parseByte();

			//if (radialid == 20)
			callback = 3;

			pack->shiftOffset(4); // shift UnicodeString command

			omr->addRadialParent(radialid, callback, "");
		}

		uint8 counter = pack->parseByte();
		omr->setCounter(counter);

	}

	void execute() {


	}
};
