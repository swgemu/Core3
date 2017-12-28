/*
 * StartingLocationTerminalImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "engine/core/ManagedReference.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

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
