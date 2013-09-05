/*
* JunkDealerSellListSuiCallback.h
*
*  Created on: Mar 24, 2011
*      Author: crush
*/

#ifndef JUNKDEALERSELLLISTSUICALLBACK_H_
#define JUNKDEALERSELLLISTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"

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
	uint64 itemId = listBox->getMenuObjectID(index);
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	ManagedReference<SceneObject*> selectedObject =inventory->getContainerObject(itemId);
	if (selectedObject == NULL || otherPressed==true ){
				return;
	}
	int iCredits = inventory->getContainerObject(itemId).castTo<TangibleObject*>()->getJunkValue();
	UnicodeString itemName = StringIdManager::instance()->getStringId(selectedObject->getDisplayedName().hashCode());
	Locker locker(selectedObject, player);
	selectedObject->destroyObjectFromWorld(true);
	selectedObject->destroyObjectFromDatabase(true);
	player->addCashCredits(iCredits,true);
	//player->sendSystemMessage("Index: " + String::valueOf(index) + " ItemID:" + String::valueOf(itemId) + " " + tst->getObjectNameStringIdName()+  " Cancel: " + String::valueOf(cancel) + " Other: " + String::valueOf(otherPressed));
	player->sendSystemMessage("You sell " + itemName + " for " + String::valueOf(iCredits) +" cr");
	bool bHaveStuffToSell = false;
    for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
    	Reference<TangibleObject*>  item = inventory->getContainerObject(i).castTo<TangibleObject*>();
    	if ((item->getJunkDealerNeeded() & 1) == 1 && item->getCraftersName().isEmpty() == true ){
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
			UnicodeString itemName = StringIdManager::instance()->getStringId(inventory->getContainerObject(i)->getDisplayedName().hashCode());
			Reference<TangibleObject*>  item = inventory->getContainerObject(i).castTo<TangibleObject*>();
			if ((item->getJunkDealerNeeded() & 1) == 1 && item->getCraftersName().isEmpty() == true )
				box->addMenuItem(itemName.toString(), inventory->getContainerObject(i)->getObjectID());
		}
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}else{
		player->sendSystemMessage("You currently have nothing further of interest.");
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
