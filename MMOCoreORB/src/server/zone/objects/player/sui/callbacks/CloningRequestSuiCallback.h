/*
 * CloningRequestConfirmSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef CLONINGREQUESTSUICALLBACK_H_
#define CLONINGREQUESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/player/PlayerManager.h"

class CloningRequestSuiCallback : public SuiCallback {
	int typeofdeath;

public:
	CloningRequestSuiCallback(ZoneServer* server, int tod)
		: SuiCallback(server) {

		typeofdeath = tod;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || player == NULL || args->size() <= 0)
			return;

		SuiListBox* listbox = cast<SuiListBox*>(suiBox);

		int index = Integer::valueOf(args->get(0).toString());

		if (!player->isDead())
			return;

		if (index < 0 || index >= listbox->getMenuSize() || cancelPressed) {
			player->sendSystemMessage("You will remain dead until you choose a location to clone or you are revived. Type /activateClone to restore the cloning window.");
			return;
		}

		PlayerManager* playerManager = server->getPlayerManager();
		playerManager->sendPlayerToCloner(player, listbox->getMenuObjectID(index), typeofdeath);
	}
};

#endif /* CLONINGRequestSUICALLBACK_H_ */
