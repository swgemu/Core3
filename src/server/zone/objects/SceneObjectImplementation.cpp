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

#include "SceneObjectImplementation.h"


SceneObjectImplementation::SceneObjectImplementation()
		: SceneObjectServant() {

}

SceneObjectImplementation::~SceneObjectImplementation() {

}

/**
 * When an object is "used" via the radial, double clicked, or accessed via hotkey, this method
 * defines its use procedure.
 * \param player The player who has requested use of this object.
 */
void SceneObjectImplementation::use(Player* player) {
}

/**
 * When a player attempts to pickup an object, this method is called.
 * \param player The player who is attempting to pickup this object.
 */
void SceneObjectImplementation::pickup(Player* player) {
	if (!player->isPrivileged())
		return;
}

/**
 * When a player attempts to drop an object, this method is called.
 * \param player The player who is attempting to drop this object.
 */
void SceneObjectImplementation::drop(Player* player) {
	if (!player->isPrivileged())
		return;
}

/**
 * When a player attempts to destroy an item via radial menu or dragging it out of the container to the world.
 * \param player The player who is attempting to destroy this object.
 */
void SceneObjectImplementation::destroy(Player* player) {
	//TODO: Confirm that the object is actually in player's inventory first.
	//TODO: Self destruction instructions.
}

/**
 * When a player attempts to open an object's container. For example, a corpse or inventory.
 * \param player The player attempting to open this object.
 */
void SceneObjectImplementation::open(Player* player) {
	//TODO: Confirm that the player has permission to open this container.
}

/**
 * When a player attempts to "activate" an object. This may be a different
 * sequence of events than use().
 * \param player The player that is attempting to activate this object.
 */
void SceneObjectImplementation::activate(Player* player) {

}

/**
 * When a player attempts to "deactivate" an object.
 * \param player The player that is attempting to deactivate this object.
 */
void SceneObjectImplementation::deactivate(Player* player) {

}

/**
 * Compares the local gameObjectType to the type passed in variable "type"
 * \param type type to compare with
 * \param similar Default: false. If true, will return true if object inherits the object specified in variable "type"
 */
bool SceneObjectImplementation::isObjectType(int type, bool similar) {
	if (similar)
		return (gameObjectType & type);
	else
		return (gameObjectType == type);

	/*

	if(!similar)
		return type == gameObjectType;

	// If similar is true, check inheritance relationship
	switch(type) {
	case INTANGIBLE:
		if(gameObjectType >= 0x800 && gameObjectType <= 0x80B && (!(gameObjectType >= 0x01 && gameObjectType <= 0x04)))
			return true;
		break;
	// Tangible & children:
	case TANGIBLE:
		if((!(gameObjectType >= 0x800 && gameObjectType <= 0x80B)) && (!(gameObjectType >= 0x01 && gameObjectType <= 0x04)))
			return true;
		break;
	case BUILDING:
		if(gameObjectType >= 200 && gameObjectType <= 203)
			return true;
		break;
	case CREATURE:
		if(gameObjectType >= 400 && gameObjectType <= 403)
			return true;
		break;
	case INSTALLATION:
		if(gameObjectType >= 0x1000 && gameObjectType <= 0x1005)
			return true;
		break;
	case TOOL:
		if(gameObjectType >= 0x8000 && gameObjectType <= 0x8005)
			return true;
		break;
	case VEHICLE:
		if(gameObjectType >= 0x10000 && gameObjectType <= 0x10001)
			return true;
		break;
	case WEAPON:
		if(gameObjectType >= 0x20000 && gameObjectType <= 0x2000E)
			return true;
		break;
	case COMPONENT:
		if(gameObjectType >= 0x40000 && gameObjectType <= 0x4000D)
			return true;
		break;
	case POWERUP:
		if(gameObjectType >= 0x80000 && gameObjectType <= 0x80006)
			return true;
		break;
	case RESOURCECONTAINER:
		if(gameObjectType >= 0x400000 && gameObjectType <= 0x40000B)
			return true;
		break;
	case DEED:
		if(gameObjectType >= 0x800000 && gameObjectType <= 0x400006)
			return true;
		break;
	case WEARABLE:
		if(gameObjectType >= 0x1000000 && gameObjectType <= 0x1000013)
			return true;
		break;
	case SHIP:
		if(gameObjectType >= 0x2000000 && gameObjectType <= 0x2000001)
			return true;
		break;
	case SCENE:
		return true;
		break;
	default:
		return false;
		break;
	}

	return false;
	*/
}
