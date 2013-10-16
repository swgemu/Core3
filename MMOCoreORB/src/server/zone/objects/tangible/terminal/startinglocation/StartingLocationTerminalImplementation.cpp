/*
 * StartingLocationTerminalImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PlayerManager.h"

void StartingLocationTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("StartingLocationTerminal");
}

int StartingLocationTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	//System::out << "entering start terminal radial call" << endl;
	if (selectedID != 20 || !authorizationState) { // not use object or not authorized
		if (!authorizationState)
			info("handleObjectMenuSelect: not authorized");

		return 1;
	}

	server->getPlayerManager()->sendStartingLocationsTo(player);

	return 0;
}
