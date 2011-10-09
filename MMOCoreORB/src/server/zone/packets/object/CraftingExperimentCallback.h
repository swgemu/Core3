/*
 * CraftingExperimentCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGEXPERIMENTCALLBACK_H_
#define CRAFTINGEXPERIMENTCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
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
		ManagedReference<CreatureObject*> player = static_cast<CreatureObject*>(client->getPlayer());

		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<CraftingTool* > craftingTool = ghost->getLastCraftingToolUsed();

		if(craftingTool == NULL) {
			player->sendSystemMessage("ui_craft", "err_no_crafting_tool");
			return;
		}

		Locker _locker(craftingTool);

		uint64 lastExperiment = craftingTool->getLastExperimentationTimestamp();

		if(Time::currentNanoTime() - lastExperiment > 500000000)

			craftingTool->experiment(player, numRowsAttempted, expString, clientCounter);

		else {
			/// If someone tried to do the experimentation cheat, they get here
			ObjectControllerMessage* objMsg =
					new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0113);
			objMsg->insertInt(0x105);

			objMsg->insertInt(craftingTool->getExperimentationResult()); // Get last result
			objMsg->insertByte(clientCounter);

			player->sendMessage(objMsg);
		}
	}
};


#endif /* CRAFTINGEXPERIMENTCALLBACK_H_ */
