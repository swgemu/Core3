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

#include "TangibleObjectImplementation.h"

TangibleObjectImplementation::TangibleObjectImplementation()
		: TangibleObjectServant() {
}

TangibleObjectImplementation::~TangibleObjectImplementation() {
}




/**
 * If this object is conversible, then this method will start the conversation with the player.
 * \param player The player attempting to initiate conversation.
 */
void TangibleObjectImplementation::converseStart(Player* player) {
}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseRespond(Player* player) {

}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseResponse(Player* player) {

}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseStop(Player* player) {

}

/**
 * This method rotates the object to the left by a set number of degrees.
 * \param player The player conversing with the object.
 * \param direction (left|right) The direction to rotate the object. Right is the default direction.
 * \param degrees How many degrees to rotate the object. Default is 90.
 */
void TangibleObjectImplementation::loot(Player* player, bool lootall) {
	//TODO: Check if the player is able to loot this object.

	if (lootall) {
		//TODO: Loot everything.
		return;
	}

	//TODO: Show the loot window to the player.
}

/**
 * This method rotates the object to the left by a set number of degrees.
 * \param player The player conversing with the object.
 * \param direction (left|right) The direction to rotate the object. Right is the default direction.
 * \param degrees How many degrees to rotate the object. Default is 90.
 */
void TangibleObjectImplementation::rotate(Player* player, const String& direction, uint32 degrees) {
	//TODO: Check to make sure the player has permission to move the object.

	if (direction.indexOf("left") == 0)
		degrees = -degrees;

	direction->rotate(Vector3::UNIT_Y, degrees);

	//TODO: Send tano delta updates.
}

/**
 * This method rotates the object to the right by a set number of degrees.
 * \param player The player conversing with the object.
 * \param direction (up|down|forward|back) The direction to move the object. Forward is the default direction.
 * \param distance How far to move the object. Default is 10.
 */
void TangibleObjectImplementation::move(Player* player, const String& direction, uint32 distance) {
	//TODO: Check to make sure the player has permission to move the object.

	if (direction.indexOf("up")) {
		//TODO: Move object up
	} else if (direction.indexOf("down")) {
		//TODO: Move object down
	} else if (direction.indexOf("back")) {
		//TODO: Move object back
	} else {
		//TODO: Move object foward
	}

	//Send tano delta updates.
}
