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
#include "../../../ZoneClient.h"
 
CraftingToolImplementation::CraftingToolImplementation(uint64 object_id, uint32 tempCRC, 
		const unicode& n, const string& tempn) : CraftingToolServant(object_id, n, tempn, tempCRC, 
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	name = n;
	init();
}
 
CraftingToolImplementation::CraftingToolImplementation(CreatureObject* creature, uint32 tempCRC, 
		const unicode& n, const string& tempn) : CraftingToolServant(creature, n, tempn, tempCRC, 
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n"; 
	templateName = tempn;
	name = n;
	init();
}
 
CraftingToolImplementation::~CraftingToolImplementation(){ 
	resourceSlots.removeAll();
	
	resourceSlotsCount.removeAll();
	
	partialResources.removeAll();
	
	resourceSlotsID.removeAll();
}
 
void CraftingToolImplementation::init() {
	
	objectSubType = TangibleObjectImplementation::CRAFTINGTOOL;
	
	setToolEffectiveness(-15.0f);
	setCraftingState(0);
	currentDraftSchematic = NULL;
	currentTano = NULL;
	
	status = "@crafting:tool_status_ready";
	hopper = NULL;
	
	assemblyResults = 0;
	
	experimentingEnabled = false;
}
 
int CraftingToolImplementation::useObject(Player* player) {
	return 0;
}
 
void CraftingToolImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;
	SceneObjectImplementation::create(client);
	if (container != NULL)
		link(client, container);
	TangibleObjectMessage3* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);
	TangibleObjectMessage6* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);
	if (doClose)
		SceneObjectImplementation::close(client);
	generateAttributes(player);
}

void CraftingToolImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {

	if(hopper != NULL){

		if(hopper->objectsSize() > 0){
			omr->addRadialItem(0, 130, 3, "Retrive Prototype");
		}
	} 
	
	omr->finish();
	
	player->sendMessage(omr);
}

void CraftingToolImplementation::parseItemAttributes() {
	string temp = "tooltype";
	tooltype = itemAttributes->getIntAttribute(temp);
	
	temp = "effectiveness";
	effectiveness = itemAttributes->getFloatAttribute(temp);
	
	temp = "craftersname";
	craftersName = itemAttributes->getStringAttribute(temp);
	
	temp = "craftedserial";
	craftedSerial = itemAttributes->getStringAttribute(temp);
	
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
	
	alm->insertAttribute("craft_tool_effectiveness", effectiveness);
	
	alm->insertAttribute("craft_tool_status", status); 
	
	if(craftersName != ""){ 
		
		alm->insertAttribute("crafter", craftersName);
	}
	if(craftedSerial != ""){
		
		alm->insertAttribute("serial_number", craftedSerial);
	}
	
}

void CraftingToolImplementation::updateCraftingValues(DraftSchematicValues * craftingValues){
	
	string name;
	
	name = "effectiveness";
	effectiveness = craftingValues->getCurrentValue("useModifier");
	itemAttributes->setFloatAttribute(name, effectiveness);
}

void CraftingToolImplementation::sendToolStart(Player* player) {
	
	// Get nearby crafting stations here
	
	experimentingEnabled = true;
	craftingToolModifier = effectiveness + 45;  // 45 is station effectiveness
	
	
	// Craft Start
	// Tano7
	
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(_this);
	player->sendMessage(tano7); 
	
	// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
    dplay9->setExperimentationPoints(0);
	dplay9->setExperimentationEnabled(experimentingEnabled);
	dplay9->setCraftingState(1);
	setCraftingState(1);
	dplay9->close();
	player->sendMessage(dplay9);
	
	// Tool Start
	// Obj Controller Msg
	ObjectControllerMessage* ocm = new ObjectControllerMessage(player->getObjectID(),0x0B, 0x102);
	ocm->insertLong(getObjectID());
	ocm->insertLong(0x00);	
	uint32 draftSchematicListSize = player->getDraftSchematicListSize();
	ocm->insertInt(draftSchematicListSize);
	
	for(int i = 0; i < draftSchematicListSize; i++) {
		DraftSchematic* draftSchematic = player->getDraftSchematic(i);
		ocm->insertInt(draftSchematic->getSchematicID());
		ocm->insertInt(draftSchematic->getSchematicCRC());
		ocm->insertInt(draftSchematic->getCraftingToolTab());		// this number decides what tab the schematic goes in (ex: 4 = food tab in crafting window)
	}
	player->sendMessage(ocm);

	// This is inefficent but for now it works fine
	// Sends all the ingredients and experimental props to the player
	
	for(int i = 0; i < draftSchematicListSize; i++) {
		DraftSchematic* draftSchematic = player->getDraftSchematic(i);
		if(draftSchematic != NULL) {
			draftSchematic->sendIngredientsToPlayer(player);
		}
	}
	
	for(int i = 0; i < draftSchematicListSize; i++) {
		DraftSchematic* draftSchematic = player->getDraftSchematic(i);
		if(draftSchematic != NULL) {
			draftSchematic->sendExperimentalPropertiesToPlayer(player);
		}
	}
	
	player->setCurrentCraftingTool(_this);
}

void CraftingToolImplementation::setWorkingTano(TangibleObject * tano){
	if(currentTano != NULL) {

		currentTano->setContainer(NULL);
		currentTano->finalize();
		currentTano = NULL;
	}

	currentTano = tano;
}

void CraftingToolImplementation::setWorkingDraftSchematic(DraftSchematic * draftSchematic){ 
	
	draftSchematic->lock();
	
	try{
	
		if(currentDraftSchematic != NULL) {
			currentDraftSchematic->setContainer(NULL);
			currentDraftSchematic->finalize();
			currentDraftSchematic = NULL;
		}
		
		// This will be replaced but the built in cloning method when available
		DraftSchematic* clonedDS = draftSchematic->dsClone(draftSchematic);
		currentDraftSchematic = clonedDS;
		
		
		draftSchematic->unlock();
	}
	catch(...){
	
		draftSchematic->unlock();
		
	}
}

void CraftingToolImplementation::clearResourceSlots(){
	
	resourceSlots.removeAll();
	
	for(int i = 0; i < currentDraftSchematic->getIngredientListSize(); i++){
		resourceSlots.add("NULL");
	}
	
	resourceSlotsCount.removeAll();
	
	for(int i = 0; i < currentDraftSchematic->getIngredientListSize(); i++){
		resourceSlotsCount.add(0);
		
	}
	
	resourceSlotsID.removeAll();
	
	for(int i = 0; i < currentDraftSchematic->getIngredientListSize(); i++){
		resourceSlotsID.add(0);
	}
}

Container * CraftingToolImplementation::getHopper(Player * player){
	if(hopper == NULL){
		Container * hop = new Container(player->getNewItemID());
	}
	return hopper;
}

void CraftingToolImplementation::retriveHopperItem(Player * player){
	
	ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();
	Inventory* inventory = player->getInventory();
	
	if(hopper != NULL){
		if(hopper->objectsSize() > 0 && inventory->getObjectCount() < 80){
			
			TangibleObject * tano = (TangibleObject*) hopper->getObject(0);
			hopper->removeObject(0);
			player->addInventoryItem(tano);
			
			itemManager->savePlayerItem(player, tano);
			
			unicode mess = unicode("Hopper item Retrieved");
			ChatSystemMessage* sysMessage = new ChatSystemMessage(mess);
			player->sendMessage(sysMessage);
			
			tano->sendTo(player);
			
			_this->setStatusReady();
		}
	}
}
void CraftingToolImplementation::cleanUp(Player * player) {

	CraftingManager * cm = player->getZone()->getZoneServer()->getCraftingManager();
	string name;
	int quantity;
	
	if(recoverResources){
		for(int i = 0; i < resourceSlots.size(); ++i){
			name = resourceSlots.get(i);
			quantity = resourceSlotsCount.get(i);
			if(quantity != 0){
				cm->putResourceBackInInventory(player, name, quantity);
			}
		}
	}
	
	if(currentDraftSchematic != NULL) {
		
		//Scene Object Destroy
		SceneObjectDestroyMessage* destroy = new SceneObjectDestroyMessage(currentDraftSchematic->getObjectID());
		player->sendMessage(destroy);

		currentDraftSchematic->setContainer(NULL);
		currentDraftSchematic->finalize();
		currentDraftSchematic = NULL;
	}
	
	if(currentTano != NULL) {
		if(status == "@crafting:tool_status_ready"){

			SceneObjectDestroyMessage* destroy = new SceneObjectDestroyMessage(currentTano->getObjectID());
			player->sendMessage(destroy);

			currentTano->setContainer(NULL);  
			currentTano->finalize();
			
		}
		currentTano = NULL;
	}
	
	uint64 resID;
	TangibleObject * tano;
	
	for(int i = 0; i < partialResources.size(); ++i){
		
		resID = partialResources.get(i);
		
		tano = (TangibleObject*)player->getZone()->lookupObject(resID);
		
		if(tano != NULL){
			
			SceneObjectDestroyMessage* destroy = new SceneObjectDestroyMessage(resID);
			player->sendMessage(destroy);
			
			tano->setContainer(NULL);
			tano->finalize();
			
			
		}
		
		tano = NULL;
		
	}
	
	resourceSlots.removeAll();
	resourceSlotsID.removeAll();
	resourceSlotsCount.removeAll();
	partialResources.removeAll();
}
