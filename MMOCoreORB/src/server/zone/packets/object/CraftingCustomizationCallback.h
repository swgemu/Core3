/*
 * CraftingAddIngredientCallback.h
 *
 *  Created on: 10/07/2010
 *      Author: Kyle
 */

#ifndef CRAFTINGCUSTOMIZATIONCALLBACK_H_
#define CRAFTINGCUSTOMIZATIONCALLBACK_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"


class CraftingCustomizationCallback : public MessageCallback {
	String name;
	String customizationString;
	int schematicCount;
	int counter;
	byte templateChoice;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CraftingCustomizationCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();

		UnicodeString n;
		message->parseUnicode(n);

		name = n.toString();

		templateChoice = message->parseByte();

		schematicCount = message->parseInt();

		counter = message->parseByte();

		int value, count;

		StringBuffer ss;

		for (int i = 0; i < counter; ++i) {

			count = message->parseInt();

			value = message->parseInt();

			ss << count << " " << value;

			if (i < counter - 1)
				ss << " ";
		}

		customizationString = ss.toString();
	}

	void run() {
		ManagedReference<CreatureObject*> player = static_cast<CreatureObject*>(client->getPlayer());

		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<CraftingTool* > craftingTool = ghost->getLastCraftingToolUsed();

		if(craftingTool == NULL) {
			player->sendSystemMessage("@ui_craft:err_no_crafting_tool");
			return;
		}

		if(!craftingTool->isASubChildOf(player)) {
			return;
		}

		Locker _locker(craftingTool);

		craftingTool->customization(player, name, templateChoice, schematicCount, customizationString);


	}
};


#endif /* CRAFTINGCUSTOMIZATIONCALLBACK_H_ */
