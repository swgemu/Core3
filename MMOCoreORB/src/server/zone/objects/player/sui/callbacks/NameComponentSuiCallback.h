/*
 * NameComponentSuiCallback.h
 *
 *  Created on: Jan 25, 2025
 *  	Author: Halyn
 */

#ifndef NAMECOMPONENTSUICALLBACK_H_
#define NAMECOMPONENTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

class NameComponentSuiCallback : public SuiCallback {
public:
	NameComponentSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (player == nullptr || sui == nullptr)
			return;

		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<SceneObject*> object = sui->getUsingObject().get();

		if (object == nullptr || !object->isShipComponentObject())
			return;

		String componentName = args->get(0).toString();

		if (componentName.isEmpty())
			return;

		ZoneProcessServer* zoneProcess = player->getZoneProcessServer();

		if (zoneProcess == nullptr)
			return;

		NameManager* nameManager = zoneProcess->getNameManager();

		if (nameManager == nullptr)
			return;

		// Player Entered a name, validate with nane manager
		if (nameManager->checkNamingFilter(componentName) != NameManagerResult::ACCEPTED) {
			player->sendSystemMessage("@reverse_engineering_tool:reserved");

			//re-send SUI
			auto ghost = player->getPlayerObject();

			if (ghost == nullptr)
				return;

			ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME);

			inputBox->setUsingObject(object);

			inputBox->setPromptTitle("@reverse_engineering_tool:title2"); // Name New Component
			inputBox->setPromptText("@reverse_engineering_tool:prompt2"); // That is a reserved name.

			inputBox->setMaxInputSize(20);

			inputBox->setCallback(new NameComponentSuiCallback(player->getZoneServer()));
			inputBox->setForceCloseDistance(-1);

			ghost->addSuiBox(inputBox);

			player->sendMessage(inputBox->generateMessage());
			return;
		}

		Locker componentLock(object, player);

		object->setCustomObjectName(componentName, true);
	}
};

#endif /* NAMECOMPONENTSUICALLBACK_H_ */
