/*
 * TravelTerminalImplementation.cpp
 *
 *  Created on: 31/05/2010
 *      Author: victor
 */

#include "TravelTerminal.h"

#include "server/zone/packets/player/EnterTicketPurchaseModeMessage.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

int TravelTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	if (controlledObject == NULL)
		return 0;

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(zone->getZoneName(), travelPointName);
	player->sendMessage(etpm);

	return 0;
}

void TravelTerminalImplementation::insertToZone(Zone* zone) {
	TerminalImplementation::insertToZone(zone);

	//Set the travel point name to which this travel terminal is bound.
	PlanetManager* planetManager = zone->getPlanetManager();
	String pointName = planetManager->getNearestPlanetTravelPointName(controlledObject);

	travelPointName = pointName;
}
