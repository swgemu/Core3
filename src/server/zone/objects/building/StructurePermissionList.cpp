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

#include "StructurePermissionList.h"

#include "../player/sui/listbox/SuiListBox.h"
#include "../player/sui/SuiWindowType.h"

StructurePermissionList::StructurePermissionList(BuildingObject* buio)
	: VectorMap<String, uint8>() {

	building = buio;
	setInsertPlan(NO_DUPLICATE);
}

void StructurePermissionList::sendTo(Player* player, uint8 permission) {
	SuiListBox* suilist = new SuiListBox(player, SuiWindowType::PERMISSION_LIST);

	switch (permission) {
	case ENTRYLIST:
		suilist->setPromptTitle("@player_structure:entry_permissions_list");
		break;
	case HOPPERLIST:
		suilist->setPromptTitle("@player_structure:hopper_permissions_list");
		break;
	case BANLIST:
		suilist->setPromptTitle("@player_structure:ban_list");
		break;
	case VENDORLIST:
		suilist->setPromptTitle("@player_structure:vendor_permissions_list");
		break;
	case ADMINLIST:
		suilist->setPromptTitle("@player_structure:admin_permissions_list");
		break;
	default:
		suilist->finalize();
		return;
	}

	suilist->setUsingObjectID(building->getObjectID());
	suilist->setCancelButton(true);

	for (int i = 0; i < size(); i++) {
		if (get(i) & permission)
			suilist->addMenuItem(elementAt(i)->getKey());
	}

	player->sendMessage(suilist->generateMessage());
	suilist->finalize();
}

bool StructurePermissionList::givePermission(Player* enforcer, Player* recipient, uint8 permission) {
	String firstname = recipient->getFirstName().toLowerCase();

	return givePermission(enforcer, firstname, permission);
}

bool StructurePermissionList::givePermission(Player* enforcer, Guild* guild, uint8 permission) {
	StringBuffer guildname;
	guildname << "guild:" << guild->getGuildTag().toLowerCase();

	return givePermission(enforcer, guildname.toString(), permission);
}

bool StructurePermissionList::givePermission(Player* enforcer, const String& entryname, uint8 permission) {
	if (enforcer->getFirstName().toLowerCase() == entryname || !isOnAdminList(enforcer))
		return false;

	if (permission & BANLIST) {
		if (contains(entryname)) {
			if (!(get(entryname) & ADMIN))
				return false;

			get(entryname) = BANLIST;
		} else {
			put(entryname, BANLIST);
		}

		return true;
	} else {
		if (contains(entryname)) {
			if (get(entryname) & BANLIST) {
				StringBuffer message;
				message << entryname << " must first be removed from the ban list.";
				enforcer->sendSystemMessage(message.toString());
				return false;
			} else {
				get(entryname) |= permission;
			}
		} else {
			put(entryname, permission);
		}
		return true;
	}

	return false;
}

bool StructurePermissionList::revokePermission(Player* enforcer, Player* recipient, uint8 permission) {
	String firstname = recipient->getFirstName().toLowerCase();

	return revokePermission(enforcer, firstname, permission);
}

bool StructurePermissionList::revokePermission(Player* enforcer, Guild* guild, uint8 permission) {
	StringBuffer guildname;
	guildname << "guild:" << guild->getGuildTag().toLowerCase();

	return revokePermission(enforcer, guildname.toString(), permission);
}

bool StructurePermissionList::revokePermission(Player* enforcer, const String& entryname, uint8 permission) {
	if (enforcer->getFirstName().toLowerCase() == entryname || !isOnAdminList(enforcer))
		return false;

	uint8 newMask = BANLIST;

	if (permission & BANLIST)
		newMask = NONE;
	else
		newMask &= ~permission;

	if (contains(entryname))
		get(entryname) = newMask;
	else
		put(entryname, newMask);

	return true;
}

bool StructurePermissionList::hasPermission(Player* player, uint8 permission) {
	String firstname = player->getFirstName().toLowerCase();

	if (isOwner(player) && !(permission & BANLIST))
		return true;

	if (contains(firstname))
		return (get(firstname) & permission);

	if (player->getGuild() != NULL) {
		StringBuffer guildname;
		guildname << "guild:" << player->getGuild()->getGuildTag().toLowerCase() << endl;

		if (contains(guildname.toString()))
			return (get(guildname.toString()) & permission);
	}

	return false;
}
