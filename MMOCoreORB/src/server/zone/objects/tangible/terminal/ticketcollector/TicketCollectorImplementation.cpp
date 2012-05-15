/*
 * TicketCollectorImplemetation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "TicketCollector.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"

int TicketCollectorImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20)
		return 0;

	player->executeObjectControllerAction(0x5DCD41A2); //boardShuttle

	return 0;
}

void TicketCollectorImplementation::useTicket(CreatureObject* player, TicketObject* ticket) {
	return;
}

