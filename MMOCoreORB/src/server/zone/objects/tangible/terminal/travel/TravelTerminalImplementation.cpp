/*
 * TravelTerminalImplementation.cpp
 *
 *  Created on: 31/05/2010
 *      Author: victor
 */

#include "TravelTerminal.h"

#include "server/zone/packets/player/EnterTicketPurchaseModeMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

int TravelTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	if (controlledObject == NULL)
		return 0;

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(planetTravelPoint);
	player->sendMessage(etpm);

	return 0;
}

void TravelTerminalImplementation::notifyInsertToZone(Zone* zone) {
	TerminalImplementation::notifyInsertToZone(zone);

	//Set the travel point name to which this travel terminal is bound.
	PlanetManager* planetManager = zone->getPlanetManager();
	Reference<PlanetTravelPoint*> ptp = planetManager->getNearestPlanetTravelPoint(controlledObject);

	planetTravelPoint = ptp;
}
