/*
 * TicketCollectorImplemetation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "TicketCollector.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
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

	player->executeObjectControllerAction(0x5DCD41A2); //boardShuttle

	return 0;
}

void TicketCollectorImplementation::useTicket(PlayerCreature* player, TicketObject* ticket) {
	return;
}

