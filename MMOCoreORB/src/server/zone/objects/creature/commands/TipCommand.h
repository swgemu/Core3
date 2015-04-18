/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TIPCOMMAND_H_
#define TIPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "../../player/sui/callbacks/TipCommandSuiCallback.h"

class TipCommand: public QueueCommand {
private:

	int performTip(CreatureObject* player, CreatureObject* targetPlayer,
			int amount) const {

		// Target player must be in range (I think it's likely to assume this is the maximum targeting range, 190m)
		if (!player->isInRange(targetPlayer, 190)) {
			StringIdChatParameter ptr("base_player", "prose_tip_range"); // You are too far away to tip %TT with cash. You can send a wire transfer instead.
			ptr.setTT(targetPlayer->getCreatureName());
			player->sendSystemMessage(ptr);
			return GENERALERROR;
		}

		// Player must have sufficient funds
		int cash = player->getCashCredits();
		if (amount > cash) {
			StringIdChatParameter ptnsfc("base_player", "prose_tip_nsf_cash"); // You lack the cash funds to tip %DI credits to %TT.
			ptnsfc.setDI(amount);
			ptnsfc.setTT(targetPlayer);
			player->sendSystemMessage(ptnsfc);
			return GENERALERROR;
		}

		// We have a target, who is on-line, in range, with sufficient funds.
		// Lock target player to prevent simultaneous tips to not register correctly.

		Locker clocker(targetPlayer, player);
		player->subtractCashCredits(amount);
		targetPlayer->addCashCredits(amount, false); // FIXME: param notifyClient does nothing atm. in CreatureObject.idl:632

		StringIdChatParameter tiptarget("base_player", "prose_tip_pass_target"); // %TT tips you %DI credits.
		tiptarget.setDI(amount);
		tiptarget.setTT(player);
		targetPlayer->sendSystemMessage(tiptarget);

		StringIdChatParameter tipself("base_player", "prose_tip_pass_self"); // You successfully tip %DI credits to %TT.
		tipself.setDI(amount);
		tipself.setTT(targetPlayer);
		player->sendSystemMessage(tipself);

		return SUCCESS;
	}

	int performBankTip(CreatureObject* player, CreatureObject* targetPlayer,
			int amount) const {

		// Player must have sufficient bank funds
		int cash = player->getBankCredits();
		if (amount > cash) {
			StringIdChatParameter ptnsfb("base_player", "prose_tip_nsf_bank"); // You lack the bank funds to wire %DI credits to %TT.
			ptnsfb.setDI(amount);
			ptnsfb.setTT(targetPlayer->getCreatureName());
			player->sendSystemMessage(ptnsfb);
			return GENERALERROR;
		}

		ManagedReference<SuiMessageBox*> confirmbox = new SuiMessageBox(player,
				SuiWindowType::BANK_TIP_CONFIRM);
		confirmbox->setCallback(
				new TipCommandSuiCallback(server->getZoneServer(),
						targetPlayer, amount));

		confirmbox->setPromptTitle("@base_player:tip_wire_title"); // Confirm Bank Transfer
		confirmbox->setPromptText("@base_player:tip_wire_prompt"); // A surcharge of 5% will be added to your requested bank-to-bank transfer amount. Would you like to continue?
		confirmbox->setCancelButton(true, "@no");
		confirmbox->setOkButton(true, "@yes");

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		if (ghost == NULL) {
			player->sendSystemMessage("@base_player:tip_error"); // There was an error processing your /tip request. Please try again.
			return GENERALERROR;
		}

		ghost->addSuiBox(confirmbox);
		player->sendMessage(confirmbox->generateMessage());

		return SUCCESS;
	}

public:

	TipCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CreatureObject*> targetPlayer = NULL;
		int amount = 0;
		bool isBank = false;

		// Check arguments. /tip [playername] <amount> [bank]
		// Parse the arguments
		StringTokenizer args(arguments.toString());

		String amountOrPlayer;
		bool syntaxError = false;

		try {
			args.getStringToken(amountOrPlayer);

			//Check for people impersonating the bank.
			if (amountOrPlayer == "bank") {
				creature->sendSystemMessage("@base_player:tip_syntax"); //SYNTAX: /tip (to current target) or /tip
				return INVALIDPARAMETERS;
			}

			amount = Integer::valueOf(amountOrPlayer);

			if (amount == 0) { // First param is player or invalid
				targetPlayer = server->getZoneServer()->getPlayerManager()->getPlayer(amountOrPlayer);

				amount = args.getIntToken();
				if(amount == 0)
					throw NumberFormatException();

				if (targetPlayer == NULL) {
					StringIdChatParameter ptip("base_player", "prose_tip_invalid_param"); // /TIP: invalid amount ("%TO") parameter.
					ptip.setTO(amountOrPlayer);
					creature->sendSystemMessage(ptip);
					return INVALIDPARAMETERS;
				}
			}

			if (args.hasMoreTokens()) {
				String param;
				args.getStringToken(param);
				isBank = (param.toLowerCase() == "bank"); //TODO: locale aware. Possibly @acct_n:bank
			} else
				isBank = false;

		} catch (Exception &e) {
			syntaxError = true;
		}

		if (!syntaxError && targetPlayer == NULL) { // No target argument, check look-at target
			ManagedReference<SceneObject*> object =
					server->getZoneServer()->getObject(target);

			if (object != NULL && object->isCreatureObject()
					&& (cast<CreatureObject*>(object.get()))->getPlayerObject()
							!= NULL) {
				targetPlayer = cast<CreatureObject*>( object.get());
			} else if (object != NULL) {
				StringIdChatParameter ptip("base_player",
						"prose_tip_invalid_param"); // /TIP: invalid amount ("%TO") parameter.
				ptip.setTO(object);
				creature->sendSystemMessage(ptip);
				return INVALIDPARAMETERS;
			} else {
				syntaxError = true;
			}
		}

		if (syntaxError) {
			creature->sendSystemMessage("@base_player:tip_syntax"); // SYNTAX: /tip (to current target) or /tip
			return INVALIDPARAMETERS;
		}

		// Need to tip more than zero credits. Prevent stealing with negative tips.
		if (amount <= 0) {
			StringIdChatParameter ptia("base_player", "prose_tip_invalid_amt"); // /TIP: invalid amount ("%DI").
			ptia.setDI(amount);
			creature->sendSystemMessage(ptia);
			return INVALIDPARAMETERS;
		}

		if (creature == targetPlayer) { // You can't use yourself as a target for /tip!
			creature->sendSystemMessage("@error_message:target_self_disallowed"); // You cannot target yourself with this command.
			return GENERALERROR;
		}

		if (isBank || !targetPlayer->isOnline()) // Default to bank tip if player is offline
			return performBankTip(creature, targetPlayer, amount);
		else
			return performTip(creature, targetPlayer, amount);
	}

};

#endif //TIPCOMMAND_H_
