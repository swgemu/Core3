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

#ifndef PERMISSIONLISTMODIFYCOMMAND_H_
#define PERMISSIONLISTMODIFYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

class PermissionListModifyCommand : public QueueCommand {
public:

	PermissionListModifyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, target);

		if (obj == NULL || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:no_building"); //You must be in a building, be near an installation, or have one targeted to do that.
			return INVALIDTARGET;
		}

		StructureObject* structureObject = (StructureObject*) obj.get();

		String targetName, listName, action;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(targetName);
			tokenizer.getStringToken(listName);
			tokenizer.getStringToken(action);

			targetName = targetName.toLowerCase();
			listName = listName.toUpperCase();
			action = action.toLowerCase();

			if (action != "remove" && action != "add" && action != "toggle")
				throw Exception();

		} catch (Exception& e) {
			return INVALIDPARAMETERS;
		}

		Locker _lock(structureObject, creature);

		if (!structureObject->hasPermissionList(listName)) {
			creature->sendSystemMessage("@player_structure:must_specify_list"); //You must specify a valid permission list (Entry, Ban, Admin, Hopper)
			return INVALIDPARAMETERS;
		}

		if (structureObject->isPermissionListFull(listName)) {
			creature->sendSystemMessage("@player_structure:too_many_entries"); //You have too many entries on that list. You must remove some before adding more.
			return INVALIDPARAMETERS;
		}

		if (targetName.length() > 40) {
			creature->sendSystemMessage("@player_structure:permission_40_char"); //Permission list entries cannot be longer than 40 characters.
			return INVALIDPARAMETERS;
		}

		bool isOwner = structureObject->isOwnerOf(creature->getObjectID());

		if (structureObject->isOnBanList(targetName)) {
			if (listName == "ENTRY" || listName == "ADMIN") {
				creature->sendSystemMessage("@player_structure:no_banned"); //You cannot add a banned player to the entry list.
				return INVALIDPARAMETERS;
			} else if (listName != "BAN") {
				StringIdChatParameter params("@player_structure:cannot_add_banned"); //%NO must first be removed from the banned list.
				params.setTO(targetName);
				creature->sendSystemMessage(params);
				return INVALIDPARAMETERS;
			}

		} else if (structureObject->isOnAdminList(targetName)) {
			if (listName == "BAN" && isOwner)
				return INVALIDPARAMETERS; //Can't ban the owner.

			if (creature->getFirstName().toLowerCase() == targetName) {
				creature->sendSystemMessage("@player_structure:cannot_remove_self"); //You cannot remove yourself from the admin list.
				return INVALIDPARAMETERS;
			}

			if (listName == "ENTRY" && !isOwner) {
				creature->sendSystemMessage("@player_structure:no_remove_admin"); //You cannot remove an admin from the entry list.
				return INVALIDPARAMETERS;
			}

			if (listName == "ADMIN" && structureObject->isOwnerOf(playerManager->getObjectID(targetName))) {
				creature->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
				return INVALIDPARAMETERS;
			}

			if (listName == "HOPPER" && !isOwner) {
				creature->sendSystemMessage("@player_structure:hopper_cannot_remove_admin"); //You cannot remove an admin from the hopper list.
				return INVALIDPARAMETERS;
			}
		} else {
			if (!playerManager->existsName(targetName)) {
				StringIdChatParameter params("@player_structure:modify_list_invalid_player"); //%NO is an invalid player name.
				params.setTO(targetName);

				creature->sendSystemMessage(params);
				return INVALIDPARAMETERS;
			}
		}

		if (listName == "BAN" && !structureObject->isOnBanList(targetName))
			structureObject->revokeAllPermissions(targetName); //Remove all existing permissions

		StringIdChatParameter params;
		params.setTO(targetName);

		int returnCode = StructurePermissionList::LISTNOTFOUND;

		if (action == "add")
			returnCode = structureObject->grantPermission(listName, targetName);
		else if (action == "remove")
			returnCode = structureObject->revokePermission(listName, targetName);
		else
			returnCode = structureObject->togglePermission(listName, targetName);

		switch (returnCode) {
		case StructurePermissionList::GRANTED:
			params.setStringId("@player_structure:player_added"); //%NO added to the list.
			break;
		case StructurePermissionList::REVOKED:
			params.setStringId("@player_structure:player_removed"); //%NO removed from the list.
			break;
		default:
			return GENERALERROR;
		}

		creature->sendSystemMessage(params);

		ManagedReference<CreatureObject*> targetPlayer = playerManager->getPlayer(targetName);

		//Update the cell permissions in case the player is in the building currently.
		if (targetPlayer != NULL && structureObject->isBuildingObject()) {
			BuildingObject* buildingObject = (BuildingObject*) structureObject;
			buildingObject->updateCellPermissionsTo(targetPlayer);
		}

		return SUCCESS;
	}

};

#endif //PERMISSIONLISTMODIFYCOMMAND_H_
