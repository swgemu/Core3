/*
 * TravelTerminalImplementation.cpp
 *
 *  Created on: 31/05/2010
 *      Author: victor
 *  Updated on: Thu Oct 13 08:34:42 PDT 2011 by lordkator - use getPlanetTravelPoint() instead of trying to resolve here
 */

#include "TravelTerminal.h"

#include "server/zone/packets/player/EnterTicketPurchaseModeMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/planet/PlanetManager.h"

int TravelTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	Reference<PlanetTravelPoint*> ptp = getPlanetTravelPoint();

	// Complain loudly if we failed to find a travel point for this terminal
	if(ptp == NULL) {
		error("TravelTerminalImplementation::handleObjectMenuSelect(" + String::valueOf(getObjectID()) + " Could not determine related PlanetTravelPoint");
		return 0;
	}

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(ptp);
	player->sendMessage(etpm);

	return 0;
}

void TravelTerminalImplementation::notifyInsertToZone(Zone* zone) {
	TerminalImplementation::notifyInsertToZone(zone);
}
