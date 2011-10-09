/*
 * ElevatorTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "ElevatorTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/tangible/ElevatorTerminalTemplate.h"

void ElevatorTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player->getParent() != parent) //Must be in same cell to use
		return;

	ElevatorTerminalTemplate* temp = dynamic_cast<ElevatorTerminalTemplate*>(getObjectTemplate());

	if (temp == NULL)
		return;

	if (elevatorDown != NULL && temp->isMovingDown())
		menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down"); //DOWN

	if (elevatorUp != NULL && temp->isMovingUp())
		menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up"); //UP
}

int ElevatorTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<SceneObject*> parentObj = getParent();

	//Ensure that the parent object is a cell
	if (parentObj == NULL || !parentObj->isCellObject())
		return 1;

	//Ensure that the player is in the same parent object.
	if (player->getParent() != parentObj)
		return 1;

	uint64 cellID = parentObj->getObjectID();

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
		}
		break;
	case 199: //DOWN
		if (elevatorDown != NULL) {
			z = elevatorDown->getPositionZ();
			player->playEffect("clienteffect/elevator_descend.cef", "");
		}
		break;
	}

	player->teleport(x, z, y, cellID);

	return 0;
}

void ElevatorTerminalImplementation::notifyInsert(QuadTreeEntry* obj) {
	TerminalImplementation::notifyInsert(obj);

	ElevatorTerminalTemplate* temp = dynamic_cast<ElevatorTerminalTemplate*>(getObjectTemplate());

	if (temp == NULL)
		return;

	SceneObject* scno = cast<SceneObject*>( obj);

	//Only check elevator terminals in the same cell.
	if (scno->getParent() != parent || !scno->isTerminal())
		return;

	Terminal* terminal = cast<Terminal*>( scno);

	if (!terminal->isElevatorTerminal())
		return;

	ElevatorTerminal* eterm = cast<ElevatorTerminal*>( terminal);

	float z = eterm->getPositionZ();

	if (z > getPositionZ() && temp->isMovingUp()) {
		//Make sure that this is the closest elevator terminal.
		if (elevatorUp == NULL || elevatorUp->getPositionZ() > z) {
			elevatorUp = eterm;
			eterm->setElevatorDown(_this);
		}
	} else if (z < getPositionZ() && temp->isMovingDown()) {
		if (elevatorDown == NULL || elevatorDown->getPositionZ() < z) {
			elevatorDown = eterm;
			eterm->setElevatorUp(_this);
		}
	}
}
