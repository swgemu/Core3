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
#include "CraftingManagerImplementation.h"

#include "events/CreateObjectEvent.h"
#include "events/UpdateToolCountdownEvent.h"

CraftingManagerImplementation* CraftingManagerImplementation::instance = NULL;

CraftingManagerImplementation::CraftingManagerImplementation(ZoneServer* serv,
		ZoneProcessServerImplementation* proc) :
	CraftingManagerServant(), Mutex("CraftingManagerMutex") {

	server = serv;
	processor = proc;

	setLoggingName("CraftingManager");

	setLogging(true);
	setGlobalLogging(true);

	init();
}

CraftingManagerImplementation::~CraftingManagerImplementation() {
	for (int i = 0; i < draftSchematicsMap.size(); ++i)
		draftSchematicsMap.get(i)->finalize();

	draftSchematicsMap.removeAll();
}

void CraftingManagerImplementation::init() {
	// Scripting
	Lua::init();
	registerFunctions();
	instance = this;
	loadDraftSchematicFile();
}

// Crafting Methods
void CraftingManagerImplementation::prepareCraftingSession(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Clones the global Draft Schematic for use locally within the crafting tool
	craftingTool->setWorkingDraftSchematic(draftSchematic);

	// Set draftSchematic to the new cloned schematic
	draftSchematic = craftingTool->getWorkingDraftSchematic();

	// Send the appropriate DraftSchematic to Player
	createDraftSchematic(player, craftingTool, draftSchematic);

	// Creates the Appropriate TangibleObject and sends to player
	createTangibleObject(player, craftingTool, draftSchematic);

	// Object Message to send necissart ingredients to player
	setupIngredients(player, craftingTool, draftSchematic);

	// If the crafting session is closed, this will recover the resources
	craftingTool->setRecoverResources(true);

}

void CraftingManagerImplementation::createDraftSchematic(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Give the newly clones draft schematic a unique ID
	draftSchematic->setObjectID(player->getNewItemID());

	// Link the DraftSchematic to the Crafting Tool
	draftSchematic->setContainer(craftingTool);

	// Send the Baselines to the player
	draftSchematic->sendTo(player);

	// Setup crafting slots
	craftingTool->initializeCraftingSlots(draftSchematic->getIngredientListSize());

}

void CraftingManagerImplementation::createTangibleObject(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Generates the tangible for crafting
	TangibleObject* tano = generateTangibleObject(player, draftSchematic);

	// Link TangibleObject to the CraftingTool
	tano->setContainer(craftingTool);

	// Send TangibleObject baselines to player
	tano->sendTo(player, true);

	// Dplay9 ********************************************************
	// Sets the Crafting state to 2, which is the Resource screen
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setExperimentationPoints(0xFFFFFFFF);
	dplay9->setCraftingState(2);
	craftingTool->setCraftingState(2);
	dplay9->close();

	player->sendMessage(dplay9);
	// End Dplay9 *****************************************************


	// Dtano3 ********************************************************
	// Update Condition Damage
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(tano);
	dtano3->updateConditionDamage();
	dtano3->close();

	player->sendMessage(dtano3);
	// End Dtano3 *****************************************************


	// Set the created tano to current tano in the crafting tool
	craftingTool->setWorkingTano(tano);

	//Add to object Map
	player->getZone()->getZoneServer()->addObject(tano, true);

	// Start the insert count so inserts and removals work
	craftingTool->setInsertCount(1);

	// Clear the tools slots in case anything lingers in the vectors
	craftingTool->resetSlots();

}

void CraftingManagerImplementation::setupIngredients(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0103);
	objMsg->insertLong(craftingTool->getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(draftSchematic->getObjectID()); // Draft Schematic Object ID
	objMsg->insertLong(craftingTool->getWorkingTano()->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(3);
	objMsg->insertByte(1);

	// Sends requested ingredients to the player
	draftSchematic->helperSendIngredientsToPlayer(objMsg);

	player->sendMessage(objMsg);
	// End Object Controller w/ Ingredients ************************


	// MSCO7 ******************************************************* Verified
	ManufactureSchematicObjectMessage7* msco7 =
			new ManufactureSchematicObjectMessage7(draftSchematic->getObjectID(), draftSchematic);

	player->sendMessage(msco7);
	// End MSCO7 ***************************************************

}



// Methods to Add items to the crafting process
void CraftingManagerImplementation::addIngredientToSlot(Player* player,
		TangibleObject* tano, int slot, int counter) {

	TangibleObject* newTano;

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL){

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();

	if (draftSchematic == NULL){

		sendSlotMessage(player, counter, SLOTNOSCHEMATIC);
		return;

	}

	DraftSchematicIngredient* dsi = draftSchematic->getIngredient(slot);

	if (dsi == NULL)
		return;

	try {

		// Lock appropriate objects
		craftingTool->wlock();
		draftSchematic->wlock();

		// Get the resouce requirements for the chosen slot
		int quantity = dsi->getResourceQuantity();

		// Get what, if anything, is in the affected slot

		TangibleObject* ingredientInSlot = craftingTool->getIngredientInSlot(slot);

		// Send slot messages base on contenst if needed
		if(ingredientInSlot != NULL) {

			if(slotIsFull(player, craftingTool, tano, ingredientInSlot, slot, quantity, counter)) {

				craftingTool->unlock();
				draftSchematic->unlock();

				return;
			}
		}

		// Set resource values appropriately
		newTano = transferIngredientToSlot(player, tano, craftingTool, quantity);

		if(newTano == NULL){

			sendSlotMessage(player, counter, SLOTBADCRATE);

			craftingTool->unlock();
			draftSchematic->unlock();

			return;
		}
		// DMSCO6 ***************************************************
		// Prepares the slot for insert
		ManufactureSchematicObjectDeltaMessage6* dMsco6 =
		new ManufactureSchematicObjectDeltaMessage6(draftSchematic->getObjectID());
		dMsco6->insertToResourceSlot(craftingTool->getInsertCount());
		dMsco6->close();

		player->sendMessage(dMsco6);
		// End DMSCO6 ********************************************F*******

		// DMSCO7 ***************************************************
		// Updates the slot
		ManufactureSchematicObjectDeltaMessage7* dMsco7 =
		new ManufactureSchematicObjectDeltaMessage7(draftSchematic->getObjectID());

		if (craftingTool->getInsertCount() == 1) {

			// If it's the first resource inserted, we need to fully update all the slots
			dMsco7->fullUpdate(draftSchematic, draftSchematic->getIngredientListSize(), slot,
					newTano->getObjectID(), quantity);
		} else {

			// If it's not the first resources, slots are updates, and only insert needs done
			dMsco7->partialUpdate(slot, draftSchematic->getIngredientListSize()
					+ craftingTool->getInsertCount(), newTano->getObjectID(), quantity);
		}
		dMsco7->close();

		player->sendMessage(dMsco7);
		// End DMSCO7 ***************************************************

		sendSlotMessage(player, counter, SLOTOK);

		// Increment the insert counter
		craftingTool->increaseInsertCount();

		// Add the resource to the "slots" in the crafting tool for tracking
		craftingTool->addIngredientToSlot(slot, newTano);

		draftSchematic->unlock();
		craftingTool->unlock();


	} catch(...) {
		draftSchematic->unlock();
		craftingTool->unlock();

		cout << "Unreported exception caught in CraftingManagerImplementation::addResourceToCraft\n";
	}

}
bool CraftingManagerImplementation::slotIsFull(Player* player,
		CraftingTool* craftingTool, TangibleObject* tano,
		TangibleObject* ingredientInSlot, int slot, int quantity, int counter) {

	if (tano->isResource()) {

		ResourceContainer* rcno = (ResourceContainer*)tano;
		ResourceContainer* rcnoinSlot = (ResourceContainer*)ingredientInSlot;

		if(rcnoinSlot == NULL)
			return true;

		try {

			rcno->wlock();
			rcnoinSlot->wlock();

			if (rcnoinSlot->getContents() != 0) {

				if (quantity == rcnoinSlot->getContents()) {

					// If slot is full send slot is full message
					sendSlotMessage(player, counter, SLOTFULL);

					rcno->unlock();
					rcnoinSlot->unlock();

					return true;

				}

				// If the is a partial resource in the slot, add it back to inventory
				// So that resource amounts are correct
				if (!rcnoinSlot->compare(rcno)) {

					// If Resource isn't the same, throw slot error
					sendSlotMessage(player, counter, SLOTINVALIDINGREDIENT);

					rcno->unlock();
					rcnoinSlot->unlock();

					return true;

				} else {

					// If resource is the same add resource to incoming stack
					rcno->setContents(rcno->getContents() + rcnoinSlot->getContents());

				}
			}

			rcno->unlock();
			rcnoinSlot->unlock();
		}
		catch(...) {

			rcno->unlock();
			rcnoinSlot->unlock();

		}

	} else {

		// deal with partial components in slot


	}

	return false;
}

void CraftingManagerImplementation::sendSlotMessage(Player* player, int counter, short message){

	// Object Controller ********************************************
	// Send Bad Slot message
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x107);
	objMsg->insertInt(message);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);
	//End Object Controller ******************************************
}

TangibleObject* CraftingManagerImplementation::transferIngredientToSlot(Player* player, TangibleObject* tano,
		CraftingTool* craftingTool, int& quantity) {


	if(tano->isResource()){

		ResourceContainer* rcno = (ResourceContainer*)tano;
		return transferResourceToSlot(player, rcno, craftingTool, quantity);

	} else if (tano->isComponent()){

		Component* component = (Component*)tano;
		return transferComponentToSlot(player, component, craftingTool, quantity);

	} else {

		cout << "I'm not a resource or a component, WTF am I = " << tano->getObjectSubType() << "\n";
		return NULL;
	}
}

TangibleObject* CraftingManagerImplementation::transferResourceToSlot(
		Player* player, ResourceContainer* rcno, CraftingTool* craftingTool,
		int& quantity) {

	string name = rcno->getResourceName();

	if (rcno->getContents() < quantity) {

		// If there are less resources in the stack
		// then required, only use what is left
		quantity = rcno->getContents();

	}

	if (rcno->getContents() - quantity < 1) {

		// If Stack is empty, remove it from inventory
		player->removeInventoryItem(rcno->getObjectID());

		// Destroy Container
		rcno->sendDestroyTo(player);
		rcno->finalize();

	} else {

		try {
			rcno->wlock();

			// Remove proper amount of resource from chosen Container
			int newContents = rcno->getContents() - quantity;
			rcno->setContents(newContents);

			// Update the ResourceContainer
			rcno->sendDeltas(player);

			// Flag ResourceContainer for saving changes
			rcno->setUpdated(true);

			rcno->unlock();
		}
		catch(...)
		{
			cout << "Error changing contents\n";
			rcno->unlock();
		}
	}

	// Here we are cloning the resource stack to prevent any operations
	// From scene destroying the stack in the slot, as it would render the
	// slot useless

	// Make a new resource stack of "name" with "quantity" units

	ResourceContainer* newRcno = makeNewResourceStack(player, name, quantity);

	if (newRcno == NULL)
		return NULL;

	// Add resource to object map
	player->getZone()->getZoneServer()->addObject(newRcno, true);

	// Sending resource to the player, but NOT to inventory
	newRcno->sendTo(player);

	newRcno->setPersistent(false);

	//Send attributes to update crafting window (Or quality bars don't show up
	newRcno->generateAttributes(player);

	// Adding the ObjectID to a vector for proper clean up when the tool is closed
	// Because otherwise the resource stack is lost in memory
	TangibleObject* tano = (TangibleObject*)newRcno;

	craftingTool->addTempIngredient(tano);

	return tano;
}

TangibleObject* CraftingManagerImplementation::transferComponentToSlot(
		Player* player, Component* component, CraftingTool* craftingTool,
		int& quantity) {

	int objectCount = component->getObjectCount();

	Component* 	newComponent = cloneComponent(player, component);

	if(objectCount == 0)
		objectCount = 1;

	if (objectCount - quantity < 1) {

		// If Stack is empty, remove it from inventory
		player->removeInventoryItem(component->getObjectID());

		// Destroy Old stack
		component->sendDestroyTo(player);

		component->finalize();


	} else {

		try {
			component->wlock();

			// Remove proper amount of item from chosen stack
			component->setObjectCount(objectCount - quantity);

			// Update the Tano
			component->sendDeltas(player);

			// Flag Tano for saving changes
			component->setUpdated(true);

			component->unlock();

		}
		catch(...)
		{
			cout << "Error changing contents\n";
			component->unlock();
		}
	}

	newComponent->setObjectCount(quantity);

	// Here we are cloning the resource stack to prevent any operations
	// From scene destroying the stack in the slot, as it would render the
	// slot useless

	//if (newComponent == NULL)
		//return NULL;

	// Add resource to object map
	player->getZone()->getZoneServer()->addObject(newComponent, true);

	// Sending resource to the player, but NOT to inventory
	newComponent->sendTo(player);

	newComponent->setPersistent(false);

	//Send attributes to update crafting window (Or quality bars don't show up
	newComponent->generateAttributes(player);

	TangibleObject* tano = (TangibleObject*)newComponent;

	// Adding the ObjectID to a vector for proper clean up when the tool is closed
	// Because otherwise the resource stack is lost in memory
	craftingTool->addTempIngredient(tano);

	return tano;

}

void CraftingManagerImplementation::removeResourceFromCraft(Player* player,
		int slot, int counter) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL) {

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();

	if (draftSchematic == NULL) {

		sendSlotMessage(player, counter, SLOTNOSCHEMATIC);
		return;

	}

	try {

		craftingTool->wlock();
		draftSchematic->wlock();

		string name;

		// Use the crafting tool to amount of resources in the slot
		TangibleObject* tano = craftingTool->getIngredientInSlot(slot);

		if (tano == NULL) {
			draftSchematic->unlock();
			craftingTool->unlock();

			return; // TODO: send some error message
		}

		// Pretty easy to understand this
		if(tano->isResource()){

			ResourceContainer* rcno = (ResourceContainer*)tano;
			player->addInventoryItem(rcno);

		} else {

			putComponentBackInInventory(player, tano);

		}

		//

		// DMCSO7 ******************************************************
		// Removes resource from client slot
		ManufactureSchematicObjectDeltaMessage7* dMsco7 =
		new ManufactureSchematicObjectDeltaMessage7(draftSchematic->getObjectID());

		dMsco7->removeResource(slot, draftSchematic->getIngredientListSize()
				+ craftingTool->getInsertCount());

		dMsco7->close();

		player->sendMessage(dMsco7);
		// End DMCSO7 ***************************************************


		// Object Controller ********************************************
		// Updates the screen with the resource removal
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x108);
		objMsg->insertInt(0);
		objMsg->insertByte(counter);

		player->sendMessage(objMsg);
		// End Object Controller *****************************************

		tano = NULL;

		// Updates CraftingTool's resource slot
		craftingTool->addIngredientToSlot(slot, tano);

		// Increases Insert Counter
		craftingTool->increaseInsertCount();

		craftingTool->unlock();
		draftSchematic->unlock();
	}
	catch(...) {

		craftingTool->unlock();
		draftSchematic->unlock();

	}
}

ResourceContainer* CraftingManagerImplementation::makeNewResourceStack(
		Player* player, string name, int quantity) {

	// This clones the resource stack to insert into the slot

	ResourceContainer* rco = new ResourceContainer(player->getNewItemID());

	rco->setResourceName(name);

	rco->setContents(quantity);

	player->getZone()->getZoneServer()->getResourceManager()->setResourceData(rco);

	return rco;
}

void CraftingManagerImplementation::putComponentBackInInventory(Player* player, TangibleObject* tano){

	Component* newComponent = cloneComponent(player, tano);

	player->addInventoryItem(newComponent);

	newComponent->sendTo(player);

	newComponent->setPersistent(true);

	tano->setContainer(NULL);

	tano->destroy(player->getClient());

	tano->finalize();

}

Component* CraftingManagerImplementation::cloneComponent(Player* player, TangibleObject* tano){

	if(tano->isComponent()){

		Component* component = (Component*)tano;
		return cloneComponent(player, component);

	}

	return NULL;

}

Component* CraftingManagerImplementation::cloneComponent(Player* player, Component* component){

	Component* newComponent = new Component(player->getNewItemID(), component->getObjectCRC(), component->getName(),
			component->getTemplateName());

	newComponent->setObjectCount(component->getObjectCount());

	player->getZone()->getZoneServer()->addObject(newComponent, true);

	return newComponent;

}

void CraftingManagerImplementation::nextCraftingStage(Player* player,
		string test) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();
	if (craftingTool == NULL)
		return;

	// If the window is closed now, this sets the resources to no be recoverable
	craftingTool->setRecoverResources(false);

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();

	if (draftSchematic == NULL)
		return;

	try {
		craftingTool->wlock();
		draftSchematic->wlock();

		// Clears all the crafting vectors
		//draftSchematic->getCraftingValues()->clearAll();

		// Get counter from packet
		int counter = atoi(test.c_str());

		if (craftingTool->getCraftingState() == 2) {

			// Flag to get the experimenting window
			if (craftingTool->isExperimenting()) {

				// Calculate exp failure for red bars
				float failure = calculateExperimentationFailureRate(player, craftingTool, draftSchematic, 0);
				draftSchematic->setExpFailure(failure);

				// Assemble with Experimenting
				initialAssembly(player, craftingTool, draftSchematic, counter, 3);

			} else {

				// Assemble without Experimenting
				initialAssembly(player, craftingTool, draftSchematic, counter, 4);

			}

		} else if (craftingTool->getCraftingState() == 3) {

			finishAssembly(player, craftingTool, draftSchematic, counter);

		} else if (craftingTool->getCraftingState() == 5) {

			finishStage1(player, counter);

		} else if (craftingTool->getCraftingState() == 6) {

			finishStage2(player, counter);
		}

		craftingTool->unlock();
		draftSchematic->unlock();

	}
	catch(...) {

		craftingTool->unlock();
		draftSchematic->unlock();

	}
}

void CraftingManagerImplementation::initialAssembly(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, int counter, int stage) {

	TangibleObject* tano = craftingTool->getWorkingTano();

	if (tano == NULL)
		return;

	// Get the appropriate number of Experimentation points from Skill
	string expskill = draftSchematic->getExperimentingSkill();
	int exppoints = int(player->getSkillMod(expskill) / 10);

	// The Experimenting counter always starts at numbers of exp titles + 1
	draftSchematic->setExpCounter();
	draftSchematic->setExpPoints(exppoints);

	// Start DPLAY9 ***********************************************************
	// Updates the stage of crafting, sets the number of experimentation points
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(stage); // 3 If Experimenting is active, 4 if already experimented/ No experimenting
	dplay9->setExperimentationPoints(exppoints);
	craftingTool->setCraftingState(stage);
	dplay9->close();

	player->sendMessage(dplay9);
	// End DPLAY9 *************************************************************

	// Determine the outcome of the craft, Amazing through Critical
	calculateAssemblySuccess(player, craftingTool, draftSchematic, 0.0f);

	//Set crafting percentages
	setInitialCraftingValues(player, craftingTool, draftSchematic);

	// Update the Tano with new values
	tano->updateCraftingValues(draftSchematic);

	// Set Crafter name and generate serial number
	tano->setCraftersName(player->getFirstName());

	string serial = generateCraftedSerial();
	tano->setCraftedSerial(serial);


	// Start DMSCO3 ***********************************************************
	// Sends the updated values to the crafting screen
	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
	dMsco3->updateCraftedValues(draftSchematic);
	dMsco3->close();

	player->sendMessage(dMsco3);
	// End DMSCO3 *************************************************************


	// Start DMSCO7 ***********************************************************
	// Sends the experimental properties and experimental percentages
	ManufactureSchematicObjectDeltaMessage7* dMsco7 =
			new ManufactureSchematicObjectDeltaMessage7(draftSchematic->getObjectID());
	dMsco7->updateForAssembly(draftSchematic);
	dMsco7->close();

	player->sendMessage(dMsco7);
	// End DMSCO7 *************************************************************


	// Start DTANO3 ***********************************************************
	// Updates the Complexity and the condition
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(tano);
	dtano3->updateComplexity(float(draftSchematic->getComplexity()));
	dtano3->updateMaxCondition();
	dtano3->close();

	player->sendMessage(dtano3);
	// End DTANO3 *************************************************************


	// Start Object Controller *******************************************
	// Send the results
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
	objMsg->insertInt(0x109);

	objMsg->insertInt(craftingTool->getAssemblyResults()); // Assembly Results
	// 0 = Amazing
	// 1 = Great
	// 2 = Good
	// 3 = Moderate
	// 4 = A succees
	// 5 = Marginally Successful
	// 6 = "ok"
	// 7 = Barely Succeeded
	// 8 = Critical Failure

	objMsg->insertByte(counter);

	player->sendMessage(objMsg);
	// End Object Controller ******************************************


	// Remove all resources - Not recovering them
	if (craftingTool->getAssemblyResults() == 8) {

		// re-setup the slots and ingredients
		setupIngredients(player, craftingTool, draftSchematic);

		// Start Dplay9 **************************************
		// Reset crafting state
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->setCraftingState(2);
		craftingTool->setCraftingState(2);
		dplay9->close();

		player->sendMessage(dplay9);
		// End DPLAY9 ****************************************

		// Reset inserts
		craftingTool->setInsertCount(1);
		craftingTool->resetSlots();
	}

}
void CraftingManagerImplementation::setInitialCraftingValues(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic){

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	string itemName, subtitle;

	float value, maxPercentage, currentPercentage, weightedSum;
	DraftSchematicExpPropGroup* dsepg;

	// These 2 values are pretty standard, adding these
	itemName = "xp";
	value = float(draftSchematic->getXp());
	craftingValues->setCurrentValue(itemName, value);

	itemName = "complexity";
	value = draftSchematic->getComplexity();
	craftingValues->setCurrentValue(itemName, value);

	int subtitleCounter = 0;

	float modifier = calculateAssemblyValueModifier(craftingTool);

	for(int i = 0; i < draftSchematic->getExpPropGroupListSize(); ++i){

		// Grab the first weight group
		dsepg = draftSchematic->getExpPropGroup(i);

		weightedSum = 0;

		for(int ii = 0; ii < dsepg->getExpPropPercentageListSize(); ++ii){

			// Based on the script we cycle through each exp group

			// Get the type from the type/weight
			int type = (dsepg->getTypeAndWeight(ii) >> 4);

			// Get the calculation percentage
			float resPercentage = dsepg->getExpPropPercentage(ii);

			// add to the weighted sum based on type and percentage
			weightedSum += getWeightedValue(player, craftingTool, draftSchematic, type) * resPercentage;

		}

		// > 0 ensures that we don't add things when there is NaN value
		if(weightedSum > 0){

			// Getting the title ex: minDamage
			subtitle = craftingValues->getExperimentalPropertySubtitle(subtitleCounter);

			// This is the formula for max experimenting percentages
			maxPercentage = ((weightedSum / 10.0f) * .01f);

			// Based on the weighted sum, we can get the initial %
			currentPercentage = (getAssemblyPercentage(weightedSum)) * modifier;

			craftingValues->setMaxPercentage(subtitle, maxPercentage);
			craftingValues->setCurrentPercentage(subtitle, currentPercentage);

			subtitleCounter++;
		}

	}

	craftingValues->recalculateValues(draftSchematic);

}

void CraftingManagerImplementation::finishAssembly(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, int counter) {

	// Start Dplay9 **************************************
	// Move crafting to State 4
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(4);
	craftingTool->setCraftingState(4);
	dplay9->close();

	player->sendMessage(dplay9);
	// End DPLAY9

	// Start Object Controller **************************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);
	// End Object Controller **************************************

}

void CraftingManagerImplementation::handleExperimenting(Player* player,
		int counter, int numRowsAttempted, string expstring) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL) {

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();

	if (draftSchematic == NULL) {

		sendSlotMessage(player, counter, SLOTNOSCHEMATIC);
		return;

	}

	TangibleObject* tano = craftingTool->getWorkingTano();

	if (tano == NULL)
		return;

	try {

		draftSchematic->wlock();
		craftingTool->wlock();
		tano->wlock();

		StringTokenizer tokenizer(expstring);

		int rowEffected, pointsAttempted, totalPoints;
		int lowestExpSuccess = 0;

		totalPoints = 0;

		float failure;

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

		craftingValues->clear();

		// Loop through all the lines of experimentation
		for (int i = 0; i < numRowsAttempted; ++i) {

			// Each line gets it's own rolls
			// Calcualte a new failure rate for each line of experimentation
			failure = calculateExperimentationFailureRate(player, craftingTool, draftSchematic, pointsAttempted);

			// Set the experimentation result ie:  Amazing Success
			calculateExperimentationSuccess(player, craftingTool, draftSchematic, failure);

			// Make sure to store the lowest roll to display (Effect the multiline rolls
			if(lowestExpSuccess < craftingTool->getAssemblyResults())
			lowestExpSuccess = craftingTool->getAssemblyResults();

			draftSchematic->increaseExpCounter();

			rowEffected = tokenizer.getIntToken();
			pointsAttempted = tokenizer.getIntToken();

			totalPoints += pointsAttempted;

			draftSchematic->increaseComplexity();

			// Do the experimenting - sets new percentages
			experimentRow(draftSchematic->getCraftingValues(), rowEffected, pointsAttempted, failure, craftingTool->getAssemblyResults());

		}

		// Use percentages to recalculate the values
		craftingValues->recalculateValues(draftSchematic);

		// Update the Tano with new values
		tano->updateCraftingValues(draftSchematic);

		// Sets the result for display
		craftingTool->setAssemblyResults(lowestExpSuccess);

		// Get exp points left
		int expPoints = draftSchematic->getExpPoints();

		// Set new exp points subtracting those used above
		draftSchematic->setExpPoints(expPoints - totalPoints);


		// Start Player Object Delta **************************************
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->setExperimentationPoints(draftSchematic->getExpPoints());
		dplay9->close();

		player->sendMessage(dplay9);
		// End Player Object Delta **************************************


		ManufactureSchematicObjectDeltaMessage3* dMsco3 =
		new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
		dMsco3->updateComplexity(draftSchematic->getComplexity());
		dMsco3->updateCraftedValues(draftSchematic);
		dMsco3->close();

		player->sendMessage(dMsco3);

		ManufactureSchematicObjectDeltaMessage7* dMsco7 =
		new ManufactureSchematicObjectDeltaMessage7(draftSchematic->getObjectID());

		dMsco7->update9(draftSchematic);
		dMsco7->close();

		player->sendMessage(dMsco7);

		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(craftingTool->getWorkingTano());
		dtano3->updateComplexity(float(draftSchematic->getComplexity()));

		dtano3->close();

		player->sendMessage(dtano3);

		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0113);
		objMsg->insertInt(0x105);

		objMsg->insertInt(craftingTool->getAssemblyResults()); // Experimentation Result
		// 0 = Amazing
		// 1 = Great
		// 2 = Good
		// 3 = Moderate
		// 4 = A succees
		// 5 = Marginally Successful
		// 6 = "ok"
		// 7 = Barely Succeeded
		// 8 = Critical Failure
		objMsg->insertByte(counter);

		player->sendMessage(objMsg);

		craftingTool->unlock();
		draftSchematic->unlock();
		tano->unlock();

	}
	catch(...) {

		craftingTool->unlock();
		draftSchematic->unlock();
		tano->unlock();

	}
}

void CraftingManagerImplementation::experimentRow(DraftSchematicValues* craftingValues,
		int rowEffected, int pointsAttempted, float failure, int assemblyResult){

	float modifier, newValue;

	string title, subtitle, subtitleClass;

	title = craftingValues->getExperimentalPropertyTitle(rowEffected);

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {

		subtitleClass = craftingValues->getExperimentalPropertySubtitleClass(i);

		if (subtitleClass == title) {

			subtitle = craftingValues->getExperimentalPropertySubtitle(i);

			modifier = calculateExperimentationValueModifier(assemblyResult,
					pointsAttempted, failure);

			newValue = craftingValues->getCurrentPercentage(subtitle)
					+ modifier;

			craftingValues->setCurrentPercentage(subtitle, newValue);
		}
	}

}

void CraftingManagerImplementation::createPrototype(Player* player, string count) {

	CraftingTool* craftingTool;
	DraftSchematic* draftSchematic;

	StringTokenizer tokenizer(count);
	int counter = tokenizer.getIntToken();
	int practice = tokenizer.getIntToken();

	try {

		craftingTool = player->getCurrentCraftingTool();

		if (craftingTool == NULL) {

			sendSlotMessage(player, counter, SLOTNOTOOL);
			return;

		}

		draftSchematic = craftingTool->getWorkingDraftSchematic();

		if (draftSchematic == NULL) {

			sendSlotMessage(player, counter, SLOTNOSCHEMATIC);
			return;

		}

		if (!draftSchematic->isFinished()) {

			//Object Controller - Closes Window
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

			string xpType = draftSchematic->getXpType();
			int xp = draftSchematic->getXp();

			if (practice != 0) {

				createObjectInInventory(player, draftSchematic->getComplexity() * 2, true);

			}
			else {

				createObjectInInventory(player, draftSchematic->getComplexity() * 2, false);
				xp = int(round(1.05 * xp));

			}

			player->addXp(xpType, xp, true);
			draftSchematic->setFinished();
		}


	} catch(...) {


	}
}

void CraftingManagerImplementation::createSchematic(Player* player,
		string count) {

	StringTokenizer tokenizer(count);

	int counter = tokenizer.getIntToken();

	// Add Schematic to datapad here
}
void CraftingManagerImplementation::craftingCustomization(Player* player,
		string name, int condition) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL)
		return;

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();
	TangibleObject* tano = craftingTool->getWorkingTano();

	if (draftSchematic == NULL || tano == NULL)
		return;

	MySqlDatabase::escapeString(name);

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(tano);
	dtano3->updateName(name);

	tano->setName(name);

	dtano3->close();

	player->sendMessage(dtano3);

	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
	dMsco3->updateName(name);
	dMsco3->updateCondition(condition);
	dMsco3->close();

	player->sendMessage(dMsco3);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x15A);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);

	craftingTool->setCraftingState(5);

}
void CraftingManagerImplementation::finishStage1(Player* player, int counter) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL){

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(5);
	dplay9->close();

	player->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);

	craftingTool->setCraftingState(6);
}

void CraftingManagerImplementation::finishStage2(Player* player, int counter) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL){

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->insertShort(5);
	dplay9->insertInt(0xFFFFFFFF);
	dplay9->setCraftingState(0);
	craftingTool->setCraftingState(0);
	dplay9->close();
	player->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(1);
	objMsg->insertByte(counter); //?!?!
	player->sendMessage(objMsg);

}

void CraftingManagerImplementation::createObjectInInventory(Player* player,
		int timer, bool create) {
	int timer2 = 0;
	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	CreateObjectEvent* createObjectEvent;
	UpdateToolCountdownEvent* updateToolCountdownEvent;

	createObjectEvent = new CreateObjectEvent(player, craftingTool, create);
	craftingTool->setStatusWorking();

	if (processor != NULL) {

		while (timer > 0) {
			updateToolCountdownEvent = new UpdateToolCountdownEvent(player, craftingTool, timer);
			processor->addEvent(updateToolCountdownEvent, timer2);
			timer-=5;
			timer2+=5000;
		}

		if (timer < 0) {
			timer2 += timer * 1000;
			timer = 0;
		}

		updateToolCountdownEvent = new UpdateToolCountdownEvent(player, craftingTool, timer);

		processor->addEvent(updateToolCountdownEvent, timer2);
		processor->addEvent(createObjectEvent, timer2);
	} else {
		cout << "Serv == NULL\n";
	}
}

TangibleObject* CraftingManagerImplementation::generateTangibleObject(Player* player, DraftSchematic* draftSchematic) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	TangibleObject* tano= NULL;

	string attributes = draftSchematic->getTanoAttributes();

	ItemAttributes* itemAttributes = new ItemAttributes();
	itemAttributes->setAttributes(attributes);

	uint64 objectid = player->getNewItemID();

	string temp = "objecttype";
	int objecttype = itemAttributes->getIntAttribute(temp);

	temp = "objectcrc";
	uint32 objectcrc = itemAttributes->getUnsignedLongAttribute(temp);

	string objectname = draftSchematic->getName();

	temp = "objecttemp";
	string objecttemp = itemAttributes->getStringAttribute(temp);

	//(objectid, objectcrc, objectname, objecttemp, false);
	// Set these defaults in case
	/*string appearance = result->getString(10);
	 BinaryData cust(appearance);
	 string custStr;
	 cust.decode(custStr);*/

	TangibleObject* item = NULL;

	bool equipped = false;

	tano = itemManager->initializeTangibleForCrafting(objecttype, objectid,
			objectcrc, objectname, objecttemp, equipped);

	if (tano == NULL) {

		TangibleObject* tano = new TangibleObject(objectid, objectname, objecttemp, objectcrc);

	}

	//item->setAttributes(attributes);
	//item->parseItemAttributes();

	//item->setCustomizationString(custStr);
	return tano;
}

void CraftingManagerImplementation::calculateAssemblySuccess(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, float modifier) {

	// Skill + Luck roll and crafting tool effectiveness determine the
	// Success of the crafting result

	int preresult, result;

	string assemblySkill = draftSchematic->getAssemblySkill();

	// Get assembly points from skill
	float assemblyPoints = float(player->getSkillMod(assemblySkill) / 10);

	// Get modifier from tool to modify success
	float toolModifier = calculateAssemblyModifier(craftingTool);

	// Gets failure rate * 100 .25 = 25, so decimals matter in the roll
	int failureRate = calculateAssemblyFailureRate(player, craftingTool, assemblyPoints)
			+ int(modifier * 100);

	int luck = System::random(100);


	if (failureRate > luck * 10) {

		result = 8;

	} else if (luck >= 95 - int(10.0f * ((toolModifier + .15f) - 1.0f))){

		result = 0;

	} else {

		preresult = int(toolModifier *((assemblyPoints * 10) + luck));


		if (preresult > 130) {

			result = 1;

		} else if (preresult > 90) {

			result = 2;

		} else if (preresult > 70) {

			result = 3;

		} else if (preresult > 60) {

			result = 4;

		} else if (preresult > 50) {

			result = 5;

		} else if (preresult > 35) {

			result = 6;

		} else {

			result = 7;

		}

	}

	craftingTool->setAssemblyResults(result);
}

void CraftingManagerImplementation::calculateExperimentationSuccess(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, float failure) {


		// Skill + Luck roll and crafting station effectiveness determine the
		// Success of the crafting result

		int result, preresult;

		// Get modifier from tool to modify success
		float stationModifier = .80;//calculateExperimentationModifier(craftingTool);
		string expSkill = draftSchematic->getExperimentingSkill();

		// Get experiemtnation points from skill
		int expPoints = player->getSkillMod(expSkill);

		// Gets failure rate * 100 .25 = 25, so decimals matter in the roll
		int failureRate = int(failure * 100);

		int luck = System::random(100);

		if (failureRate > luck * 10) {

			result = 8;

		} else if (luck >= 99 - int(9.0f * stationModifier)){

			result = 0;

		} else {

			if(stationModifier < .8f)
				stationModifier = .8f;

			preresult = int(stationModifier *(expPoints + luck));

//cout << "PRERESULT = " << preresult << "  expPoints = " << expPoints << "   luck = " << luck << endl;


			if (preresult > 90) {

				result = 1;

			} else if (preresult > 80) {

				result = 2;

			} else if (preresult > 70) {

				result = 3;

			} else if (preresult > 50) {

				result = 4;

			} else if (preresult > 20) {

				result = 5;

			} else { //if (preresult > 40) {

				result = 6;

			} //else {

				//result = 7;

			//}

		}
		craftingTool->setAssemblyResults(result);
}

float CraftingManagerImplementation::calculateExperimentationFailureRate(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, int pointsUsed) {

	// Skill + Luck roll and crafting tool effectiveness determine the
	// Success of the crafting result

	// Get the Weighted value of MA
	float ma = getWeightedValue(player, craftingTool, draftSchematic, 4);

	// Get Experimentation skill
	string expSkill = draftSchematic->getExperimentingSkill();
	float expPoints = player->getSkillMod(expSkill);

	float failure = (50.0f + (ma - 500.0f)/40.0f + expPoints - 5.0f * pointsUsed) / 100.0f;

	// Return 0 if > 1.0 and return 1.0 - failure if < 1.0
	if (failure > 1)
		return 0;
	else
		return (1.0f - failure);
}

int CraftingManagerImplementation::calculateAssemblyFailureRate(Player* player, CraftingTool* craftingTool, float assemblyPoints) {

	// Here we take the standard failure rate(From the equation below), and add a rate from 0-15% based on the
	// Negative value of the crafting tool.  Positive values have no effect

	float effectiveness = 1.0f + (craftingTool->getToolEffectiveness() / 100);

	if(effectiveness > 0)
		effectiveness = 0;


	int failureRate = int(round(((( 2.68 / getLog(assemblyPoints+5.2) ) -.89 ) * 100) + effectiveness));

	if(failureRate < 0)
		failureRate = 0;

	return failureRate;

}

float CraftingManagerImplementation::calculateAssemblyModifier(CraftingTool* craftingTool) {

	// Using the tools effectiveness, we return a modifier
	float effectiveness = 1.0f + (craftingTool->getToolEffectiveness() / 100);

	return effectiveness;

}

float CraftingManagerImplementation::calculateAssemblyValueModifier(CraftingTool* craftingTool) {

	int assembly = craftingTool->getAssemblyResults();

	float results = (( 3.4 / getLog(assembly + 4) ) -1.1111 );

	// Unles we want amazing assemblies to get a bonus, we cap the madifier at 1

	if (results > 1.00) {

		if(results < 1.05){

			results = 1.0f;

		} else {

			results = 1.2f;

		}

	}

	return results;

}

float CraftingManagerImplementation::getLog(float value){

	return (log10(value) / log10(CONSTE));

}

float CraftingManagerImplementation::calculateExperimentationValueModifier(int assemblyResult, int pointsAttempted,
		float failure) {

	// Make it so failure detract

	float results;

	switch(assemblyResult){

	case 0:
		results = 0.08f;
		break;
	case 1:
		results = 0.07f;
		break;
	case 2:
		results = 0.055f;
		break;
	case 3:
		results = 0.015f;
		break;
	case 4:
		results = 0.01f;
		break;
	case 5:
		results = 0.00f;
		break;
	case 6:
		results = -0.04f;
		break;
	case 7:
		results = -0.07f;
		break;
	case 8:
		results = -0.08f;
		break;
	default:
		results = 0;
		break;
	}

	results *= pointsAttempted;


	return results;

}

float CraftingManagerImplementation::getWeightedValue(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, int type) {

	int stat = 0;
	int n = 0;
	int nsum = 0;
	float weightedAverage = 0;

	for (int i = 0; i < draftSchematic->getIngredientListSize(); ++i) {

		n = draftSchematic->getIngredient(i)->getResourceQuantity();
		stat = lookUpResourceAttribute(player, craftingTool, type, i);

		if (stat != 0) {

			nsum += n;
			weightedAverage += (stat * n);

		}

	}

	weightedAverage /= float(nsum);

	return weightedAverage;
}

float CraftingManagerImplementation::getAssemblyPercentage(float value) {

	float percentage = (value * (0.000015 * value + .015))  * 0.01f;

	return percentage;
}

int CraftingManagerImplementation::lookUpResourceAttribute(Player* player,
		CraftingTool* craftingTool, int type, int slot) {

	TangibleObject* tano = craftingTool->getIngredientInSlot(slot);

	if (tano == NULL)
		return 0;

	if(!tano->isResource())
		return 0;

	ResourceContainer* rcno = (ResourceContainer*)tano;

	int tempValue = 0;

	/*
	 * 0 Potency
	1 CR
	2 CD
	3 DR
	4 HR
	5 FL
	6 MA
	7 PE
	8 OQ
	9 SR
	A UT
	B Bulk
	*/

	switch (type) {
	case 1: // CR
		tempValue = rcno->getColdResistance();
		break;
	case 2: // CD
		tempValue = rcno->getConductivity();
		break;
	case 3: // DR
		tempValue = rcno->getDecayResistance();
		break;
	case 4: // HR
		tempValue = rcno->getHeatResistance();
		break;
	case 5: // FL
		tempValue = rcno->getFlavor();
		break;
	case 6: // MA
		tempValue = rcno->getMalleability();
		break;
	case 7: // PE
		tempValue = rcno->getPotentialEnergy();
		break;
	case 8: // OQ
		tempValue = rcno->getQuality();
		break;
	case 9: // SR
		tempValue = rcno->getShockResistance();
		break;
	case 10: // UT
		tempValue = rcno->getToughness();
		break;
	case 11: // ER
		tempValue = rcno->getEntangleResistance();
		break;
	}

	rcno = NULL;

	return tempValue;

}
string CraftingManagerImplementation::generateCraftedSerial() {

	stringstream ss;
	char a;

	ss << "(";

	for (int i = 0; i < 8; ++i) {

		a = (System::random(34));
		if (a < 9) {
			a = a + 48;
		} else {
			a -= 9;
			a = a + 97;
		}
		ss << a;
	}

	ss << ")";

	return ss.str();
}

/*void CraftingManagerImplementation::WriteDraftSchematicToDB(DraftSchematic* draftSchematic) {
 try {
 stringstream query;
 query << "INSERT INTO `draft_schematics` "
 << "(`object_id`,`name`,`object_crc`, `group_name`)"
 << " VALUES(" << draftSchematic->getObjectID() << ",'\\" << draftSchematic->getName().c_str() << "',"
 << draftSchematic->getObjectCRC() << ",'" << draftSchematic->getGroupName() << "'," << ")";

 ServerDatabase::instance()->executeStatement(query);

 draftSchematic->setPersistent(true);
 } catch (DatabaseException& e) {
 cout << e.getMessage() << "\n";
 }
 }*/

void CraftingManagerImplementation::addDraftSchematicsFromGroupName(
		Player* player, const string& schematicGroupName) {
	lock();

	if (draftSchematicsMap.contains(schematicGroupName)) {
		DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);

		if (dsg != NULL) {
			for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
				DraftSchematic* draftSchematic = dsg->getDraftSchematic(i);
				player->addDraftSchematic(draftSchematic);
			}
		}
	}

	unlock();
}

void CraftingManagerImplementation::subtractDraftSchematicsFromGroupName(
		Player* player, const string& schematicGroupName) {
	lock();

	if (draftSchematicsMap.contains(schematicGroupName)) {
		DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);

		if (dsg != NULL) {
			for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
				DraftSchematic* draftSchematic = dsg->getDraftSchematic(i);
				player->subtractDraftSchematic(draftSchematic);
			}
		}
	}

	unlock();
}

void CraftingManagerImplementation::registerFunctions() {
	//lua_register(getLuaState(), "RunCraftingConfiguration", runCraftingConfiguration);
	lua_register(getLuaState(), "RunDraftSchematicFile", runDraftSchematicFile);
	lua_register(getLuaState(), "AddDraftSchematicToServer", addDraftSchematicToServer);
}

/*int CraftingManagerImplementation::runCraftingConfiguration(lua_State* L) {
	string craftingBonus = getFloatParameter(L);

	runFile("scripts/crafting/" + filename, L);

	return 0;
}*/

int CraftingManagerImplementation::addDraftSchematicToServer(lua_State *L) {
	LuaObject schematic(L);

	if (!schematic.isValidTable())
		return 1;

	instance->lock();

	// The objName is the name you want the object to have
	// example: object/draft_schematic/item/shared_item_battery_droid.iff
	// objName could be "A Droid Battery"
	string objectName = schematic.getStringField("objectName");

	// The objTemplateCRC is the CRC value of the object using it's .iff file
	// example: object/draft_schematic/item/shared_item_battery_droid.iff
	// objCRC would be 0xD1207EFF
	uint32 objCRC = schematic.getIntField("objectCRC");

	// The groupName will be used as the key to return a list of schematics with that groupName
	// example: "craftArtisanNewbieGroupA" (this is one groupName from Novice Artisan)
	// this groupName will include, CDEF Carbine, CDEF Rifle, Bofa Treat, etc...
	string groupName = schematic.getStringField("groupName");

	// The number that tells the client which crafting tool tab to put the draftSchematic in
	int craftingToolTab = schematic.getIntField("craftingToolTab");

	// The objID is two of the crc combined to make a uint64
	uint32 schematicID = objCRC;

	// The complexity will give a number that will correspond to which level of crafting tools and or
	// crafting stations are required
	uint32 complexity = schematic.getIntField("complexity");

	// I have no idea what the schematicSize is used for :D, but it's a part of all draft schematics
	uint32 schematicSize = schematic.getIntField("size");


	DraftSchematic* draftSchematic = new DraftSchematic(schematicID, objectName, objCRC, groupName,
			complexity, schematicSize, craftingToolTab);

	// Parse the Ingredient data of DraftSchematic from LUA
	// example: craft_food_ingredients_n, craft_food_ingredients_n, craft_food_ingredients_n
	string unparIngredientTemplateNames = schematic.getStringField("ingredientTemplateNames");
	Vector<string> parsedIngredientTemplateNames =
			instance->parseStringsFromString(unparIngredientTemplateNames);

	// example: dried Fruit, crust, additive
	string unparIngredientTitleNames = schematic.getStringField("ingredientTitleNames");
	Vector<string> parsedIngredientTitleNames =
		instance->parseStringsFromString(unparIngredientTitleNames);

	// example: 1 for optional, 0 for mandatory
	string unparOptionalFlags = schematic.getStringField("ingredientOptionals");
	Vector<uint32> parsedOptionalFlags =
		instance->parseUnsignedInt32sFromString(unparOptionalFlags);

	// example: organic, cereal, object/tangible/food/crafted/additive/shared_additive_light.iff
	string unparResourceTypes = schematic.getStringField("resourceTypes");
	Vector<string> parsedResourceTypes =
		instance->parseStringsFromString(unparResourceTypes);

	// example: 3,8,1
	string unparResourceQuantities = schematic.getStringField("resourceQuantities");
	Vector<uint32> parsedResourceQuantities =
		instance->parseUnsignedInt32sFromString(unparResourceQuantities);

	// Add resource requirement sets to schematic
	// Each vector just parsed should all have the same .size() so any .size() will work
	// for the amount of times the loop should execute
	for (int i = 0; i < parsedIngredientTemplateNames.size(); i++) {
		draftSchematic->addIngredient(parsedIngredientTemplateNames.get(i),
				parsedIngredientTitleNames.get(i),
				(bool)parsedOptionalFlags.get(i), parsedResourceTypes.get(i),
				parsedResourceQuantities.get(i));
	}

	// Parse Experimental Properties of Draft Schematic from DB
	// example: 1, 1, 1, 2, 2, 2, 2
	string unparNumberExperimentalProperties = schematic.getStringField("numberExperimentalProperties");
	Vector<uint32> parsedNumberExperimentalProperties =
		instance->parseUnsignedInt32sFromString(unparNumberExperimentalProperties);

	// example: XX, XX, XX, OQ, PE, FL, OQ, DR, PE, DR, OQ
	string unparExperimentalProperties = schematic.getStringField("experimentalProperties");
	Vector<string> parsedExperimentalProperties =
		instance->parseStringsFromString(unparExperimentalProperties);

	// example: 0, 0, 0, 1, 2, 2, 1, 1, 3, 3, 1
	string unparExperimentalWeights = schematic.getStringField("experimentalWeights");
	Vector<uint32> parsedExperimentalWeights =
		instance->parseUnsignedInt32sFromString(unparExperimentalWeights);

	// Add experimental properties groups to the draft schematic
	uint32 iterator = 0;
	for (uint32 i = 0; i < parsedNumberExperimentalProperties.size(); i++) {
		for (uint32 j = 0; j < parsedNumberExperimentalProperties.get(i); j++) {
			draftSchematic->addExperimentalProperty(i,
					parsedExperimentalProperties.get(iterator),
					parsedExperimentalWeights.get(iterator));
			iterator++;
		}
	}

	// example: exp_filling, exp_flavor, exp_nutrition, exp_quantity
	string unparExperimentalGroupTitles = schematic.getStringField("experimentalGroupTitles");
	Vector<string> parsedExperimentalGroupTitles =
		instance->parseStringsFromString(unparExperimentalGroupTitles);

	string unparExperimentalSubGroupCount = schematic.getStringField("experimentalSubGroupCount");
	Vector<uint32> parsedExperimentalSubGroupCount =
		instance->parseUnsignedInt32sFromString(unparExperimentalSubGroupCount);

	string unparExperimentalSubGroupTitles = schematic.getStringField("experimentalSubGroupTitles");
	Vector<string> parsedExperimentalSubGroupTitles =
		instance->parseStringsFromString(unparExperimentalSubGroupTitles);

	string title, subtitle;
	int position = 0;

	for (int i = 0; i < parsedExperimentalGroupTitles.size(); ++i) {

		title = parsedExperimentalGroupTitles.get(i);

		for (int j = 0; j < parsedExperimentalSubGroupCount.get(i); ++j) {

			subtitle = parsedExperimentalSubGroupTitles.get(position);

			draftSchematic->getCraftingValues()->addExperimentalPropertySubtitle(title, subtitle);

			position++;
		}
	}

	// Save schematics tano attributes
	string tanoAttributes = schematic.getStringField("tanoAttributes");
	draftSchematic->setTanoAttributes(tanoAttributes);

	// Set ItemAttribute properties for values in crafting assembly/experimentation
	string unparAttributesToSet = schematic.getStringField("attributesToSet");
	Vector<string> parsedAttributesToSet =
		instance->parseStringsFromString(unparAttributesToSet);

	// Set ItemAttribute properties for values in crafting assembly/experimentation
	string unparAttributesExpProps = schematic.getStringField("attributeExperimentalProperties");
	Vector<string> parsedAttributesExpProps =
		instance->parseStringsFromString(unparAttributesExpProps);

	// Set associated exp property
	string unparAttributesMinMaxToSet = schematic.getStringField("attributesMinMax");
	Vector<string> parsedAttributesMinMaxToSet =
		instance->parseStringsFromString(unparAttributesMinMaxToSet);

	int ii = 0;
	string attribute, attributeExpProp;
	float minVal, maxVal;

	for (int i = 0; i < parsedAttributesToSet.size(); i++) {
		attribute = parsedAttributesToSet.get(i);
		minVal = atof(parsedAttributesMinMaxToSet.get(ii).c_str());
		maxVal = atof(parsedAttributesMinMaxToSet.get(ii + 1).c_str());
		attributeExpProp = parsedAttributesExpProps.get(i);
		draftSchematic->addAttributeToSet(attribute, minVal, maxVal, attributeExpProp);
		ii = ii + 2;
	}

	string xptype = schematic.getStringField("xpType");
	draftSchematic->setXpType(xptype);

	int xp = schematic.getIntField("xp");
	draftSchematic->setXp(xp);

	string assemblySkill = schematic.getStringField("assemblySkill");
	draftSchematic->setAssemblySkill(assemblySkill);

	string experimentingSkill = schematic.getStringField("experimentingSkill");
	draftSchematic->setExperimentingSkill(experimentingSkill);

	int componentMath = schematic.getIntField("componentMath");
	//draftSchematic->setComponentMathType(componentMath);

	instance->mapDraftSchematic(draftSchematic);
	instance->unlock();

	return 0;
}

void CraftingManagerImplementation::mapDraftSchematic(DraftSchematic* draftSchematic) {
	string groupName = draftSchematic->getGroupName();
	if (!draftSchematicsMap.contains(groupName)) {
		DraftSchematicGroup* dsg = new DraftSchematicGroup();

		dsg->addDraftSchematic(draftSchematic);

		draftSchematicsMap.put(groupName, dsg);
	} else
		draftSchematicsMap.get(draftSchematic->getGroupName())->addDraftSchematic(draftSchematic);
}

int CraftingManagerImplementation::runDraftSchematicFile(lua_State* L) {
	string filename = getStringParameter(L);

	runFile("scripts/crafting/" + filename, L);

	return 0;
}

Vector<string> CraftingManagerImplementation::parseStringsFromString(
		const string& unparsedStrings) {
	string parseHelper;
	Vector<string> parsedStrings;

	for (int i = 0; i < unparsedStrings.size(); i++) {
		char currentChar = unparsedStrings.at(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				parsedStrings.add(parseHelper);
				parseHelper.clear();
			} else {
				parseHelper += currentChar;
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	parsedStrings.add(parseHelper);

	return parsedStrings;
}

Vector<uint32> CraftingManagerImplementation::parseUnsignedInt32sFromString(
		const string& unparsedInts) {
	string parseHelper;
	Vector<uint32> parsedInts;

	for (int i = 0; i < unparsedInts.size(); i++) {
		char currentChar = unparsedInts.at(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				uint32 resourceQuantity = (uint32)atoi(parseHelper.c_str());
				parsedInts.add(resourceQuantity);
				parseHelper.clear();
			} else {
				parseHelper += currentChar;
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	uint32 resourceQuantity = (uint32)atoi(parseHelper.c_str());
	parsedInts.add(resourceQuantity);

	return parsedInts;
}
