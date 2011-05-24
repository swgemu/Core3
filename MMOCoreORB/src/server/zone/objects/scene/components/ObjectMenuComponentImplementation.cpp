/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

*/

#include "ObjectMenuComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void ObjectMenuComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//All objects in a cell can be picked up, if the player is on the structures permission list.
	//This opens the door to allow admins to be able to drop/pickup items in public structures
	SceneObject* parent = sceneObject->getParent();

	if (parent == NULL || !parent->isCellObject())
		return;

	ManagedReference<SceneObject*> obj = parent->getParent();

	if (!obj->isBuildingObject())
		return;

	ManagedReference<BuildingObject*> buio = (BuildingObject*) obj.get();

	//Is this player on the permission list?
	if (!buio->isOnAdminList(player))
		return;

	if (sceneObject->isPlayerCreature())
		return;

	menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup"); //Pick up

	menuResponse->addRadialMenuItem(54, 1, "@ui_radial:item_move"); //Move
	menuResponse->addRadialMenuItem(51, 1, "@ui_radial:item_rotate"); //Rotate

	menuResponse->addRadialMenuItemToRadialID(54, 55, 3, "@ui_radial:item_move_forward"); //Move Forward
	menuResponse->addRadialMenuItemToRadialID(54, 56, 3, "@ui_radial:item_move_back"); //Move Back
	menuResponse->addRadialMenuItemToRadialID(54, 57, 3, "@ui_radial:item_move_up"); //Move Up
	menuResponse->addRadialMenuItemToRadialID(54, 58, 3, "@ui_radial:item_move_down"); //Move Down

	menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@ui_radial:item_rotate_left"); //Rotate Left
	menuResponse->addRadialMenuItemToRadialID(51, 53, 3, "@ui_radial:item_rotate_right"); //Rotate Right
}


int ObjectMenuComponentImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
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
