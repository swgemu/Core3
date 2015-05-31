/*
 * TrainerCreatureImplementation.cpp
 *
 *  Created on: 26/05/2010 -a
 *      Author: victor
 */

#include "server/zone/objects/creature/junkdealer/JunkdealerCreature.h"
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


bool JunkdealerCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return false;

	CreatureObject* player = cast<CreatureObject*>( obj);
	int dealerType = _this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType();
	if (dealerType == JUNKCONVJAWAARMS || dealerType == JUNKCONVJAWAFINARY || dealerType == JUNKCONVJAWAGENERIC || dealerType == JUNKCONVJAWATUSKEN){
		if (player->hasSkill("combat_smuggler_underworld_01")){
			StringIdChatParameter msg;
			msg.setStringId("@jawa_trader:understand");
			player->sendSystemMessage(msg);
		}else{
			StringIdChatParameter msg;
			msg.setStringId("@jawa_trader:cant_understand");
			player->sendSystemMessage(msg);
			return false;
		}
	}

	PlayerObject* ghost = player->getPlayerObject();
	StartNpcConversation* conv = new StartNpcConversation(player, getObjectID(), "");
	player->sendMessage(conv);
	ghost->setLastNpcConvStr(getObjectNameStringIdName());
	ghost->setLastNpcConvMessStr("");
	sendInitialMessage(player);

	return true;
}


void JunkdealerCreatureImplementation::sendInitialMessage(CreatureObject* player) {
	int dealerConversationType= _this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType();
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
			stfname = "s_e88820";
			break;
		}
		case JUNKCONVDENDERTHEED:{
			stfname = "s_e88820"; //On Hold
			break;
		}
		case JUNKCONVLILABORVO:{
			stfname = "s_ea90afa0";
			break;
		}
		case JUNKCONVMALIKVISTAL:{
			stfname = "s_769000a5";
			break;
		}
		case JUNKCONVNADOWATTOS:{
			stfname = "s_294d7f51";
			break;
		}
		case JUNKCONVNATHANTAIKE:{
			stfname = "s_5ceff11f";
			break;
		}
		case JUNKCONVOLLOBOJABBAS:{
			stfname = "s_6d35d0e1";
			break;
		}
		case JUNKCONVQUICHDANTOOINE:{
			stfname = "s_87c4b1c3";
			break;
		}
		case JUNKCONVREGGINYM:{
			stfname = "s_60d2f507";
			break;
		}
		case JUNKCONVSHEANILAKE:{
			stfname = "s_d3c4bb84";
			break;
		}
		case JUNKCONVSNEGVALARIAN:{
			stfname = "s_6dbdfc7";
			break;
		}
		case JUNKCONVJAWAGENERIC:{
			stfname = "greeting_thought_01";
			break;
		}
		case JUNKCONVJAWAFINARY:{
			stfname = "greeting_thought_03";
			break;
		}
		case JUNKCONVJAWAARMS:{
			stfname = "greeting_thought_02";
			break;
		}
		case JUNKCONVJAWATUSKEN:{
			stfname = "greeting_thought_bounty";
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
	int dealerConversationType= _this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType();
	String sOptionsMsg ="junkdealer_options";
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
			slist->insertOption(getConversationString(JUNKCONVDENDERRORI), "s_c9aa99a2"); //I am listening.
			slist->insertOption(getConversationString(JUNKCONVDENDERRORI), "s_13d756ae"); //Whoa, sorry about that didn't mean to bother you.
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVDENDERTHEED:{ // On Hold
			slist->insertOption(getConversationString(JUNKCONVDENDERTHEED), "s_54fab04f");// Not being implemented at this time
			break;
		}
		case JUNKCONVLILABORVO:{
			slist->insertOption(getConversationString(JUNKCONVLILABORVO), "s_a16cfd3b");//I hear that you are the person to see if one has something they need to move.
			slist->insertOption(getConversationString(JUNKCONVLILABORVO), "s_e8b03c7c");//This seems a little shady. I don't think I want to be involved.
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVMALIKVISTAL:{ //TD
			slist->insertOption(getConversationString(JUNKCONVMALIKVISTAL), "s_f836463");
			slist->insertOption(getConversationString(JUNKCONVMALIKVISTAL), "s_f66e6241");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVNADOWATTOS:{
			slist->insertOption(getConversationString(JUNKCONVNADOWATTOS), "s_d94d5d64"); //What sort of things do you buy?
			slist->insertOption(getConversationString(JUNKCONVNADOWATTOS), "s_50c8b3e1"); //I am just taking a look around.
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVNATHANTAIKE:{ //TD
			slist->insertOption(getConversationString(JUNKCONVNATHANTAIKE), "s_c20cb2b0");
			slist->insertOption(getConversationString(JUNKCONVNATHANTAIKE), "s_e613f19");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVOLLOBOJABBAS:{ //TD
			slist->insertOption(getConversationString(JUNKCONVOLLOBOJABBAS), "s_6ee477c3");
			slist->insertOption(getConversationString(JUNKCONVOLLOBOJABBAS), "s_aadc214b");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVQUICHDANTOOINE:{
			slist->insertOption(getConversationString(JUNKCONVQUICHDANTOOINE), "s_2313ac9e");
			slist->insertOption(getConversationString(JUNKCONVQUICHDANTOOINE), "s_953d967f");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVREGGINYM:{
			slist->insertOption(getConversationString(JUNKCONVREGGINYM), "s_ef8c7236");
			slist->insertOption(getConversationString(JUNKCONVREGGINYM), "s_53d778d8");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVSHEANILAKE:{
			slist->insertOption(getConversationString(JUNKCONVSHEANILAKE), "s_45632ab8");
			slist->insertOption(getConversationString(JUNKCONVSHEANILAKE), "s_f6c161d");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVSNEGVALARIAN:{ //TD
			slist->insertOption(getConversationString(JUNKCONVSNEGVALARIAN), "s_f0f3bea2");
			slist->insertOption(getConversationString(JUNKCONVSNEGVALARIAN), "s_50c8b3e1");
			sOptionsMsg ="dealer_specific-1";
			break;
		}
		case JUNKCONVJAWAGENERIC:{
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_370a03c");
			break;
		}
		case JUNKCONVJAWAFINARY:{
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_370a03c");
			break;
		}
		case JUNKCONVJAWAARMS:{
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_370a03c");
			break;
		}
		case JUNKCONVJAWATUSKEN:{
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_c86eba88");
			slist->insertOption(getConversationString(JUNKCONVARMS), "s_370a03c");
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
	ghost->setLastNpcConvMessStr(sOptionsMsg);
	player->sendMessage(slist);
}

void JunkdealerCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return;

	CreatureObject* player = cast<CreatureObject*>( obj);
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost->getLastNpcConvStr() != getObjectNameStringIdName())
		return;
	if (_this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType()>JUNKCONVJAWATUSKEN) {
		return;
	}
	String stffile = getConversationString(_this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType());
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
			case 0: { //                   0  1             2            3            4            5            6            7            8            9            10           11           12           13           14           15           16           17           18
				String chatResponses[] = {"","s_84a67771", "s_24f30320","s_e8ceb290","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","start_trading","start_trading","start_trading","start_trading"};

				if (getJunkDealerConversationType() < 20 && getJunkDealerConversationType() >= 0)
					sendConversationTerminate(player,stffile,chatResponses[getJunkDealerConversationType()]);
				else
					throw ArrayIndexOutOfBoundsException(getJunkDealerConversationType());

				createSellJunkLootSelection(player);
				break;
			}
			case 1: {
				String chatResponses[] = {"","s_4bd9d15e", "s_df5bd64e","s_1eb9feb7","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","s_84a67771","goodbye","goodbye","goodbye","goodbye"};

				if (getJunkDealerConversationType() < 20 && getJunkDealerConversationType() >= 0)
					sendConversationTerminate(player,stffile,chatResponses[getJunkDealerConversationType()]);
				else
					throw ArrayIndexOutOfBoundsException(getJunkDealerConversationType());

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
	} else if (ghost->getLastNpcConvMessStr() == "dealer_specific-1") {
		switch (option) {
			case 0:{
				ghost->setLastNpcConvMessStr("dealer_specific-2");
				switch (getJunkDealerConversationType()){
					case JUNKCONVNADOWATTOS:{ //What sort of things do you buy?
						sendConversationContinue(player,stffile,"s_17e67aee","s_a5d02a3c","s_90b63763");
						break;
					}
					case JUNKCONVNATHANTAIKE:{
						sendConversationContinue(player,stffile,"s_47a68e94","s_34475b33","s_5b767310");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationContinue(player,stffile,"s_fd11d689","s_6925372f","s_19e6693b");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{
						sendConversationContinue(player,stffile,"s_86df00aa","s_f2e88b32","s_fbe44b83");
						break;
					}
					case JUNKCONVLILABORVO:{
						sendConversationContinue(player,stffile,"s_113dbce8","s_1875d09c","s_210d33b4");
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationContinue(player,stffile,"s_9251cdb4","s_b44309e2","s_91196436");
						break;
					}
					case JUNKCONVOLLOBOJABBAS:{
						sendConversationContinue(player,stffile,"s_472f3294","s_e2ee167d","s_b85badf5");
						break;
					}
					case JUNKCONVREGGINYM:{
						sendConversationContinue(player,stffile,"s_14e5bdc0","s_b8e27f3c","s_2e005077");
						break;
					}
					case JUNKCONVSHEANILAKE:{
						sendConversationContinue(player,stffile,"s_38c64dea","s_370197a6","s_d264cf44");
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationContinue(player,stffile,"s_4717ab1e","s_14b517b1","s_b4cc3fb7");
						break;
					}
				}
				break;
			}
			case 1:{
				switch (getJunkDealerConversationType()){
					case JUNKCONVNADOWATTOS:{ //I am just taking a look around.
						sendConversationTerminate(player,stffile,"s_6afe640d");
						break;
					}
					case JUNKCONVNATHANTAIKE:{ //Bah! I should have figured that a stranger wouldn't understand the extent of the problem.
						sendConversationTerminate(player,stffile,"s_808503a8");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationTerminate(player,stffile,"s_1ea1fb0f");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{
						sendConversationTerminate(player,stffile,"s_35b56f0a");
						break;
					}
					case JUNKCONVLILABORVO:{
						sendConversationTerminate(player,stffile,"s_98d18f02");
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationTerminate(player,stffile,"s_420b90b8");
						break;
					}
					case JUNKCONVOLLOBOJABBAS:{
						sendConversationTerminate(player,stffile,"s_935bfcd0");
						break;
					}
					case JUNKCONVREGGINYM:{
						sendConversationTerminate(player,stffile,"s_f25d9c2");
						break;
					}
					case JUNKCONVSHEANILAKE:{
						sendConversationTerminate(player,stffile,"s_57feadd0");
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationTerminate(player,stffile,"s_f7c66216");
						break;
					}
				}
			}
		}
	}else if (ghost->getLastNpcConvMessStr() == "dealer_specific-2") {
		switch (option){
			case 0:{
				ghost->setLastNpcConvMessStr("dealer_specific-3");
				switch (getJunkDealerConversationType()) {
					case JUNKCONVNADOWATTOS:{ ///I think I might have a few things that will spark your interest.
						sendConversationTerminate(player,stffile,"s_8441c2ce");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVNATHANTAIKE:{
						sendConversationContinue(player,stffile,"s_3b924e4a","s_e022ccee","s_b47d6575");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationContinue(player,stffile,"s_42c6dbd2","s_6925372f","s_e2f6a3b8");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{
						sendConversationContinue(player,stffile,"s_5bc0c939","s_463bc6c4","s_6e11f342");
						break;
					}
					case JUNKCONVLILABORVO:{
						sendConversationTerminate(player,stffile,"s_7edb783c");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationContinue(player,stffile,"s_18123132","s_fc51be40","s_d36db42d");
						break;
					}
					case JUNKCONVOLLOBOJABBAS:{
						sendConversationTerminate(player,stffile,"s_73b59dd6");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVREGGINYM:{
						sendConversationTerminate(player,stffile,"s_5c453a2f");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVSHEANILAKE:{
						sendConversationTerminate(player,stffile,"s_82f469f5");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationContinue(player,stffile,"s_7debe28e","s_94fa366f","s_50b9f32f");
						break;
					}
				}
				break;
			}
			case 1:{
				switch (getJunkDealerConversationType()) {
					case JUNKCONVNADOWATTOS:{ //I am sorry but I don't have anything you would be interested in.
						sendConversationTerminate(player,stffile,"s_6afe640d");
						break;
					}
					case JUNKCONVNATHANTAIKE:{ //Bah! I should have figured that a stranger wouldn't understand the extent of the problem.
						sendConversationTerminate(player,stffile,"s_735e3c59");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationTerminate(player,stffile,"s_cfe66406");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{
						sendConversationTerminate(player,stffile,"s_f5349262");
						break;
					}
					case JUNKCONVLILABORVO:{
						sendConversationTerminate(player,stffile,"s_a83a2e6b");
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationTerminate(player,stffile,"s_af6451b5");
						break;
					}
					case JUNKCONVOLLOBOJABBAS:{
						sendConversationTerminate(player,stffile,"s_b950c3eb");
						break;
					}
					case JUNKCONVREGGINYM:{
						sendConversationTerminate(player,stffile,"s_233f3214");
						break;
					}
					case JUNKCONVSHEANILAKE:{
						sendConversationTerminate(player,stffile,"s_d4565283");
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationTerminate(player,stffile,"s_a3ad61f1");
						break;
					}
				}
				break;
			}
		}
	} else if (ghost->getLastNpcConvMessStr() == "dealer_specific-3") {
		switch (option){
			case 0:{
				ghost->setLastNpcConvMessStr("dealer_specific-4");
				switch (getJunkDealerConversationType()) {
					case JUNKCONVNATHANTAIKE:{ //I am sorry but I don't have anything you would be interested in.
						sendConversationContinue(player,stffile,"s_aaac386c","s_ecf19442","s_69567be7");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationContinue(player,stffile,"s_7d842aa5","s_673b632f","s_a753e4d6");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{ //I am sorry but I don't have anything you would be interested in.
						sendConversationTerminate(player,stffile,"s_ba5cc7c");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationTerminate(player,stffile,"s_9334c0a0");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationTerminate(player,stffile,"s_63a817cf");
						createSellJunkLootSelection(player);
						break;
					}
				}
				break;
			}
			case 1:{
				switch (getJunkDealerConversationType()) {
					case JUNKCONVNATHANTAIKE:{ //Bah! I should have figured that a stranger wouldn't understand the extent of the problem.
						sendConversationTerminate(player,stffile,"s_eadc8d6e");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationTerminate(player,stffile,"s_ef66cf46");
						break;
					}
					case JUNKCONVQUICHDANTOOINE:{
						sendConversationTerminate(player,stffile,"s_413bfd08");
						break;
					}
					case JUNKCONVMALIKVISTAL:{
						sendConversationTerminate(player,stffile,"s_9c1435e4");
						break;
					}
					case JUNKCONVSNEGVALARIAN:{
						sendConversationTerminate(player,stffile,"s_e27c50ad");
						break;
					}
				}
				break;
			}
		}
	}else if (ghost->getLastNpcConvMessStr() == "dealer_specific-4") {
		switch (option){
			case 0:{
				switch (_this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType()) {
					case JUNKCONVNATHANTAIKE:{ //I am sorry but I don't have anything you would be interested in.
						sendConversationTerminate(player,stffile,"s_33db8b80");
						createSellJunkLootSelection(player);
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationTerminate(player,stffile,"s_9aa94773");
						createSellJunkLootSelection(player);
						break;
					}
				}
				break;
			}
			case 1:{
				switch (_this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType()) {
					case JUNKCONVNATHANTAIKE:{ //Bah! I should have figured that a stranger wouldn't understand the extent of the problem.
						sendConversationTerminate(player,stffile,"s_2d363db3");
						break;
					}
					case JUNKCONVDENDERRORI:{
						sendConversationTerminate(player,stffile,"s_b0d63c3a");
						break;
					}
				}
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
			ghost->setLastNpcConvMessStr("junkdealer_kit4");
			ghost->addLastNpcConvOptions(choice);
			sendConversationContinue(player,stffile,"s_4d65752","s_d347bee3","s_b60b73f8");
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
			sendConversationTerminate(player,stffile,"s_3633b5a5");
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
			sendConversationTerminate(player,stffile,"s_3df21ea0");

		} else if (inventory->hasFullContainerObjects()) {
			sendConversationTerminate(player,stffile,"s_5b10c0b9");

		} else {
			sendConversationTerminate(player,stffile,"s_14efaaa2");

			ManagedReference<LootkitObject*> lootkit = (server->getZoneServer()->createObject(CRC, 2)).castTo<LootkitObject*>();

			if (inventory->transferObject(lootkit, -1, true)) {
				lootkit->sendTo(player, true);
			} else {
				info("Could not add object.", true);
				lootkit->destroyObjectFromDatabase(true);
			}
		}
	} else {
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
	}
}

void JunkdealerCreatureImplementation::createSellJunkLootSelection(CreatureObject* player) {
	if (player == NULL)
		return;

	if (_this.getReferenceUnsafeStaticCast()->getJunkDealerConversationType()==0){
		player->sendSystemMessage("Junk Dealer Not Configured at this time :(");
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
	}else{
		int dealerType= _this.getReferenceUnsafeStaticCast()->getJunkDealerBuyerType();
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
				String itemName = inventory->getContainerObject(i)->getDisplayedName();

				ManagedReference<TangibleObject*>  item = cast<TangibleObject*>(inventory->getContainerObject(i).get());
				if (canInventoryItemBeSoldAsJunk(item,dealerType)==true)
					box->addMenuItem("[" + String::valueOf(item->getJunkValue()) + "] " + itemName, inventory->getContainerObject(i)->getObjectID());
			}

			box->setUsingObject(_this.getReferenceUnsafeStaticCast());
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
	return( (lootItem->getJunkDealerNeeded() & dealerType) == lootItem->getJunkDealerNeeded() || (lootItem->getJunkDealerNeeded() & dealerType) == dealerType )
			&& lootItem->getJunkDealerNeeded() > 0
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
			{return "conversation/junk_sheani_lake";}
		case JUNKCONVSNEGVALARIAN:
			{return "conversation/junk_sneg_valarian";}
		case JUNKCONVJAWAGENERIC:
			{return "jawa_trader";}
		case JUNKCONVJAWAFINARY:
			{return "jawa_trader";}
		case JUNKCONVJAWAARMS:
			{return "jawa_trader";}
		case JUNKCONVJAWATUSKEN:
			{return "jawa_trader";}
		default:
			{return "conversation/junk_dealer_generic";}
		}
}
void JunkdealerCreatureImplementation::sendConversationTerminate(CreatureObject* player, const String& stfFile, const String& convTerminateMsg){
	StringIdChatParameter params(stfFile, convTerminateMsg);
	NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
	player->sendMessage(skillmsg);
	player->sendMessage(new StopNpcConversation(player, getObjectID()));
}
void JunkdealerCreatureImplementation::sendConversationContinue(CreatureObject* player, const String& stfFile, const String& convMsg,const String& convOption1,const String& convOption2){
	StringIdChatParameter params(stfFile, convMsg);
	NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
	player->sendMessage(skillmsg);
	StringList* slist = new StringList(player);
	slist->insertOption(stfFile, convOption1);
	slist->insertOption(stfFile, convOption2);
	player->sendMessage(slist);
}
