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

CraftingSession::CraftingSession() {
	insertCount = 1;
}

CraftingSession::~CraftingSession() {

}
/// Player is locked pre
void CraftingSession::request(PlayerCreature* pl, PlayerObject* play, CraftingTool* tool,
		CraftingStation* station) {

	/// Check Jedi tool usage later
	//if(getToolType() == JEDI && !player->isJedi()) {
	//	sendToolStartFailure(player, "jedi_spam", "not_your_lightsaber");
	//	return;
	//}

	playerObject = play;
	player = pl;
	craftingTool = tool;
	craftingStation = station;

	if(craftingTool != NULL) {
		collectSchematics();
		sendStart();
	} else
		player->sendSystemMessage("You do not have a crafting tool compatible with this station");
}

void CraftingSession::cancel() {

	if(playerObject != NULL && player != NULL) {
		// DPlay9
		PlayerObjectDeltaMessage9* dplay9 =
				new PlayerObjectDeltaMessage9(playerObject);
		dplay9->setCraftingState(0);
		dplay9->close();
		player->sendMessage(dplay9);
	}

	playerObject = NULL;
	player = NULL;
	craftingTool = NULL;
	craftingStation = NULL;
	schematic = NULL;
	object = NULL;
	schematics.removeAll();
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

void CraftingSession::collectSchematics() {

	schematics = playerObject->filterSchematicList(craftingTool->getToolTabs());
}

void CraftingSession::sendStart() {

	/// Packet Sending Start
	/// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
	dplay9->setExperimentationEnabled(craftingStation != NULL);
	dplay9->setCraftingState(1);
	currentState = 1;

	if(craftingStation != NULL)
		dplay9->setClosestCraftingStation(craftingStation->getObjectID());
	else
		dplay9->setClosestCraftingStation(0)
		;
	dplay9->setExperimentationPoints(0);
	dplay9->close();
	player->sendMessage(dplay9);
	// End dplay9***********************************

	/// Object Controller Message 102 - Schematic List
	ObjectControllerMessage* ocm = new ObjectControllerMessage(
			player->getObjectID(), 0x0B, 0x102);
	ocm->insertLong(craftingTool->getObjectID());

	if(craftingStation != NULL)
		ocm->insertLong(craftingStation->getObjectID());
	else
		ocm->insertLong(0);

	ocm->insertInt(schematics.size());
	for (int i = 0; i < schematics.size(); ++i) {

		DraftSchematic* draftSchematic = schematics.get(i).get();
		ocm->insertInt(draftSchematic->getSchematicID());
		ocm->insertInt(draftSchematic->getClientObjectCRC());
		ocm->insertInt(draftSchematic->getToolTab()); // this number decides what tab the schematic goes in (ex: 4 = food tab in crafting window)
	}
	player->sendMessage(ocm);



	/// Send all the ingredients to the player
	for (int i = 0; i < schematics.size(); ++i) {

		DraftSchematic* draftSchematic = schematics.get(i).get();

		/// Object Controller Message 1BF
		draftSchematic->sendDraftSlotsTo(player);
		// End OBJC 1BF***********************************
	}

	/// Send all the experimental properties to the player
	for (int i = 0; i < schematics.size(); ++i) {

		DraftSchematic* draftSchematic = schematics.get(i).get();

		/// Object Controller Message 207
		draftSchematic->sendResourceWeightsTo(player);
		// End OBJC 207***********************************
	}
}

void CraftingSession::selectDraftSchematic(ManufactureSchematic* manu, TangibleObject* tano) {

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

void CraftingSession::synchronizedUIListen() {

	ManufactureSchematicObjectMessage7* mcso7 = new ManufactureSchematicObjectMessage7(schematic);
	player->sendMessage(mcso7);

	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0103);
	objMsg->insertLong(craftingTool->getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(schematic->getObjectID());// Manufacture Schematic Object ID
	objMsg->insertLong(object->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(2);
	objMsg->insertByte(1);

	int draftSlotCount = draftSchematic->getDraftSlotCount();
	objMsg->insertInt(draftSlotCount);

	// Send all the ingredient data
	for (int i = 0; i < draftSlotCount; i++) {
		DraftSlot* slot = draftSchematic->getDraftSlot(i);
		if (slot != NULL)
			slot->insertToMessage(objMsg);
	}
	objMsg->insertShort(0);

	player->sendMessage(objMsg);
}
