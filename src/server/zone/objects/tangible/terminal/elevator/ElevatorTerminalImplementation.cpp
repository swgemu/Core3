/*
 * ElevatorTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "ElevatorTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/SharedObjectTemplate.h"

void ElevatorTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (player->getParent() != parent) //Must be in same cell to use
		return;

	if (elevatorDown != NULL)
		menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down"); //DOWN

	if (elevatorUp != NULL)
		menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up"); //UP
}

int ElevatorTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	ManagedReference<SceneObject*> parentObj = getParent();

	//Ensure that the parent object is a cell
	if (parentObj == NULL || !parentObj->isCellObject())
		return 1;

	//Ensure that the player is in the same parent object.
	if (player->getParent() != parentObj)
		return 1;

	float x = player->getPositionX();
	float z = player->getPositionZ();
	float y = player->getPositionY();

	switch (selectedID) {
	default:
		return 1;

	case 198: //UP
		if (elevatorUp != NULL) {
			z = elevatorUp->getPositionZ();
			player->playEffect("clienteffect/elevator_rise.cef", "");
			player->teleport(x, z, y, parentObj->getObjectID());
		}
		break;
	case 199: //DOWN
		if (elevatorDown != NULL) {
			z = elevatorDown->getPositionZ();
			player->playEffect("clienteffect/elevator_descend.cef", "");
			player->teleport(x, z, y, parentObj->getObjectID());
		}
		break;
	}

	return 0;
}

void ElevatorTerminalImplementation::notifyInsert(QuadTreeEntry* obj) {
	TerminalImplementation::notifyInsert(obj);

	SceneObject* scno = (SceneObject*) obj;

	//Only check elevator terminals in the same cell.
	if (scno->getParent() != parent || !scno->isTerminal())
		return;

	Terminal* terminal = (Terminal*) scno;

	if (!terminal->isElevatorTerminal())
		return;

	ElevatorTerminal* eterm = (ElevatorTerminal*) terminal;

	float z = eterm->getPositionZ();

	if (z > positionZ) {
		//Make sure that this is the closest elevator terminal.
		if (elevatorUp == NULL || elevatorUp->getPositionZ() > z)
			elevatorUp = eterm;
	} else if (z < positionZ) {
		if (elevatorDown == NULL || elevatorDown->getPositionZ() < z)
			elevatorDown = eterm;
	}
}
