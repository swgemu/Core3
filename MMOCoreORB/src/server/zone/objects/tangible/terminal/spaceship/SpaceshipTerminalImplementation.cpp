/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/tangible/terminal/spaceship/SpaceshipTerminal.h"
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

int SpaceshipTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	return 0;
}
