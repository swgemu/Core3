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
	if (selectedID != 20)
		return 0;

	if (controlledObject == NULL)
		return 0;

	if (controlledObject->getZone() == NULL)
		return 0;

	//Make sure the controlled object is in a region, or the region name will fail.

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(controlledObject);
	player->sendMessage(etpm);

	return 0;
}
