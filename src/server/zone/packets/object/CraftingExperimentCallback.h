/*
 * CraftingExperimentCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGEXPERIMENTCALLBACK_H_
#define CRAFTINGEXPERIMENTCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"


class CraftingExperimentCallback : public MessageCallback {

	int clientCounter;
	int numRowsAttempted;
	String expString;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingExperimentCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();

		clientCounter = message->parseByte();

		numRowsAttempted = message->parseInt();

		int rowEffected, pointsAttempted;
		StringBuffer ss;

		for (int i = 0; i < numRowsAttempted; ++i) {

			rowEffected = message->parseInt();
			pointsAttempted = message->parseInt();

			ss << rowEffected << " " << pointsAttempted << " ";
		}

		expString = ss.toString();
	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		ManagedReference<CraftingTool* > craftingTool = player->getLastCraftingToolUsed();

		if(craftingTool == NULL) {
			player->sendSystemMessage("ui_craft", "err_no_crafting_tool");
			return;
		}

		Locker _locker(craftingTool);

		craftingTool->experiment(player, numRowsAttempted, expString, clientCounter);
	}
};


#endif /* CRAFTINGEXPERIMENTCALLBACK_H_ */
