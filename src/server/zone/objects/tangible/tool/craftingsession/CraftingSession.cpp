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

#include "CraftingSession.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage7.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"

CraftingSession::CraftingSession() {
	insertCount = 1;
}

CraftingSession::~CraftingSession() {

}

/*void CraftingSession::closeCraftingWindow() {

	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(1);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);

	objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(0);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);

	objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01C2);
	objMsg->insertByte(counter);
	player->sendMessage(objMsg);
}*/

void CraftingSession::selectDraftSchematic(ManufactureSchematic* manu, TangibleObject* tano) {
	if (player == NULL || playerObject == NULL) {
		cancel();
		return;
	}

	if(manu == NULL) {
		player->sendSystemMessage("ui_craft", "err_no_manf_schematic");
		cancel();
		return;
	}

	if(tano == NULL) {
		player->sendSystemMessage("ui_craft", "err_no_prototype");
		cancel();
		return;
	}

	schematic = manu;
	draftSchematic = schematic->getDraftSchematic();
	object = tano;

	schematic->setParent(craftingTool);
	schematic->setContainmentType(0x4);
	schematic->sendTo(player, true);

	object->setParent(craftingTool);
	object->setContainmentType(0xFFFFFFFF);
	object->sendTo(player, true);

	// Dplay9 ********************************************************
	// Sets the Crafting state to 2, which is the Resource screen
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(playerObject);
	dplay9->setExperimentationPoints(0xFFFFFFFF);
	dplay9->setCraftingState(2);
	currentState = 2;
	dplay9->close();

	player->sendMessage(dplay9);
	// End Dplay9 *****************************************************

	// Dtano3 ********************************************************
	// Update Condition Damage
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(object);
	dtano3->updateConditionDamage();
	dtano3->close();

	player->sendMessage(dtano3);
	// End Dtano3 *****************************************************

	// Start the insert count so inserts and removals work
	insertCount = 1;
}


