/*
 * CloningRequestConfirmSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef CLONINGREQUESTSUICALLBACK_H_
#define CLONINGREQUESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class CloningRequestSuiCallback : public SuiCallback {
public:
	CloningRequestSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || player == NULL)
			return;

		if (args->size() < 1) {
			player->info("CloningRequestSuiCallback: Wrong arg count");
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		PlayerManager* playerManager = server->getPlayerManager();

		if (index >= 0 && !cancelPressed) {
			if (!player->isDead()) {
				player->sendSystemMessage("You must be dead to activate your clone.");
			} else {
				SuiListBox* suiListBox = cast<SuiListBox*>( suiBox);
				playerManager->sendPlayerToCloner(player, suiListBox->getMenuObjectID(index), suiBox->getWindowType() - 1);
			}
		} else {
			if (player->isDead())
				player->sendSystemMessage("You will remain dead until you choose a location to clone or you are revived. Type /activateClone to restore the clone window.");
		}

	}
};

#endif /* CLONINGRequestSUICALLBACK_H_ */
