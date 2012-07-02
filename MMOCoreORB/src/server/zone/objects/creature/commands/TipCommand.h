/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 2 of the License,
 or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for
 more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

 Linking Engine3 statically or dynamically with other modules
 is making a combined work based on Engine3.
 Thus, the terms and conditions of the GNU Lesser General Public License
 cover the whole combination.

 In addition, as a special exception, the copyright holders of Engine3
 give you permission to combine Engine3 program with free software
 programs or libraries that are released under the GNU LGPL and with
 code included in the standard release of Core3 under the GNU LGPL
 license (or modified versions of such code, with unchanged license).
 You may copy and distribute such a system following the terms of the
 GNU LGPL for Engine3 and the licenses of the other code concerned,
 provided that you include the source code of that other code when
 and as the GNU LGPL requires distribution of source code.

 Note that people who make modified versions of Engine3 are not obligated
 to grant this special exception for their modified versions;
 it is their choice whether to do so. The GNU Lesser General Public License
 gives permission to release a modified version without this exception;
 this exception also makes it possible to release a modified version
 which carries forward this exception.
 */

#ifndef TIPCOMMAND_H_
#define TIPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "../../player/sui/callbacks/TipCommandSuiCallback.h"

class TipCommand: public QueueCommand {
private:

	int performTip(CreatureObject* player, CreatureObject* targetPlayer,
			int amount) {

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
			int amount) {

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
			const UnicodeString& arguments) {

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

			amount = Integer::valueOf(amountOrPlayer);

			if (amount == 0) { // First param is player or invalid
				targetPlayer
						= server->getZoneServer()->getPlayerManager()->getPlayer(
								amountOrPlayer);

				amount = args.getIntToken();
				if(amount == 0)
					throw NumberFormatException();

				if (targetPlayer == NULL) {
					StringIdChatParameter ptip("base_player",
							"prose_tip_invalid_param"); // /TIP: invalid amount ("%TO") parameter.
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
