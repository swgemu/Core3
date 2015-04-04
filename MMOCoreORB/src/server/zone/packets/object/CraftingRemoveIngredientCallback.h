/*
 * CraftingRemoveIngredientCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGREMOVEINGREDIENTCALLBACK_H_
#define CRAFTINGREMOVEINGREDIENTCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class CraftingRemoveIngredientCallback : public MessageCallback {
	uint64 objectID;
	int slot;
	int counter;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingRemoveIngredientCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		objectID(0), slot(0), counter(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();

		slot = message->parseInt();

		objectID = message->parseLong();

		counter = message->parseByte();
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		Reference<CraftingSession*> session = player->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			//warning("Trying to remove an ingredient when no session exists");
			return;
		}

		if(session->getState() > 2){
			//warning("Trying to remove an ingredient when the item is already assembled");
			return;
		}

		ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(player);
		}

		ManagedReference<SceneObject* > object = player->getZoneServer()->getObject(objectID);

		if(object == NULL || !object->isTangibleObject()) {
			player->sendSystemMessage("@ui_craft:err_invalid_ingredient");
			return;
		}

		Locker locker(session);

		TangibleObject* tano = cast<TangibleObject*>( object.get());
		session->removeIngredient(tano, slot, counter);
	}
};


#endif /* CRAFTINGREMOVEINGREDIENTCALLBACK_H_ */
