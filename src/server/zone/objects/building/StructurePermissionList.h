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

#ifndef STRUCTUREPERMISSIONLIST_H_
#define STRUCTUREPERMISSIONLIST_H_

#include "engine/engine.h"

#include "../player/Player.h"
#include "../guild/Guild.h"

#include "BuildingObject.h"

class StructurePermissionList : public VectorMap<String, uint8> {
	BuildingObject* building;

public:
	//List Permissions - Are they on said list.
	static const uint8 BANLIST = 0;
	static const uint8 NONE = 1;
	static const uint8 HOPPERLIST = 2;
	static const uint8 ENTRYLIST = 4;
	static const uint8 VENDORLIST = 8;
	static const uint8 ADMINLIST = 16;

	//Super Permissions
	static const uint8 VENDOR = ENTRYLIST | VENDORLIST | ~BANLIST;
	static const uint8 ADMIN = HOPPERLIST | VENDOR | ADMINLIST;

public:
	StructurePermissionList(BuildingObject* buio);

	bool givePermission(Player* enforcer, Player* recipient, uint8 permission);
	bool givePermission(Player* enforcer, Guild* guild, uint8 permission);
	bool givePermission(Player* enforcer, const String& entryname, uint8 permission);

	bool revokePermission(Player* enforcer, Player* recipient, uint8 permission);
	bool revokePermission(Player* enforcer, Guild* guild, uint8 permission);
	bool revokePermission(Player* enforcer, const String& entryname, uint8 permission);

	void setPermissionsFromString(const String& permissionsString) {
		//TODO: This should take a string, and populate the list with its data.
	}

	void sendTo(Player* player, uint8 permission);

	bool hasPermission(Player* player, uint8 permission);

	inline void setBuilding(BuildingObject* buio) {
		building = buio;
	}

	inline BuildingObject* getBuilding() {
		return building;
	}

	inline bool isOwner(Player* player) {
		if (building != NULL)
			return (building->getOwnerID() == player->getObjectID());

		return false;
	}

	bool isOnAdminList(Player* player) {
		return hasPermission(player, ADMIN) || isOwner(player);
	}

	bool isOnBanList(Player* player) {
		return hasPermission(player, BANLIST);
	}

	bool isOnEntryList(Player* player) {
		return hasPermission(player, ENTRYLIST) || isOwner(player);
	}

	bool isOnVendorList(Player* player) {
		return hasPermission(player, VENDOR) || isOwner(player);
	}

	bool isOnHopperList(Player* player) {
		return hasPermission(player, HOPPERLIST) || isOwner(player);
	}
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
