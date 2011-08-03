/*
 * TipBankSuiCallback.h
 *
 *  Created on: 18 jul. 2011
 *      Author: Moncai
 */

#ifndef TIPBANKSUICALLBACK_H_
#define TIPBANKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class TipCommandSuiCallback: public SuiCallback {
private:
	ManagedReference<CreatureObject*> targetPlayer;
	int amount;

public:
	TipCommandSuiCallback(ZoneServer* server, CreatureObject* target,
			int amount) :
		SuiCallback(server) {
		this->targetPlayer = target;
		this->amount = amount;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed,
			Vector<UnicodeString>* args) {

		if (!suiBox->isMessageBox() || cancelPressed) {
			return;
		}

		// Player must have sufficient funds including surcharge
		int cash = player->getBankCredits();
		int surcharge = amount < 21 ? 1 : round(amount * 0.05); // minimum surcharge is 1c as per Live.
		if ((amount + surcharge) > cash) {
			StringIdChatParameter ptnsfw("base_player", "prose_tip_nsf_wire"); // You do not have %DI credits (surcharge included) to tip the desired amount to %TT.
			ptnsfw.setDI(amount + surcharge);
			ptnsfw.setTT(targetPlayer->getCreatureName());
			player->sendSystemMessage(ptnsfw);
			return;
		}

		// Perform the bank tip
		Locker clocker(targetPlayer, player);
		player->substractBankCredits(amount + surcharge);
		targetPlayer->addBankCredits(amount, false); // FIXME: param notifyClient does nothing atm. in CreatureObject.idl:637

		// Duly notify parties involved
		if (targetPlayer->isOnline()) {
			StringIdChatParameter pwpt("base_player", "prose_wire_pass_target"); // You have successfully received %DI bank credits from %TO.
			pwpt.setDI(amount);
			pwpt.setTO(player->getCreatureName());
			targetPlayer->sendSystemMessage(pwpt);
		}

		// Send tell to player.
		StringIdChatParameter pwps("base_player", "prose_wire_pass_self"); // You have successfully sent %DI bank credits to %TO.
		pwps.setDI(amount);
		pwps.setTO(targetPlayer->getCreatureName());
		player->sendSystemMessage(pwps);

		ManagedReference<ChatManager*> cman =
				player->getZoneServer()->getChatManager();
		if (cman == NULL)
			return;

		UnicodeString subject("@base_player:wire_mail_subject"); // Bank Transfer Complete...
		String sender = "bank"; // As per Live. TODO: locale aware. Possibly @acct_n:bank

		StringIdChatParameter body("@base_player:prose_wire_mail_target");
		// %DI credits from %TO have been successfully delivered from escrow to your bank account.
		body.setTO(player->getCreatureName());
		body.setDI(amount);
		cman->sendMail(sender, subject, body,
				targetPlayer->getFirstName());

		StringIdChatParameter bodyself("@base_player:prose_wire_mail_self");
		// %TO has received %DI credits from you, via bank wire transfer.
		bodyself.setTO(targetPlayer->getCreatureName());
		bodyself.setDI(amount);
		cman->sendMail(sender, subject, bodyself,
				player->getFirstName());
	}
};

#endif /* TIPBANKSUICALLBACK_H_ */
