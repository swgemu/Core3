/*
 * CraftingSessionImplementation.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Kyle
 */

#include "CraftingSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/managers/crafting/CraftingManager.h"

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"

#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"

#include "server/zone/objects/player/sessions/crafting/events/CreateObjectTask.h"
#include "server/zone/objects/player/sessions/crafting/events/UpdateToolCountdownTask.h"

int CraftingSessionImplementation::initializeSession(CraftingTool* tool, CraftingStation* station) {

	craftingTool = tool;
	craftingStation = station;

	crafter->addActiveSession(SessionFacadeType::CRAFTING, _this);
	craftingTool->addActiveSession(SessionFacadeType::CRAFTING, _this);

	craftingManager = crafter->getZoneServer()->getCraftingManager();

	experimentationPointsTotal = 0;
	experimentationPointsUsed = 0;

	return startSession();
}

int CraftingSessionImplementation::startSession() {
	// crafter and craftingTool locked already in initializeSession
	if(crafter == NULL || craftingTool == NULL) {
		cancelSession();
		return false;
	}

	/// Get current allowed complexity
	PlayerObject* playerObject = crafter->getPlayerObject();
	int complexityLevel = craftingTool->getComplexityLevel();

	if (craftingStation != NULL)
		complexityLevel = craftingStation->getComplexityLevel();

	/// Get filtered schematic list based on tool type and complexity
	currentSchematicList.removeAll();

	currentSchematicList =
			playerObject->filterSchematicList(crafter,
			craftingTool->getToolTabs(), complexityLevel);

	/// DPlay9 ***********************************
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(playerObject);
	dplay9->setExperimentationEnabled(craftingStation != NULL);
	dplay9->setCraftingState(1);

	if (craftingStation != NULL)
		dplay9->setClosestCraftingStation(craftingStation->getObjectID());
	else
		dplay9->setClosestCraftingStation(0);

	dplay9->setExperimentationPoints(experimentationPointsTotal);
	dplay9->close();
	crafter->sendMessage(dplay9);
	// End dplay9***********************************

	/// Object Controller Message 102 - Schematic List
	ObjectControllerMessage* ocm = new ObjectControllerMessage(
			crafter->getObjectID(), 0x0B, 0x102);

	ocm->insertLong(craftingTool->getObjectID());

	if (craftingStation != NULL)
		ocm->insertLong(craftingStation->getObjectID());
	else
		ocm->insertLong(0);

	ocm->insertInt(currentSchematicList.size());
	for (int i = 0; i < currentSchematicList.size(); ++i) {

		DraftSchematic* draftSchematic = currentSchematicList.get(i).get();

		ocm->insertInt(draftSchematic->getClientObjectCRC());
		ocm->insertInt(draftSchematic->getClientObjectCRC());
		ocm->insertInt(draftSchematic->getToolTab()); // this number decides what tab the schematic goes in (ex: 4 = food tab in crafting window)
	}
	crafter->sendMessage(ocm);
	/// ***********************************************

	/// Send all the ingredients to the player
	for (int i = 0; i < currentSchematicList.size(); ++i) {

		DraftSchematic* draftSchematic = currentSchematicList.get(i).get();

		/// Object Controller Message 1BF
		draftSchematic->sendDraftSlotsTo(crafter);
		// End OBJC 1BF***********************************
	}

	/// Send all the experimental properties to the player
	for (int i = 0; i < currentSchematicList.size(); ++i) {

		DraftSchematic* draftSchematic = currentSchematicList.get(i).get();

		/// Object Controller Message 207
		draftSchematic->sendResourceWeightsTo(crafter);
		// End OBJC 207***********************************
	}

	/// Reset session state
	state = 1;

	return true;
}

int CraftingSessionImplementation::cancelSession() {

	if(craftingTool != NULL)
		craftingTool->dropActiveSession(SessionFacadeType::CRAFTING);

	if (crafter != NULL) {
		crafter->dropActiveSession(SessionFacadeType::CRAFTING);
		// DPlay9 *****************************
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				crafter->getPlayerObject());
		dplay9->setCraftingState(0);
		dplay9->close();
		crafter->sendMessage(dplay9);
		// *************************************
	}

	return clearSession();
}

int CraftingSessionImplementation::clearSession() {

	if (manufactureSchematic != NULL) {

		Locker locker(manufactureSchematic);

		if (manufactureSchematic->getParent() == craftingTool) {
			manufactureSchematic->setDraftSchematic(NULL);
			manufactureSchematic->cleanupIngredientSlots(crafter);
			manufactureSchematic->destroyObjectFromWorld(true);
		}

		manufactureSchematic = NULL;
	}

	Locker locker2(craftingTool);

	// Remove all items that aren't the prototype
	while (craftingTool->getContainerObjectsSize() > 1) {
		craftingTool->getContainerObject(1)->destroyObjectFromWorld(true);
	}


	if (prototype != NULL) {

		Locker locker3(prototype);

		if (craftingTool->isReady()) {

			if (prototype->getParent() == craftingTool) {
				prototype->destroyObjectFromWorld(true);
			}
			prototype = NULL;
		}
	}
	return 0;
}

void CraftingSessionImplementation::closeCraftingWindow(int clientCounter) {

	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(1);
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);

	objMsg = new ObjectControllerMessage(crafter->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(0);
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);

	objMsg = new ObjectControllerMessage(crafter->getObjectID(), 0x1B, 0x01C2);
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);
}

void CraftingSessionImplementation::sendSlotMessage(int counter, int message) {

	// Object Controller ********************************************
	// Send Bad Slot message
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x107);
	objMsg->insertInt(message);
	objMsg->insertByte(counter);

	crafter->sendMessage(objMsg);
	//End Object Controller ******************************************
}

void CraftingSessionImplementation::selectDraftSchematic(int index) {

	if (index >= currentSchematicList.size()) {
		StringBuffer message;
		message << "Selected draft schematic is out of range, index = "
				<< index << " Schematic List size = "
				<< currentSchematicList.size();
		crafter->sendSystemMessage(message.toString());
		error(message.toString());
		closeCraftingWindow(1);
		cancelSession();
		return;
	}

	DraftSchematic* draftschematic = currentSchematicList.get(index);

	if (draftschematic == NULL) {
		crafter->sendSystemMessage("@ui_craft:err_no_draft_schematic");
		closeCraftingWindow(1);
		cancelSession();
		return;
	}

	clearSession();

	state = 2;

	Locker locker(craftingTool);

	if (createSessionObjects(draftschematic)) {

		if (prototype == NULL) {
			crafter->sendSystemMessage("@ui_craft:err_no_prototype");
			return;
		}

		// Dplay9 ********************************************************
		// Sets the Crafting state to 2, which is the Resource screen
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				crafter->getPlayerObject());
		dplay9->setExperimentationPoints(0xFFFFFFFF);
		dplay9->setCraftingState(2);
		dplay9->close();

		crafter->sendMessage(dplay9);
		// End Dplay9 *****************************************************

		// Dtano3 ********************************************************
		// Update Condition Damage
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(
				prototype);
		dtano3->updateConditionDamage();
		dtano3->close();
		crafter->sendMessage(dtano3);
		// End Dtano3 *****************************************************

	} else {
		crafter->sendSystemMessage("This type of object has not yet been implemented");
	}
}

bool CraftingSessionImplementation::createSessionObjects(DraftSchematic* draftSchematic) {

	if (createManufactureSchematic(draftSchematic))
		return createPrototypeObject(draftSchematic);
	else
		return false;
}

bool CraftingSessionImplementation::createManufactureSchematic(DraftSchematic* draftschematic) {

	manufactureSchematic =
			cast<ManufactureSchematic*> (draftschematic->createManufactureSchematic(craftingTool));

	if (manufactureSchematic == NULL) {
		crafter->sendSystemMessage("@ui_craft:err_no_manf_schematic");
		closeCraftingWindow(1);
		cancelSession();
		return false;
	}

	craftingTool->transferObject(manufactureSchematic, 0x4, true);
	//manufactureSchematic->sendTo(crafter, true);

	return true;
}

bool CraftingSessionImplementation::createPrototypeObject(DraftSchematic* draftschematic) {

	// Remove all items, incase there are any
	while (craftingTool->getContainerObjectsSize() > 0) {
		craftingTool->getContainerObject(0)->destroyObjectFromWorld(true);
	}

	prototype = cast<TangibleObject*> (crafter->getZoneServer()->createObject(
			draftschematic->getTanoCRC(), 0));

	if (prototype == NULL) {
		crafter->sendSystemMessage("@ui_craft:err_no_prototype");
		closeCraftingWindow(1);
		cancelSession();
		return false;
	}

	prototype->createChildObjects();

	craftingTool->transferObject(prototype, -1, false);
	prototype->sendTo(crafter, true);

	return true;
}

void CraftingSessionImplementation::sendIngredientForUIListen() {
	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x0103);
	objMsg->insertLong(craftingTool->getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(manufactureSchematic->getObjectID());// Manufacture Schematic Object ID
	objMsg->insertLong(prototype->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(2);
	objMsg->insertByte(1);

	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
	int draftSlotCount = draftSchematic->getDraftSlotCount();
	objMsg->insertInt(draftSlotCount);

	// Send all the ingredient data
	for (int i = 0; i < draftSlotCount; i++) {
		DraftSlot* slot = draftSchematic->getDraftSlot(i);

		if (slot != NULL)
			slot->insertToMessage(objMsg);
	}
	objMsg->insertShort(0);

	crafter->sendMessage(objMsg);
}

void CraftingSessionImplementation::addIngredient(TangibleObject* tano, int slot, int clientCounter) {

	if (crafter == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALID);
		return;
	}

	if (manufactureSchematic == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	if (tano == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALIDINGREDIENT);
		return;
	}

	SceneObject* inventory = crafter->getSlottedObject("inventory");
	if (inventory == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOINVENTORY);
		return;
	}

	/// Check if item is on the player, but not in a crafting tool
	/// Or if the item is in a crafting station to prevent some duping
	if(!tano->isASubChildOf(crafter) && (craftingStation == NULL || !tano->isASubChildOf(craftingStation))) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALIDINGREDIENT);
		return;
	}

	int result = manufactureSchematic->addIngredientToSlot(crafter, tano, slot);

	sendSlotMessage(clientCounter, result);

}

void CraftingSessionImplementation::removeIngredient(TangibleObject* tano, int slotUpdated, int clientCounter) {
	if (crafter == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALID);
		return;
	}

	if (manufactureSchematic == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	if (tano == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALIDINGREDIENT);
		return;
	}

	SceneObject* inventory = crafter->getSlottedObject("inventory");
	if (inventory == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOINVENTORY);
		return;
	}

	int result = manufactureSchematic->removeIngredientFromSlot(crafter, tano, slotUpdated);

	if(result == IngredientSlot::OK) {
		// Object Controller ********************************************
		// Updates the screen with the resource removal
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(
				crafter->getObjectID(), 0x1B, 0x010C);
		objMsg->insertInt(0x108);
		objMsg->insertInt(0);
		objMsg->insertByte(clientCounter);

		crafter->sendMessage(objMsg);
		// End Object Controller *****************************************
	}
}

void CraftingSessionImplementation::nextCraftingStage(int clientCounter) {

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	// Make sure all the require resources are there, if not, return them to inventory and close tool
	if (!manufactureSchematic->isReadyForAssembly()) {

		closeCraftingWindow(clientCounter);

		cancelSession();

		return;
	}

	Locker locker(manufactureSchematic);

	manufactureSchematic->setAssembled();

	if (state == 2) {

		// Flag to get the experimenting window
		if (craftingStation != NULL)
			// Assemble with Experimenting
			state = 3;

		else
			// Assemble without Experimenting
			state = 4;

		initialAssembly(clientCounter);

	} else if (state == 3) {

		finishAssembly(clientCounter);

	} else if (state == 5) {

		finishStage1(clientCounter);

	} else if (state == 6) {

		finishStage2(clientCounter);
	}
}

void CraftingSessionImplementation::initialAssembly(int clientCounter) {

	// Get the appropriate number of Experimentation points from Skill
	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	// Set crafter
	manufactureSchematic->setCrafter(crafter);

	String expskill = draftSchematic->getExperimentationSkill();
	experimentationPointsTotal = int(crafter->getSkillMod(expskill) / 10);
	experimentationPointsUsed = 0;

	// Calculate exp failure for red bars
	int experimentalFailureRate = craftingManager->calculateExperimentationFailureRate(crafter, manufactureSchematic, 0);

	// Get the level of customization
	String custskill = draftSchematic->getCustomizationSkill();
	int custpoints = int(crafter->getSkillMod(custskill));

	// Start DPLAY9 ***********************************************************
	// Updates the stage of crafting, sets the number of experimentation points
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(crafter->getPlayerObject());
	dplay9->setCraftingState(state); // 3 If Experimenting is active, 4 if already experimented/ No experimenting
	dplay9->setExperimentationPoints(experimentationPointsTotal);
	dplay9->close();

	crafter->sendMessage(dplay9);
	// End DPLAY9 *************************************************************

	// Determine the outcome of the craft, Amazing through Critical
	assemblyResult = craftingManager->calculateAssemblySuccess(crafter,
			draftSchematic, craftingTool->getEffectiveness());

	Locker locker(prototype);
	//Set initial crafting percentages
	prototype->setInitialCraftingValues(manufactureSchematic);

	Reference<CraftingValues*> craftingValues = manufactureSchematic->getCraftingValues();
	craftingValues->setManufactureSchematic(manufactureSchematic);
	craftingValues->setPlayer(crafter);

	// Set Crafter name and generate serial number
	String name = crafter->getFirstName();
	prototype->setCraftersName(name);

	String serial = craftingManager->generateSerial();
	prototype->setSerialNumber(serial);

	// Update the prototype with new values
	prototype->updateCraftingValues(craftingValues, true);

	// Set default customization
	Vector < byte >* customizationOptions
			= draftSchematic->getCustomizationOptions();
	Vector < byte >* customizationDefaultValues
			= draftSchematic->getCustomizationDefaultValues();

	for (int i = 0; i < customizationOptions->size(); ++i) {
		prototype->setCustomizationVariable(customizationOptions->get(i), customizationDefaultValues->get(i));
	}

	// Start DMSCO3 ***********************************************************
	// Sends the updated values to the crafting screen
	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(manufactureSchematic);
	dMsco3->updateCraftingValues(manufactureSchematic);
	dMsco3->close();

	crafter->sendMessage(dMsco3);
	// End DMSCO3 *************************************************************

	// Start DMSCO7 ***********************************************************
	// Sends the experimental properties and experimental percentages
	ManufactureSchematicObjectDeltaMessage7* dMsco7 =
			new ManufactureSchematicObjectDeltaMessage7(manufactureSchematic);

	dMsco7->updateForAssembly(manufactureSchematic, experimentalFailureRate);
	if (custpoints > 0)
		dMsco7->updateCustomizationOptions(manufactureSchematic, custpoints);

	dMsco7->close();

	crafter->sendMessage(dMsco7);
	// End DMSCO7 *************************************************************

	// Start DTANO3 ***********************************************************
	// Updates the Complexity and the condition
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(
			prototype);
	dtano3->updateComplexity(manufactureSchematic->getComplexity());
	dtano3->updateMaxCondition();
	dtano3->close();

	crafter->sendMessage(dtano3);
	// End DTANO3 *************************************************************


	// Start Object Controller *******************************************
	// Send the results
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x01BE);
	objMsg->insertInt(0x109);

	objMsg->insertInt(assemblyResult); // Assembly Results

	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);
	// End Object Controller ******************************************

	// If the window is closed now, this sets the resources to no be recoverable
	manufactureSchematic->setAssembled();

	// Remove all resources - Not recovering them
	if (assemblyResult == CraftingManager::CRITICALFAILURE) {

		createPrototypeObject(draftSchematic);

		state = 2;

		// re-setup the slots and ingredients
		manufactureSchematic->synchronizedUIListen(crafter, 0);

		// Start Dplay9 **************************************
		// Reset crafting state
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				crafter->getPlayerObject());
		dplay9->setExperimentationPoints(0xFFFFFFFF);
		dplay9->setCraftingState(state);

		dplay9->close();

		crafter->sendMessage(dplay9);
		// End DPLAY9 ****************************************

	} else {

		PlayerObject* ghost = cast<PlayerObject*> (crafter->getSlottedObject("ghost"));
		if (ghost == NULL)
			return;

		ghost->decreaseSchematicUseCount(draftSchematic);

	}
}

void CraftingSessionImplementation::finishAssembly(int clientCounter) {

	// Start Dplay9 **************************************
	// Move crafting to State 4
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			crafter->getPlayerObject());
	dplay9->setCraftingState(4);
	state = 4;
	dplay9->close();

	crafter->sendMessage(dplay9);
	// End DPLAY9

	// Start Object Controller **************************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);

	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);
	// End Object Controller **************************************
}

void CraftingSessionImplementation::experiment(int rowsAttempted, const String& expAttempt, int clientCounter) {

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	Locker locker(craftingTool);
	Locker locker2(manufactureSchematic);

	StringTokenizer tokenizer(expAttempt);

	int rowEffected, pointsAttempted, failure;
	int lowestExpSuccess = 0;

	//lastExperimentationTimestamp = Time::currentNanoTime();

	Reference<CraftingValues*> craftingValues = manufactureSchematic->getCraftingValues();
	craftingValues->clear();

	// Loop through all the lines of experimentation
	for (int i = 0; i < rowsAttempted; ++i) {

		rowEffected = tokenizer.getIntToken();
		pointsAttempted = tokenizer.getIntToken();

		experimentationPointsUsed += pointsAttempted;

		// Each line gets it's own rolls
		// Calcualte a new failure rate for each line of experimentation
		failure = craftingManager->calculateExperimentationFailureRate(crafter,
				manufactureSchematic, pointsAttempted);

		if (experimentationPointsUsed <= experimentationPointsTotal) {
			// Set the experimentation result ie:  Amazing Success
			experimentationResult = craftingManager->calculateExperimentationSuccess(
					crafter, manufactureSchematic->getDraftSchematic(), failure);
		} else {
			// If this code is reached, they have likely tried to hack to
			// get more experimenting points, so lets just give them a failure
			experimentationResult = CraftingManager::CRITICALFAILURE;
		}

		// Make sure to store the lowest roll to display (Effect the multiline rolls
		if (lowestExpSuccess < experimentationResult)
			lowestExpSuccess = experimentationResult;

		manufactureSchematic->increaseComplexity();

		// Do the experimenting - sets new percentages
		craftingManager->experimentRow(craftingValues, rowEffected,
				pointsAttempted, failure, experimentationResult);

	}

	manufactureSchematic->setExperimentingCounter(
			manufactureSchematic->getExperimentingCounter() + rowsAttempted);

	// Use percentages to recalculate the values
	craftingValues->recalculateValues(false);

	// Update the Tano with new values
	prototype->updateCraftingValues(manufactureSchematic->getCraftingValues(), false);

	// Sets the result for display
	experimentationResult = lowestExpSuccess;

	// Start Player Object Delta **************************************
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			crafter->getPlayerObject());
	dplay9->setExperimentationPoints(experimentationPointsTotal
			- experimentationPointsUsed);
	dplay9->close();

	crafter->sendMessage(dplay9);
	// End Player Object Delta **************************************


	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(
					manufactureSchematic);
	dMsco3->updateComplexity(manufactureSchematic->getComplexity());
	dMsco3->updateCraftingValues(manufactureSchematic);
	dMsco3->close();

	crafter->sendMessage(dMsco3);

	ManufactureSchematicObjectDeltaMessage7* dMsco7 =
			new ManufactureSchematicObjectDeltaMessage7(
					manufactureSchematic);
	dMsco7->update9(manufactureSchematic, false);
	dMsco7->close();

	crafter->sendMessage(dMsco7);

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(
			prototype);
	dtano3->updateComplexity(float(manufactureSchematic->getComplexity()));
	dtano3->close();

	crafter->sendMessage(dtano3);

	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x0113);
	objMsg->insertInt(0x105);

	objMsg->insertInt(experimentationResult); // Experimentation Result
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);
}

void CraftingSessionImplementation::customization(const String& name, byte templateChoice, int schematicCount, const String& customizationString) {

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	//if(NameManager::instance()->isProfane(name)) {
	//	player->sendSystemMessage("Your selected name has been declined because it may contain inappropriate language.  Close the 'customizing' window and try again");
	//	return;
	//}

	Locker locker(craftingTool);
	Locker locker2(manufactureSchematic);

	if (templateChoice != 0xFF) {

		Reference<DraftSchematic*> draftSchematic =
				manufactureSchematic->getDraftSchematic();

		if (draftSchematic != NULL) {
			if (draftSchematic->getTemplateListSize() >= (int) templateChoice) {
				uint32 clientCRC = draftSchematic->getTemplate(
						(int) templateChoice).hashCode();
				prototype->setClientObjectCRC(clientCRC);

				prototype->sendDestroyTo(crafter);
				prototype->sendTo(crafter, true);
			}
		}
	}

	manufactureSchematic->setManufactureLimit(schematicCount);

	StringTokenizer tokenizer(customizationString);
	byte customizationindex, customizationvalue, customizationtype;

	//Database::escapeString(name);

	UnicodeString customName(name);
	prototype->setCustomObjectName(customName, false);

	/// Set Name
	manufactureSchematic->getObjectName()->setStringId(
			prototype->getObjectNameStringIdFile(),
			prototype->getObjectNameStringIdName());

	/// Set Manufacture Schematic Custom name
	if (!name.isEmpty())
		manufactureSchematic->setCustomObjectName(customName, false);

	Vector < byte > *customizationOptions
			= manufactureSchematic->getDraftSchematic()->getCustomizationOptions();

	while (tokenizer.hasMoreTokens()) {

		customizationindex = (byte) tokenizer.getIntToken();
		customizationtype = customizationOptions->get(customizationindex);

		customizationvalue = (byte) tokenizer.getIntToken();

		prototype->setCustomizationVariable(customizationtype,
				customizationvalue);
	}

	TangibleObjectDeltaMessage3* dtano3 =
			new TangibleObjectDeltaMessage3(prototype);
	dtano3->updateName(name);
	dtano3->updateCustomizationString();
	dtano3->close();

	crafter->sendMessage(dtano3);

	ManufactureSchematicObjectDeltaMessage3 * dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(
					manufactureSchematic);
	dMsco3->updateName(name);
	dMsco3->updateCondition(schematicCount);
	dMsco3->close();

	crafter->sendMessage(dMsco3);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x15A);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	crafter->sendMessage(objMsg);

	state = 5;
}

void CraftingSessionImplementation::finishStage1(int clientCounter) {

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			crafter->getPlayerObject());
	dplay9->setCraftingState(state);
	dplay9->close();

	crafter->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x01BE);
	objMsg->insertInt(0x109);
	objMsg->insertInt(4);
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);

	state = 6;
}

void CraftingSessionImplementation::finishStage2(int clientCounter) {

	state = 0;

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			crafter->getPlayerObject());
	dplay9->insertShort(5);
	dplay9->insertInt(0xFFFFFFFF);
	dplay9->setCraftingState(0);

	dplay9->close();
	crafter->sendMessage(dplay9);

	//Object Controller
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x10A);
	objMsg->insertInt(1);
	objMsg->insertByte(clientCounter);
	crafter->sendMessage(objMsg);
}

void CraftingSessionImplementation::createPrototype(int clientCounter, bool practice) {

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	Locker locker2(manufactureSchematic);

	if (manufactureSchematic->isAssembled()
			&& !manufactureSchematic->isCompleted()) {

		closeCraftingWindow(clientCounter);

		String xpType = manufactureSchematic->getDraftSchematic()->getXpType();
		int xp = manufactureSchematic->getDraftSchematic()->getXpAmount();

		if (practice != 0) {

			startCreationTasks(manufactureSchematic->getComplexity() * 2, false);

		} else {

			// This is for practiceing
			startCreationTasks(manufactureSchematic->getComplexity() * 2, true);
			xp *= 1.05f;
		}

		Reference<PlayerManager*> playerManager = crafter->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(crafter, xpType, xp, true);

		manufactureSchematic->setCompleted();

	} else {

		closeCraftingWindow(clientCounter);

		sendSlotMessage(clientCounter, IngredientSlot::WEIRDFAILEDMESSAGE);
	}
}


void CraftingSessionImplementation::startCreationTasks(int timer, bool pract) {

	int timer2 = 1;

	Reference<UpdateToolCountdownTask*> updateToolCountdownTask;
	Reference<CreateObjectTask*> createObjectTask = new CreateObjectTask(crafter, craftingTool);

	practice = pract;

	ManagedReference<ZoneServer*> server = crafter->getZoneServer();

	if (server != NULL) {

		Locker locker(craftingTool);
		craftingTool->setBusy();

		if(!practice)
			craftingTool->transferObject(prototype, -1, true);

		while (timer > 0) {
			updateToolCountdownTask = new UpdateToolCountdownTask(crafter,
					craftingTool, timer);
			updateToolCountdownTask->schedule(timer2);
			timer -= 5;
			timer2 += 5000;
		}

		if (timer < 0) {
			timer2 += (timer * 1000);
			timer = 0;
		}

		updateToolCountdownTask = new UpdateToolCountdownTask(crafter, craftingTool,
				timer);

		updateToolCountdownTask->schedule(timer2);
		createObjectTask->schedule(timer2);
	}
}

void CraftingSessionImplementation::createManufactureSchematic(int clientCounter) {

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	if (manufactureSchematic->isAssembled()
			&& !manufactureSchematic->isCompleted()) {

		//Object Controller
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(
				crafter->getObjectID(), 0x1B, 0x010C);
		objMsg->insertInt(0x10B);
		objMsg->insertInt(1);
		objMsg->insertByte(clientCounter);

		crafter->sendMessage(objMsg);

		ManagedReference<SceneObject*> datapad = crafter->getSlottedObject("datapad");

		prototype->destroyObjectFromWorld(0);

		manufactureSchematic->setPersistent(2);
		prototype->setPersistent(2);

		datapad->transferObject(manufactureSchematic, -1, true);
		manufactureSchematic->setPrototype(prototype);

	} else {

		closeCraftingWindow(clientCounter);

		sendSlotMessage(clientCounter, IngredientSlot::WEIRDFAILEDMESSAGE);
	}

}
