/*
 * TicketCollectorImplemetation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "TicketCollector.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/creature/shuttle/ShuttleCreature.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/city/CityHallObject.h"

int TicketCollectorImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	player->sendSystemMessage("Travel is currently disabled.");

	return 0;
}

bool TicketCollectorImplementation::checkTime(ShuttleCreature* shuttle, PlayerCreature* player) {
	int landTime = shuttle->getArrivalTime();

	if (landTime > 0) {
		int min = landTime / 60;
		int seconds = (landTime % 60);

		if (min > 1 && seconds > 1) {
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minutes and " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.toString());
		} else if (min > 1 && seconds == 1) {
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minutes and " << seconds << " second";
			player->sendSystemMessage(arrivalTime.toString());
		} else if (min > 1 && seconds == 0) {
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minutes and " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.toString());
	    } else if (min == 1 && seconds > 1) {
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minute and " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.toString());
	    } else if (min == 1 && seconds == 1) {
	    	StringBuffer arrivalTime;
	    	arrivalTime << "The next shuttle will be ready to board in " << min << " minute and " << seconds << " second";
	    	player->sendSystemMessage(arrivalTime.toString());
	    } else if (min == 1 && seconds == 0) {
	    	StringBuffer arrivalTime;
	    	arrivalTime << "The next shuttle will be ready to board in " << min << " minute and " << seconds << " seconds";
	    	player->sendSystemMessage(arrivalTime.toString());
	    } else if (min == 0 && seconds > 1) {
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.toString());
		} else if (min == 0 && seconds < 2){
			StringBuffer arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << seconds << " second";
			player->sendSystemMessage(arrivalTime.toString());
		}

		return false;
	} else if (landTime > -20) {
		StringBuffer arrivalTime;
		arrivalTime << "The next shuttle is about to begin boarding";
		player->sendSystemMessage(arrivalTime.toString());

		return false;
	}

	return true;
}

void TicketCollectorImplementation::useTicket(PlayerCreature* player, TicketObject* ticket) {
	// Pre: player wlocked
	// Post: player wlocked
	ManagedReference<TicketObject*> ticketObject = ticket;

	if (player->isMounted()) {
		player->sendSystemMessage("travel", "no_pets");
		return;
	}

	if (player->isInCombat())
		return;

	if (!checkTime(shuttle, player))
		return;

	String city = shuttle->getCity();
	String planet = shuttle->getPlanet();

	/*PlanetManager* planetManager = zone->getPlanetManager();
	ShuttleCreature* arrivalShuttle = planetManager->getShuttle(shuttle);

	if (zone != arrivalShuttle) {
		if (!shuttle->isStarport() || !arrivalShuttle->isStarport())
			return;
	}*/

	if ((ticket->getDeparturePoint() == city) &&  (ticket->getDeparturePlanet() == planet)) {
		ManagedReference<SceneObject*> objectParent = ticket->getParent();

		if (objectParent != NULL)
			objectParent->removeObject(ticket, true);

		ticket->destroyObjectFromDatabase();

		shuttle->sendPlayerTo(player, ticket);

		return;
	}

	player->sendSystemMessage("travel", "wrong_shuttle");

	return;
}

