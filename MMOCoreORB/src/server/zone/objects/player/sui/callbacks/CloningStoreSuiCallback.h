/*
 * CloningStoreConfirmSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef CLONINGSTORESUICALLBACK_H_
#define CLONINGSTORESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"

class CloningStoreSuiCallback : public SuiCallback {
public:
	CloningStoreSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed || player == NULL)
			return;

		int bank = player->getBankCredits();
		int cash = player->getCashCredits();

		int cost = 1000;

		ManagedReference<SceneObject*> term = suiBox->getUsingObject().get();

		if (term == NULL) {
			StringIdChatParameter params;
			params.setStringId("@ui:action_target_not_found_prose");
			params.setTT("@terminal_name:terminal_cloning");
			player->sendSystemMessage(params);
			return;
		}

		if (!player->isInRange(term, 15.0f)) {
			StringIdChatParameter params;
			params.setStringId("@container_error_message:container09_prose");
			params.setTT(term->getObjectName());
			player->sendSystemMessage(params);
			return;
		}
		//clone

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL) {
			return;
		}

		if (bank < cost) {
			int diff = cost - bank;

			if (diff > cash) {
				StringIdChatParameter params;
				params.setStringId("@error_message:nsf_clone");
				params.setDI((int)diff - cash);
				player->sendSystemMessage(params);

				return;
			}

			//pay bank portion
			player->subtractBankCredits(cost - diff);
			player->subtractCashCredits(diff);
		} else {
			player->subtractBankCredits(cost);
		}

		ManagedReference<SceneObject*> building = term->getRootParent();

		if (building == NULL || !building->isBuildingObject()) {
			return;
		}

		ManagedReference<BuildingObject*> buildingObject = dynamic_cast<BuildingObject*>(building.get());

		if (buildingObject != NULL) {
			ghost->setCloningFacility(buildingObject);
		}

		player->sendSystemMessage("@base_player:clone_success");

	}
};

#endif /* CLONINGSTORESUICALLBACK_H_ */
