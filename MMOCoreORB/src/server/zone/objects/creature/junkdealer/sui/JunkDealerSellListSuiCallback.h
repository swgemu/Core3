/*
 * JunkDealerSellListSuiCallback.h
 *
 *  Created on: Mar 24, 2011 -a
 *      Author: cRush
 */

#ifndef JUNKDEALERSELLLISTSUICALLBACK_H_
#define JUNKDEALERSELLLISTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class JunkDealerSellListSuiCallback : public SuiCallback {

public:
	JunkDealerSellListSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());

		int index = Integer::valueOf(args->get(1).toString());

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		ManagedReference<SceneObject*> dealerScene = suiBox->getUsingObject().get();

		if (inventory == NULL || dealerScene == NULL || !dealerScene->isJunkDealer())
			return;

		JunkdealerCreature* junkDealer = dealerScene.castTo<JunkdealerCreature*>();
		int dealerType = junkDealer->getJunkDealerBuyerType();

		if (otherPressed == true) {
			int iCreditsTotal =0;

			for (int i = inventory->getContainerObjectsSize()-1; i > 0; i--) {
				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (junkDealer->canInventoryItemBeSoldAsJunk(item, dealerType)) {
					Locker locker(item, player);
					iCreditsTotal += item->getJunkValue();
					item->destroyObjectFromWorld(true);
					item->destroyObjectFromDatabase(true);
				}
			}

			StringIdChatParameter msg;
			player->addCashCredits(iCreditsTotal,true);
			msg.setStringId("@loot_dealer:prose_sold_all_junk");
			msg.setTT(suiBox->getUsingObject().get()->getObjectID());
			msg.setDI(iCreditsTotal);
			player->sendSystemMessage(msg);
			player->sendMessage(new StopNpcConversation(player, suiBox->getUsingObject().get()->getObjectID()));

		} else {
			uint64 itemId = listBox->getMenuObjectID(index);
			ManagedReference<SceneObject*> selectedObject = inventory->getContainerObject(itemId);

			if (selectedObject == NULL || !selectedObject->isTangibleObject()) {
				return;
			}

			Locker locker(selectedObject, player);
			StringIdChatParameter msg;
			msg.setStringId("@loot_dealer:prose_sold_junk");
			msg.setTT(selectedObject->getObjectID());
			int iCredits = selectedObject.castTo<TangibleObject*>()->getJunkValue();
			msg.setDI(iCredits);
			player->sendSystemMessage(msg);

			selectedObject->destroyObjectFromWorld(true);
			selectedObject->destroyObjectFromDatabase(true);
			player->addCashCredits(iCredits,true);
			bool bHaveStuffToSell = false;

			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (junkDealer->canInventoryItemBeSoldAsJunk(item, dealerType) == true) {
					bHaveStuffToSell = true;
					break;
				}
			}

			if (bHaveStuffToSell == true) {
				// create new window
				ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUNK_DEALER_SELL_LIST, SuiListBox::HANDLETHREEBUTTON);
				box->setCallback(new JunkDealerSellListSuiCallback(player->getZoneServer()));
				box->setPromptText("@loot_dealer:sell_prompt");
				box->setOtherButton(true, "@loot_dealer:btn_sell_all");
				box->setPromptTitle("@loot_dealer:sell_title");
				box->setHandlerText("handleUpdateSchematic");
				box->setOkButton(true, "@loot_dealer:btn_sell");
				box->setCancelButton(true, "@cancel");

				for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
					String itemName = inventory->getContainerObject(i)->getDisplayedName();

					ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
					if (junkDealer->canInventoryItemBeSoldAsJunk(item, dealerType) == true)
						box->addMenuItem("[" + String::valueOf(item->getJunkValue()) + "] " + itemName, inventory->getContainerObject(i)->getObjectID());
				}

				box->setUsingObject(suiBox->getUsingObject().get());
				player->getPlayerObject()->addSuiBox(box);
				player->sendMessage(box->generateMessage());
			} else {
				player->sendMessage(new StopNpcConversation(player, suiBox->getUsingObject().get()->getObjectID()));
			}
		}
	}
};

#endif /* JUNKDEALERSELLLISTSUICALLBACK_H_ */
