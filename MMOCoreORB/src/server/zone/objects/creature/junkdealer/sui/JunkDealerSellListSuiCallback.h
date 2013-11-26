/*
 * JunkDealerSellListSuiCallback.h
 *
 *  Created on: Mar 24, 2011 -a
 *      Author: crush
 */

#ifndef JUNKDEALERSELLLISTSUICALLBACK_H_
#define JUNKDEALERSELLLISTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/creature/AiAgent.h"

class JunkDealerSellListSuiCallback : public SuiCallback {

public:
	JunkDealerSellListSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancel, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancel != 0)
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());

		if (otherPressed)
			player->info("Sell All");
		else if (cancel == 0)
			player->info("Sell");
		SuiListBox* listBox = cast<SuiListBox*>( suiBox);
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		ManagedReference<SceneObject*>  dealerScene = suiBox->getUsingObject().get();
		int dealerType= cast<JunkdealerCreature*>(dealerScene.get())->getJunkDealerBuyerType();
		if ( otherPressed==true ){
			int iCreditsTotal =0;
			for (int i = inventory->getContainerObjectsSize()-1; i > 0; i--) {
				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (cast<JunkdealerCreature*>(dealerScene.get())->canInventoryItemBeSoldAsJunk(item,dealerType)){
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
		}else{
			uint64 itemId = listBox->getMenuObjectID(index);
			ManagedReference<SceneObject*> selectedObject =inventory->getContainerObject(itemId);
			if (selectedObject == NULL){
				return;
			}
			Locker locker(selectedObject, player);
			StringIdChatParameter msg;
			msg.setStringId("@loot_dealer:prose_sold_junk");
			msg.setTT(selectedObject->getObjectID());
			int iCredits = cast<TangibleObject*>(inventory->getContainerObject(itemId).get())->getJunkValue();
			msg.setDI(iCredits);
			player->sendSystemMessage(msg);

			selectedObject->destroyObjectFromWorld(true);
			selectedObject->destroyObjectFromDatabase(true);
			player->addCashCredits(iCredits,true);
			//String itemName = selectedObject->getDisplayedName();
			//player->sendSystemMessage("Index: " + String::valueOf(index) + " ItemID:" + String::valueOf(itemId) + " " + tst->getObjectNameStringIdName()+  " Cancel: " + String::valueOf(cancel) + " Other: " + String::valueOf(otherPressed));
			//player->sendSystemMessage("You sell " + itemName + " for " + String::valueOf(iCredits) +" cr");
			bool bHaveStuffToSell = false;
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (cast<JunkdealerCreature*>(dealerScene.get())->canInventoryItemBeSoldAsJunk(item,dealerType)==true){
					bHaveStuffToSell=true;
					break;
				}
			}
			if (bHaveStuffToSell==true) {
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
					if (cast<JunkdealerCreature*>(dealerScene.get())->canInventoryItemBeSoldAsJunk(item,dealerType)==true )
						box->addMenuItem("[" + String::valueOf(item->getJunkValue()) + "] " +itemName, inventory->getContainerObject(i)->getObjectID());
				}
				box->setUsingObject(suiBox->getUsingObject().get());
				player->getPlayerObject()->addSuiBox(box);
				player->sendMessage(box->generateMessage());
			}else{
				player->sendMessage(new StopNpcConversation(player, suiBox->getUsingObject().get()->getObjectID()));
			}
		}

		/*try {
				player->wlock();

				SuiListBox* listbox = cast<SuiListBox*>( player->getSuiBox(boxid));

				if (listbox == NULL) {
							player->unlock();
							return;
				}

				if (cancel != 1 && index != -1) {
							Zone* zone = player->getZone();

							if (zone == NULL || zone->getZoneServer() == NULL) {
										player->removeSuiBox(boxid);
										listbox->finalize();
										player->unlock();
										return;
							}

							ZoneServer* zoneserver = zone->getZoneServer();

							ItemManager* itemmanager = zoneserver->getItemManager();

							if (itemmanager == NULL) {
										player->removeSuiBox(boxid);
										listbox->finalize();
										player->unlock();
										return;
							}

							ManagedReference<SceneObject*> dealerobj = suiBox->getUsingObject();

							if (dealerobj == NULL)
										return;

							//TODO: Check if the dealerobj is a junkdealer creature and cast.

							if (junkdealer == NULL) {
										player->sendSystemMessage("An error has occurred, preventing you from selling your junk to the junk dealer.");
										player->removeSuiBox(boxid);
										listbox->finalize();
										player->unlock();
										return;
							}

							uint64 itemid = listbox->getMenuObjectID(index);
							TangibleObject* item = cast<TangibleObject*>( player->getInventoryItem(itemid));

							if (item == NULL) {
										player->sendSystemMessage("An error has occurred, preventing you from selling your junk to the junk dealer.");
										player->removeSuiBox(boxid);
										listbox->finalize();
										player->unlock();
										return;
							}

							int lootvalue = item->getLootValue();

							if (lootvalue <= 0) {
										StfParameter* params = new StfParameter();
										params->addTU(junkdealerid);
										params->addTT(itemid);
										player->sendSystemMessage("junk_dealer", "prose_no_buy", params); //%TU shows no interest in purchasing %TT.
										delete params;

										player->removeSuiBox(boxid);
										listbox->finalize();
										player->unlock();
										return;
							}

							player->removeInventoryItem(itemid);
							item->sendDestroyTo(player);
							itemmanager->deletePlayerItem(player, item, false);
							item->finalize();

							player->addCashCredits(lootvalue);

							StfParameter* params = new StfParameter();
							params->addTT(itemid);
							params->addDI(lootvalue);
							player->sendSystemMessage("junk_dealer", "prose_sold_junk", params);
							delete params;

							//Send the list again.
							junkdealer->sendSellJunkListTo(player);
				}

				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
	} catch (...) {
				error("Unreported exception caught in SuiManager::handleSellJunkLootSelection");
				player->unlock();
	}*/
	}
};


#endif /* JUNKDEALERSELLLISTSUICALLBACK_H_ */
