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

#ifndef PURCHASETICKETSLASHCOMMAND_H_
#define PURCHASETICKETSLASHCOMMAND_H_

#include "../../../scene/SceneObject.h"
#include "../../../../managers/planet/PlanetManager.h"
#include "../../../creature/shuttle/ShuttleCreature.h"
#include "../../sui/messagebox/SuiMessageBox.h"
#include "../../sui/SuiWindowType.h"
#include "../../../tangible/ticket/Ticket.h"

class PurchaseTicketSlashCommand : public SlashCommand {
public:

	PurchaseTicketSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: SlashCommand(name, server) {

	}

	bool doSlashCommand(Player* player, Message* packet) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		packet->shiftOffset(8); // skip ObjectID and size

		UnicodeString ticketmessage;
		packet->parseUnicode(ticketmessage);

		StringTokenizer tokenizer(ticketmessage.toString());

		String departurePlanet;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(departurePlanet);
		else
			return false;

		String departurePoint;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(departurePoint);
		else
			return false;

		String arrivalPlanet;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(arrivalPlanet);
		else
			return false;

		String arrivalPoint;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(arrivalPoint);
		else
			return false;

		bool roundTrip;
		if (tokenizer.hasMoreTokens())
			roundTrip = tokenizer.getIntToken();
		else
			return false;

		PlanetManager* planetManager = player->getZone()->getPlanetManager();

		uint32 fare = planetManager->getTravelFare(departurePlanet, arrivalPlanet);

		if (fare == 0) {
			//Travel not allowed between these planets
			return false;
		}

		//Replace Underscores with spaces
		departurePoint = departurePoint.replaceAll("_", " ");

		ShuttleCreature* shuttle = planetManager->getShuttle(departurePoint);

		if (shuttle == NULL) {
			SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
			sui->setPromptTitle("@base_player:swg");
			sui->setPromptText("@travel:no_location_found");

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());
			return false;
		}

		uint32 tax = shuttle->getTax();

		uint32 totalFee = fare + tax;

		if (roundTrip)
			totalFee *= 2;

		if (!player->verifyCashCredits(totalFee)) {
			SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
			sui->setPromptTitle("@base_player:swg");
			sui->setPromptText("@travel:short_funds");

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());
			return false;

		} else {
			player->subtractCashCredits(totalFee);
		}

		// create ticket item
		Ticket* ticket = new Ticket(player, 0xDAA0DE83, UnicodeString(
				"Travel Ticket"), "travel_ticket", departurePlanet, departurePoint,
				arrivalPlanet, arrivalPoint);

		player->addInventoryItem(ticket);
		ticket->sendTo(player, true);

		if (roundTrip) {
			Ticket* returnTicket = new Ticket(player, 0xDAA0DE83, UnicodeString(
					"Travel Ticket"), "travel_ticket", arrivalPlanet, arrivalPoint,
					departurePlanet, departurePoint);

			player->addInventoryItem(returnTicket);
			returnTicket->sendTo(player, true);
		}

		SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:ticket_purchase_complete");

		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
		return true;
	}

};

#endif //PURCHASETICKETSLASHCOMMAND_H_
