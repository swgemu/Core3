/*
 * TrainerCreatureImplementation.cpp
 *
 *  Created on: 26/05/2010 -a
 *      Author: victor
 */

#include "JunkdealerCreature.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/tangible/loot/LootkitObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/junkdealer/sui/JunkDealerSellListSuiCallback.h"
#include "server/zone/objects/creature/AiAgent.h"


void JunkdealerCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return;

	CreatureObject* player = cast<CreatureObject*>( obj);
	PlayerObject* ghost = player->getPlayerObject();
	StartNpcConversation* conv = new StartNpcConversation(player, getObjectID(), "");
	player->sendMessage(conv);
	ghost->setLastNpcConvStr(getObjectNameStringIdName());
	ghost->setLastNpcConvMessStr("");
	sendInitialMessage(player);

}


void JunkdealerCreatureImplementation::sendInitialMessage(CreatureObject* player) {
	int dealerConversationType= _this.get()->getJunkDealerConversationType();
	String stffile = getConversationString(dealerConversationType);
	String stfname = "s_bef51e38";
	switch (dealerConversationType){
		case JUNKCONVARMS:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVFINARY:{
			stfname = "s_9666d79a";
			break;
		}
		case JUNKCONVDENDERRORI:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVDENDERTHEED:{
			stfname = "s_e88820";
			break;
		}
		case JUNKCONVLILABORVO:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVMALIKVISTAL:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVNADOWATTOS:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVNATHANTAIKE:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVOLLOBOJABBAS:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVQUICHDANTOOINE:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVREGGINYM:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVSHEANILAKE:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVSNEGVALARIAN:{
			stfname = "s_3c06418f";
			break;
		}
		case JUNKCONVJAWATRADER:{
			stfname = "s_3c06418f";
			break;
		}
		default:{ // This Covers JUNKCONVGENERIC as well
			stfname = "s_bef51e38";
			break;
		}

	}
	StringIdChatParameter params(stffile, stfname);
	NpcConversationMessage* m1 = new NpcConversationMessage(player, params);
	player->sendMessage(m1);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->setLastNpcConvMessStr("junkdealer_initial");
	sendInitialChoices(player);
}


void JunkdealerCreatureImplementation::sendInitialChoices(CreatureObject* player) {
	StringList* slist = new StringList(player);
	int dealerConversationType= _this.get()->getJunkDealerConversationType();
	switch (dealerConversationType){
		case JUNKCONVARMS:{
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_370a03c");
			break;
		}
		case JUNKCONVFINARY:{
			slist->insertOption(getConversationString(JUNKCONVFINARY), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVFINARY), "s_370a03c");
			break;
		}
		case JUNKCONVDENDERRORI:{
			slist->insertOption(getConversationString(JUNKCONVDENDERRORI), "s_673b632f");
			slist->insertOption(getConversationString(JUNKCONVDENDERRORI), "s_a753e4d6");
			break;
		}
		case JUNKCONVDENDERTHEED:{
			slist->insertOption(getConversationString(JUNKCONVDENDERTHEED), "s_54fab04f");
			break;
		}
		case JUNKCONVLILABORVO:{
			slist->insertOption(getConversationString(JUNKCONVLILABORVO), "s_54fab04f");
			break;
		}
		case JUNKCONVMALIKVISTAL:{
			slist->insertOption(getConversationString(JUNKCONVMALIKVISTAL), "s_54fab04f");
			break;
		}
		case JUNKCONVNADOWATTOS:{
			slist->insertOption(getConversationString(JUNKCONVNADOWATTOS), "s_54fab04f");
			break;
		}
		case JUNKCONVNATHANTAIKE:{
			slist->insertOption(getConversationString(JUNKCONVNATHANTAIKE), "s_54fab04f");
			break;
		}
		case JUNKCONVOLLOBOJABBAS:{
			slist->insertOption(getConversationString(JUNKCONVOLLOBOJABBAS), "s_54fab04f");
			break;
		}
		case JUNKCONVQUICHDANTOOINE:{
			slist->insertOption(getConversationString(JUNKCONVQUICHDANTOOINE), "s_54fab04f");
			break;
		}
		case JUNKCONVREGGINYM:{
			slist->insertOption(getConversationString(JUNKCONVREGGINYM), "s_54fab04f");
			break;
		}
		case JUNKCONVSHEANILAKE:{
			slist->insertOption(getConversationString(JUNKCONVSHEANILAKE), "s_54fab04f");
			break;
		}
		case JUNKCONVSNEGVALARIAN:{
			slist->insertOption(getConversationString(JUNKCONVSNEGVALARIAN), "s_54fab04f");
			break;
		}
		case JUNKCONVJAWATRADER:{
			slist->insertOption(getConversationString(JUNKCONVJAWATRADER), "s_54fab04f");
			break;
		}
		default:{ // This Covers JUNKCONVGENERIC as well
			slist->insertOption(getConversationString(JUNKCONVGENERIC), "s_54fab04f");
			slist->insertOption(getConversationString(JUNKCONVGENERIC), "s_cd7a3f41");
			slist->insertOption(getConversationString(JUNKCONVGENERIC), "s_3aa18b2d");
			break;
		}
	}
	PlayerObject* ghost = player->getPlayerObject();
	ghost->setLastNpcConvMessStr("junkdealer_options");

	player->sendMessage(slist);
}

void JunkdealerCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return;

	CreatureObject* player = cast<CreatureObject*>( obj);
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost->getLastNpcConvStr() != getObjectNameStringIdName())
		return;

	String stffile = getConversationString(_this.get()->getJunkDealerConversationType());

	String choice;

	if (ghost->countLastNpcConvOptions() > 0) {
		if (ghost->getLastNpcConvMessStr() == "junkdealer_kit5")
			choice = ghost->getLastNpcConvOption(0);
		else if (ghost->countLastNpcConvOptions() > (uint32)option)
			choice = ghost->getLastNpcConvOption(option);
	}

	ghost->clearLastNpcConvOptions();


	if (ghost->getLastNpcConvMessStr() == "junkdealer_options") {
		switch (option) {
			case 0: {
				String chatResponses[] = {"","s_84a67771", "s_24f30320","s_e8ceb290","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771"};
				StringIdChatParameter params(stffile, chatResponses[_this.get()->getJunkDealerConversationType()]);
				NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
				ghost->setLastNpcConvMessStr("junkdealer_sell");
				ghost->addLastNpcConvOptions(choice);
				player->sendMessage(skillmsg);

				createSellJunkLootSelection(player);
				player->sendMessage(new StopNpcConversation(player, getObjectID()));
				break;
			}
			case 1: {
				String chatResponses[] = {"","s_4bd9d15e", "s_df5bd64e","s_1eb9feb7","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771"};
				StringIdChatParameter params(stffile, chatResponses[_this.get()->getJunkDealerConversationType()]);
				NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
				ghost->setLastNpcConvMessStr("junkdealer_nosell");
				ghost->addLastNpcConvOptions(choice);
				player->sendMessage(skillmsg);
				player->sendMessage(new StopNpcConversation(player, getObjectID()));
				break;
			}
			case 2: {
				StringIdChatParameter params(stffile, "s_d9e6b751");
				NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
				ghost->setLastNpcConvMessStr("junkdealer_kit1");
				ghost->addLastNpcConvOptions(choice);
				player->sendMessage(skillmsg);

				StringList* slist = new StringList(player);

				slist->insertOption(stffile, "s_6d53d062");

				player->sendMessage(slist);

				break;
			}
		}
	} else if (ghost->getLastNpcConvMessStr() == "junkdealer_kit1") {
		if (option == 0) {
			StringIdChatParameter params(stffile, "s_e29f48dc");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_kit2");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

			StringList* slist = new StringList(player);

			slist->insertOption(stffile, "s_324b9b0f");

			player->sendMessage(slist);

		}
	} else if (ghost->getLastNpcConvMessStr() == "junkdealer_kit2") {
		if (option == 0) {
			StringIdChatParameter params(stffile, "s_12fe83a6");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_kit3");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

			StringList* slist = new StringList(player);

			slist->insertOption(stffile, "s_e1a103e5");

			player->sendMessage(slist);

		}
	} else if (ghost->getLastNpcConvMessStr() == "junkdealer_kit3") {
		if (option == 0) {
			StringIdChatParameter params(stffile, "s_4d65752");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_kit4");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

			StringList* slist = new StringList(player);

			slist->insertOption(stffile, "s_d347bee3");
			slist->insertOption(stffile, "s_b60b73f8");

			player->sendMessage(slist);

		}
	} else if (ghost->getLastNpcConvMessStr() == "junkdealer_kit4") {
		if (option == 0) {
			StringIdChatParameter params(stffile, "s_3fc7eb45");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_kit5");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

			StringList* slist = new StringList(player);

			slist->insertOption(stffile, "s_ee977dee");
			slist->insertOption(stffile, "s_8f39769");
			slist->insertOption(stffile, "s_fe657cdd");
			slist->insertOption(stffile, "s_9ede4b84");
			slist->insertOption(stffile, "s_87c5851b");

			player->sendMessage(slist);

		} else {
			StringIdChatParameter params(stffile, "s_3633b5a5");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_nokit");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);
		}

	} else if (ghost->getLastNpcConvMessStr() == "junkdealer_kit5") {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		bool found = false;

		uint32 CRC = 0;

		switch (option) {
			case 0: {
				CRC = ORANGERUG;
				break;
			}
			case 1: {
				CRC = BLUERUG;
				break;
			}
			case 2: {
				CRC = GONG;
				break;
			}
			case 3: {
				CRC = TABLE;
				break;
			}
			default: {
				CRC = SCULPTURE;
				break;
			}
		}

		Locker locker(inventory);

		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			uint32 objectCRC = inventory->getContainerObject(i)->getServerObjectCRC();
			if (objectCRC == BLUERUG || objectCRC == ORANGERUG || objectCRC == GONG || objectCRC == TABLE || objectCRC == SCULPTURE) {
				found = true;
			}
		}

		ManagedReference<SceneObject*> bank = player->getSlottedObject("bank");

		Locker blocker(bank);

		for (int j = 0; j < bank->getContainerObjectsSize(); j++) {
			uint32 objectCRC = bank->getContainerObject(j)->getServerObjectCRC();
			if (objectCRC == BLUERUG || objectCRC == ORANGERUG || objectCRC == GONG || objectCRC == TABLE || objectCRC == SCULPTURE) {
				found = true;
			}
		}

		if (found) {
			StringIdChatParameter params(stffile, "s_3df21ea0");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_alreadyhavekit");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

		} else if (inventory->hasFullContainerObjects()) {
			StringIdChatParameter params(stffile, "s_5b10c0b9");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_inventoryfull");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

		} else {
			StringIdChatParameter params(stffile, "s_14efaaa2");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("junkdealer_givekit");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);

			ManagedReference<LootkitObject*> lootkit = (server->getZoneServer()->createObject(CRC, 2)).castTo<LootkitObject*>();

			lootkit->sendTo(player, true);
			if (!inventory->transferObject(lootkit, -1, true))
				info("Could not add object.", true);
		}
	} else
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
}

void JunkdealerCreatureImplementation::createSellJunkLootSelection(CreatureObject* player) {
	if (player == NULL)
		return;

	if (_this.get()->getJunkDealerConversationType()==0){
		player->sendSystemMessage("Junk Dealer Not Configured at this time :(");
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
	}else{
		int dealerType= _this.get()->getJunkDealerBuyerType();
		bool bHaveStuffToSell = false;
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
			if (canInventoryItemBeSoldAsJunk(item,dealerType)==true){
				bHaveStuffToSell=true;
				break;
			}
		}

		if (bHaveStuffToSell==true) {
			// create new window
			ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUNK_DEALER_SELL_LIST, SuiListBox::HANDLETHREEBUTTON);
			box->setCallback(new JunkDealerSellListSuiCallback(server->getZoneServer()));

			box->setPromptText("@loot_dealer:sell_prompt");
			box->setOtherButton(true, "@loot_dealer:btn_sell_all");
			box->setPromptTitle("@loot_dealer:sell_title");

			box->setHandlerText("handleUpdateSchematic");
			box->setOkButton(true, "@loot_dealer:btn_sell");
			box->setCancelButton(true, "@cancel");

			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				UnicodeString itemName = StringIdManager::instance()->getStringId(inventory->getContainerObject(i)->getDisplayedName().hashCode());
				if (itemName == "")
					itemName=inventory->getContainerObject(i)->getCustomObjectName();
				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (canInventoryItemBeSoldAsJunk(item,dealerType)==true)
					box->addMenuItem("[" + String::valueOf(item->getJunkValue()) + "Cr] " + itemName.toString(), inventory->getContainerObject(i)->getObjectID());
			}

			box->setUsingObject(_this.get());
			player->getPlayerObject()->addSuiBox(box);
			player->sendMessage(box->generateMessage());
		}else{
			StringIdChatParameter msg;
			msg.setStringId("@loot_dealer:prose_no_buy_all");
			msg.setTT(getObjectID());
			player->sendSystemMessage(msg);
			player->sendMessage(new StopNpcConversation(player, getObjectID()));
		}
	}

}
bool JunkdealerCreatureImplementation::canInventoryItemBeSoldAsJunk(TangibleObject* lootItem,int dealerType){
	return (lootItem->getJunkDealerNeeded() & dealerType) == dealerType
			&& lootItem->getCraftersName().isEmpty() == true
			&& lootItem->isBroken()==false
			&& lootItem->isSliced() == false
			&& lootItem->isNoTrade() == false
			&& (lootItem->isContainerObject() ==false || (lootItem->isContainerObject() ==true && lootItem->getContainerObjectsSize()==0));

}
String JunkdealerCreatureImplementation::getConversationString(int dealerType) {
	switch (dealerType){
		case JUNKCONVGENERIC:
			{return "conversation/junk_dealer_generic";}
		case JUNKCONVARMS:
			{return "conversation/junk_dealer_arms";}
		case JUNKCONVFINARY:
			{return "conversation/junk_dealer_finery";}
		case JUNKCONVDENDERRORI:
			{return "conversation/junk_dender_rori";}
		case JUNKCONVDENDERTHEED:
			{return "conversation/junk_dender_theed";}
		case JUNKCONVLILABORVO:
			{return "conversation/junk_lila_borvo";}
		case JUNKCONVMALIKVISTAL:
			{return "conversation/junk_malik_vistal";}
		case JUNKCONVNADOWATTOS:
			{return "conversation/junk_nado_wattos";}
		case JUNKCONVNATHANTAIKE:
			{return "conversation/junk_nathan_taike";}
		case JUNKCONVOLLOBOJABBAS:
			{return "conversation/junk_ollobo_jabbas";}
		case JUNKCONVQUICHDANTOOINE:
			{return "conversation/junk_quich_dantooine";}
		case JUNKCONVREGGINYM:
			{return "conversation/junk_reggi_nym";}
		case JUNKCONVSHEANILAKE:
			{return "conversation/sheani_lake";}
		case JUNKCONVSNEGVALARIAN:
			{return "conversation/junk_sneg_valarian";}
		case JUNKCONVJAWATRADER:
			{return "conversation/jawa_trader";}
		default:
			{return "conversation/junk_dealer_generic";}
		}

}
