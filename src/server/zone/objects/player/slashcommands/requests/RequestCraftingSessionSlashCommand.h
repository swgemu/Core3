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

#ifndef REQUESTCRAFTINGSESSIONSLASHCOMMAND_H_

#define REQUESTCRAFTINGSESSIONSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
#include "../../../tangible/crafting/CraftingTool.h"
#include "../../../tangible/crafting/CraftingStation.h"
#include "../../../../packets.h"

class RequestCraftingSessionSlashCommand : public SlashCommand {
public:

	RequestCraftingSessionSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: SlashCommand(name, server) {

	}

	bool doSlashCommand(Player* player, Message* packet) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		uint64 oid = packet->parseLong();
		ManagedReference<SceneObject> scno = player->getZone()->lookupObject(oid);

		if (scno == NULL)
			return false;

		if (!scno->isTangible())
			return false;

		if (((TangibleObject*) scno.get())->isCraftingTool()) {

			CraftingTool* craftingTool = (CraftingTool*) scno.get();

			if (craftingTool != NULL) {

				if (player->isRidingMount()) {
					craftingTool->sendToolStartFailure(player, "error_message",
 	                                                "survey_on_mount");
					return false;
				}

				if (craftingTool->isReady()) {

					craftingTool->sendToolStart(player);
					return true;
				}

				else if (craftingTool->isFinished())

					craftingTool->sendToolStartFailure(player, "system_msg",
 	                                                "crafting_tool_full");

				else

					craftingTool->sendToolStartFailure(player, "system_msg",
 	                                                "crafting_tool_creating_prototype");

			}
		} else {

			if (!((TangibleObject*) scno.get())->isCraftingStation())
				return false;

			CraftingStation* craftingStation = (CraftingStation*) scno.get();

			if (craftingStation == NULL)
				return false;

			CraftingTool* craftingTool = player->getCraftingTool(
					craftingStation->getStationType(), false);

			if (craftingTool != NULL) {
				craftingTool->sendToolStart(player);
				return true;
			}
			else
				player->sendSystemMessage("No tool available to start.");
		}
		return false;
	}

};

#endif //REQUESTCRAFTINGSESSIONSLASHCOMMAND_H_

