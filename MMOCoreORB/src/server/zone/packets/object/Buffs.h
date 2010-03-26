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

#ifndef BUFFS_H_
#define BUFFS_H_

#include "ObjectControllerMessage.h"

class AddBuffMessage : public ObjectControllerMessage {
public:
	/**
	 * Adds the buff to the player's buff window.
	 * @param player {PlayerCreature} The player to add this buff to.
	 * @param buffcrc {uint32} The crc of the buff to add.
	 * @param duration {float} The duration of the buff in seconds.
	 * @return {AddBuffMessage} The add buff message..
	 */
	AddBuffMessage(PlayerCreature* player, uint32 buffcrc, float duration)
			: ObjectControllerMessage(player->getObjectID(), 0x1B, 0x229, false) {

		insertInt(buffcrc);
		insertFloat(duration);
	}
};

class RemoveBuffMessage : public ObjectControllerMessage {
public:
	/**
	 * Removes a buff from a player's buff window.
	 * @param player {PlayerCreature} The player whom's buff should be removed.
	 * @param buffcrc {uint32} The crc of the buff to remove.
	 * @return {RemoveBuffMessage} The remove buff message.
	 */
	RemoveBuffMessage(PlayerCreature* player, uint32 buffcrc)
			: ObjectControllerMessage(player->getObjectID(), 0x1B, 0x22A, false) {

		insertInt(buffcrc);
	}
};

#endif /*BUFFS_H_*/
