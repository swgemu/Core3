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
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

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
		ManagedReference<CreatureObject*> player = static_cast<CreatureObject*>(client->getPlayer().get().get());

		Reference<CraftingSession*> session = cast<CraftingSession*>(player->getActiveSession(SessionFacadeType::CRAFTING));

		if(session == NULL) {
			warning("Trying to experiment when no session exists");
			return;
		}

		Locker locker(session);
		session->experiment(numRowsAttempted, expString, clientCounter);
	}
};


#endif /* CRAFTINGEXPERIMENTCALLBACK_H_ */
