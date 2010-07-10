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

#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage7.h"

void CraftingToolImplementation::loadTemplateData(
		SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CraftingToolTemplate* craftingToolData =
			dynamic_cast<CraftingToolTemplate*> (templateData);

	if (craftingToolData == NULL) {
		throw Exception("invalid template for CraftingTool");
	}

	type = craftingToolData->getToolType();

	for (int i = 0; i < craftingToolData->getTabs().size(); ++i)
		enabledTabs.add(craftingToolData->getTabs().get(i));
}

void CraftingToolImplementation::fillObjectMenuResponse(
		ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

}

int CraftingToolImplementation::handleObjectMenuSelect(
		PlayerCreature* playerCreature, byte selectedID) {
	PlayerObject* playerObject = playerCreature->getPlayerObject();

	if (selectedID == 20) { // use object

	}

	return 1;
}

void CraftingToolImplementation::fillAttributeList(AttributeListMessage* alm,
		PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("craft_tool_effectiveness", Math::getPrecision(
			effectiveness, 2));

	alm->insertAttribute("craft_tool_status", status);

	if (craftersName != "") {

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftersSerial != "") {

		alm->insertAttribute("serial_number", craftersSerial);
	}
}

Vector<uint32>* CraftingToolImplementation::getToolTabs() {
	return &enabledTabs;
}

void CraftingToolImplementation::requestCraftingSession(PlayerCreature* player,
		CraftingStation* station) {

	Locker _locker(player);

	craftingStation = station;

	//Locate closest crafting station, if exists.
	if (craftingStation == NULL)
		locateCraftingStation(player, getToolType());

	sendStart(player);
}

void CraftingToolImplementation::sendStart(PlayerCreature* player) {
	if (player == NULL) {
		return;
	}

	insertCounter = 1;

	PlayerObject* playerObject = player->getPlayerObject();

	Vector<ManagedReference<DraftSchematic*> > schematics =
			playerObject->filterSchematicList(getToolTabs());

	/// Packet Sending Start
	/// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			playerObject);
	dplay9->setExperimentationEnabled(craftingStation != NULL);
	dplay9->setCraftingState(1);
	state = 1;

	if (craftingStation != NULL)
		dplay9->setClosestCraftingStation(craftingStation->getObjectID());
	else
		dplay9->setClosestCraftingStation(0);
	dplay9->setExperimentationPoints(0);
	dplay9->close();
	player->sendMessage(dplay9);
	// End dplay9***********************************

	/// Object Controller Message 102 - Schematic List
	ObjectControllerMessage* ocm = new ObjectControllerMessage(
			player->getObjectID(), 0x0B, 0x102);
	ocm->insertLong(getObjectID());

	if (craftingStation != NULL)
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

	player->setLastCraftingToolUsed(_this);
}

void CraftingToolImplementation::cancelCraftingSession(PlayerCreature* player) {

	removeObject(manufactureSchematic);
	manufactureSchematic->setDraftSchematic(NULL);
	manufactureSchematic = NULL;

	removeObject(prototype);
	prototype = NULL;

	if (player != NULL) {
		// DPlay9
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				player->getPlayerObject());
		dplay9->setCraftingState(0);
		state = 0;
		dplay9->close();
		player->sendMessage(dplay9);
	}
}

void CraftingToolImplementation::locateCraftingStation(PlayerCreature* player,
		int toolType) {

	ZoneServer* server = player->getZone()->getZoneServer();
	Zone* zone = player->getZone();

	Locker zoneLocker(zone);
	ManagedReference<CraftingStation*> station = NULL;

	for (int i = 0; i < player->inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno =
				(SceneObjectImplementation*) player->getInRangeObject(i);

		if (scno->isCraftingStation() && player->isInRange(scno, 7.0f)) {

			station = (CraftingStation*) server->getObject(scno->getObjectID());

			if (station == NULL)
				continue;

			if (toolType == station->getStationType() || (toolType
					== CraftingTool::JEDI && station->getStationType()
					== CraftingTool::WEAPON)) {
				craftingStation = station;
				return;
			}
		}
	}
}

void CraftingToolImplementation::selectDraftSchematic(PlayerCreature* player,
		int index) {

	DraftSchematic* draftschematic = player->getPlayerObject()->getSchematic(
			index);

	if (draftschematic == NULL) {
		player->sendSystemMessage("ui_craft", "err_no_draft_schematic");
		return;
	}

	try {

		manufactureSchematic
				= (ManufactureSchematic*) draftschematic->createManufactureSchematic();

		if (manufactureSchematic == NULL) {
			player->sendSystemMessage("ui_craft", "err_no_manf_schematic");
			return;
		}

		addObject(manufactureSchematic, 0x4, false);
		manufactureSchematic->sendTo(player, true);

		prototype = dynamic_cast<TangibleObject*> (player->getZoneServer()->createObject(
				draftschematic->getTanoCRC(), 0));

		if (prototype == NULL) {
			player->sendSystemMessage("ui_craft", "err_no_prototype");
			return;
		}

		addObject(prototype, 0xFFFFFFFF, false);
		prototype->sendTo(player, true);

		// Dplay9 ********************************************************
		// Sets the Crafting state to 2, which is the Resource screen
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				player->getPlayerObject());
		dplay9->setExperimentationPoints(0xFFFFFFFF);
		dplay9->setCraftingState(2);
		state = 2;
		dplay9->close();

		player->sendMessage(dplay9);
		// End Dplay9 *****************************************************

		// Dtano3 ********************************************************
		// Update Condition Damage
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(prototype);
		dtano3->updateConditionDamage();
		dtano3->close();
		player->sendMessage(dtano3);
		// End Dtano3 *****************************************************

		// Start the insert count so inserts and removals work
		insertCounter = 1;

	} catch (...) {
		player->sendSystemMessage("ui_craft", "err_no_prototype");
	}
}

void CraftingToolImplementation::synchronizedUIListenForSchematic(PlayerCreature* player) {

	if(manufactureSchematic == NULL)
		return;

	ManufactureSchematicObjectMessage7* mcso7 =
			new ManufactureSchematicObjectMessage7(manufactureSchematic);
	player->sendMessage(mcso7);

	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			player->getObjectID(), 0x0B, 0x0103);
	objMsg->insertLong(getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(manufactureSchematic->getObjectID());// Manufacture Schematic Object ID
	objMsg->insertLong(prototype->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(2);
	objMsg->insertByte(1);

	ManagedReference<DraftSchematic*> draftSchematic =
			manufactureSchematic->getDraftSchematic();

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
