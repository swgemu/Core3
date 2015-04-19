/*
 * InsuranceAllConfirmSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef INSURANCEALLCONFIRMSUICALLBACK_H_
#define INSURANCEALLCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/OptionBitmask.h"

class InsuranceAllConfirmSuiCallback : public SuiCallback {
public:
	InsuranceAllConfirmSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || cancelPressed || player == NULL)
			return;

		ZoneServer* zoneServer = player->getZoneServer();

		int bank = player->getBankCredits();
		int cash = player->getCashCredits();

		int cost = 100;

		ManagedReference<SceneObject*> term = suiBox->getUsingObject();

		if (term == NULL) {
			StringIdChatParameter params;
			params.setStringId("@ui:action_target_not_found_prose");
			params.setTT("@terminal_name:terminal_insurance");
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

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		Vector<ManagedReference<SceneObject*> > insurableItems = playerManager->getInsurableItems(player);

		if (insurableItems.size() == 0) {
			player->sendSystemMessage("@terminal_ui:no_uninsured_insurables");
			return;
		}

		int money = cash + bank;

		int j = 0;
		bool finished = true;

		for (int i = 0; i < insurableItems.size(); ++i) {
			SceneObject* obj = insurableItems.get(i);
			if (((i + 1) * 100) > money) {
				StringIdChatParameter params;
				params.setStringId("@error_message:prose_nsf_insure");
				params.setTT(obj->getObjectName());
				player->sendSystemMessage(params);
				finished = false;
				break;
			}

			if (obj != NULL && obj->isTangibleObject()) {
				j++;
				TangibleObject* item = cast<TangibleObject*>( obj);

				Locker locker(item, player);

				uint32 bitmask = item->getOptionsBitmask();
				bitmask |= OptionBitmask::INSURED;
				item->setOptionsBitmask(bitmask);
			}
		}

		cost *= j;

		if (bank < cost) {
			int diff = cost - bank;

			player->subtractBankCredits(cost - diff);
			player->subtractCashCredits(diff);
		} else {
			player->subtractBankCredits(cost);
		}

		if (finished) {
			player->sendSystemMessage("@base_player:insure_success");
		}
	}
};

#endif /* INSURANCEALLCONFIRMSUICALLBACK_H_ */
