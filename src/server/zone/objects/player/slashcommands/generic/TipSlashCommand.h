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

#ifndef TIPSLASHCOMMAND_H_

#define TIPSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
#include "../../../../packets.h"

class TipSlashCommand : public SlashCommand {
public:

	TipSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: SlashCommand(name, server) {

	}

	bool doSlashCommand(Player* player, Message* packet) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		if (!player->canTip()) {
			player->sendSystemMessage("You can only tip once every 10 seconds.");
			return false;
		}

		PlayerManager* playerManager = server->getPlayerManager();
		if (playerManager == NULL)
			return false;

		StfParameter* params = new StfParameter();

		player->updateNextTipTime();

		uint64 recipientID = packet->parseLong();

		UnicodeString tipParams;
		packet->parseUnicode(tipParams);

		StringTokenizer tokenizer(tipParams.toString());
		tokenizer.setDelimeter(" ");

		if (!tokenizer.hasMoreTokens()) {
			delete params;
			return false;
		}

		uint32 tipAmount = 0;

		if (recipientID == 0) {
			//either player not in range. Or not online. So lets do a bank tip.

			String recipientName;
			tokenizer.getStringToken(recipientName);

			//Ok so now we have the name. Lets verify they exist first before doing anything else.
			if (!playerManager->validateName(recipientName)) {
				//Ok so the player exists. So lets parse the rest of the packet now.

				if (!tokenizer.hasMoreTokens()) {
					delete params;
					return false;
				}

				String tips;
				tokenizer.getStringToken(tips);

				tipAmount = atol(tips.toCharArray());

				if (tipAmount == 0) {
					params->addTO(tips);
					player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
					delete params;
					return false;
				}

				/*
				 if (tokenizer.hasMoreTokens()) {
				 //Theres more crap typed, we can just ignore it.
				 //Maybe change this in the future. To FORCE players to type bank.
				 player->sendSystemMessage("Invalid Tip Parameter (More Tokens)");
				 return;
				 }
				 */

				Player* recipient = playerManager->getPlayer(recipientName);

				if (recipient == NULL) {
					//The player exists but they are offline, so still do the tip.
					//Do stuff like altering the db here since they arent online.
					if (playerManager->modifyOfflineBank(player, recipientName, tipAmount))
						player->sendSystemMessage("Player not online. Credits should be transferred.");

					delete params;
					return false;
				} else {
					//Player is online. Tip their stuff and send mail etc;
					//make sure they have the proper credits first.
					try {
						recipient->wlock(player);
						player->bankTipStart(recipient, tipAmount);
						recipient->unlock();
					} catch (...) {
						player->error("Unhandled exception in ObjectControllerMessage:parseTip");
						recipient->unlock();
					}
				}

			} else {
				//Invalid Player Name
				player->sendSystemMessage("ui_cmnty", "friend_location_failed_noname"); //No player with that name exists.
				delete params;
				return false;
			}

		} else {
			//The player has SOMETHING targetted.
			//Lets first check if its a player, cause if it is we can skip some stuff.
			SceneObject* object = player->getZone()->lookupObject(recipientID);

			if (object == NULL) {
				player->sendSystemMessage("Usage: /tip <amount> with the player you want to tip as target. Use  '/tip <name> <amount> bank' to tip with the recipients name via bank.");
				delete params;
				return false;
			}

			if (object == player) {
				player->sendSystemMessage("You cannot tip yourself.");
				delete params;
				return false;
			}

			if (object->isPlayer()) {
				//Ok so we know its a player.
				//If its a player in range, the client will omit any text referencing the name.
				//So the next param SHOULD be the tip amount.
				if (!tokenizer.hasMoreTokens()) {
					delete params;
					return false;
				}

				String tips;
				tokenizer.getStringToken(tips);
				tipAmount = atoi(tips.toCharArray());

				//Quick cast of the object to a Player.
				Player* recipient = (Player*) object;

				//They didnt type in a number, or typed in 0.
				if (tipAmount == 0) {
					params->addTO(tips);
					player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
					delete params;
					return false;
				}

				//Now that we have the tip amount, we have to see if they want it to be a regular tip
				//or a bank tip. So we check if theres more tokens.
				if (tokenizer.hasMoreTokens()) {
					//Theres more crap typed, so we have to check that they typed ONLY bank.
					String bankParam;
					tokenizer.getStringToken(bankParam);

					if (bankParam == "bank") {
						//Bank tip. We don't need to parse anything else now that we have this info.
						try {
							recipient->wlock(player);
							player->bankTipStart(recipient, tipAmount);
							recipient->unlock();
						} catch (...) {
							player->error("Unhandled exception in ObjectControllerMessage:parseTip");
							recipient->unlock();
						}

					} else {
						//They typed something else other than bank.
						params->addTO(bankParam);
						player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
						delete params;
						return false;
					}

				} else {
					//Theres nothing else typed, so they want to do a cash tip. Cake!
					try {
						recipient->wlock(player);
						player->cashTip(recipient, tipAmount);
						recipient->unlock();
					} catch (...) {
						player->error("Unhandled exception in ObjectControllerMessage:parseTip");
						recipient->unlock();
					}
				}

			} else {
				//The current target is not a player.
				//So we have to parse for a valid player name. (THIS IS ONLY FOR BANK TIPS)

				if (!tokenizer.hasMoreTokens()) {
					delete params;
					return false;
				}

				String recipientName;
				tokenizer.getStringToken(recipientName);

				//Before we go any further we should validate the player name.
				if (!playerManager->validateName(recipientName)) {
					//They exist at least. Now lets grab the tip amount.
					if (!tokenizer.hasMoreTokens()) {
						delete params;
						return false;
					}

					String tips;
					tokenizer.getStringToken(tips);
					tipAmount = atoi(tips.toCharArray());

					//They didnt type in a number, or typed in 0.
					if (tipAmount == 0) {
						params->addTO(tips);
						player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
						delete params;
						return false;
					}

					//Ok so now we have the name, and we've verified the tip amount.
					//Now all thats left to do is the bank tip.
					//We have to make sure the player typed bank at the end.
					if (tokenizer.hasMoreTokens()) {
						//Theres more crap typed, so we have to check that they typed ONLY bank.
						String bankParam;
						tokenizer.getStringToken(bankParam);

						if (bankParam == "bank") {
							//Bank tip. We don't need to parse anything else now that we have this info.
							Player* recipient = playerManager->getPlayer(recipientName);
							if (recipient == NULL) {
								//The player exists but they are offline. So Still do the tip.
								//Do stuff like altering the db here since they arent online.
								playerManager->modifyOfflineBank(player, recipientName, tipAmount);
								player->sendSystemMessage("Player not online. Add Altering the DB in later.");
								delete params;
								return false;
							} else {
								//Player is online. Tip their stuff and send mail etc;
								//make sure they have the proper credits first.
								try {
									recipient->wlock(player);
									player->bankTipStart(recipient, tipAmount);
									recipient->unlock();
								} catch (...) {
									player->error("Unhandled exception in ObjectControllerMessage:parseTip");
									recipient->unlock();
								}
							}
						} else {
							//They typed something else other than bank.
							params->addTO(bankParam);
							player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
							delete params;
							return false;
						}
					}
				} else {
					//Invalid Player Name
					player->sendSystemMessage("ui_cmnty", "friend_location_failed_noname"); //No player with that name exists.
					delete params;
					return false;
				}
			}
		}
		return true;
	}

};

#endif //TIPSLASHCOMMAND_H_

