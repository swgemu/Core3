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
		ZoneServer* zoneServer = creature->getZoneServer();
		Zone* zone = creature->getZone();

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) creature;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(player);

		if (obj == NULL || !obj->isStructureObject()) {
			player->sendSystemMessage("@player_structure:command_no_building"); //You must be in a building or near an installation to use that command.
			return GENERALERROR;
		}

		StructureObject* structureObject = (StructureObject*) obj.get();

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		String targetPlayerName;
		tokenizer.getStringToken(targetPlayerName);

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		String listName;
		tokenizer.getStringToken(listName);

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		String action;
		tokenizer.getStringToken(action);

		if (action != "remove" && !playerManager->existsName(targetPlayerName)) {
			StringIdChatParameter params;
			params.setStringId("@player_structure:modify_list_invalid_player"); //%NO is an invalid player name.
			params.setTO(targetPlayerName);
			player->sendSystemMessage(params);
			return INVALIDPARAMETERS;
		}

		if (listName != "ADMIN" && listName != "ENTRY" && listName != "BAN" && listName != "HOPPER" && listName != "VENDOR")
			return INVALIDPARAMETERS;

		if (action == "add") {
			if (structureObject->addPermission(player, targetPlayerName, listName)) {
				StringIdChatParameter params;
				params.setStringId("@player_structure:player_added"); //%NO added to the list.
				params.setTO(targetPlayerName);
				player->sendSystemMessage(params);
			}
		} else if (action == "remove") {
			if (structureObject->removePermission(player, targetPlayerName, listName)) {
				StringIdChatParameter params;
				params.setStringId("@player_structure:player_removed"); //%NO removed from the list.
				params.setTO(targetPlayerName);
				player->sendSystemMessage(params);
			}
		}

		ManagedReference<ChatManager*> chatManager = zoneServer->getChatManager();

		if (chatManager == NULL)
			return SUCCESS;

		ManagedReference<PlayerCreature*> targetPlayer = chatManager->getPlayer(targetPlayerName);

		//Update the cell permissions in case the player is in the building currently.
		if (targetPlayer != NULL && structureObject->isBuildingObject()) {
			BuildingObject* buildingObject = (BuildingObject*) structureObject;
			buildingObject->updateCellPermissionsTo(targetPlayer);
		}

		return SUCCESS;
	}

};

#endif //PERMISSIONLISTMODIFYCOMMAND_H_
