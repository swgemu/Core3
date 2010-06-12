/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

#include "CraftingTool.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/tool/CraftingToolTemplate.h"


void CraftingToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CraftingToolTemplate* craftingToolData = dynamic_cast<CraftingToolTemplate*>(templateData);

	type = craftingToolData->getToolType();

	for(int i = 0; i < craftingToolData->getTabs().size(); ++i)
		enabledTabs.add(craftingToolData->getTabs().get(i));
}

void CraftingToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

}

int CraftingToolImplementation::handleObjectMenuSelect(PlayerCreature* playerCreature, byte selectedID) {
	PlayerObject* playerObject = playerCreature->getPlayerObject();

	if (selectedID == 20) { // use object

	}

	return 1;
}

void CraftingToolImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("craft_tool_effectiveness", Math::getPrecision(effectiveness, 2));

	alm->insertAttribute("craft_tool_status", status);

	if (craftersName != ""){

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftersSerial != ""){

		alm->insertAttribute("serial_number", craftersSerial);
	}
}

void CraftingToolImplementation::reqeustCraftingSession(PlayerCreature* player) {

	uint64 craftingStationID = 0;
	/// Identify type of nearby crafting station, if in range
	//oidOfLocatedCraftingStation = findCraftingStation(player, workingStationComplexity);

	/// Crafting station complexity
	float maxComplexity = 15 + effectiveness;

	/// Get schematics based on type of tool and complexity level
	player->getPlayerObject()->requestCraftingSession(player, _this, enabledTabs, maxComplexity, craftingStationID);
}
