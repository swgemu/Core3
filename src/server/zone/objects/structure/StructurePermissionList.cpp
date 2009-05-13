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

#include "engine/engine.h"

#include "StructurePermissionList.h"

//#include "../player/Player.h"
#include "../../packets/ui/PermissionListCreateMessage.h"

StructurePermissionList::StructurePermissionList(SceneObject* structure)
		: VectorMap<String, uint8>() {

	parentStructure = structure;
	permissionsString = "";
	setInsertPlan(NO_DUPLICATE);
}

/**
 * Will send the client sided representation of the list to the player.
 * \param player The player who requested the permission list.
 * \param permission Which permission list is being requested.
 */
void StructurePermissionList::sendTo(Player* player, const String& listname) {
	PermissionListCreateMessage* listmsg = new PermissionListCreateMessage(listname);
	listmsg->addName(parentStructure->getOwnerName());

	for (int i = 0; i < size(); i++) {
		VectorMapEntry<String, uint8>* entry = elementAt(i);
		if (entry->getValue() & getPermission(listname))
			listmsg->addName(entry->getKey());
	}

	listmsg->generateMessage(); //must be called after adding all the names to the list

	player->sendMessage(listmsg);
}

/**
 * Adds the passed entry to the specified permission list.
 * \param player The player granting permission.
 * \param entryname The entry to be added to the list.
 * \param listname The name of the list to add them to: BAN, ENTRY, ADMIN, HOPPER, VENDOR
 */
void StructurePermissionList::grantPermission(Player* player, const String& entryname, const String& listname) {
	uint8 listpermission = getPermission(listname);

	if (contains(entryname)) {
		uint8 permission = get(entryname);

		if (permission & listpermission)
			return;

		get(entryname) |= listpermission;
	} else {
		put(entryname, listpermission);
	}

	StfParameter* params = new StfParameter();
	params->addTO(entryname);
	player->sendSystemMessage("player_structure", "player_added", params);
	delete params;
}


/**
 * Adds the passed entry to the specified permission list.
 * \param player The player granting permission.
 * \param entryname The entry to be added to the list.
 * \param listname The name of the list to add them to: BAN, ENTRY, ADMIN, HOPPER, VENDOR
 */
void StructurePermissionList::revokePermission(Player* player, const String& entryname, const String& listname) {
	uint8 listpermission = getPermission(listname);

	if (entryname == parentStructure->getOwnerName().toLowerCase()) {
		player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
		return;
	}

	if (contains(entryname)) {
		uint8 permission = get(entryname);

		if (!(permission & listpermission))
			return;

		get(entryname) &= ~listpermission;

		StfParameter* params = new StfParameter();
		params->addTO(entryname);
		player->sendSystemMessage("player_structure", "player_removed", params);
		delete params;
	}
}



void StructurePermissionList::parsePermissionsString(const String& permissions) {
	if (permissions.isEmpty())
		return;

	removeAll();

	try {
		StringTokenizer tokenizer(permissions);
		tokenizer.setDelimeter(":");

		while (tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			if (token.isEmpty())
				continue;

			StringTokenizer keyvalue(token);
			keyvalue.setDelimeter("=");

			String key;
			String value;

			keyvalue.getStringToken(key);
			keyvalue.getStringToken(value);

			put(key, Integer::valueOf(value));
		}
	} catch (...) {
		System::out << "StructurePermissionList::parsePermissionsString >> Improperly formatted permissions string attempted to be loaded: " << permissions << endl;
	}
}

String& StructurePermissionList::getPermissionsString() {
	StringBuffer permissionsstring;

	for (int i = 0; i < size(); i++) {
		VectorMapEntry<String, uint8>* entry = elementAt(i);
		permissionsstring << entry->getKey() << "=" << entry->getValue() << ":";
	}

	permissionsString = permissionsstring.toString();
	return permissionsString;
}
