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

#ifndef SELECTDRAFTSCHEMATICSLASHCOMMAND_H_

#define SELECTDRAFTSCHEMATICSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
/*#include "../../../tangible/crafting/CraftingTool.h"
#include "../../../draftschematic/DraftSchematic.h"
#include "../../../../packets.h"*/

class SelectDraftSchematicSlashCommand : public QueueCommand {
public:

	SelectDraftSchematicSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doSlashCommand(PlayerCreature* player, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		/*CraftingTool* craftingTool = player->getActiveCraftingTool();

		if(craftingTool == NULL)
			return false;

		uint64 unknown = packet->parseLong();

		if(unknown != 0)
			System::out << "parseSelectDraftSchematic's unknown is " << unknown << endl;

		UnicodeString uniIndexOfSelectedSchematic;
		packet->parseUnicode(uniIndexOfSelectedSchematic);

		StringTokenizer tokenizer(uniIndexOfSelectedSchematic.toString());

		int indexOfSelectedSchematic;

		if (tokenizer.hasMoreTokens()) {
			indexOfSelectedSchematic = tokenizer.getIntToken();

			DraftSchematic* draftSchematic =
				craftingTool->getCurrentDraftSchematic(indexOfSelectedSchematic);

			if (draftSchematic == NULL) {

				parseCancelCraftingSession(player, packet);
				craftingTool->sendToolStart(player);
				draftSchematic = craftingTool->getCurrentDraftSchematic(indexOfSelectedSchematic);
			}

			if (draftSchematic != NULL) {

				CraftingManager* craftingManager =
					player->getZone()->getZoneServer()->getCraftingManager();
				if (craftingManager == NULL)
					return false;

				craftingManager->prepareCraftingSession(player, craftingTool, draftSchematic);

			} else {
				// This else should never execute
				player->sendSystemMessage("Selected Draft Schematic was invalid.  Please inform Kyle of this error.");
			}
		}*/
		return true;
	}

	/*void parseCancelCraftingSession(PlayerCreature* player, Message* packet) {

		CraftingTool* craftingTool = player->getActiveCraftingTool();

		if (craftingTool == NULL)
			return;

		// DPlay9
		PlayerObjectDeltaMessage9* dplay9 =
				new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->setCraftingState(0);
		craftingTool->setCraftingState(0);
		dplay9->close();
		player->sendMessage(dplay9);

		player->setActiveCraftingTool(NULL);

		// Clean up crafting here, delete, sceneremove unneeded objects
		craftingTool->cleanUp(player);
	}*/

};

#endif //SELECTDRAFTSCHEMATICSLASHCOMMAND_H_

