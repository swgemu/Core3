/*
 * TicketObjectImplementation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/Zone.h"

void TicketObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("travel_departure_planet", "@planet_n:" + departurePlanet);
	alm->insertAttribute("travel_departure_point", departurePoint);
	alm->insertAttribute("travel_arrival_planet", "@planet_n:" + arrivalPlanet);
	alm->insertAttribute("travel_arrival_point", arrivalPoint);
}


int TicketObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	if (!isASubChildOf(player))
		return 0;

	player->executeObjectControllerAction(0x5DCD41A2, getObjectID(), ""); //boardShuttle

	return 0;
}
