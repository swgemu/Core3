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

#include "../../../packets.h"
#include "../../../objects.h"
#include "CraftingTool.h"
#include "CraftingToolImplementation.h"
#include "../../../ZoneClientSession.h"

CraftingToolImplementation::CraftingToolImplementation(uint64 object_id, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : CraftingToolServant(object_id, tempCRC, n, tempn,
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	stfFile = "obj_n";
	stfName = tempn;
	customName = n;
	init();
}

CraftingToolImplementation::CraftingToolImplementation(CreatureObject* creature, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : CraftingToolServant(creature, tempCRC, n, tempn,
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	stfFile = "obj_n";
	stfName = tempn;
	customName = n;
	init();
}

CraftingToolImplementation::~CraftingToolImplementation(){
	tempIngredient.removeAll();

	tabIds.removeAll();

	schematicsToSend.removeAll();

	delete craftingSlots;

	craftingSlots = NULL;
}

void CraftingToolImplementation::init() {
	objectSubType = TangibleObjectImplementation::CRAFTINGTOOL;

	setToolEffectiveness(-15.0f);
	setCraftingState(0);
	currentDraftSchematic = NULL;
	currentTano = NULL;
	recoverResources = true;

	craftingSlots = new CraftingSlots();

	status = "@crafting:tool_status_ready";
	hopper = NULL;

	assemblyResults = 0;

	experimentingEnabled = false;

	tabIds.removeAll();

	recoverResources = true;

	if (objectCRC == 0x3EE5146D){

		setToolType(GENERIC);
		tabIds.add(1);
		tabIds.add(2);
		tabIds.add(4);
		tabIds.add(8);
		tabIds.add(1024);
		tabIds.add(4096);
		tabIds.add(524288);
	}

	if (objectCRC == 0x2CED1748){

		setToolType(CLOTHING);
		tabIds.add(2);
		tabIds.add(8);
		tabIds.add(16384);
		tabIds.add(32768);
	}

	if (objectCRC == 0xA9D9972F){

		setToolType(FOOD);
		tabIds.add(4);
		tabIds.add(64);
		tabIds.add(128);
		tabIds.add(256);
		tabIds.add(8192);

	}

	if (objectCRC == 0x2CF24272){

		setToolType(JEDI);
		tabIds.add(2048);

	}

	if (objectCRC == 0xAD0E3DB0){

		setToolType(SPACE);
		tabIds.add(131072);
		tabIds.add(262144);

	}

	if (objectCRC == 0xFEDA0435){

		setToolType(STRUCTURE);
		tabIds.add(512);
		tabIds.add(1024);


	}

	if (objectCRC == 0x64F6D031){

		setToolType(WEAPON);
		tabIds.add(1);
		tabIds.add(16);
		tabIds.add(32);
		tabIds.add(4096);
		tabIds.add(65536);
		tabIds.add(524288);

	}

}

int CraftingToolImplementation::useObject(Player* player) {
	return 0;
}

void CraftingToolImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;
	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	TangibleObjectMessage3* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	TangibleObjectMessage6* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);

	if (doClose)
		SceneObjectImplementation::close(client);

	generateAttributes(player);
}

void CraftingToolImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {

	if(hopper != NULL) {
		if(hopper->getContainerObjectsSize() > 0) {
			omr->addRadialParent(132, 3, "@ui_radial:craft_hopper_output");
		}
	}

	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			if (_this->isTangible())
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->finish();

	player->sendMessage(omr);
}

void CraftingToolImplementation::parseItemAttributes() {

	String temp;

	temp = "effectiveness";
	effectiveness = itemAttributes->getFloatAttribute(temp);

	temp = "craftersname";
	craftersName = itemAttributes->getStringAttribute(temp);

	temp = "craftedserial";
	craftedSerial = itemAttributes->getStringAttribute(temp);


}

void CraftingToolImplementation::generateAttributes(SceneObject* obj) {

	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void CraftingToolImplementation::addAttributes(AttributeListMessage* alm) {

	alm->insertAttribute("volume", "1");

	alm->insertAttribute("craft_tool_effectiveness", getPrecision(effectiveness, 2));

	alm->insertAttribute("craft_tool_status", status);

	if (craftersName != ""){

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftedSerial != ""){

		alm->insertAttribute("serial_number", craftedSerial);
	}

}

void CraftingToolImplementation::updateCraftingValues(DraftSchematic* draftSchematic){

	String name;

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();
	//craftingValues->toString();

	name = "effectiveness";
	effectiveness = craftingValues->getCurrentValue("usemodifier");
	itemAttributes->setFloatAttribute(name, effectiveness);

}

bool CraftingToolImplementation::hasAllRequiredResources(DraftSchematic* draftSchematic) {

	/*for(int i = 0; i < getSlotCount(); ++i) {
		bool optional = draftSchematic->getIngredient(i)->isOptionalSlot();
		if(!optional && getIngredientInSlot(i) == NULL ||
				getIngredientInSlotQuantity(i) != draftSchematic->getIngredient(i)->getResourceQuantity())
			return false;
	}
	return true;*/

	for(int i = 0; i < getSlotCount(); ++i) {
		bool optional = draftSchematic->getIngredient(i)->isOptionalSlot();
		if(!optional && getIngredientInSlot(i) == NULL)
			return false;
	}
	return true;
}

/*
 *  This method starts the crafting process.  It starts when a crafting tool
 *  is opened, and ends after sending the appropriate packets to display tool
 *  and data on the screen
 *  \params Player - The player object that started the crafting tool
 */
void CraftingToolImplementation::sendToolStart(Player* player) {

	/// Temporary reference for schematic objects
	DraftSchematic* draftSchematic;

	setRecoverResources(true);

	/// Default Crafting station complexity
	float workingStationComplexity = 15;

	/// Object ID and type of station, if found nearby
	int stationType = 0;
	uint64 oidOfLocatedCraftingStation = 0;

	/// Identify type of nearby crafting station, if in range
	oidOfLocatedCraftingStation = findCraftingStation(player, workingStationComplexity);

	/// If station is found, we enable experimenting
	if (oidOfLocatedCraftingStation != 0)
		experimentingEnabled = true;
	else
		experimentingEnabled = false;

	/// Get schematics based on type of tool and complexity level
	getSchematicsForTool(player, workingStationComplexity);

	/// Packet Sending Start

	/// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setExperimentationEnabled(experimentingEnabled);
	dplay9->setCraftingState(1);
	setCraftingState(1);
	dplay9->setClosestCraftingStation(oidOfLocatedCraftingStation);
	dplay9->setExperimentationPoints(0);
	dplay9->close();
	player->sendMessage(dplay9);
	// End dplay9***********************************

	/// Object Controller Message 102 - Schematic List
	ObjectControllerMessage* ocm = new ObjectControllerMessage(player->getObjectID(),0x0B, 0x102);
	ocm->insertLong(getObjectID());
	ocm->insertLong(oidOfLocatedCraftingStation);
	uint32 draftSchematicListSize = schematicsToSend.size();
	ocm->insertInt(draftSchematicListSize);

	for (int i = 0; i < draftSchematicListSize; ++i){

		draftSchematic = schematicsToSend.get(i);

		ocm->insertInt(draftSchematic->getSchematicID());
		ocm->insertInt(draftSchematic->getObjectCRC());

		ocm->insertInt(draftSchematic->getCraftingToolTab()); // this number decides what tab the schematic goes in (ex: 4 = food tab in crafting window)
	}
	player->sendMessage(ocm);
	// End OBJC 102***********************************

	/// Send all the ingredients to the player
	for (int i = 0; i < draftSchematicListSize; ++i){

		draftSchematic = schematicsToSend.get(i);

		/// Object Controller Message 1BF
		draftSchematic->sendIngredientsToPlayer(player);
		// End OBJC 1BF***********************************
	}

	/// Send all the experimental properties to the player
	for (int i = 0; i < draftSchematicListSize; ++i){

		draftSchematic = schematicsToSend.get(i);

		/// Object Controller Message 207
		draftSchematic->sendExperimentalPropertiesToPlayer(player);
		// End OBJC 207***********************************
	}

	player->setActiveCraftingTool(_this);
}

void CraftingToolImplementation::sendToolStartFailure(Player* player, const String& stfFile, const String& stfValue) {

	player->sendSystemMessage(stfFile, stfValue);

	// Start Object Controller **(Failed to start crafting Session************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x10F);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);
}

void CraftingToolImplementation::getSchematicsForTool(Player* player, float workingStationComplexity){

	bool toolUsesTab;
	schematicsToSend.removeAll();

	for (int i = 0; i < player->getDraftSchematicListSize(); i++) {
		DraftSchematic* draftSchematic = player->getDraftSchematic(i);

		if (draftSchematic != NULL) {

			toolUsesTab = false;

			for (int j = 0; j < tabIds.size(); ++j) {

				if (tabIds.get(j) == draftSchematic->getCraftingToolTab()) {

					toolUsesTab = true;
					break;
				}
			}

			if (workingStationComplexity >= draftSchematic->getComplexity()
					&& toolUsesTab) {

				schematicsToSend.add(draftSchematic);
			}
		}
	}
}

uint64 CraftingToolImplementation::findCraftingStation(Player* player, float& workingStationComplexity){

	QuadTreeEntry* entry;
	SceneObject* object;
	TangibleObject* inRangeObject;
	CraftingStation* station;
	uint64 oid;
	ZoneServer* server = player->getZone()->getZoneServer();
	Zone* zone = player->getZone();

	try {

		zone->lock();

		int closeObjectCount = player->inRangeObjectCount();

		for (int i = 0; i < closeObjectCount; ++i) {

			entry = player->getInRangeObject(i);

			oid = entry->getObjectID();

			object = server->getObject(oid);

			if (object != NULL && object->isTangible()) {
				inRangeObject = (TangibleObject*) object;

				if (inRangeObject->isCraftingStation() && player->isInRange(
						inRangeObject, 7.0f)) {
					station = (CraftingStation*) inRangeObject;

					//System::out << "Station = " << station->getStationType() << "   Tool = " << _this->getToolType() << endl;

					if (_this->getToolType() == station->getStationType()
							|| (_this->getToolType() == JEDI
									&& station->getStationType() == WEAPON)) {

						workingStationComplexity = ((CraftingStation*) inRangeObject)->getComplexityLevel();
						zone->unlock();
						return station->getObjectID();
					}
				}
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
	return 0;
}

void CraftingToolImplementation::setWorkingTano(TangibleObject* tano){

	if (currentTano != NULL) {

		currentTano->setParent(NULL);
		currentTano->finalize();
		currentTano = NULL;
	}

	currentTano = tano;
}

void CraftingToolImplementation::setWorkingDraftSchematic(
		DraftSchematic* draftSchematic) {

	if (currentDraftSchematic != NULL) {
		currentDraftSchematic->setParent(NULL);
		currentDraftSchematic->finalize();

		currentDraftSchematic = NULL;
	}

	currentDraftSchematic = draftSchematic->dsClone(draftSchematic);

	craftingSlots->init(currentDraftSchematic);
}

void CraftingToolImplementation::resetSlots() {

	if (currentDraftSchematic != NULL) {

		craftingSlots->init(currentDraftSchematic);

	} else {

		craftingSlots->init(0);
	}
}

Container* CraftingToolImplementation::getHopper(Player* player){
	if (hopper == NULL){
		Container* hop = new Container(player->getNewItemID());
	}
	return hopper;
}

void CraftingToolImplementation::retriveHopperItem(Player* player){

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	Inventory* inventory = player->getInventory();

	if (hopper != NULL){
		if (hopper->getContainerObjectsSize() > 0 && inventory->getObjectCount() < 80){

			TangibleObject* tano = (TangibleObject*) hopper->getObject(0);
			hopper->removeObject(0);
			player->addInventoryItem(tano);

			itemManager->savePlayerItem(player, tano);

			UnicodeString mess = UnicodeString("Hopper item Retrieved");
			ChatSystemMessage* sysMessage = new ChatSystemMessage(mess);
			player->sendMessage(sysMessage);

			tano->sendTo(player);

			_this->setStatusReady();
		}
	}
}
void CraftingToolImplementation::cleanUp(Player* player) {

	CraftingManager* cm = player->getZone()->getZoneServer()->getCraftingManager();
	TangibleObject* tano;

	int quantity;

	if (recoverResources) {
		for (int i = 0; i < craftingSlots->size(); ++i) {

			tano = craftingSlots->getIngredientInSlot(i);

			craftingSlots->clearIngredientInSlot(i);

			if (tano != NULL) {

				if (tano->isResource()) {

					ResourceContainer* rcno = (ResourceContainer*) tano;

					if (rcno->getContents() > 0) {

						player->addInventoryResource(rcno);

					}

				} else if (tano->isComponent()) {

					Component* component = (Component*) tano;
					cm->putComponentBackInInventory(player, component);
				}
			}
		}
	}

	if (currentDraftSchematic != NULL) {

		//Scene Object Destroy
		SceneObjectDestroyMessage* destroy =
						new SceneObjectDestroyMessage(currentDraftSchematic->getObjectID());
		player->sendMessage(destroy);

		currentDraftSchematic->setParent(NULL);
		currentDraftSchematic->finalize();
		currentDraftSchematic = NULL;
	}

	if (currentTano != NULL) {
		if (status == "@crafting:tool_status_ready") {

			SceneObjectDestroyMessage* destroy =
					new SceneObjectDestroyMessage(currentTano->getObjectID());
			player->sendMessage(destroy);

			currentTano->setParent(NULL);
			currentTano->finalize();

		}
		currentTano = NULL;
	}

	SceneObject* tempScno;

	for (int i = 0; i < tempIngredient.size(); ++i) {

		tano = tempIngredient.get(i);
		tempScno = player->getInventoryItem(tano->getObjectID());

		if (tano != NULL && tempScno == NULL) {

			SceneObjectDestroyMessage* destroy =
					new SceneObjectDestroyMessage(tano->getObjectID());
			player->sendMessage(destroy);

			tano->setParent(NULL);
			tano->finalize();
		}

		tano = NULL;

	}

	tempIngredient.removeAll();
	schematicsToSend.removeAll();

	player->setActiveCraftingTool(NULL);
}
