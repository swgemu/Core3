/*
 * CloningTerminalImplementation.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: crush
 */

#include "CloningTerminal.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/player/PlayerCreature.h"

int CloningTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20)
		return 1;

	//Store cloning data
	return 0;
}
