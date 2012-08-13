/*
 * InsuranceMenuSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef INSURANCEMENUSUICALLBACK_H_
#define INSURANCEMENUSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/InsuranceAllConfirmSuiCallback.h"
#include "server/zone/objects/tangible/OptionBitmask.h"

class InsuranceMenuSuiCallback : public SuiCallback {
public:
	InsuranceMenuSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed || player == NULL)
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ZoneServer* zoneServer = player->getZoneServer();

		int bank = player->getBankCredits();
		int cash = player->getCashCredits();

		int cost = 100;

		ManagedReference<SceneObject*> term = listBox->getUsingObject();

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

		if (otherPressed) {

			int items = listBox->getMenuSize();

			StringBuffer promptText;
			promptText << "You are about to insure all your items. The total cost is " << String::valueOf(items * cost) << " credits.\n\nAre you sure?";

			ManagedReference<SuiMessageBox*> insureAll = new SuiMessageBox(player, SuiWindowType::INSURANCE_CONFIRM_ALL);
			insureAll->setUsingObject(term);
			insureAll->setPromptTitle("@terminal_ui:insure_all_t");
			insureAll->setPromptText(promptText.toString());
			insureAll->setCancelButton(true, "");
			insureAll->setForceCloseDistance(32.f);
			insureAll->setCallback(new InsuranceAllConfirmSuiCallback(server));


			player->getPlayerObject()->addSuiBox(insureAll);
			player->sendMessage(insureAll->generateMessage());

		} else {
			if (index != -1) {
				uint64 objectID = listBox->getMenuObjectID(index);
				ManagedReference<SceneObject*> obj = zoneServer->getObject(objectID);

				if (obj == NULL || !obj->isTangibleObject()) {
					player->sendSystemMessage("@error_message:unable_to_insure");
					return;
				}

				TangibleObject* item = cast<TangibleObject*>( obj.get());

				if (item != NULL && !(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isWeaponObject() || item->isArmorObject() || item->isWearableObject())) {

					if (bank < cost) {
						int diff = cost - bank;

						if (diff > cash) {
							StringIdChatParameter params;
							params.setStringId("@error_message:prose_nsf_insure");
							params.setTT(item->getObjectName());
							player->sendSystemMessage(params);
							return;
						}

						//pay bank portion
						player->subtractBankCredits(cost - diff);
						player->subtractCashCredits(diff);
					} else {
						player->subtractBankCredits(cost);
					}

					uint32 bitmask = item->getOptionsBitmask();
					bitmask |= OptionBitmask::INSURED;
					item->setOptionsBitmask(bitmask);

					StringIdChatParameter params;
					params.setStringId("@base_player:prose_insure_success");
					params.setTT(item->getObjectName());
					player->sendSystemMessage(params);

				} else if (item->getOptionsBitmask() & OptionBitmask::INSURED) {
					StringIdChatParameter params;
					params.setStringId("@error_message:prose_item_already_insured");
					params.setTT(item->getObjectName());
					player->sendSystemMessage(params);
				} else {
					StringIdChatParameter params;
					params.setStringId("@error_message:prose_item_uninsurable");
					params.setTT(item->getObjectName());
					player->sendSystemMessage(params);
				}
			} else {
				player->sendSystemMessage("@ui_auc:err_no_item_selected");
			}
		}
	}
};

#endif /* GUILDMEMBEROPTIONSSUICALLBACK_H_ */
