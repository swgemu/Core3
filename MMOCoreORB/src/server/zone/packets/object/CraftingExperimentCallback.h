/*
 * CraftingExperimentCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGEXPERIMENTCALLBACK_H_
#define CRAFTINGEXPERIMENTCALLBACK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

class CraftingExperimentCallback : public MessageCallback {

	int clientCounter;
	int numRowsAttempted;
	String expString;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingExperimentCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		clientCounter(0), numRowsAttempted(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
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
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr) {
			return;
		}

		Reference<CraftingSession*> session = player->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if (session == nullptr) {
			warning() << "Player attempting to experiment when no CraftingSession exists -- Player: " << player->getDisplayedName() << " ID: " << player->getObjectID();
			return;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		// Lock the player
		Locker lock(player);

		ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != nullptr) {
			auto playerManager = zoneServer->getPlayerManager();

			if (playerManager == nullptr) {
				return;
			}

			playerManager->handleAbortTradeMessage(player);
		}

		if (session->getState() != 3)
			return;

		// Cross lock the session to the player
		Locker sessionLock(session, player);

		session->experiment(numRowsAttempted, expString, clientCounter);
	}
};


#endif /* CRAFTINGEXPERIMENTCALLBACK_H_ */
