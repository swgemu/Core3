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

#ifndef FINDPLAYERCOMMAND_H_
#define FINDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class FindPlayerCommand : public QueueCommand {
public:

	FindPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		//TODO: Research if this gets handled already by the absence of the 'admin' skill.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		//if (!ghost->isPrivileged())
			//return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		String targetName;
		tokenizer.getStringToken(targetName);

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		uint64 objectid = playerManager->getObjectID(targetName);

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objectid);

		if (obj == NULL || !obj->isPlayerCreature()) {
			//Send message about player not existing.
			StringIdChatParameter params;
			params.setStringId("@player_structure:modify_list_invalid_player"); //%NO is an invalid player name.
			params.setTO(targetName);
			player->sendSystemMessage(params);
			return GENERALERROR;
		}

		CreatureObject* targetObject = cast<CreatureObject*>( obj.get());
		PlayerObject* targetGhost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0x00);
		suiBox->setPromptTitle("Find Player Results");

		StringBuffer text;
		text << "Player Name:\t  " << targetObject->getDisplayedName() << "\n";

		text << "Online Status:\t  " << (targetGhost->isOffline() ? "\\#ff3300 Offline" : "\\#00ff33 Online") << "\\#.\n";

		Vector3 worldPosition = targetObject->getWorldPosition();
		text << "World Position:\t  {x:" << worldPosition.getX() << ", z:" << worldPosition.getZ() << ", y:" << worldPosition.getY() << "} " << "\n";

		if (targetObject->getParent() != NULL && targetObject->getParent()->isCellObject()) {
			ManagedReference<CellObject*> cell = cast<CellObject*>( targetObject->getParent());
			Vector3 cellPosition = targetObject->getPosition();
			text << "Cell Position:\t  {x:" << cellPosition.getX() << ", z:" << cellPosition.getZ() << ", y:" << cellPosition.getY() << "} Cell: " << cell->getCellNumber() << " (" << cell->getObjectID() << ")\n";
		}

		Quaternion* dir = targetObject->getDirection();
		text << "Direction:\t\t  {x:" << dir->getX() << ", y:" << dir->getY() << ", z:" << dir->getZ() << ", w:" << dir->getW() << "}\n";

		suiBox->setPromptText(text.toString());

		player->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //FINDPLAYERCOMMAND_H_
