/*
 * ObjectMenuRequest.h
 *
 *  Created on: 03/08/2009
 *      Author: victor
 */

#include "ObjectControllerMessage.h"
#include "ObjectMenuResponse.h"
#include "server/zone/managers/radial/RadialManager.h"

class RadialClientItem {
	uint8 index;
	uint8 parentid;
	uint8 radialid;
	uint8 callback;

	UnicodeString command;

public:
	RadialClientItem() {

	}

	RadialClientItem(uint8 i, uint8 p, uint8 r, uint8 call, UnicodeString& c) {
		index = i;
		parentid = p;
		radialid = r;
		callback = call;
		command = c;
	}

	RadialClientItem(const RadialClientItem& c) {
		index = c.index;
		parentid = c.parentid;
		radialid = c.radialid;
		callback = c.callback;
		command = c.command;
	}

	RadialClientItem& operator=(const RadialClientItem& c) {
		if (this == &c)
			return *this;

		index = c.index;
		parentid = c.parentid;
		radialid = c.radialid;
		callback = c.callback;
		command = c.command;

		return *this;
	}

	void addToResponse(ObjectMenuResponse* menuResponse) {
		menuResponse->addRadialMenuItem(parentid, radialid, 3, command);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}
};

class ObjectMenuRequestCallback : public MessageCallback {
	int unknownSize;
	uint64 objectID;
	uint64 playerID;

	uint8 counter;

	//Reference<ObjectMenuResponse*> menuResponse;

	ObjectControllerMessageCallback* objectControllerMain;
	Vector<RadialClientItem> radialItems;

public:
	ObjectMenuRequestCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		unknownSize = message->parseInt();

		objectID = message->parseLong();
		playerID = message->parseLong();

		int size = message->parseInt();

		//menuResponse = new ObjectMenuResponse(client->getPlayer(), objectID, 0);

		try {
			for (int i = 0; i < size; i++) {
				uint8 index = message->parseByte();
				uint8 parentid = message->parseByte();
				uint8 radialid = message->parseByte();
				uint8 callback = message->parseByte();
				UnicodeString command;
				message->parseUnicode(command);

				radialItems.add(RadialClientItem(index, parentid, radialid, callback, command));

				/*StringBuffer infoMsg;
				infoMsg << "idx: " << index << " parent: " << parentid << " radialid: " << radialid;
				client->getPlayer()->info(infoMsg.toString());*/

				//if (radialid == 20)
				//callback = 3;

				//menuResponse->addRadialMenuItem(parentid, radialid, 3, command);
			}
		} catch (const Exception& e) {
			/*delete menuResponse;
			menuResponse = NULL;*/

			throw e;
		}

		//menuResponse->addRadialMenuItem(1, 20, 3, "test");

		counter = message->parseByte();
		//menuResponse->setCounter(counter);

		/*SceneObject* player = client->getPlayer();

		if (player != NULL)
			player->info("received object menu request");*/

	}

	void run() {
		//menuResponse->setCounter(counter);
		ManagedReference<CreatureObject*> player = (CreatureObject*)client->getPlayer();

		if (player == NULL)
			return;

		Reference<ObjectMenuResponse*> menuResponse = new ObjectMenuResponse(player, objectID, 0);

		for (int i = 0; i < radialItems.size(); ++i) {
			radialItems.get(i).addToResponse(menuResponse);
		}

		menuResponse->setCounter(counter);

		RadialManager* radialManager = server->getZoneServer()->getRadialManager();
		radialManager->handleObjectMenuRequest(player, menuResponse, objectID);

	}
};
