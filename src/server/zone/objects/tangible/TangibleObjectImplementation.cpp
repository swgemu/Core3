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
#include "creature/CreatureObject.h"

TangibleObjectImplementation::TangibleObjectImplementation(uint64 objectid, int type)
		: TangibleObjectServant(objectid, type) {
}

TangibleObjectImplementation::~TangibleObjectImplementation() {
}






/*************************************************************************
 * General Actions
 *************************************************************************/
/**
 * If this object is conversible, then this method will start the conversation with the player.
 * \param player The player attempting to initiate conversation.
 */
void TangibleObjectImplementation::converseStart(PlayerObject* player) {
}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseRespond(PlayerObject* player) {

}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseResponse(PlayerObject* player) {

}

/**
 * TODO: Fill in description for this method.
 * \param player The player conversing with the object.
 */
void TangibleObjectImplementation::converseStop(PlayerObject* player) {

}

/**
 * This method rotates the object to the left by a set number of degrees.
 * \param player The player conversing with the object.
 * \param direction (left|right) The direction to rotate the object. Right is the default direction.
 * \param degrees How many degrees to rotate the object. Default is 90.
 */
void TangibleObjectImplementation::loot(PlayerObject* player, bool lootall) {
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
 * \param orientation (left|right) The direction to rotate the object. Right is the default direction.
 * \param degrees How many degrees to rotate the object. Default is 90.
 */
void TangibleObjectImplementation::rotate(PlayerObject* player, const String& orientation, uint32 degrees) {
	//TODO: Check to make sure the player has permission to move the object.

	if (orientation.indexOf("left") == 0)
		degrees = -degrees;

	direction.rotate(Vector3::UNIT_Y, degrees);

	//TODO: Send tano delta updates.
}

/**
 * This method rotates the object to the right by a set number of degrees.
 * \param player The player conversing with the object.
 * \param orientation (up|down|forward|back) The direction to move the object. Forward is the default direction.
 * \param distance How far to move the object. Default is 10.
 */
void TangibleObjectImplementation::move(PlayerObject* player, const String& orientation, uint32 distance) {
	//TODO: Check to make sure the player has permission to move the object.

	if (orientation.indexOf("up")) {
		//TODO: Move object up
	} else if (orientation.indexOf("down")) {
		//TODO: Move object down
	} else if (orientation.indexOf("back")) {
		//TODO: Move object back
	} else {
		//TODO: Move object foward
	}

	//Send tano delta updates.
}


/*************************************************************************
 * Event Handlers
 *************************************************************************/
/**
 * This event should be fired when a creature uses equip() to equip this item. Any special
 * code that is non standard to the equiping process should be processed here.
 * \param creature The creature equiping the object.
 */
void TangibleObjectImplementation::onEquip(CreatureObject* creature) {

}

/**
 * This event should be fired when a creature uses unequip() to unequip this item. Any special
 * code that is non standard to the unequiping process should be processed here.
 * \param creature The creature unequiping the object.
 */
void TangibleObjectImplementation::onUnequip(CreatureObject* creature) {

}
