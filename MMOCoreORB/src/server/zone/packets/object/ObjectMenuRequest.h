/*
 * ObjectMenuRequest.h
 *
 *  Created on: 03/08/2009
 *      Author: victor
 */

#include "ObjectControllerMessage.h"
#include "ObjectMenuResponse.h"
#include "server/zone/managers/radial/RadialManager.h"

class ObjectMenuRequestCallback : public MessageCallback {
	int unknownSize;
	uint64 objectID;
	uint64 playerID;

	ObjectMenuResponse* menuResponse;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	ObjectMenuRequestCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
		menuResponse = NULL;
	}

	void parse(Message* message) {
		unknownSize = message->parseInt();

		objectID = message->parseLong();
		playerID = message->parseLong();

		int size = message->parseInt();

		menuResponse = new ObjectMenuResponse(client->getPlayer(), objectID, 0);

		try {
			for (int i = 0; i < size; i++) {
				uint8 index = message->parseByte();
				uint8 parentid = message->parseByte();
				uint8 radialid = message->parseByte();
				uint8 callback = message->parseByte();
				UnicodeString command;
				message->parseUnicode(command);

				/*StringBuffer infoMsg;
				infoMsg << "idx: " << index << " parent: " << parentid << " radialid: " << radialid;
				client->getPlayer()->info(infoMsg.toString());*/

				//if (radialid == 20)
				//callback = 3;

				menuResponse->addRadialMenuItem(parentid, radialid, 3, command);
			}
		} catch (const Exception& e) {
			delete menuResponse;
			menuResponse = NULL;

			throw e;
		}

		//menuResponse->addRadialMenuItem(1, 20, 3, "test");

		uint8 counter = message->parseByte();
		menuResponse->setCounter(counter);

		/*SceneObject* player = client->getPlayer();

		if (player != NULL)
			player->info("received object menu request");*/

	}

	void run() {
		if (menuResponse != NULL) {
			ManagedReference<PlayerCreature*> player = (PlayerCreature*)client->getPlayer();

			if (player != NULL) {
				RadialManager* radialManager = server->getZoneServer()->getRadialManager();
				radialManager->handleObjectMenuRequest(player, menuResponse, objectID);
			}
		}
	}
};
