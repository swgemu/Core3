/*
 * ElevatorTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "ElevatorTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"

int ElevatorTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	ManagedReference<SceneObject*> parentObj = getParent();

	//Ensure that the parent object is a cell
	if (parentObj == NULL || parentObj->isCellObject())
		return 1;

	//Ensure that the player is in the same parent object.
	if (player->getParent() != parentObj)
		return 1;

	float x = player->getPositionX();
	float z = player->getPositionZ() + deltaZ;
	float y = player->getPositionY();

	//Update their new position.
	player->setPosition(x, z, y);
	player->updateZoneWithParent(parentObj, true);

	return 0;
}
