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
#include "templates/params/OptionBitmask.h"
#include "server/zone/objects/transaction/TransactionLog.h"

class InsuranceAllConfirmSuiCallback : public SuiCallback {
public:
	InsuranceAllConfirmSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed || player == nullptr)
			return;

		ZoneServer* zoneServer = player->getZoneServer();

		int bank = player->getBankCredits();
		int cash = player->getCashCredits();

		int cost = 100;

		ManagedReference<SceneObject*> term = suiBox->getUsingObject().get();

		if (term == nullptr) {
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

		TransactionLog trxBank(player, TrxCode::INSURANCESYSTEM, 100 * insurableItems.size()); // Actual cost is set below

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

			if (obj != nullptr && obj->isTangibleObject()) {
				j++;
				TangibleObject* item = cast<TangibleObject*>( obj);

				Locker locker(item, player);

				uint32 bitmask = item->getOptionsBitmask();
				bitmask |= OptionBitmask::INSURED;
				item->setOptionsBitmask(bitmask);
				trxBank.addRelatedObject(obj->getObjectID());
			}
		}

		trxBank.addState("insuredCount", j);
		cost *= j;

		if (bank < cost) {
			int diff = cost - bank;

			trxBank.setAmount(diff, true);
			player->subtractBankCredits(cost - diff);
			trxBank.commit();

			TransactionLog trxCash(player, TrxCode::INSURANCESYSTEM, cost - diff, true);
			trxCash.groupWith(trxBank);
			player->subtractCashCredits(diff);
		} else {
			trxBank.setAmount(cost, false);
			player->subtractBankCredits(cost);
		}

		if (finished) {
			player->sendSystemMessage("@base_player:insure_success");
		}
	}
};

#endif /* INSURANCEALLCONFIRMSUICALLBACK_H_ */
