/*
 * GuildTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "GuildTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void GuildTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	return;
}

int GuildTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return 0;
}
