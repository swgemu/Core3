/*
 * CityVoteTerminalImplementation.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: crush
 */


#include "CityVoteTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void CityVoteTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {

}

int CityVoteTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return 0;
}
