/*
 * CityVoteTerminalImplementation.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: crush
 */


#include "CityVoteTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void CityVoteTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {

}

int CityVoteTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	return 0;
}
