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

#include "PlayerStructureTerminal.h"
#include "PlayerStructureTerminalImplementation.h"

PlayerStructureTerminalImplementation::PlayerStructureTerminalImplementation(BuildingObject* buio, uint64 objid, float x, float z, float y) :
	PlayerStructureTerminalServant(0xEFCF3082, objid, UnicodeString(""), "terminal_player_structure", x, z, y, PLAYERSTRUCTURE) {

		structure = buio;
}

int PlayerStructureTerminalImplementation::useObject(Player* player) {
	return 0;
}

void PlayerStructureTerminalImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->addRadialItem(0, 118, 3, "@player_structure:management"); //Structure Management
	omr->addRadialItem(0, 117, 3, "@player_structure:permissions"); //Structure Permissions

		omr->addRadialItem(3, 126, 3, "@player_structure:management_transfer"); //Transfer Ownership
		omr->addRadialItem(3, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
		omr->addRadialItem(3, 124, 3, "@player_structure:management_status"); //Status
		omr->addRadialItem(3, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
		omr->addRadialItem(3, 127, 3, "@player_structure:management_residence"); //Declare Residence
		omr->addRadialItem(3, 125, 3, "@player_structure:management_privacy"); //Privacy

		omr->addRadialItem(2, 119, 3, "@player_structure:permission_enter"); //Entry List
		omr->addRadialItem(2, 120, 3, "@player_structure:permission_banned"); //Ban List
		omr->addRadialItem(2, 121, 3, "@player_structure:permission_admin"); //Administrator List
		omr->addRadialItem(2, 122, 3, "@player_structure:permission_vendor"); //Vendor List

		omr->finish();
		player->sendMessage(omr);
}

void PlayerStructureTerminalImplementation::sendPermissionListTo(Player* player, uint8 listtype) {
	if (structure == NULL)
		return;

	structure->sendPermissionListTo(player, listtype);
}
