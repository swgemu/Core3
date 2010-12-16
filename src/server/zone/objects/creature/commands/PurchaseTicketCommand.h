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

#ifndef PURCHASETICKETCOMMAND_H_
#define PURCHASETICKETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

class PurchaseTicketCommand : public QueueCommand {
public:

	PurchaseTicketCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerCreature* player = (PlayerCreature*) creature;

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory == NULL)
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		String departurePlanet;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(departurePlanet);
		else
			return GENERALERROR;

		String departurePoint;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(departurePoint);
		else
			return GENERALERROR;

		String arrivalPlanet;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(arrivalPlanet);
		else
			return GENERALERROR;

		String arrivalPoint;
		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(arrivalPoint);
		else
			return GENERALERROR;

		bool roundTrip;
		if (tokenizer.hasMoreTokens())
			roundTrip = tokenizer.getIntToken();
		else
			return GENERALERROR;

		PlanetManager* planetManager = player->getZone()->getPlanetManager();

		uint32 fare = planetManager->getTravelFare(departurePlanet, arrivalPlanet);

		if (fare == 0) {
			//Travel not allowed between these planets
			return GENERALERROR;
		}

		//Replace Underscores with spaces
		departurePoint = departurePoint.replaceAll("_", " ");
		arrivalPoint = arrivalPoint.replaceAll("_", " ");

		ManagedReference<ShuttleCreature*> shuttle = planetManager->getShuttle(departurePoint);

		if (shuttle == NULL) {
			SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
			sui->setPromptTitle("@base_player:swg");
			sui->setPromptText("@travel:no_location_found");

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());
			return GENERALERROR;
		}

		uint32 tax = shuttle->getTax();

		uint32 totalFee = fare + tax;

		if (roundTrip)
			totalFee *= 2;

		if (player->verifyCashCredits(totalFee)) {

			player->substractCashCredits(totalFee);

		} else if (player->verifyBankCredits(totalFee)) {

			player->substractBankCredits(totalFee);

		} else {

			SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
			sui->setPromptTitle("@base_player:swg");
			sui->setPromptText("@travel:short_funds");

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());
			return SUCCESS;
		}

		//

		uint32 crc = String("object/tangible/travel/travel_ticket/base/base_travel_ticket.iff").hashCode();

		// create ticket item
		ManagedReference<TicketObject*> ticket = (TicketObject*) server->getZoneServer()->createObject(crc, 1);
		ticket->setDeparturePlanet(departurePlanet);
		ticket->setDeparturePoint(departurePoint);
		ticket->setArrivalPlanet(arrivalPlanet);
		ticket->setArrivalPoint(arrivalPoint);

		inventory->addObject(ticket, -1);
		ticket->sendTo(player, true);

		ticket->updateToDatabase();

		if (roundTrip) {
			ManagedReference<TicketObject*> ticketObj = (TicketObject*) server->getZoneServer()->createObject(crc, 1);
			ticketObj->setDeparturePlanet(arrivalPlanet);
			ticketObj->setDeparturePoint(arrivalPoint);
			ticketObj->setArrivalPlanet(departurePlanet);
			ticketObj->setArrivalPoint(departurePoint);

			inventory->addObject(ticketObj, -1);
			ticketObj->sendTo(player, true);

			ticketObj->updateToDatabase();
		}

		SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:ticket_purchase_complete");

		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());

		//TODO: This should say the city name if bought from a city?
		StringIdChatParameter params("@base_player:prose_pay_acct_success");
		params.setTO("@money/acct_n:travelsystem"); //the Galactic Travel Commission
		player->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //PURCHASETICKETCOMMAND_H_
