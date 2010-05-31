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

int TravelTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	// Pre: player wlocked
	// Post: player wlocked

	if (selectedID != 20)
		return 0;

	EnterTicketPurchaseModeMessage* etpm = new EnterTicketPurchaseModeMessage(shuttle->getPlanet(), shuttle->getCity());
	player->sendMessage(etpm);

	return 0;
}
