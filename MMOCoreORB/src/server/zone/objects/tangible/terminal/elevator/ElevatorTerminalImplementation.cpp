/*
 * ElevatorTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "ElevatorTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/templates/tangible/ElevatorTerminalTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/SharedObjectTemplate.h"

void ElevatorTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TerminalImplementation::loadTemplateData(templateData);

	ElevatorTerminalTemplate* elevatorTemplate = dynamic_cast<ElevatorTerminalTemplate*>(templateData);

	deltaZ = elevatorTemplate->getDeltaZ();
}

void ElevatorTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (deltaZ == 0) //Elevator doesn't go anywhere...
		return;

	if (deltaZ < 0)
		menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down"); //DOWN
	else
		menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up"); //UP
}

int ElevatorTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 198 && selectedID != 199) // not up or down
		return 1;

	ManagedReference<SceneObject*> parentObj = getParent();

	//Ensure that the parent object is a cell
	if (parentObj == NULL || !parentObj->isCellObject())
		return 1;

	//Ensure that the player is in the same parent object.
	if (player->getParent() != parentObj)
		return 1;

	float x = player->getPositionX();
	float z = player->getPositionZ() + deltaZ;
	float y = player->getPositionY();

	//Update their new position.
	//player->setPosition(x, z, y);
	//player->updateZoneWithParent(parentObj, true);
	player->teleport(x, z, y, parentObj->getObjectID());

	if (deltaZ < 0)
		player->playEffect("clienteffect/elevator_descend.cef", "");
	else
		player->playEffect("clienteffect/elevator_rise.cef", "");

	return 0;
}
