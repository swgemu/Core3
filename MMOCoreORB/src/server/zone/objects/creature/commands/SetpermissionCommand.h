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

#ifndef SETPERMISSIONCOMMAND_H_
#define SETPERMISSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetpermissionCommand : public QueueCommand {
public:

	SetpermissionCommand(const String& name, ZoneProcessServer* server)
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
			//TODO: Return a message about not being near an administered structure.
			return INVALIDTARGET;
		}

		String listName, targetName;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(listName);
			tokenizer.getStringToken(targetName);
		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:format_setpermission_type_player"); //Format: /setPermission <type> <player>
			return INVALIDPARAMETERS;
		}

		if (targetName.length() > 40) {
			creature->sendSystemMessage("@player_structure:permission_40_char"); //Permission list entries cannot be longer than 40 characters.
			return INVALIDTARGET;
		}

		if (!playerManager->existsName(targetName)) {
			StringIdChatParameter param("@player_structure:modify_list_invalid_player"); //%NO is an invalid player name.
			param.setTO(targetName);
			creature->sendSystemMessage(param);

			return INVALIDTARGET;
		}

		StructureObject* structure = (StructureObject*) obj.get();

		Locker _lock(structure);

		int returnCode = structure->togglePermission(listName, targetName);

		//TODO: Implement messages!
		//@player_structure:too_many_entries //You have too many entries on that list. You must remove some before adding more.

		//@player_structure:must_specify_list //You must specify a valid permission list (Entry, Ban, Admin, Hopper)
		//@player_structure:no_remove_admin //You cannot remove an admin from the entry list.
		//@player_structure:hopper_cannot_remove_admin //You cannot remove an admin from the hopper list.
		//@player_structure:cannot_remove_self //You cannot remove yourself from the admin list.
		//@player_structure:cannot_remove_owner //You cannot remove the owner from the admin list.

		//TODO: Handle return codes better.
		StringIdChatParameter param("@player_structure:player_added"); //%NO added to the list.
		param.setTO(targetName);

		if (returnCode == 0)
			param.setStringId("@player_structure:player_removed"); //%NO removed from the list.

		creature->sendSystemMessage(param);

		return SUCCESS;
	}

};

#endif //SETPERMISSIONCOMMAND_H_
