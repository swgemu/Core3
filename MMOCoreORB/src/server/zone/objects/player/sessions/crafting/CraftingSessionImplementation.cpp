/*
 * CraftingSessionImplementation.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/crafting/ComponentMap.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"

#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"

#include "server/zone/objects/player/sessions/crafting/events/CreateObjectTask.h"
#include "server/zone/objects/player/sessions/crafting/events/UpdateToolCountdownTask.h"

#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/templates/params/RangedIntCustomizationVariable.h"


int CraftingSessionImplementation::initializeSession(CraftingTool* tool, CraftingStation* station) {

	craftingTool = tool;
	craftingStation = station;

	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();

	crafter->addActiveSession(SessionFacadeType::CRAFTING, _this.get());
	craftingTool->addActiveSession(SessionFacadeType::CRAFTING, _this.get());

	craftingTool->setCountdownTimer(0, true);

	craftingTool->disperseItems();

	crafterGhost = crafter->getPlayerObject();

	craftingManager = crafter->getZoneServer()->getCraftingManager();

	experimentationPointsTotal = 0;
	experimentationPointsUsed = 0;

	return startSession();
}

int CraftingSessionImplementation::startSession() {
	// crafter and craftingTool locked already in initializeSession
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();

	if(crafter == NULL || craftingTool == NULL || crafterGhost == NULL) {
		cancelSession();
		return false;
	}

	/// Get current allowed complexity
	ManagedReference<PlayerObject*> playerObject = crafter->getPlayerObject();
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

	/// Reset session state
	state = 1;

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("*** Starting new crafting session ***");
	}

	return true;
}

int CraftingSessionImplementation::cancelSession() {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();

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

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("*** Canceling crafting session ***");
	}

	return clearSession();
}

int CraftingSessionImplementation::clearSession() {
	Locker slocker(_this.get());

	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

	if (manufactureSchematic != NULL) {

		Locker locker(manufactureSchematic);

		if (manufactureSchematic->getParent() == craftingTool) {
			manufactureSchematic->setDraftSchematic(NULL);
			manufactureSchematic->cleanupIngredientSlots(crafter);
			manufactureSchematic->destroyObjectFromWorld(true);
		}

		this->manufactureSchematic = NULL;
	}

	if (craftingTool != NULL) {
		Locker locker2(craftingTool);

		// Remove all items that aren't the prototype
		while (craftingTool->getContainerObjectsSize() > 1) {
			craftingTool->getContainerObject(1)->destroyObjectFromWorld(true);
		}

		craftingTool->dropSlottedObject("crafted_components");

		if (prototype != NULL) {

			Locker locker3(prototype);

			if (craftingTool->isReady()) {

				if (prototype->getParent() == craftingTool) {
					prototype->destroyObjectFromWorld(true);
				}

				this->prototype = NULL;
			}
		}
	}

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("*** Clearing crafting session ***");
	}

	return 0;
}

void CraftingSessionImplementation::closeCraftingWindow(int clientCounter) {
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();

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

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("*** Closing crafting window ***");
	}
}

void CraftingSessionImplementation::sendSlotMessage(int counter, int message) {
	ManagedReference<CreatureObject*> crafter = this->crafter.get();

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
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();

	if (index >= currentSchematicList.size()) {
		crafter->sendSystemMessage("Invalid Schematic Index");
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

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("Selected DraftSchematic: " + draftschematic->getCustomName());
	}

	state = 2;

	if (craftingTool != NULL) {
		Locker locker(craftingTool);

		if (createSessionObjects(draftschematic)) {

			if (prototype == NULL) {
				crafter->sendSystemMessage("@ui_craft:err_no_prototype");
				closeCraftingWindow(1);
				cancelSession();
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

		} else {
			crafter->sendSystemMessage("This type of object has not yet been implemented");
		}
	} else {
		crafter->sendSystemMessage("@ui_craft:err_no_crafting_tool");
		closeCraftingWindow(1);
		cancelSession();
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
			 (draftschematic->createManufactureSchematic(craftingTool.get())).castTo<ManufactureSchematic*>();

	if (manufactureSchematic == NULL) {
		crafter.get()->sendSystemMessage("@ui_craft:err_no_manf_schematic");
		closeCraftingWindow(1);
		cancelSession();
		return false;
	}

	craftingTool.get()->transferObject(manufactureSchematic.get(), 0x4, true);
	//manufactureSchematic->sendTo(crafter, true);

	if(crafterGhost != NULL && crafterGhost.get()->getDebug()) {
		crafter.get()->sendSystemMessage("ManufactureSchematic Created");
	}

	return true;
}

bool CraftingSessionImplementation::createPrototypeObject(DraftSchematic* draftschematic) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();

	// Remove all items, incase there are any
	while (craftingTool->getContainerObjectsSize() > 0) {
		craftingTool->getContainerObject(0)->destroyObjectFromWorld(true);
	}

	prototype = (crafter.get()->getZoneServer()->createObject(
			draftschematic->getTanoCRC(), 0)).castTo<TangibleObject*>();

	if (prototype == NULL) {
		crafter.get()->sendSystemMessage("@ui_craft:err_no_prototype");
		closeCraftingWindow(1);
		cancelSession();
		return false;
	}

	prototype.get()->createChildObjects();

	craftingTool->transferObject(prototype.get(), -1, false);
	prototype.get()->sendTo(crafter.get(), true);

	if(crafterGhost != NULL && crafterGhost.get()->getDebug()) {
		crafter.get()->sendSystemMessage("Prototype Created");
	}

	return true;
}

void CraftingSessionImplementation::sendIngredientForUIListen() {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

	if (crafter == NULL) {
		return;
	}

	if (craftingTool == NULL) {
		return;
	}

	if (manufactureSchematic == NULL) {
		return;
	}

	if (prototype == NULL) {
		return;
	}
	uint8 allowFactory = 1;
	if (!craftingManager.get()->allowManufactureSchematic(manufactureSchematic)) {
		allowFactory = 0;
	}
	// Object Controller w/ Ingredients ***************************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x0103);
	objMsg->insertLong(craftingTool->getObjectID()); // Crafting Tool Object ID
	objMsg->insertLong(manufactureSchematic->getObjectID());// Manufacture Schematic Object ID
	objMsg->insertLong(prototype->getObjectID()); // Crafting Tangible Object ID
	objMsg->insertInt(2);
	objMsg->insertByte(allowFactory); // set to 1 to allow create manufact schematic, 0 to prevent it.

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

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("Sent UI Listen");
	}
}

void CraftingSessionImplementation::addIngredient(TangibleObject* tano, int slot, int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

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

	Locker locker(tano);

	/// Check if item is on the player, but not in a crafting tool
	/// Or if the item is in a crafting station to prevent some duping
	if(!tano->isASubChildOf(crafter) && (craftingStation == NULL || !tano->isASubChildOf(craftingStation))) {
		sendSlotMessage(clientCounter, IngredientSlot::INVALIDINGREDIENT);
		return;
	}

	ManagedReference<SceneObject*> objectsParent = tano->getParent();

	if (objectsParent == NULL || !objectsParent->checkContainerPermission(crafter, ContainerPermissions::MOVEOUT)){
		sendSlotMessage(clientCounter, IngredientSlot::INVALIDINGREDIENT);
		return;
	}

	ManagedReference<SceneObject*> craftingComponents = craftingTool->getSlottedObject("crafted_components");
	ManagedReference<SceneObject*> craftingComponentsSatchel = NULL;

	if(craftingComponents == NULL) {

		/// Add Components to crafted object
		String craftingComponentsPath = "object/tangible/crafting/crafting_components_container.iff";
		craftingComponents = crafter->getZoneServer()->createObject(craftingComponentsPath.hashCode(), 1);

		Locker componentsLocker(craftingComponents);

		craftingComponents->setSendToClient(false);
		craftingTool->transferObject(craftingComponents, 4, false);

		craftingComponents->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDefaultAllowPermission(0);
		craftingComponents->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDenyPermission("admin", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerAllowPermission("owner", 0);
		craftingComponents->setContainerAllowPermission("admin", 0);
		craftingComponents->setContainerInheritPermissionsFromParent(false);

		//String craftingComponentsSatchelPath = "object/tangible/container/base/base_container_volume.iff";
		String craftingComponentsSatchelPath = "object/tangible/hopper/crafting_station_hopper/crafting_station_ingredient_hopper_large.iff";
		craftingComponentsSatchel = crafter->getZoneServer()->createObject(craftingComponentsSatchelPath.hashCode(), 1);

		Locker satchelLocker(craftingComponentsSatchel, craftingComponents);

		craftingComponentsSatchel->setContainerInheritPermissionsFromParent(false);
		craftingComponentsSatchel->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerDefaultAllowPermission(0);
		craftingComponentsSatchel->setContainerAllowPermission("admin", ContainerPermissions::OPEN);
		craftingComponentsSatchel->setContainerDenyPermission("admin", ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerAllowPermission("owner", 0);
		craftingComponentsSatchel->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);

		craftingComponentsSatchel->sendTo(crafter, true);
		craftingComponents->transferObject(craftingComponentsSatchel, -1, false);

	} else {
		craftingComponentsSatchel = craftingComponents->getContainerObject(0);
	}
	// Lock the craft and satchel as well
	//Locker crossSatcheLock(craftingComponentsSatchel,crafter);
	// crafter is pre-locked before entering this method, satchel::trasnferObject is thread safe

	int result = manufactureSchematic->addIngredientToSlot(crafter, craftingComponentsSatchel, tano, slot);

	sendSlotMessage(clientCounter, result);

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("Adding ingredient: " + tano->getDisplayedName());
	}

}

void CraftingSessionImplementation::removeIngredient(TangibleObject* tano, int slotUpdated, int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

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

	Locker locker(tano);

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

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage("Removing ingredient: " + tano->getDisplayedName());
	}
}

void CraftingSessionImplementation::nextCraftingStage(int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

	if (manufactureSchematic == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	// Make sure all the require resources are there, if not, return them to inventory and close tool
	if (!manufactureSchematic->isAssembled() && !manufactureSchematic->isReadyForAssembly()) {

		sendSlotMessage(clientCounter, IngredientSlot::PARTIALASSEMBLE);
		return;
	}

	Locker locker(manufactureSchematic);

	ManagedReference<SceneObject*> craftingComponents = craftingTool->getSlottedObject("crafted_components");

	if(craftingComponents != NULL) {

		/// Add Components to crafted object
		prototype->transferObject(craftingComponents, 4, false);
		craftingComponents->setSendToClient(false);
	}
	manufactureSchematic->setAssembled();

	if (state == 2) {

		initialAssembly(clientCounter);

	} else if (state == 3) {

		finishAssembly(clientCounter);

	} else if (state == 4) {

		finishStage1(clientCounter);
		finishStage2(clientCounter);
		state = 6;

	} else if (state == 5) {

		finishStage1(clientCounter);

	} else if (state == 6) {

		finishStage2(clientCounter);
	}
}

void CraftingSessionImplementation::initialAssembly(int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	// Get the appropriate number of Experimentation points from Skill
	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	// Set crafter
	manufactureSchematic->setCrafter(crafter);

	String expskill = draftSchematic->getExperimentationSkill();
	experimentationPointsTotal = int(crafter->getSkillMod(expskill) / 10);
	experimentationPointsUsed = 0;

	// Calculate exp failure for red bars
	int experimentalFailureRate = craftingManager.get()->calculateExperimentationFailureRate(crafter, manufactureSchematic, 0);

	// Get the level of customization
	String custskill = draftSchematic->getCustomizationSkill();
	int custpoints = int(crafter->getSkillMod(custskill));

	// Determine the outcome of the craft, Amazing through Critical
	assemblyResult = craftingManager.get()->calculateAssemblySuccess(crafter,
			draftSchematic, craftingTool->getEffectiveness());

	Locker locker(prototype);
	//Set initial crafting percentages
	craftingManager.get()->setInitialCraftingValues(prototype,manufactureSchematic,assemblyResult);
	//prototype->setInitialCraftingValues(manufactureSchematic, assemblyResult);

	Reference<CraftingValues*> craftingValues = manufactureSchematic->getCraftingValues();
	craftingValues->setManufactureSchematic(manufactureSchematic);
	craftingValues->setPlayer(crafter);

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		ComponentSlot* compSlot = cast<ComponentSlot*>(manufactureSchematic->getSlot(i));
		if (compSlot == NULL)
			continue;

		ManagedReference<TangibleObject*> tano = compSlot->getPrototype();
		if (tano == NULL)
			continue;

		uint32 tanoCRC = prototype->getClientObjectCRC();
		uint32 visSlot = draftSchematic->getAppearance(i).hashCode();

		// we know that we can only have one component per hardpoint slot, so don't worry about checking them
		if (visSlot > 0) {
			uint32 id = ComponentMap::instance()->getVisibleCRC(tanoCRC, visSlot);
			if (id > 0)
				prototype->addVisibleComponent(id, false);
		}
	}

	if (prototype->getVisibleComponents() != NULL && prototype->getVisibleComponents()->size() > 0) {
		prototype->sendDestroyTo(crafter);
		prototype->sendTo(crafter, true);
	}

	// Flag to get the experimenting window
	if (craftingStation != NULL && (craftingValues->getVisibleExperimentalPropertyTitleSize() > 0 || manufactureSchematic->allowFactoryRun()))
		// Assemble with Experimenting
		state = 3;

	else
		// Assemble without Experimenting
		state = 4;

	// Start DPLAY9 ***********************************************************
	// Updates the stage of crafting, sets the number of experimentation points
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(crafter->getPlayerObject());
	dplay9->setCraftingState(state); // 3 If Experimenting is active, 4 if already experimented/ No experimenting
	dplay9->setExperimentationPoints(experimentationPointsTotal);
	dplay9->close();

	crafter->sendMessage(dplay9);
	// End DPLAY9 *************************************************************

	// Set Crafter name and generate serial number
	String name = crafter->getFirstName();
	prototype->setCraftersName(name);

	String serial = craftingManager.get()->generateSerial();
	prototype->setSerialNumber(serial);

	// Update the prototype with new values
	prototype->updateCraftingValues(craftingValues, true);

	addSkillMods();

	addWeaponDots();

	// Set default customization
	SharedTangibleObjectTemplate* templateData =
			cast<SharedTangibleObjectTemplate*>(prototype->getObjectTemplate());
	if (templateData == NULL) {
		error("No template for: " + String::valueOf(prototype->getServerObjectCRC()));
		return;
	}

	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(templateData->getAppearanceFilename().hashCode(), variables, true);

	for (int i = 0; i < variables.size(); ++i) {
		Reference<RangedIntCustomizationVariable*> var = cast<RangedIntCustomizationVariable*>(variables.get(i).get());
		if(var != NULL) {
			prototype->setCustomizationVariable(variables.elementAt(i).getKey(), var->getDefaultValue());
		}
	}

	prototype->setComplexity(manufactureSchematic->getComplexity());

	// Start DMSCO3 ***********************************************************
	// Sends the updated values to the crafting screen
	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(manufactureSchematic);
	dMsco3->updateCraftingValues(manufactureSchematic);
	dMsco3->updateComplexity(manufactureSchematic->getComplexity());

	dMsco3->close();

	crafter->sendMessage(dMsco3);
	// End DMSCO3 *************************************************************

	// Start DMSCO7 ***********************************************************
	// Sends the experimental properties and experimental percentages
	ManufactureSchematicObjectDeltaMessage7* dMsco7 =
			new ManufactureSchematicObjectDeltaMessage7(manufactureSchematic);

	dMsco7->updateForAssembly(manufactureSchematic, experimentalFailureRate);
	if (custpoints > 0)
		dMsco7->updateCustomizationOptions(&variables, custpoints);

	dMsco7->close();

	crafter->sendMessage(dMsco7);
	// End DMSCO7 *************************************************************

	// Start DTANO3 ***********************************************************
	// Updates the Complexity and the condition
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(
			prototype);
	dtano3->updateComplexity();
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

	crafter->notifyObservers(ObserverEventType::CRAFTINGASSEMBLY, crafter, 0);

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

		crafterGhost->decreaseSchematicUseCount(draftSchematic);

	}

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage(craftingValues->toString());
	}
}

void CraftingSessionImplementation::finishAssembly(int clientCounter) {
	ManagedReference<CreatureObject*> crafter = this->crafter.get();

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
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	ManagedReference<CraftingManager*> craftingManager = this->craftingManager.get();

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
	Locker locker3(prototype);

	StringTokenizer tokenizer(expAttempt);

	int rowEffected, pointsAttempted, failure;
	int lowestExpSuccess = 0;

	//lastExperimentationTimestamp = Time::currentNanoTime();

	Reference<CraftingValues*> craftingValues = manufactureSchematic->getCraftingValues();
	craftingValues->clear();
	int numberOfRows = craftingValues->getVisibleExperimentalPropertyTitleSize();
	if (rowsAttempted > numberOfRows || rowsAttempted < 1) {
		cancelSession();
		return;
	}
	// Loop through all the lines of experimentation
	for (int i = 0; i < rowsAttempted; ++i) {

		rowEffected = tokenizer.getIntToken();
		pointsAttempted = tokenizer.getIntToken();
		// check for hack attempts
		if (pointsAttempted > (experimentationPointsTotal - experimentationPointsUsed) || pointsAttempted < 1 || rowEffected < 0 || rowEffected > (numberOfRows - 1)){
			cancelSession();
			return;
		}
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
			// we jsut cancel it so they cant overflow it
			cancelSession();
			return;
		}

		// Make sure to store the lowest roll to display (Effect the multiline rolls
		if (lowestExpSuccess < experimentationResult)
			lowestExpSuccess = experimentationResult;

		manufactureSchematic->increaseComplexity();
		prototype->setComplexity(manufactureSchematic->getComplexity());

		// Do the experimenting - sets new percentages
		craftingManager->experimentRow(manufactureSchematic, craftingValues, rowEffected,
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
	dtano3->updateComplexity();
	dtano3->close();

	crafter->sendMessage(dtano3);

	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x0113);
	objMsg->insertInt(0x105);

	objMsg->insertInt(experimentationResult); // Experimentation Result
	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);

	crafter->notifyObservers(ObserverEventType::CRAFTINGEXPERIMENTATION, crafter, 0);

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage(craftingValues->toString());
	}
}

void CraftingSessionImplementation::customization(const String& name, byte templateChoice, int schematicCount, const String& customizationString) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	ManagedReference<CraftingManager*> craftingManager = this->craftingManager.get();

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
	Locker locker3(prototype);

	if (templateChoice != 0xFF) {

		Reference<DraftSchematic*> draftSchematic =
				manufactureSchematic->getDraftSchematic();

		if (draftSchematic != NULL) {
			if (draftSchematic->getTemplateListSize() >= (int) templateChoice) {
				String chosenTemplate = draftSchematic->getTemplate((int) templateChoice);
				uint32 clientCRC = chosenTemplate.hashCode();
				prototype->setClientObjectCRC(clientCRC);

				String minusShared = chosenTemplate.replaceAll("shared_","");
				SharedObjectTemplate* newTemplate = TemplateManager::instance()->getTemplate(minusShared.hashCode());

				prototype->loadTemplateData(newTemplate);
				prototype->updateCraftingValues(manufactureSchematic->getCraftingValues(), false);

				prototype->sendDestroyTo(crafter);
				prototype->sendTo(crafter, true);
			}
		}
	}

	if(schematicCount < 0 || schematicCount > 1000)
		schematicCount = 1000;

	manufactureSchematic->setManufactureLimit(schematicCount);

	StringTokenizer tokenizer(customizationString);
	byte customizationindex, customizationvalue;
	String customizationname = "";

	//Database::escapeString(name);

	//Remove color codes
	String newName = name;
	while (newName.contains("\\#")) {
		int index = newName.indexOf("\\#");
		String sub = "\\" + newName.subString(index, index + 2);
		newName = newName.replaceFirst(sub,"");
	}

	UnicodeString customName(newName);
	prototype->setCustomObjectName(customName, false);

	/// Set Name
	manufactureSchematic->getObjectName()->setStringId(
			prototype->getObjectNameStringIdFile(),
			prototype->getObjectNameStringIdName());

	/// Set Manufacture Schematic Custom name
	if (!newName.isEmpty())
		manufactureSchematic->setCustomObjectName(customName, false);

	while (tokenizer.hasMoreTokens()) {

		customizationindex = (byte) tokenizer.getIntToken();

		customizationname = variables.elementAt(customizationindex).getKey();

		customizationvalue = (byte) tokenizer.getIntToken();

		prototype->setCustomizationVariable(customizationname,
				customizationvalue);
	}

	TangibleObjectDeltaMessage3* dtano3 =
			new TangibleObjectDeltaMessage3(prototype);
	dtano3->updateName(newName);
	dtano3->updateCustomizationString();
	dtano3->close();

	crafter->sendMessage(dtano3);

	ManufactureSchematicObjectDeltaMessage3 * dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(
					manufactureSchematic);
	dMsco3->updateName(newName);
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
	ManagedReference<CreatureObject*> crafter = this->crafter.get();

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
	ManagedReference<CreatureObject*> crafter = this->crafter.get();

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
			crafter->getPlayerObject());
	dplay9->insertShort(5);
	dplay9->insertInt(0xFFFFFFFF);
	dplay9->setCraftingState(state);

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

void CraftingSessionImplementation::createPrototype(int clientCounter, bool createItem) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();

	if (manufactureSchematic == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(clientCounter, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	Locker locker(manufactureSchematic);


	if (manufactureSchematic->isAssembled()
			&& !manufactureSchematic->isCompleted()) {

		closeCraftingWindow(clientCounter);

		String xpType = manufactureSchematic->getDraftSchematic()->getXpType();
		int xp = manufactureSchematic->getDraftSchematic()->getXpAmount();

		if (createItem) {

			startCreationTasks(manufactureSchematic->getComplexity() * 2, false);

		} else {

			// This is for practicing
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

	cancelSession();
}


void CraftingSessionImplementation::startCreationTasks(int timer, bool practice) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	ManagedReference<CraftingManager*> craftingManager = this->craftingManager.get();

	int timer2 = 1;

	Reference<UpdateToolCountdownTask*> updateToolCountdownTask;
	Reference<CreateObjectTask*> createObjectTask = new CreateObjectTask(crafter, craftingTool, practice);

	ManagedReference<ZoneServer*> server = crafter->getZoneServer();

	if (server != NULL) {

		Locker locker(craftingTool);
		craftingTool->setBusy();

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

		updateToolCountdownTask = new UpdateToolCountdownTask(crafter, craftingTool, timer);
		updateToolCountdownTask->schedule(timer2);
		createObjectTask->schedule(timer2);
	}
}

void CraftingSessionImplementation::createManufactureSchematic(int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	ManagedReference<CraftingManager*> craftingManager = this->craftingManager.get();

	if (manufactureSchematic == NULL) {
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
		return;
	}

	if (prototype == NULL) {
		sendSlotMessage(0, IngredientSlot::PROTOTYPENOTFOUND);
		return;
	}

	if (!craftingManager.get()->allowManufactureSchematic(manufactureSchematic)){
		sendSlotMessage(0, IngredientSlot::NOSCHEMATIC);
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

		Locker prototypeLocker(prototype);

		prototype->destroyObjectFromWorld(0);

		manufactureSchematic->setPersistent(2);
		prototype->setPersistent(2);

		datapad->transferObject(manufactureSchematic, -1, true);
		manufactureSchematic->setPrototype(prototype);

	} else {

		closeCraftingWindow(clientCounter);

		sendSlotMessage(clientCounter, IngredientSlot::WEIRDFAILEDMESSAGE);
	}

	cancelSession();
}

void CraftingSessionImplementation::addSkillMods() {
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	VectorMap<String, int>* skillMods = draftSchematic->getDraftSchematicTemplate()->getSkillMods();

	for (int i = 0; i < skillMods->size(); i++) {
		VectorMapEntry<String, int> mod = skillMods->elementAt(i);

		if (prototype->isWearableObject()) {
			WearableObject* wearable = prototype.castTo<WearableObject*>();
			VectorMap<String, int>* wearableMods = wearable->getWearableSkillMods();

			if (wearableMods->contains(mod.getKey())) {
				int oldValue = wearableMods->get(mod.getKey());
				int newValue = mod.getValue() + oldValue;

				if (newValue > 25)
					newValue = 25;

				wearableMods->put(mod.getKey(), newValue);
				continue;
			}
		}

		prototype->addSkillMod(SkillModManager::WEARABLE, mod.getKey(), mod.getValue(), false);
	}
}

void CraftingSessionImplementation::addWeaponDots() {
	ManagedReference<TangibleObject*> prototype = this->prototype.get();

	if (!(prototype->isWeaponObject()))
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(prototype.get());

	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	Vector<VectorMap<String, int> >* weaponDots = draftSchematic->getDraftSchematicTemplate()->getWeaponDots();

	for (int i = 0; i < weaponDots->size(); i++) {
		VectorMap<String, int> dot = weaponDots->elementAt(i);

		for (int j = 0; j < dot.size(); j++) {
			String property = dot.elementAt(j).getKey();
			int value = dot.elementAt(j).getValue();

			if (property == "type")
				weapon->addDotType(value);
			else if (property == "attribute")
				weapon->addDotAttribute(value);
			else if (property == "strength")
				weapon->addDotStrength(value);
			else if (property == "duration")
				weapon->addDotDuration(value);
			else if (property == "potency")
				weapon->addDotPotency(value);
			else if (property == "uses")
				weapon->addDotUses(value);

		}
	}
}
