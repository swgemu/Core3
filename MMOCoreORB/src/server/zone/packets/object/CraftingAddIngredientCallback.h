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
#include "server/zone/objects/tangible/tool/CraftingTool.h"


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
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer());

		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<CraftingTool* > craftingTool = ghost->getLastCraftingToolUsed();

		if(craftingTool == NULL) {
			player->sendSystemMessage("@ui_craft:err_no_crafting_tool");
			return;
		}

		if(!craftingTool->isASubChildOf(player)) {
			return;
		}

		ManagedReference<SceneObject* > object = player->getZoneServer()->getObject(objectID);

		if(object != NULL && object->isTangibleObject()) {

			Locker _locker(craftingTool);

			TangibleObject* tano = cast<TangibleObject*>( object.get());
			craftingTool->addIngredient(player, tano, slot, counter);

		} else {
			player->sendSystemMessage("@ui_craft:err_invalid_ingredient");
		}

	}
};


#endif /* CRAFTINGADDINGREDIENTCALLBACK_H_ */
