/*
 * TravelTerminalImplementation.cpp
 *
 *  Created on: 31/05/2010
 *      Author: victor
 */

#include "TravelTerminal.h"

#include "server/zone/packets/player/EnterTicketPurchaseModeMessage.h"
#include "server/zone/objects/creature/shuttle/ShuttleCreature.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/city/CityHallObject.h"

int TravelTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	// Pre: player wlocked
	// Post: player wlocked

	if (selectedID != 20)
		return 0;

	if (!player->isInRange(_this, 5)) {
		player->sendSystemMessage("travel", "too_far");
		return 1;
	}

	//Check to see if they have been city banned from travelling in this city.
	ManagedReference<ActiveArea*> activeArea = getActiveRegion();

	if (activeArea != NULL && activeArea->isRegion()) {
		Region* region = (Region*) activeArea.get();

		ManagedReference<CityHallObject*> city = region->getCityHall();

		if (city != NULL && city->isBanned(player->getObjectID())) {
			player->sendSystemMessage("@city/city:city_cant_purchase_ticket"); //You are banned from using the services of this city.\nYou cannot purchase a ticket.
			return 1;
		}
	}

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(shuttle->getPlanet(), shuttle->getCity());
	player->sendMessage(etpm);

	return 0;
}
