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


class CraftingRemoveIngredientCallback : public MessageCallback {
	uint64 objectID;
	int slot;
	int counter;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingRemoveIngredientCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
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

		Reference<CraftingSession*> session = cast<CraftingSession*>(player->getActiveSession(SessionFacadeType::CRAFTING));

		if(session == NULL) {
			warning("Trying to add an ingredient when no session exists");
			return;
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
