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
#include "events/ChangeItemMaskEvent.h"

CraftingManagerImplementation* CraftingManagerImplementation::instance = NULL;

/*
 *  Constructor for CraftingManagerImplementation
 *  Enables Logging and initializes manager
 */

CraftingManagerImplementation::CraftingManagerImplementation(ZoneServer* serv,
		ZoneProcessServerImplementation* proc) :
	CraftingManagerServant(), Mutex("CraftingManagerMutex") {

	server = serv;
	processor = proc;

	setLoggingName("CraftingManager");

	setLogging(true);
	setGlobalLogging(true);

	tempMask = 0;

	init();
}

/*
 *  Deconstructor for CraftingManagerImplementation
 *  Finalizes each item in the schematic map
 */

CraftingManagerImplementation::~CraftingManagerImplementation() {
	for (int i = 0; i < draftSchematicsMap.size(); ++i)
		draftSchematicsMap.get(i)->finalize();

	draftSchematicsMap.removeAll();
}

/*
 *  Registers LUA functions, and starts loading the schematic LUA's
 */

void CraftingManagerImplementation::init() {
	// Scripting
	Lua::init();
	registerFunctions();
	instance = this;
	loadDraftSchematicFile();
}

void CraftingManagerImplementation::reloadSchematicTable() {

	Lua::deinit();
	Lua::init();
	registerFunctions();
	draftSchematicsMap.removeAll();
	loadDraftSchematicFile();
}

// Crafting Methods
void CraftingManagerImplementation::prepareCraftingSession(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Clones the global Draft Schematic for use locally within the crafting tool
	craftingTool->setWorkingDraftSchematic(draftSchematic);

	// Set draftSchematic to the new cloned schematic
	draftSchematic = craftingTool->getWorkingDraftSchematic();

	// Set active crafter is schematic
	draftSchematic->setCrafter(player);

	// Send the appropriate DraftSchematic to Player
	createDraftSchematic(player, craftingTool, draftSchematic);

	// Creates the Appropriate TangibleObject and sends to player
	if(!createTangibleObject(player, craftingTool, draftSchematic))
		return;

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
}

TangibleObject* CraftingManagerImplementation::createTangibleObject(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Generates the tangible for crafting
	TangibleObject* tano = generateTangibleObject(player, draftSchematic);

	if(tano == NULL)
		return NULL;

	// Link TangibleObject to the CraftingTool
	tano->setParent(craftingTool);

	// Send TangibleObject baselines to player
	tano->sendTo(player, true);

	// Dplay9 ********************************************************
	// Sets the Crafting state to 2, which is the Resource screen
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
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

	return tano;

}

void CraftingManagerImplementation::setupIngredients(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0103);
	objMsg->insertLong(craftingTool->getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(draftSchematic->getObjectID()); // Draft Schematic Object ID
	objMsg->insertLong(craftingTool->getWorkingTano()->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(3);
	objMsg->insertByte(1);

	// Sends requested ingredients to the player
	draftSchematic->helperSendIngredientsToPlayer(objMsg);

	player->sendMessage(objMsg);
	// End Object Controller w/ Ingredients ************************


	// MSCO7 *******************************************************
	ManufactureSchematicObjectMessage7 * msco7 =
			new ManufactureSchematicObjectMessage7(draftSchematic->getObjectID(), draftSchematic);

	player->sendMessage(msco7);
	// End MSCO7 ***************************************************

}

// Methods to Add items to the crafting process
void CraftingManagerImplementation::addIngredientToSlot(Player* player,
		TangibleObject* tano, int slot, int counter) {

	TangibleObject* newTano;

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

	DraftSchematicIngredient* dsi = draftSchematic->getIngredient(slot);

	if (dsi == NULL) {
		return;
	}

	try {

		// Get the resouce requirements for the chosen slot
		int quantity = dsi->getResourceQuantity();

		// Get what, if anything, is in the designated slot
		TangibleObject* ingredientInSlot = craftingTool->getIngredientInSlot(slot);
		int ingredientInSlotQuantity = craftingTool->getIngredientInSlotQuantity(slot);

		// Send slot messages base on content, if needed
		if (ingredientInSlot != NULL) {

			if (slotIsFull(player, craftingTool, tano, ingredientInSlot, ingredientInSlotQuantity, slot,
					quantity, counter)) {

				return;
			}
		}

		quantity = quantity - ingredientInSlotQuantity;

		// Set resource values appropriately
		newTano = transferIngredientToSlot(player, tano, craftingTool, quantity);

		if (newTano == NULL) {
			sendSlotMessage(player, counter, SLOTBADCRATE);
			return;
		}

		// Add the resource to the "slots" in the crafting tool for tracking
		if (!craftingTool->addIngredientToSlot(slot, newTano)) {
			sendSlotMessage(player, counter, SLOTINVALIDINGREDIENT);
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
		ManufactureSchematicObjectDeltaMessage7 * dMsco7 =
						new ManufactureSchematicObjectDeltaMessage7(draftSchematic->getObjectID());

		if (craftingTool->getInsertCount() == 1) {

			// If it's the first resource inserted, we need to fully update all the slots
			dMsco7->fullUpdate(draftSchematic,
					draftSchematic->getIngredientListSize(), slot,
					newTano->getObjectID(), quantity + ingredientInSlotQuantity);
		} else {

			// If it's not the first resources, slots are updates, and only insert needs done
			dMsco7->partialUpdate(slot, draftSchematic->getIngredientListSize()
					+ craftingTool->getInsertCount(), newTano->getObjectID(),
					quantity + ingredientInSlotQuantity);

			draftSchematic->increaseComplexity();
		}
		dMsco7->close();

		player->sendMessage(dMsco7);
		// End DMSCO7 ***************************************************

		// Start DMSCO3 ***********************************************************
		// Updates the Complexity
		ManufactureSchematicObjectDeltaMessage3* dMsco3 =
				new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
		dMsco3->updateComplexity(draftSchematic->getComplexity());
		dMsco3->close();

		player->sendMessage(dMsco3);
		// End DMSCO3 *************************************************************

		sendSlotMessage(player, counter, SLOTOK);

		// Increment the insert counter
		craftingTool->increaseInsertCount();

	} catch (...) {
		info(
				"Unreported exception caught in CraftingManagerImplementation::addIngredientToSlot");
	}
}

bool CraftingManagerImplementation::slotIsFull(Player* player,
		CraftingTool* craftingTool, TangibleObject* tano, TangibleObject* ingredientInSlot,
		int ingredientInSlotQuantity, int slot, int quantity, int counter) {

	if (tano->isResource()) {

		ResourceContainer* rcno = (ResourceContainer*) tano;
		ResourceContainer* rcnoinSlot = (ResourceContainer*) ingredientInSlot;

		if (rcnoinSlot == NULL)
			return true;

		if (rcnoinSlot->getContents() != 0) {

			if (quantity == rcnoinSlot->getContents()) {

				// If slot is full send slot is full message
				sendSlotMessage(player, counter, SLOTFULL);
				return true;
			}

			// If the is a partial resource in the slot, add it back to inventory
			// So that resource amounts are correct
			if (!rcnoinSlot->compare(rcno)) {

				// If Resource isn't the same, throw slot error
				sendSlotMessage(player, counter, SLOTINVALIDINGREDIENT);
				return true;

			}
		}

	} else {

		// deal with partial components in slot


	}

	return false;
}

void CraftingManagerImplementation::sendSlotMessage(Player* player,
		int counter, short message) {

	// Object Controller ********************************************
	// Send Bad Slot message
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x107);
	objMsg->insertInt(message);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);
	//End Object Controller ******************************************
}

TangibleObject* CraftingManagerImplementation::transferIngredientToSlot(
		Player* player, TangibleObject* tano, CraftingTool* craftingTool,
		int& quantity) {

	if (tano->isResource()) {

		ResourceContainer* rcno = (ResourceContainer*) tano;
		return transferResourceToSlot(player, rcno, craftingTool, quantity);

	} else if (tano->isComponent()) {

		Component* component = (Component*) tano;
		return transferComponentToSlot(player, component, craftingTool,
				quantity);

	} else {

		info("CraftingManagerImplementation::transferIngredientToSlot - I'm not a resource or a component, WTF am I = "
						+ tano->getObjectSubType());
		return NULL;
	}
}

TangibleObject* CraftingManagerImplementation::transferResourceToSlot(
		Player* player, ResourceContainer* incomingResource, CraftingTool* craftingTool,
		int& quantity) {

	String name = incomingResource->getResourceName();

	if (incomingResource->getContents() < quantity) {

		// If there are less resources in the stack
		// then required, only use what is left
		quantity = incomingResource->getContents();

	}

	if (incomingResource->getContents() - quantity < 1) {

		// If Stack is empty, remove it from inventory
		player->removeInventoryItem(incomingResource->getObjectID());

		// Destroy Container
		incomingResource->sendDestroyTo(player);
		incomingResource->finalize();

	} else {

		try {
			// Remove proper amount of resource from chosen Container
			int newContents = incomingResource->getContents() - quantity;
			incomingResource->setContents(newContents);

			// Update the ResourceContainer
			incomingResource->sendDeltas(player);

			// Flag ResourceContainer for saving changes
			incomingResource->setUpdated(true);

		} catch (...) {
			info(
					"CraftingManagerImplementation::transferResourceToSlot - Error changing contents");

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
	TangibleObject* tano = (TangibleObject*) newRcno;

	craftingTool->addTempIngredient(tano);

	return tano;
}

TangibleObject* CraftingManagerImplementation::transferComponentToSlot(
		Player* player, Component* component, CraftingTool* craftingTool,
		int& quantity) {

	int objectCount = component->getObjectCount();

	Component* newComponent;
	newComponent = component->cloneComponent(component, player->getNewItemID());

	if (newComponent == NULL)
		return NULL;

	if (objectCount == 0)
		objectCount = 1;

	if (objectCount - quantity < 1) {

		// If Stack is empty, remove it from inventory
		player->removeInventoryItem(component->getObjectID());

		// Destroy Old stack
		component->sendDestroyTo(player);

		component->finalize();

		quantity = objectCount;

	} else {

		try {

			// Remove proper amount of item from chosen stack
			component->setObjectCount(objectCount - quantity);

			// Update the Tano
			component->sendDeltas(player);

			// Flag Tano for saving changes
			component->setUpdated(true);

		} catch (...) {
			info("CraftingManagerImplementation::transferComponentToSlot - Error changing contents");

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

	// We don't want the temp component to save
	newComponent->setPersistent(true);
	newComponent->setUpdated(false);

	//Send attributes to update crafting window (Or quality bars don't show up
	newComponent->generateAttributes(player);

	TangibleObject* tano = (TangibleObject*) newComponent;

	// Adding the ObjectID to a vector for proper clean up when the tool is closed
	// Because otherwise the resource stack is lost in memory
	craftingTool->addTempIngredient(tano);

	return tano;

}

void CraftingManagerImplementation::removeIngredientFromSlot(Player* player,
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
		String name;

		// Use the crafting tool to amount of resources in the slot
		TangibleObject* tano = craftingTool->getIngredientInSlot(slot);

		if (tano == NULL) {
			player->sendSystemMessage("Bad ingredient in slot");
			return; // TODO: send some error message
		}

		// Pretty easy to understand this
		if (tano->isResource()) {

			ResourceContainer* rcno = (ResourceContainer*) tano;
			player->addInventoryResource(rcno);
		} else {

			Component* component = (Component*) tano;

			if (component == NULL) {
				sendSlotMessage(player, counter, SLOTNOCOMPONENTTRANSFER);
				return;
			}
			putComponentBackInInventory(player, component);
		}

		// Clears CraftingTool's resource slot
		craftingTool->clearIngredientInSlot(slot);

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
		ObjectControllerMessage* objMsg =
						new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x108);
		objMsg->insertInt(0);
		objMsg->insertByte(counter);

		player->sendMessage(objMsg);
		// End Object Controller *****************************************

		tano = NULL;

		if(craftingTool->getInsertCount() > 0)
			draftSchematic->decreaseComplexity();

		// Start DMSCO3 ***********************************************************
		// Updates the Complexity
		ManufactureSchematicObjectDeltaMessage3* dMsco3 =
				new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
		dMsco3->updateComplexity(draftSchematic->getComplexity());
		dMsco3->close();

		player->sendMessage(dMsco3);
		// End DMSCO3 *************************************************************

		// Increases Insert Counter
		craftingTool->increaseInsertCount();

	} catch (...) {

		info("Error removing resource from slot");

	}
}

ResourceContainer* CraftingManagerImplementation::makeNewResourceStack(
		Player* player, String name, int quantity) {

	// This clones the resource stack to insert into the slot

	ResourceContainer* rco = new ResourceContainer(player->getNewItemID());

	rco->setResourceName(name);

	rco->setContents(quantity);

	player->getZone()->getZoneServer()->getResourceManager()->setResourceData(
			rco);

	return rco;
}

void CraftingManagerImplementation::putComponentBackInInventory(Player* player,
		Component* component) {

	Component* newComponent;
	newComponent = component->cloneComponent(component, player->getNewItemID());

	if (newComponent == NULL)
		return;

	player->getZone()->getZoneServer()->addObject(newComponent, true);

	newComponent->deploy();

	newComponent->setPersistent(false);

	server->addObject(newComponent);

	player->addInventoryItem(newComponent);
	newComponent->sendTo(player);

	component->setParent(NULL);
	component->destroy(player->getClient());
	component->finalize();

}

void CraftingManagerImplementation::nextCraftingStage(Player* player, String test) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();
	if (craftingTool == NULL)
		return;

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();

	if (draftSchematic == NULL)
		return;

	// Get counter from packet
	int counter = atoi(test.toCharArray());

	// Make sure all the require resources are there, if not, return them to inventory and close tool
	if(!craftingTool->hasAllRequiredResources(draftSchematic)){

		craftingTool->cleanUp(player);

		closeCraftingWindow(player, counter);

		return;
	}

	// If the window is closed now, this sets the resources to no be recoverable
	craftingTool->setRecoverResources(false);
	draftSchematic->setResourcesWereRemoved();

	if (craftingTool->getCraftingState() == 2) {

		// Calculate exp failure for red bars
		float failure = calculateExperimentationFailureRate(player,
				craftingTool, draftSchematic, 0);
		draftSchematic->setExpFailure(failure);

		// Flag to get the experimenting window
		if (craftingTool->isExperimenting()) {

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

}

void CraftingManagerImplementation::initialAssembly(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic,
		int counter, int stage) {

	TangibleObject* tano = craftingTool->getWorkingTano();

	if (tano == NULL)
		return;

	// Get the appropriate number of Experimentation points from Skill
	String expskill = draftSchematic->getExperimentingSkill();
	int exppoints = int(player->getSkillMod(expskill) / 10);

	// Get the level of customization
	String custskill = draftSchematic->getCustomizationSkill();
	int custpoints = int(player->getSkillMod(custskill));

	// The Experimenting counter always starts at numbers of exp titles + 1
	draftSchematic->setExpPoints(exppoints);

	// Start DPLAY9 ***********************************************************
	// Updates the stage of crafting, sets the number of experimentation points
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
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

	// Set Crafter name and generate serial number
	tano->setCraftersName(player->getFirstName());

	String serial = generateCraftedSerial();
	tano->setCraftedSerial(serial);

	// Update the Tano with new values
	tano->updateCraftingValues(draftSchematic);

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
	if (custpoints > 0) {
		dMsco7->updateCustomizationOptions(draftSchematic, custpoints);
	}
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
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
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
		PlayerObjectDeltaMessage9* dplay9 =
				new PlayerObjectDeltaMessage9(player->getPlayerObject());
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
void CraftingManagerImplementation::setInitialCraftingValues(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic) {

	//DraftSchematicAttribute* attrib;

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	String itemName, subtitle, title;

	float value, maxPercentage, currentPercentage, weightedSum;
	DraftSchematicExpPropGroup* dsepg;

	// These 2 values are pretty standard, adding these
	itemName = "xp";
	value = float(draftSchematic->getXp());
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, 1);

	itemName = "complexity";
	value = draftSchematic->getComplexity();
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, 1);

	int subtitleCounter = 0;

	float modifier = calculateAssemblyValueModifier(craftingTool);

	for (int i = 0; i < draftSchematic->getExpPropGroupListSize(); ++i) {

		// Grab the first weight group
		dsepg = draftSchematic->getExpPropGroup(i);

		// Getting the title ex: expDamage
		title = dsepg->getTitle();

		// Getting the subtitle ex: minDamage
		subtitle = dsepg->getSubtitle();

		weightedSum = 0;

		craftingValues->addExperimentalProperty(title, subtitle, dsepg->getMinValue(), dsepg->getMaxValue(), dsepg->getPrecision(), dsepg->isFiller());

		for (int ii = 0; ii < dsepg->getExpPropPercentageListSize(); ++ii) {

			// Based on the script we cycle through each exp group

			// Get the type from the type/weight
			int type = (dsepg->getTypeAndWeight(ii) >> 4);

			// Get the calculation percentage
			float resPercentage = dsepg->getExpPropPercentage(ii);

			// add to the weighted sum based on type and percentage
			weightedSum += getWeightedValue(player, craftingTool,
					draftSchematic, type) * resPercentage;

		}

		// > 0 ensures that we don't add things when there is NaN value
		if (weightedSum > 0) {

			// This is the formula for max experimenting percentages
			maxPercentage = ((weightedSum / 10.0f) * .01f);

			// Based on the weighted sum, we can get the initial %
			currentPercentage = (getAssemblyPercentage(weightedSum)) * modifier;

			craftingValues->setMaxPercentage(subtitle, maxPercentage);
			craftingValues->setCurrentPercentage(subtitle, currentPercentage);
//System::out << "Subtitle: " << subtitle << " weighted = " << weightedSum << " current: " << currentPercentage << " max: " << maxPercentage << endl;
			subtitleCounter++;
		} else {

		}

	}

	craftingValues->recalculateValues(draftSchematic, true);

	if (applyComponentBoost(draftSchematic, craftingTool))
		craftingValues->recalculateValues(draftSchematic, true);

	//craftingValues->toString();
}

bool CraftingManagerImplementation::applyComponentBoost(
		DraftSchematic* draftSchematic, CraftingTool* craftingTool) {

	DraftSchematicIngredient* ingredient;
	TangibleObject* tano;
	TangibleObject* workingTano = craftingTool->getWorkingTano();
	Component* component;
	float max, min, currentvalue, propertyvalue;
	int precision;
	bool modified = false;
	bool hidden;
	String experimentalTitle, property;

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	for (int i = 0; i < draftSchematic->getIngredientListSize(); ++i) {

		ingredient = draftSchematic->getIngredient(i);

		if (ingredient != NULL) {

			tano = craftingTool->getIngredientInSlot(i);

			if (tano != NULL && tano->isComponent()) {

				component = (Component*) tano;

				for (int j = 0; j < component->getPropertyCount(); ++j) {

					property = component->getProperty(j); // charges

					modified = true;

					if (craftingValues->hasProperty(property) && !component->getAttributeHidden(property)) {

						max = craftingValues->getMaxValue(property);

						min = craftingValues->getMinValue(property);

						hidden = craftingValues->isHidden(property);

						currentvalue = craftingValues->getCurrentValue(property);

						propertyvalue = component->getAttributeValue(property) * ingredient->getContribution();

						currentvalue += propertyvalue;
						min += propertyvalue;
						max += propertyvalue;

						craftingValues->setMinValue(property, min);
						craftingValues->setMaxValue(property, max);

						if (ingredient->getCombineType() == COMPONENTLINEAR) {

							craftingValues->setCurrentValue(property, currentvalue);

						} else if (ingredient->getCombineType() == COMPONENTPERCENTAGE) {

							craftingValues->setCurrentPercentage(property, currentvalue);

						}
					} else if(!component->getAttributeHidden(property)) {

						currentvalue = component->getAttributeValue(property);
						precision = component->getAttributePrecision(property);
						experimentalTitle = component->getAttributeTitle(property);

						craftingValues->addExperimentalProperty(experimentalTitle, property, currentvalue, currentvalue, precision, false);
						craftingValues->setCurrentPercentage(property, .5f);
						craftingValues->setMaxPercentage(property, 1.0f);
						craftingValues->setCurrentValue(property, currentvalue);
					}
				}
			}
		}
	}
	return modified;
}

void CraftingManagerImplementation::finishAssembly(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic, int counter) {

	// Start Dplay9 **************************************
	// Move crafting to State 4
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(4);
	craftingTool->setCraftingState(4);
	dplay9->close();

	player->sendMessage(dplay9);
	// End DPLAY9

	// Start Object Controller **************************************
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);

	objMsg->insertByte(counter);

	player->sendMessage(objMsg);
	// End Object Controller **************************************

}

void CraftingManagerImplementation::handleExperimenting(Player* player,
		int counter, int numRowsAttempted, String expString) {

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

	StringTokenizer tokenizer(expString);

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
		failure = calculateExperimentationFailureRate(player, craftingTool,
				draftSchematic, pointsAttempted);

		// Set the experimentation result ie:  Amazing Success
		calculateExperimentationSuccess(player, craftingTool, draftSchematic,
				failure);

		// Make sure to store the lowest roll to display (Effect the multiline rolls
		if (lowestExpSuccess < craftingTool->getAssemblyResults())
			lowestExpSuccess = craftingTool->getAssemblyResults();

		draftSchematic->increaseExpCounter();

		rowEffected = tokenizer.getIntToken();
		pointsAttempted = tokenizer.getIntToken();

		totalPoints += pointsAttempted;

		draftSchematic->increaseComplexity();

		// Do the experimenting - sets new percentages
		experimentRow(draftSchematic->getCraftingValues(), rowEffected,
				pointsAttempted, failure, craftingTool->getAssemblyResults());

	}

	// Use percentages to recalculate the values
	craftingValues->recalculateValues(draftSchematic, false);

	// Update the Tano with new values
	tano->updateCraftingValues(draftSchematic);

	// Sets the result for display
	craftingTool->setAssemblyResults(lowestExpSuccess);

	// Get exp points left
	int expPoints = draftSchematic->getExpPoints();

	// Set new exp points subtracting those used above
	draftSchematic->setExpPoints(expPoints - totalPoints);

	// Start Player Object Delta **************************************
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
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
	dMsco7->update9(draftSchematic, false);
	dMsco7->close();

	player->sendMessage(dMsco7);

	TangibleObjectDeltaMessage3* dtano3 =
			new TangibleObjectDeltaMessage3(craftingTool->getWorkingTano());
	dtano3->updateComplexity(float(draftSchematic->getComplexity()));
	dtano3->close();

	player->sendMessage(dtano3);

	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0113);
	objMsg->insertInt(0x105);

	objMsg->insertInt(craftingTool->getAssemblyResults()); // Experimentation Result
	// 0 = Amazing
	// 1 = Great
	// 2 = Good
	// 3 = Moderate
	// 4 = A success
	// 5 = Marginally Successful
	// 6 = "ok"
	// 7 = Barely Succeeded
	// 8 = Critical Failure
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);

}

void CraftingManagerImplementation::experimentRow(
		DraftSchematicValues* craftingValues, int rowEffected,
		int pointsAttempted, float failure, int assemblyResult) {

	float modifier, newValue;

	String title, subtitle, subtitlesTitle;

	title = craftingValues->getVisibleExperimentalPropertyTitle(rowEffected);

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {

		subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(i);

		if (subtitlesTitle == title) {

			subtitle = craftingValues->getExperimentalPropertySubtitle(i);

			modifier = calculateExperimentationValueModifier(assemblyResult,
					pointsAttempted, failure);

			newValue = craftingValues->getCurrentPercentage(subtitle)
					+ modifier;

			if (newValue > craftingValues->getMaxPercentage(subtitle))
				newValue = craftingValues->getMaxPercentage(subtitle);

			craftingValues->setCurrentPercentage(subtitle, newValue);
		}
	}
}

void CraftingManagerImplementation::createPrototype(Player* player, String count) {

	CraftingTool* craftingTool;
	DraftSchematic* draftSchematic;
	TangibleObject* workingTano;
	int counter, practice;

	StringTokenizer tokenizer(count);

	counter = tokenizer.getIntToken();
	practice = tokenizer.getIntToken();

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

		workingTano = craftingTool->getWorkingTano();

		if (workingTano == NULL) {

			sendSlotMessage(player, counter, SLOTPROTOTYPENOTFOUND);
			return;

		}

		if (!draftSchematic->isFinished() && draftSchematic->resourcesWereRemoved()) {

			closeCraftingWindow(player, counter);

			String xpType = draftSchematic->getXpType();
			int xp = draftSchematic->getXp();

			if (practice != 0) {

				createObjectInInventory(player, draftSchematic->getComplexity() * 2, true);

			} else {

				// This is for practiceing
				//createObjectInInventory(player, draftSchematic->getComplexity() * 2, false);

				// factory crates are rigged to output on createObjectInInventory(x, x, FALSE);
				// so uncomment this next line to create a factory crate of 25 items
				//createObjectInInventory(player, draftSchematic->getComplexity() * 2, false);

				//comment this next line if you are making factory crates instead
				createObjectInInventory(player, draftSchematic->getComplexity() * 2, true);

				//workingTano->setOptionsBitmask(8192);

				// This is an item mask test below - It cycles through the item masks - for testing
				/*createObjectInInventory(player, 1, true);
				xp = int(round(1.05 * xp));

				for(int i = -500; i < pow(2,32);  ++i) {

					ChangeItemMaskEvent* maskEvent = new ChangeItemMaskEvent(player, craftingTool->getWorkingTano(), (int)pow(2, i));

					processor->addEvent(maskEvent, (i * 200));
				}*/
			}

			player->addXp(xpType, xp, true);
			draftSchematic->setFinished();
		} else {

			closeCraftingWindow(player, counter);

			sendSlotMessage(player, counter, WEIRDFAILEDMESSAGE);
		}

	} catch (...) {

	}
}

void CraftingManagerImplementation::closeCraftingWindow(Player* player, int counter) {

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
}

void CraftingManagerImplementation::createSchematic(Player* player,
		String count) {

	CraftingTool* craftingTool;
	DraftSchematic* draftSchematic;
	TangibleObject* workingTano;
	int counter, practice;

	StringTokenizer tokenizer(count);

	counter = tokenizer.getIntToken();
	practice = tokenizer.getIntToken();

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

		workingTano = craftingTool->getWorkingTano();

		if (workingTano == NULL) {

			sendSlotMessage(player, counter, SLOTPROTOTYPENOTFOUND);
			return;

		}

		if (!draftSchematic->isFinished() && draftSchematic->resourcesWereRemoved()) {


			//Object Controller
			ObjectControllerMessage* objMsg =
					new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
			objMsg->insertInt(0x10B);
			objMsg->insertInt(1);
			objMsg->insertByte(counter);

			player->sendMessage(objMsg);

			//player->addXp(xpType, xp, true);
			draftSchematic->setFinished();

			// Create and send datapad schematic to player

			/*IntangibleObject* datapadSchematic =
				new IntangibleObject((SceneObject*) player->getDatapad(), workingTano->getObjectCRC(), player->getNewItemID());

			datapadSchematic->setName(workingTano->getTemplateName());
			datapadSchematic->setDetailName(workingTano->getTemplateTypeName());
			datapadSchematic->setWorldObject(workingTano);*/

			player->addDatapadItem((SceneObject*) workingTano);

			workingTano->sendTo(player, true);

			UpdateContainmentMessage* ucm = new UpdateContainmentMessage((SceneObject*) workingTano, (SceneObject*) player->getDatapad(), 0xFFFFFFFF);
			player->sendMessage(ucm);

		} else {

			closeCraftingWindow(player, counter);

			sendSlotMessage(player, counter, WEIRDFAILEDMESSAGE);
		}

	} catch (...) {

	}
}
void CraftingManagerImplementation::craftingCustomization(Player* player,
		String name, int manufacturingSchematicLimit, String customizationString) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL)
		return;

	DraftSchematic* draftSchematic = craftingTool->getWorkingDraftSchematic();
	TangibleObject* tano = craftingTool->getWorkingTano();

	if (draftSchematic == NULL || tano == NULL)
		return;

	StringTokenizer tokenizer(customizationString);
	int customizationnumber, customizationvalue;
	String customization;

	MySqlDatabase::escapeString(name);

	tano->setCustomName(name);

	VectorMap<String, int> customizationMap;

	while (tokenizer.hasMoreTokens()) {

		customizationnumber = tokenizer.getIntToken();
		customization = draftSchematic->getCustomizationOption(customizationnumber);

		customization = customization.replaceAll("/private/", "");
		customizationvalue = tokenizer.getIntToken();

		customizationMap.put(customization, customizationvalue);
	}

	for (int i = 0; i < customizationMap.size(); ++i) {
		tano->setCustomizationVariable(customizationMap.elementAt(i)->getKey(), customizationMap.get(i));
	}

	tano->setUpdated(true);

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(tano);
	dtano3->updateName(name);
	dtano3->updateCustomizationString();
	dtano3->close();

	player->sendMessage(dtano3);

	ManufactureSchematicObjectDeltaMessage3 * dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(draftSchematic->getObjectID());
	dMsco3->updateName(name);
	dMsco3->updateCondition(manufacturingSchematicLimit);
	dMsco3->close();

	player->sendMessage(dMsco3);

	//Object Controller
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
	objMsg->insertInt(0x15A);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);

	craftingTool->setCraftingState(5);

}
void CraftingManagerImplementation::finishStage1(Player* player, int counter) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL) {

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(5);
	dplay9->close();

	player->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);
	objMsg->insertByte(counter);

	player->sendMessage(objMsg);

	craftingTool->setCraftingState(6);
}

void CraftingManagerImplementation::finishStage2(Player* player, int counter) {

	CraftingTool* craftingTool = player->getCurrentCraftingTool();

	if (craftingTool == NULL) {

		sendSlotMessage(player, counter, SLOTNOTOOL);
		return;

	}

	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->insertShort(5);
	dplay9->insertInt(0xFFFFFFFF);
	dplay9->setCraftingState(0);
	craftingTool->setCraftingState(0);
	dplay9->close();
	player->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
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
			updateToolCountdownEvent
					= new UpdateToolCountdownEvent(player, craftingTool, timer);
			processor->addEvent(updateToolCountdownEvent, timer2);
			timer -= 5;
			timer2 += 5000;
		}

		if (timer < 0) {
			timer2 += timer;// * 1000;
			timer = 0;
		}

		updateToolCountdownEvent
				= new UpdateToolCountdownEvent(player, craftingTool, timer);

		processor->addEvent(updateToolCountdownEvent, timer2);
		processor->addEvent(createObjectEvent, timer2);

	} else {
		System::out << "Serv == NULL\n";
	}
}

TangibleObject* CraftingManagerImplementation::generateTangibleObject(
		Player* player, DraftSchematic* draftSchematic) {
	ItemManager* itemManager =
			player->getZone()->getZoneServer()->getItemManager();
	TangibleObject* tano = NULL;

	String attributes = draftSchematic->getTanoAttributes();

	ItemAttributes* itemAttributes = new ItemAttributes();
	itemAttributes->setAttributes(attributes);

	uint64 objectid = player->getNewItemID();

	String temp = "objecttype";
	int objecttype = itemAttributes->getIntAttribute(temp);

	temp = "objectcrc";
	uint32 objectcrc = itemAttributes->getUnsignedLongAttribute(temp);

	String objectname = "";

	temp = "objecttemp";
	String objecttemp = itemAttributes->getStringAttribute(temp);

	temp = "templatetype";
	String templatetype = itemAttributes->getStringAttribute(temp);

	temp = "itemmask";
	int mask = itemAttributes->getIntAttribute(temp);

	temp = "customattributes";
	String customattributes = itemAttributes->getStringAttribute(temp);

	if(!customattributes.isEmpty()) {
		customattributes = customattributes.replaceAll(";", ":");
		customattributes = customattributes.replaceAll(",", ";");
	}

	TangibleObject* item = NULL;

	bool equipped = false;

	tano = itemManager->initializeTangibleForCrafting(objecttype, objectid,
			objectcrc, objectname, objecttemp, equipped);

	if (tano == NULL) {

		player->sendSystemMessage("Failed to make tangible item, perhaps the Object type is wrong, or it doesn't exist in ItemManager");
		return NULL;

	}

	tano->setPlayerUseMask(mask);

	tano->setTemplateTypeName(templatetype);

	tano->setAttributes(customattributes);

	tano->parseItemAttributes();

	//item->setCustomizationString(custStr);
	return tano;
}

void CraftingManagerImplementation::calculateAssemblySuccess(Player* player,
		CraftingTool* craftingTool, DraftSchematic* draftSchematic,
		float modifier) {

	// Skill + Luck roll and crafting tool effectiveness determine the
	// Success of the crafting result

	int preresult, result;

	String assemblySkill = draftSchematic->getAssemblySkill();

	// Get assembly points from skill
	float assemblyPoints = float(player->getSkillMod(assemblySkill) / 10);

	// Get modifier from tool to modify success
	float toolModifier = calculateAssemblyModifier(craftingTool);

	// Gets failure rate * 100 .25 = 25, so decimals matter in the roll
	int failureRate = calculateAssemblyFailureRate(player, craftingTool,
			assemblyPoints) + int(modifier * 100);

	int luck = System::random(100);

	if (failureRate > luck * 10) {

		result = 8;

	} else if (luck >= 95 - int(10.0f * ((toolModifier + .15f) - 1.0f))) {

		result = 0;

	} else {

		preresult = int(toolModifier * ((assemblyPoints * 10) + luck));

		if (preresult > 110) {

			result = 1;

		} else if (preresult > 80) {

			result = 2;

		} else if (preresult > 60) {

			result = 3;

		} else if (preresult > 50) {

			result = 4;

		} else if (preresult > 40) {

			result = 5;

		} else if (preresult > 30) {

			result = 6;

		} else {

			result = 7;

		}

	}

	craftingTool->setAssemblyResults(result);
}

void CraftingManagerImplementation::calculateExperimentationSuccess(
		Player* player, CraftingTool* craftingTool,
		DraftSchematic* draftSchematic, float failure) {

	// Skill + Luck roll and crafting station effectiveness determine the
	// Success of the crafting result

	int result, preresult;

	// Get modifier from tool to modify success
	float stationModifier = .80;//calculateExperimentationModifier(craftingTool);
	String expSkill = draftSchematic->getExperimentingSkill();

	// Get experiemtnation points from skill
	int expPoints = player->getSkillMod(expSkill);

	// Gets failure rate * 100 .25 = 25, so decimals matter in the roll
	int failureRate = int(failure * 100);

	int luck = System::random(100);

	if (failureRate > luck * 10) {

		result = 8;

	} else if (luck >= 99 - int(9.0f * stationModifier)) {

		result = 0;

	} else {

		if (stationModifier < .8f)
			stationModifier = .8f;

		preresult = int(stationModifier * (expPoints + luck));

		//System::out << "PRERESULT = " << preresult << "  expPoints = " << expPoints << "   luck = " << luck << endl;


		if (preresult > 90) {

			result = 1;

		} else if (preresult > 60) {

			result = 2;

		} else if (preresult > 50) {

			result = 3;

		} else if (preresult > 40) {

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

float CraftingManagerImplementation::calculateExperimentationFailureRate(
		Player* player, CraftingTool* craftingTool,
		DraftSchematic* draftSchematic, int pointsUsed) {

	// Skill + Luck roll and crafting tool effectiveness determine the
	// Success of the crafting result

	// Get the Weighted value of MA
	float ma = getWeightedValue(player, craftingTool, draftSchematic, 4);

	// Get Experimentation skill
	String expSkill = draftSchematic->getExperimentingSkill();
	float expPoints = player->getSkillMod(expSkill);

	float failure = (50.0f + (ma - 500.0f) / 40.0f + expPoints - 5.0f
			* pointsUsed) / 100.0f;

	// Return 0 if > 1.0 and return 1.0 - failure if < 1.0
	if (failure > 1.0f)
		return 0;
	else
		return (1.0f - failure);
}

int CraftingManagerImplementation::calculateAssemblyFailureRate(Player* player,
		CraftingTool* craftingTool, float assemblyPoints) {

	// Here we take the standard failure rate(From the equation below), and add a rate from 0-15% based on the
	// Negative value of the crafting tool.  Positive values have no effect

	float effectiveness = 1.0f + (craftingTool->getToolEffectiveness() / 100);

	if (effectiveness > 0)
		effectiveness = 0;

	int failureRate = int(round((((2.68 / getLog(assemblyPoints + 5.2)) - .89)
			* 100) + effectiveness));

	if (failureRate < 0)
		failureRate = 0;

	return failureRate;

}

float CraftingManagerImplementation::calculateAssemblyModifier(
		CraftingTool* craftingTool) {

	// Using the tools effectiveness, we return a modifier
	float effectiveness = 1.0f + (craftingTool->getToolEffectiveness() / 100);

	return effectiveness;

}

float CraftingManagerImplementation::calculateAssemblyValueModifier(
		CraftingTool* craftingTool) {

	int assembly = craftingTool->getAssemblyResults();

	float results = ((3.4 / getLog(assembly + 4)) - 1.1111);

	// Unles we want amazing assemblies to get a bonus, we cap the madifier at 1

	if (results > 1.00) {

		if (results < 1.05) {

			results = 1.0f;

		} else {

			results = 1.2f;

		}

	}

	return results;

}

float CraftingManagerImplementation::getLog(float value) {

	return (log10(value) / log10(CONSTE));

}

float CraftingManagerImplementation::calculateExperimentationValueModifier(
		int assemblyResult, int pointsAttempted, float failure) {

	// Make it so failure detract

	float results;

	switch (assemblyResult) {

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

	DraftSchematicIngredient* ingredient;
	TangibleObject* tano;

	int stat = 0;
	int n = 0;
	int nsum = 0;
	int combineType = 0;
	float weightedAverage = 0;

	if (draftSchematic->getIngredientListSize() != craftingTool->getSlotCount()) {
		info(
				"Error in sizes in CraftingManagerImplementation::getWeightedValue.  This is very bad");
		player->sendSystemMessage(
				"Error in sizes in CraftingManagerImplementation::getWeightedValue.  This is very bad");
		return 0.0f;
	}

	for (int i = 0; i < draftSchematic->getIngredientListSize(); ++i) {

		ingredient = draftSchematic->getIngredient(i);
		tano = craftingTool->getIngredientInSlot(i);
		combineType = ingredient->getCombineType();

		switch (combineType) {
		case RESOURCE:
			n = ingredient->getResourceQuantity();
			stat = lookUpResourceAttribute(player, tano, type, i);

			if (stat != 0) {

				nsum += n;
				weightedAverage += (stat * n);

			}
			break;
		case COMPONENTLINEAR:
		case COMPONENTPERCENTAGE:
			break;

		}
	}

	if (weightedAverage != 0)
		weightedAverage /= float(nsum);

	return weightedAverage;
}

float CraftingManagerImplementation::getAssemblyPercentage(float value) {

	float percentage = (value * (0.000015f * value + .015f)) * 0.01f;

	return percentage;
}

int CraftingManagerImplementation::lookUpResourceAttribute(Player* player,
		TangibleObject* tano, int type, int slot) {

	if (tano == NULL)
		return 0;

	if (!tano->isResource())
		return 0;

	ResourceContainer* rcno = (ResourceContainer*) tano;

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
String& CraftingManagerImplementation::generateCraftedSerial() {

	StringBuffer ss;
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

	generatedSerial = ss.toString();
	return generatedSerial;
}

/*void CraftingManagerImplementation::WriteDraftSchematicToDB(DraftSchematic* draftSchematic) {
 try {
 StringBuffer query;
 query << "INSERT INTO `draft_schematics` "
 << "(`object_id`,`name`,`object_crc`, `group_name`)"
 << " VALUES(" << draftSchematic->getObjectID() << ",'\\" << draftSchematic->getName().toCharArray() << "',"
 << draftSchematic->getObjectCRC() << ",'" << draftSchematic->getGroupName() << "'," << ")";

 ServerDatabase::instance()->executeStatement(query);

 draftSchematic->setPersistent(true);
 } catch (DatabaseException& e) {
 System::out << e.getMessage() << "\n";
 }
 }*/

void CraftingManagerImplementation::addDraftSchematicsFromGroupName(
		Player* player, const String& schematicGroupName) {
	lock();

	if (draftSchematicsMap.contains(schematicGroupName)) {
		DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);

		if (dsg != NULL) {
			for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
				DraftSchematic* draftSchematic = dsg->getDraftSchematic(i);

				player->addDraftSchematic(draftSchematic);

				/*PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(player->getPlayerObject());
				msg->addDraftSchematic(draftSchematic);
				msg->close();
				player->sendMessage(msg);

				draftSchematic->sendIngredientsToPlayer(player);
				draftSchematic->sendExperimentalPropertiesToPlayer(player);*/
			}

			PlayerObjectDeltaMessage9* msg =
					new PlayerObjectDeltaMessage9(player->getPlayerObject());
			msg->updateDraftSchematics();
			msg->close();
			player->sendMessage(msg);
		}
	}

	unlock();
}

void CraftingManagerImplementation::subtractDraftSchematicsFromGroupName(
		Player* player, const String& schematicGroupName) {
	lock();

	if (draftSchematicsMap.contains(schematicGroupName)) {
		DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);

		if (dsg != NULL) {
			for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
				DraftSchematic* draftSchematic = dsg->getDraftSchematic(i);

				player->subtractDraftSchematic(draftSchematic);

				/*PlayerObjectDeltaMessage9* msg = new PlayerObjectDeltaMessage9(player->getPlayerObject());
				msg->removeDraftSchematic(draftSchematic);
				msg->close();

				player->sendMessage(msg);*/
			}
			PlayerObjectDeltaMessage9* msg =
					new PlayerObjectDeltaMessage9(player->getPlayerObject());
			msg->updateDraftSchematics();
			msg->close();
			player->sendMessage(msg);
		}
	}



	unlock();
}

void CraftingManagerImplementation::refreshDraftSchematics(Player* player) {
	lock();

	for (int i = 0; i < draftSchematicsMap.size(); ++i) {
		DraftSchematicGroup* dsg = draftSchematicsMap.get(i);

		for (int j = 0; j < dsg->getSizeOfDraftSchematicList(); ++j) {

			if (dsg != NULL) {

				DraftSchematic* draftSchematic = dsg->getDraftSchematic(j);
				player->subtractDraftSchematic(draftSchematic);

				player->addDraftSchematic(draftSchematic);

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
 String craftingBonus = getFloatParameter(L);

 runFile("scripts/crafting/" + filename, L);

 return 0;
 }*/

int CraftingManagerImplementation::addDraftSchematicToServer(lua_State *L) {
	LuaObject schematic(L);

	String objectName = "";

	if (!schematic.isValidTable())
		return 1;

	try {

		instance->lock();

		// The objName is the name you want the object to have
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objName could be "A Droid Battery"
		objectName = schematic.getStringField("objectName");

		String stfName = schematic.getStringField("stfName");

		// The objTemplateCRC is the CRC value of the object using it's .iff file
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objCRC would be 0xD1207EFF
		uint32 objCRC = schematic.getIntField("objectCRC");

		// The groupName will be used as the key to return a list of schematics with that groupName
		// example: "craftArtisanNewbieGroupA" (this is one groupName from Novice Artisan)
		// this groupName will include, CDEF Carbine, CDEF Rifle, Bofa Treat, etc...
		String groupName = schematic.getStringField("groupName");

		// The number that tells the client which crafting tool tab to put the draftSchematic in
		int craftingToolTab = schematic.getIntField("craftingToolTab");

		// The objID is two of the crc combined to make a uint64
		uint32 schematicID = objCRC;

		// The complexity will give a number that will correspond to which level of crafting tools and or
		// crafting stations are required
		uint32 complexity = schematic.getIntField("complexity");

		// I have no idea what the schematicSize is used for :D, but it's a part of all draft schematics
		uint32 schematicSize = schematic.getIntField("size");

		DraftSchematic* draftSchematic = new DraftSchematic(schematicID,
				objectName, stfName, objCRC, groupName, complexity, schematicSize,
				craftingToolTab);

		String xptype = schematic.getStringField("xpType");
		draftSchematic->setXpType(xptype);

		int xp = schematic.getIntField("xp");
		draftSchematic->setXp(xp);

		String assemblySkill = schematic.getStringField("assemblySkill");
		draftSchematic->setAssemblySkill(assemblySkill);

		String experimentingSkill = schematic.getStringField(
				"experimentingSkill");
		draftSchematic->setExperimentingSkill(experimentingSkill);

		// Parse the Ingredient data of DraftSchematic from LUA
		// example: craft_food_ingredients_n, craft_food_ingredients_n, craft_food_ingredients_n
		String unparIngredientTemplateNames = schematic.getStringField(
				"ingredientTemplateNames");
		Vector<String> parsedIngredientTemplateNames =
				instance->parseStringsFromString(unparIngredientTemplateNames);

		// example: dried Fruit, crust, additive
		String unparIngredientTitleNames = schematic.getStringField(
				"ingredientTitleNames");
		Vector<String> parsedIngredientTitleNames =
				instance->parseStringsFromString(unparIngredientTitleNames);

		// example: 2 for identical, 1 for optional, 0 for mandatory
		String unparOptionalFlags = schematic.getStringField(
				"ingredientSlotType");
		Vector<uint32> parsedOptionalFlags =
				instance->parseUnsignedInt32sFromString(unparOptionalFlags);

		// example: organic, cereal, object/tangible/food/crafted/additive/shared_additive_light.iff
		String unparResourceTypes = schematic.getStringField("resourceTypes");
		Vector<String> parsedResourceTypes = instance->parseStringsFromString(
				unparResourceTypes);

		// example: 3,8,1
		String unparResourceQuantities = schematic.getStringField(
				"resourceQuantities");
		Vector<uint32>
				parsedResourceQuantities =
						instance->parseUnsignedInt32sFromString(
								unparResourceQuantities);

		// example: 1,2,3
		String unparCombineTypes = schematic.getStringField("combineTypes");
		Vector<uint32> parsedCombineTypes =
				instance->parseUnsignedInt32sFromString(unparCombineTypes);

		// example: 1,2,3
		String unparContribution = schematic.getStringField("contribution");
		Vector<uint32> parsedContribution =
				instance->parseUnsignedInt32sFromString(unparContribution);

		// Add resource requirement sets to schematic
		// Each vector just parsed should all have the same .size() so any .size() will work
		// for the amount of times the loop should execute
		for (int i = 0; i < parsedIngredientTemplateNames.size(); i++) {
			draftSchematic->addIngredient(parsedIngredientTemplateNames.get(i),
					parsedIngredientTitleNames.get(i),
					parsedOptionalFlags.get(i), parsedResourceTypes.get(
							i), parsedResourceQuantities.get(i),
					parsedCombineTypes.get(i), parsedContribution.get(i));
		}

		// Parse Experimental Properties of Draft Schematic from DB
		// example: 1, 1, 1, 2, 2, 2, 2
		String unparNumberExperimentalProperties = schematic.getStringField(
				"numberExperimentalProperties");
		Vector<uint32> parsedNumberExperimentalProperties =
				instance->parseUnsignedInt32sFromString(
						unparNumberExperimentalProperties);

		// example: XX, XX, XX, OQ, PE, FL, OQ, DR, PE, DR, OQ
		String unparExperimentalProperties = schematic.getStringField(
				"experimentalProperties");
		Vector<String> parsedExperimentalProperties =
				instance->parseStringsFromString(unparExperimentalProperties);

		// example: 0, 0, 0, 1, 2, 2, 1, 1, 3, 3, 1
		String unparExperimentalWeights = schematic.getStringField(
				"experimentalWeights");
		Vector<uint32> parsedExperimentalWeights =
				instance->parseUnsignedInt32sFromString(
						unparExperimentalWeights);

		// example: exp_filling, exp_flavor, exp_nutrition, exp_quantity
		String unparExperimentalGroupTitles = schematic.getStringField(
				"experimentalGroupTitles");
		Vector<String> parsedExperimentalGroupTitles =
				instance->parseStringsFromString(unparExperimentalGroupTitles);

		String unparExperimentalSubGroupTitles = schematic.getStringField(
				"experimentalSubGroupTitles");
		Vector<String> parsedExperimentalSubGroupTitles =
				instance->parseStringsFromString(
						unparExperimentalSubGroupTitles);

		// Set associated exp property
		String unparExperimentalMinToSet = schematic.getStringField(
				"experimentalMin");
		Vector<float> parsedExperimentalMinToSet =
				instance->parseFloatsFromString(unparExperimentalMinToSet);

		// Set associated exp property
		String unparExperimentalMaxToSet = schematic.getStringField(
				"experimentalMax");
		Vector<float> parsedExperimentalMaxToSet =
				instance->parseFloatsFromString(unparExperimentalMaxToSet);

		// Set associated precision
		String unparExperimentalPrecisionToSet = schematic.getStringField(
				"experimentalPrecision");
		Vector<int> parsedExperimentalPrecisionToSet =
				instance->parseInt32sFromString(unparExperimentalPrecisionToSet);

		// Add experimental properties groups to the draft schematic
		uint32 weightIterator = 0;
		String subtitle = "";
		for (uint32 i = 0; i < parsedNumberExperimentalProperties.size(); i++) {
			for (uint32 j = 0; j < parsedNumberExperimentalProperties.get(i); j++) {

				draftSchematic->addExperimentalProperty(i,
						parsedExperimentalProperties.get(weightIterator),
						parsedExperimentalWeights.get(weightIterator),
						parsedExperimentalGroupTitles.get(i),
						parsedExperimentalSubGroupTitles.get(i),
						parsedExperimentalMinToSet.get(i),
						parsedExperimentalMaxToSet.get(i),
						parsedExperimentalPrecisionToSet.get(i));
				weightIterator++;
			}
		}

		// Save schematics tano attributes
		String tanoAttributes = schematic.getStringField("tanoAttributes");
		draftSchematic->setTanoAttributes(tanoAttributes);

		// Set Customization options
		String unparCustomizationOptions = schematic.getStringField(
				"customizationOptions");
		Vector<String> parsedCustomizationOptions =
				instance->parseStringsFromString(unparCustomizationOptions);

		// Set Default Customization values
		String unparCustomizationValues = schematic.getStringField(
				"customizationDefaults");
		Vector<uint32> parsedCustomizationValues =
				instance->parseUnsignedInt32sFromString(unparCustomizationValues);

		for (int i = 0; i < parsedCustomizationOptions.size(); ++i) {
			draftSchematic->addCustomizationOption(parsedCustomizationOptions.get(i),
					parsedCustomizationValues.get(i));
		}

		// Save schematics tano attributes
		String customizationSkill = schematic.getStringField("customizationSkill");
		draftSchematic->setCustomizationSkill(customizationSkill);


		instance->mapDraftSchematic(draftSchematic);
		instance->unlock();
	} catch (...) {

		System::out << "Failed to load " << objectName << endl;
		instance->unlock();

	}

	return 0;
}

void CraftingManagerImplementation::mapDraftSchematic(
		DraftSchematic* draftSchematic) {
	String groupName = draftSchematic->getGroupName();
	if (!draftSchematicsMap.contains(groupName)) {
		DraftSchematicGroup* dsg = new DraftSchematicGroup();

		dsg->addDraftSchematic(draftSchematic);

		draftSchematicsMap.put(groupName, dsg);
	} else
		draftSchematicsMap.get(draftSchematic->getGroupName())->addDraftSchematic(
				draftSchematic);
}

int CraftingManagerImplementation::runDraftSchematicFile(lua_State* L) {
	String filename = getStringParameter(L);

	runFile("scripts/crafting/" + filename, L);

	return 0;
}

Vector<String> CraftingManagerImplementation::parseStringsFromString(
		const String& unparsedStrings) {
	StringBuffer parseHelper;
	Vector<String> parsedStrings;

	for (int i = 0; i < unparsedStrings.length(); i++) {
		char currentChar = unparsedStrings.charAt(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				parsedStrings.add(parseHelper.toString());

				parseHelper.deleteAll();
			} else {
				parseHelper.append(currentChar);
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	parsedStrings.add(parseHelper.toString());

	return parsedStrings;
}

Vector<uint32> CraftingManagerImplementation::parseUnsignedInt32sFromString(
		const String& unparsedInts) {
	StringBuffer parseHelper;
	Vector<uint32> parsedInts;

	for (int i = 0; i < unparsedInts.length(); i++) {
		char currentChar = unparsedInts.charAt(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				uint32 resourceQuantity = (uint32) Integer::valueOf(parseHelper.toString());
				parsedInts.add(resourceQuantity);

				parseHelper.deleteAll();
			} else {
				parseHelper.append(currentChar);
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	uint32 resourceQuantity = (uint32) Integer::valueOf(parseHelper.toString());
	parsedInts.add(resourceQuantity);

	return parsedInts;
}

Vector<int> CraftingManagerImplementation::parseInt32sFromString(
		const String& unparsedInts) {
	StringBuffer parseHelper;
	Vector<int> parsedInts;

	for (int i = 0; i < unparsedInts.length(); i++) {
		char currentChar = unparsedInts.charAt(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				int resourceQuantity = (int) Integer::valueOf(parseHelper.toString());
				parsedInts.add(resourceQuantity);

				parseHelper.deleteAll();
			} else {
				parseHelper.append(currentChar);
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	int resourceQuantity = (int) Integer::valueOf(parseHelper.toString());
	parsedInts.add(resourceQuantity);

	return parsedInts;
}

Vector<float> CraftingManagerImplementation::parseFloatsFromString(
		const String& unparsedFloats) {
	StringBuffer parseHelper;
	Vector<float> parsedFloats;

	for (int i = 0; i < unparsedFloats.length(); i++) {
		char currentChar = unparsedFloats.charAt(i);

		if (currentChar != ' ') {
			if (currentChar == ',') {
				float resourceQuantity = (float) Float::valueOf(parseHelper.toString());
				parsedFloats.add(resourceQuantity);

				parseHelper.deleteAll();
			} else {
				parseHelper.append(currentChar);
			}
		}
	}

	// The last template name has to be added because it was not added during the loop
	float resourceQuantity = (float) Float::valueOf(parseHelper.toString());
	parsedFloats.add(resourceQuantity);

	return parsedFloats;
}
