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


CraftingSession::CraftingSession() {

}

CraftingSession::~CraftingSession() {

}

void CraftingSession::request(PlayerCreature* pl, PlayerObject* play, CraftingTool* tool, Vector<uint32>& enabledTabs, float maxComplexity, uint64 stationID) {

	/// Check Jedi tool usage later
	//if(getToolType() == JEDI && !player->isJedi()) {
	//	sendToolStartFailure(player, "jedi_spam", "not_your_lightsaber");
	//	return;
	//}

	playerObject = play;
	player = pl;
	craftingTool = tool;
	experimentingEnabled = stationID != 0;
	complexityLevel = maxComplexity;
	craftingStationID = stationID;

	collectSchematics(enabledTabs);

	sendStart();
}

void CraftingSession::cancel() {
	playerObject = NULL;
	player = NULL;
	craftingTool = NULL;
	experimentingEnabled = false;
	complexityLevel = 0;
	craftingStationID = 0;
	schematics.removeAll();
}

void CraftingSession::collectSchematics(Vector<uint32>& enabledTabs) {

	schematics = playerObject->filterSchematicList(enabledTabs);
}

void CraftingSession::sendStart() {

	/// Packet Sending Start
	/// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(playerObject);
	dplay9->setExperimentationEnabled(experimentingEnabled);
	dplay9->setCraftingState(1);
	dplay9->setClosestCraftingStation(craftingStationID);
	dplay9->setExperimentationPoints(0);
	dplay9->close();
	player->sendMessage(dplay9);
	// End dplay9***********************************

	/// Object Controller Message 102 - Schematic List
	ObjectControllerMessage* ocm = new ObjectControllerMessage(
			player->getObjectID(), 0x0B, 0x102);
	ocm->insertLong(craftingTool->getObjectID());
	ocm->insertLong(craftingStationID);

	ocm->insertInt(schematics.size());
	for (int i = 0; i < schematics.size(); ++i) {

		DraftSchematic* draftSchematic = schematics.get(i).get();
		//ocm->insertLong(draftSchematic->getObjectID());
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
