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
#include "server/zone/objects/transaction/TransactionLog.h"

class CloningStoreSuiCallback : public SuiCallback {
	bool hasCoupon;

public:
	CloningStoreSuiCallback(ZoneServer* server, bool coupon) : SuiCallback(server) {
		hasCoupon = coupon;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed || player == nullptr)
			return;

		ManagedReference<SceneObject*> term = suiBox->getUsingObject().get();

		if (term == nullptr) {
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

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		if (hasCoupon) {
			Locker lock(player);

			SceneObject* inventory = player->getSlottedObject("inventory");

			if (inventory == nullptr)
				return;

			uint32 couponCRC = STRING_HASHCODE("object/tangible/item/new_player/new_player_cloning_coupon.iff");

			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* sceneO = inventory->getContainerObject(i);

				if (sceneO == nullptr)
					continue;

				if (sceneO->getServerObjectCRC() == couponCRC) {
					Locker clock(sceneO, player);

					sceneO->destroyObjectFromWorld(true);
					sceneO->destroyObjectFromDatabase();
				}
			}
		} else {
			int bank = player->getBankCredits();
			int cash = player->getCashCredits();

			int cost = 1000;

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
				TransactionLog trxBank(player, TrxCode::CLONINGSYSTEM, cost - diff);

				player->subtractBankCredits(cost - diff);

				TransactionLog trxCash(player, TrxCode::CLONINGSYSTEM, diff, true);
				trxCash.groupWith(trxBank);

				player->subtractCashCredits(diff);
			} else {
				TransactionLog trx(player, TrxCode::INSURANCESYSTEM, cost);
				player->subtractBankCredits(cost);
			}
		}

		ManagedReference<SceneObject*> building = term->getRootParent();

		if (building == nullptr || !building->isBuildingObject()) {
			return;
		}

		ManagedReference<BuildingObject*> buildingObject = dynamic_cast<BuildingObject*>(building.get());

		if (buildingObject != nullptr) {
			ghost->setCloningFacility(buildingObject);
		}

		player->sendSystemMessage("@base_player:clone_success");

	}
};

#endif /* CLONINGSTORESUICALLBACK_H_ */
