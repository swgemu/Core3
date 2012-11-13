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
#include "server/zone/objects/region/CityRegion.h"

class PurchaseTicketCommand : public QueueCommand {
public:

	PurchaseTicketCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CityRegion*> currentCity = creature->getCityRegion().get();

		if (currentCity != NULL){
			if (currentCity->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:city_cant_purchase_ticket"); //You are banned from using the services of this city. You cannot purchase a ticket.
				return GENERALERROR;
			}
		}
		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == NULL)
			return GENERALERROR;

		String departurePlanet, departurePoint, arrivalPlanet, arrivalPoint;
		bool roundTrip;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(departurePlanet);
			tokenizer.getStringToken(departurePoint);
			tokenizer.getStringToken(arrivalPlanet);
			tokenizer.getStringToken(arrivalPoint);
			roundTrip = (bool) tokenizer.getIntToken();

		} catch(Exception& e) {
			return INVALIDPARAMETERS;
		}

		departurePlanet = departurePlanet.replaceAll("_", " ");
		departurePoint = departurePoint.replaceAll("_", " ");
		arrivalPlanet = arrivalPlanet.replaceAll("_", " ");
		arrivalPoint = arrivalPoint.replaceAll("_", " ");

		ManagedReference<Zone*> departureZone = server->getZoneServer()->getZone(departurePlanet);
		ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);


		//Check to see if the departure planet is the same planet the player is on.
		if (creature->getZone() != departureZone)
			return INVALIDPARAMETERS;

		if (departureZone == NULL)
			return GENERALERROR;

		if (arrivalZone == NULL)
			return GENERALERROR;

		ManagedReference<PlanetManager*> pmDeparture = departureZone->getPlanetManager();
		ManagedReference<PlanetManager*> pmArrival = arrivalZone->getPlanetManager();

		if (!pmArrival->isExistingPlanetTravelPoint(arrivalPoint)) {
			creature->sendSystemMessage("@travel:no_location_found"); //No location was found for your destination.
			return INVALIDPARAMETERS;
		}

		Reference<PlanetTravelPoint*>  destPoint = pmArrival->getPlanetTravelPoint(arrivalPoint);

		if (destPoint == NULL)
			return GENERALERROR;

		ManagedReference<CreatureObject*> arrivalShuttle = destPoint->getShuttle();

		if (arrivalShuttle == NULL)
			return GENERALERROR;

		ManagedReference<CityRegion*> destCity = arrivalShuttle->getCityRegion();

		if (destCity != NULL){
			if (destCity.get()->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:banned_from_that_city");  // You have been banned from traveling to that city by the city militia
				return GENERALERROR;
			}
		}

		//Check to see if this point can be reached from this location.
		if (!pmDeparture->isTravelToLocationPermitted(departurePoint, arrivalPlanet, arrivalPoint))
			return GENERALERROR;

		if (roundTrip && !pmArrival->isTravelToLocationPermitted(arrivalPoint, departurePlanet, departurePoint))
			return GENERALERROR; //If they are doing a round trip, make sure they can travel back.

		int fare = pmDeparture->getTravelFare(departurePlanet, arrivalPlanet);

		if (roundTrip)
			fare += pmArrival->getTravelFare(arrivalPlanet, departurePlanet);

		//Make sure they have space in the inventory for the tickets before purchasing them.
		Locker _lock(inventory, creature);

		if (inventory->getContainerObjectsSize() + ((roundTrip) ? 2 : 1) > inventory->getContainerVolumeLimit()) {
			creature->sendSystemMessage("@error_message:inv_full"); //Your inventory is full.
			return GENERALERROR;
		}

		//Check if they have funds.
		int bank = creature->getBankCredits();
		int cash = creature->getCashCredits();

		if (bank < fare) {
			int diff = fare - bank;

			if (diff > cash) {
				ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
				suiBox->setPromptTitle("");
				suiBox->setPromptText("You do not have sufficient funds for that.");

				creature->sendMessage(suiBox->generateMessage());
				return GENERALERROR;
			}

			creature->subtractBankCredits(bank); //Take all from the bank, since they didn't have enough to cover.
			creature->subtractCashCredits(diff); //Take the rest from the cash.
		} else {
			creature->subtractBankCredits(fare); //Take all of the fare from the bank.
		}

		StringIdChatParameter params("@base_player:prose_pay_acct_success"); //You successfully make a payment of %DI credits to %TO.
		params.setDI(fare);
		params.setTO("@money/acct_n:travelsystem"); //the Galactic Travel Commission

		creature->sendSystemMessage(params);

		//ManagedReference<SceneObject*> obj = server->getZoneServer()->createObject(String("object/tangible/travel/travel_ticket/base/base_travel_ticket.iff").hashCode(), 1);
		ManagedReference<SceneObject*> ticket1 = pmDeparture->createTicket(departurePoint, arrivalPlanet, arrivalPoint);
		ticket1->sendTo(creature, true);
		inventory->transferObject(ticket1, -1, true);

		if (roundTrip) {
			ManagedReference<SceneObject*> ticket2 = pmArrival->createTicket(arrivalPoint, departurePlanet, departurePoint);
			ticket2->sendTo(creature, true);
			inventory->transferObject(ticket2, -1, true);
		}

		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
		suiBox->setPromptTitle("");
		suiBox->setPromptText("@travel:ticket_purchase_complete"); //Ticket purchase complete

		creature->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //PURCHASETICKETCOMMAND_H_
