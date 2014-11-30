/*
 * CraftingAddIngredientCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGADDINGREDIENTCALLBACK_H_
#define CRAFTINGADDINGREDIENTCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class CraftingAddIngredientCallback : public MessageCallback {
	uint64 objectID;
	int slot;
	int counter;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingAddIngredientCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();

		objectID = message->parseLong();

		slot = message->parseInt();

		message->parseInt();

		counter = message->parseByte();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer().castTo<CreatureObject*>();

		if (player == NULL)
			return;

		Reference<CraftingSession*> session = player->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			//warning("Trying to add an ingredient when no session exists");
			return;
		}

		if(session->getState() > 2){
			//warning("Trying to add an ingredient when the item is already assembled");
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
		session->addIngredient(tano, slot, counter);
	}
};


#endif /* CRAFTINGADDINGREDIENTCALLBACK_H_ */
