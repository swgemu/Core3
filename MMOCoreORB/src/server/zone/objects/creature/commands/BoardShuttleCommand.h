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

/*
 * Updated on: Thu Oct 13 08:16:00 PDT 2011 by lordkator - Fixes to make travel debugging easier and fixed dialog timing
 */

#ifndef BOARDSHUTTLECOMMAND_H_
#define BOARDSHUTTLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/TicketSelectionSuiCallback.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"

class BoardShuttleCommand : public QueueCommand {
public:

	BoardShuttleCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Zone*> zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		Reference<PlanetTravelPoint*> closestPoint = planetManager->getNearestPlanetTravelPoint(creature, 128.f);

		// Check to make sure the creature is within range of a PlanetTravelPoint
		if (closestPoint == NULL) {
			// Could do @player_structure:boarding_too_far here but this allows you to know in-game that no point was found
			creature->sendSystemMessage("There is no shuttle nearby.");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> shuttle = closestPoint->getShuttle();

		// Is there a shuttle object related to this point?
		if (shuttle == NULL) {
			error("WARNING: Missing a shuttle object:" + closestPoint->toString());

			// Different error so it's obvious from in-game that the shuttle did not link to this travel point.
			creature->sendSystemMessage("Shuttle destroyed by terrorists.");
			return GENERALERROR;
		}

		float range = 128.f;

		if (creature->getParent() == NULL)
			range = 25.f; //If they are outside, the range is decreased to 25m.

		if (!shuttle->isInRange(creature, range)) {
			creature->sendSystemMessage("@player_structure:boarding_too_far"); //You are too far from the shuttle to board.
			return GENERALERROR;
		}

		// Get tickets user has in inventory for this location
		SortedVector<ManagedReference<TicketObject*> > tickets = findTicketsInInventory(creature, closestPoint);

		// Do they have any tickets for this location?
		if (tickets.size() == 0) {
			creature->sendSystemMessage("@travel:no_ticket"); //You do not have a ticket to board this shuttle.
			return GENERALERROR;
		}

		// Is shuttle ready to board yet?
		if (!planetManager->checkShuttleStatus(creature, shuttle))
			return GENERALERROR;

		uint64 ticketoid = target;

		// If only one ticket and no target use the first ticket
		if (tickets.size() == 1 && ticketoid == 0) {
			ticketoid = tickets.get(0)->getObjectID();
		}

		ManagedReference<TicketObject*> ticketObject = dynamic_cast<TicketObject*>(server->getZoneServer()->getObject(ticketoid));

		//If no ticket was passed as the target, then send the selection box.
		if (ticketObject == NULL) {
			sendTicketSelectionBoxTo(creature, tickets);
			return SUCCESS;
		}

		String departurePlanet = ticketObject->getDeparturePlanet();
		String departurePoint = ticketObject->getDeparturePoint();

		if (!closestPoint->isPoint(departurePlanet, departurePoint)) {
			creature->sendSystemMessage("@travel:no_ticket"); //You do not have a ticket to board this shuttle.
			return GENERALERROR;
		}

		String arrivalPlanet = ticketObject->getArrivalPlanet();
		String arrivalPointName = ticketObject->getArrivalPoint();

		ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);

		if (arrivalZone == NULL) {
			creature->sendSystemMessage("@travel:route_not_available"); //This ticket's route is no longer available.
			return GENERALERROR;
		}

		Reference<PlanetTravelPoint*> arrivalPoint = arrivalZone->getPlanetManager()->getPlanetTravelPoint(arrivalPointName);

		if (arrivalPoint == NULL || !closestPoint->canTravelTo(arrivalPoint)) {
			creature->sendSystemMessage("@travel:wrong_shuttle"); //The ticket is not valid for the given shuttle.
			return GENERALERROR;
		}

		// Randomize the arrival a bit to try and avoid everyone zoning on top of each other
		Coordinate p;
		p.initializePosition(arrivalPoint->getArrivalPosition());
		p.randomizePosition(5);

		creature->switchZone(arrivalZone->getZoneName(), p.getPositionX(), p.getPositionZ(), p.getPreviousPositionY(), 0);

		//remove the ticket from inventory and destory it.
		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");
		ticketObject->destroyObjectFromWorld(true);

		ticketObject->destroyObjectFromDatabase(true);
		return SUCCESS;
	}

private:
	SortedVector<ManagedReference<TicketObject*> > findTicketsInInventory(CreatureObject* creature, PlanetTravelPoint* departurePoint) {
		SortedVector<ManagedReference<TicketObject*> > tickets;

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		int totalObjects = inventory->getContainerObjectsSize();

		if (inventory == NULL || totalObjects <= 0)
			return tickets;

		for (int i = 0; i < totalObjects; ++i) {
			ManagedReference<SceneObject*> obj = inventory->getContainerObject(i);

			if (!obj->isTangibleObject() || !(cast<TangibleObject*>(obj.get()))->isTicketObject())
				continue;

			TicketObject* ticket = cast<TicketObject*>( obj.get());

			//Check to see if the ticket is for this destination
			if (!departurePoint->isPoint(ticket->getDeparturePlanet(), ticket->getDeparturePoint()))
				continue;

			tickets.put(ticket);
		}

		return tickets;
	}

	void sendTicketSelectionBoxTo(CreatureObject* creature, SortedVector<ManagedReference<TicketObject*> > tickets) {
		//Make sure it's a player before sending it a sui box...
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SuiListBox*> suiListBox = new SuiListBox(player, SuiWindowType::TRAVEL_TICKET_SELECTION);
		suiListBox->setPromptTitle("Select Destination");
		suiListBox->setPromptText("Select Destination");

		for (int i = 0; i < tickets.size(); ++i) {
			ManagedReference<TicketObject*> ticket = tickets.get(i);
			suiListBox->addMenuItem(ticket->getArrivalPoint(), ticket->getObjectID());
		}

		suiListBox->setCallback(new TicketSelectionSuiCallback(server->getZoneServer()));

		player->getPlayerObject()->addSuiBox(suiListBox);
		player->sendMessage(suiListBox->generateMessage());
	}
};

#endif //BOARDSHUTTLECOMMAND_H_
