/*
 * ObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "ObjectMenuComponent.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void ObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	//All objects in a cell can be picked up, if the player is on the structures permission list.
	//This opens the door to allow admins to be able to drop/pickup items in public structures
	if (sceneObject == nullptr)
		return;

	if (sceneObject->isPlayerCreature() || sceneObject->isPet())
		return;

	ManagedReference<SceneObject*> rootParent = sceneObject->getRootParent();

	if (rootParent == nullptr || !rootParent->isBuildingObject()) {
		return;
	}

	ManagedReference<BuildingObject*> building = rootParent.castTo<BuildingObject*>();

	//Is this player on the permission list?
	if (!building->isOnAdminList(player))
		return;

	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

	if (parent == nullptr) {
		return;
	}

	bool parentIsCell = parent->isCellObject();
	bool nestedOnPlayer = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (parentIsCell || (parent->getGameObjectType() == SceneObjectType::CONTAINER && !nestedOnPlayer))
		menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup"); //Pick up

	if (parentIsCell) {
		menuResponse->addRadialMenuItem(54, 1, "@ui_radial:item_move"); //Move
		menuResponse->addRadialMenuItem(51, 1, "@ui_radial:item_rotate"); //Rotate

		menuResponse->addRadialMenuItemToRadialID(54, 55, 3, "@ui_radial:item_move_forward"); //Move Forward
		menuResponse->addRadialMenuItemToRadialID(54, 56, 3, "@ui_radial:item_move_back"); //Move Back
		menuResponse->addRadialMenuItemToRadialID(54, 57, 3, "@ui_radial:item_move_up"); //Move Up
		menuResponse->addRadialMenuItemToRadialID(54, 58, 3, "@ui_radial:item_move_down"); //Move Down

		menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@ui_radial:item_rotate_left"); //Rotate Left
		menuResponse->addRadialMenuItemToRadialID(51, 53, 3, "@ui_radial:item_rotate_right"); //Rotate Right
	}
}


int ObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	switch (selectedID) {
	case 10: //Pick Up
	{
		//String actionName = "transferitemmisc";
		//player->executeObjectControllerAction(actionName.hashCode(), getObjectID(), "");
		//transferitem
		break;
	}
	}

	return 0;
}
