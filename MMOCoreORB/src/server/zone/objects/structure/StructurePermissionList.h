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

class StructurePermissionList : public VectorMap<String, uint8> {
	SceneObject* parentStructure;
	String permissionsString;

public:
	static const uint8 BAN = 0;
	static const uint8 ENTRY = 1;
	static const uint8 ADMIN = 2;
	static const uint8 HOPPER = 3;
	static const uint8 VENDOR = 4;

public:
	StructurePermissionList(SceneObject* structure);

	void parsePermissionsString(const String& permissions);
	String& getPermissionsString();

	void sendTo(Player* player, const String& listname);

	void grantPermission(Player* player, const String& entryname, const String& listname);
	void revokePermission(Player* player, const String& entryname, const String& listname);

	//Setters
	inline void setParentStructure(SceneObject* structure) {
		parentStructure = structure;
	}

	//Getters
	inline SceneObject* getParentStructure() {
		return parentStructure;
	}

	inline uint8 getPermission(const String& listname) {
		if (listname == "BAN")
			return (uint8)pow(2, BAN);
		else if (listname == "ENTRY")
			return (uint8)pow(2, ENTRY);
		else if (listname == "HOPPER")
			return (uint8)pow(2, HOPPER);
		else if (listname == "VENDOR")
			return (uint8)pow(2, VENDOR);

		return (uint8)pow(2, ADMIN);
	}

	inline bool isOwner(Player* player) {
		return parentStructure->isOwner(player->getCharacterID());
	}

	inline bool isOnAdminList(Player* player) {
		if (isOwner(player))
			return true;

		String fname = player->getFirstName().toLowerCase();

		if (!contains(fname))
			return false;

		return (get(fname) & getPermission("ADMIN"));
	}

	inline bool isOnBanList(Player* player) {
		if (isOwner(player))
			return false;

		String fname = player->getFirstName().toLowerCase();

		if (!contains(fname))
			return false;

		return (get(fname) & getPermission("BAN"));
	}

	inline bool isOnEntryList(Player* player) {
		if (isOwner(player))
			return true;

		String fname = player->getFirstName().toLowerCase();

		if (!contains(fname))
			return false;

		return (get(fname) & getPermission("ENTRY"));
	}

	inline bool isOnVendorList(Player* player) {
		if (isOwner(player))
			return true;

		String fname = player->getFirstName().toLowerCase();

		if (!contains(fname))
			return false;

		return (get(fname) & getPermission("VENDOR"));
	}

	inline bool isOnHopperList(Player* player) {
		if (isOwner(player))
			return true;

		String fname = player->getFirstName().toLowerCase();

		if (!contains(fname))
			return false;

		return (get(fname) & getPermission("HOPPER"));
	}
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
