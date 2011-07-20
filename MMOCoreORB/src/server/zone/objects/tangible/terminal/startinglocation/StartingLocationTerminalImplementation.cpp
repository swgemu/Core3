/*
 * StartingLocationTerminalImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "StartingLocationTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PlayerManager.h"

void StartingLocationTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("StartingLocationTerminal");
}

int StartingLocationTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	//System::out << "entering start terminal radial call" << endl;

	if (selectedID != 20) // not use object
		return 1;

	server->getPlayerManager()->sendStartingLocationsTo(player);

	return 0;
}
