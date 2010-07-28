/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: kyle
 */

#include "FactoryObject.h"
#include "tasks/CreateFactoryObjectTask.h"

#include "server/zone/managers/resource/ResourceManager.h"

#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"
#include "server/zone/packets/factory/FactoryCrateObjectDeltaMessage3.h"

#include "server/zone/packets/chat/ChatSystemMessage.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

#include "server/zone/templates/installation/FactoryObjectTemplate.h"

void FactoryObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	InstallationObjectImplementation::loadTemplateData(templateData);

	FactoryObjectTemplate* factory = dynamic_cast<FactoryObjectTemplate*>(templateData);

	craftingTabsSupported = factory->getCraftingTabsSupported();
}

void FactoryObjectImplementation::createChildObjects() {

	String ingredientHopperName = "object/tangible/hopper/manufacture_installation_ingredient_hopper_1.iff";
	ManagedReference<SceneObject*> ingredientHopper = server->getZoneServer()->createObject(ingredientHopperName.hashCode(), 1);

	addObject(ingredientHopper, 4);

	String outputHopperName = "object/tangible/hopper/manufacture_installation_output_hopper_1.iff";
	ManagedReference<SceneObject*> outputHopper = server->getZoneServer()->createObject(outputHopperName.hashCode(), 1);

	addObject(outputHopper, 4);
}

void FactoryObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//All objects in a cell can be picked up, if the player is on the structures permission list.
	//This opens the door to allow admins to be able to drop/pickup items in public structures

	if (!isOnAdminList(player))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItemToRadialID(122, 77, 3, "@player_structure:management_power");

	menuResponse->addRadialMenuItem(117, 1, "@player_structure:permissions");
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin");

	menuResponse->addRadialMenuItem(118, 3, "@manf_station:options");

	if(getContainerObjectsSize() > 0) {
		if(!operating)
			menuResponse->addRadialMenuItemToRadialID(118, 254, 3, "@manf_station:activate");
		else
			menuResponse->addRadialMenuItemToRadialID(118, 254, 3, "@manf_station:deactivate");

		if(!operating)
			menuResponse->addRadialMenuItemToRadialID(118, 253, 3, "@manf_station:ingredients");
	}

	if(!operating) {
		menuResponse->addRadialMenuItemToRadialID(118, 197, 3, "@manf_station:schematic");
		menuResponse->addRadialMenuItemToRadialID(118, 195, 3, "@manf_station:input_hopper");
		menuResponse->addRadialMenuItemToRadialID(118, 196, 3, "@manf_station:output_hopper");
	}
}

int FactoryObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (!isOnAdminList(player))
		return 1;

	switch (selectedID) {
	case 77:
		handleStructureAddEnergy(player);
		break;
	case 195: /// Send ingredient Hopper
		sendIngredientHopper(player);
		break;
	case 118:
	case 196: /// Send output Hopper
		sendOutputHopper(player);
		break;
	case 197: /// Schematic Slot
		sendInsertManuSui(player);
		break;
	case 253: /// Send schematic requirements
		sendIngredientsNeededSui(player);
		break;
	case 254: /// Send schematic requirements
		handleOperateToggle(player);
		break;

	default:
		InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendInsertManuSui(PlayerCreature* player){

	SuiListBox* schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC);
	schematics->setPromptTitle("STAR WARS GALAXIES");//found a SS with this as the title so....

	if(getContainerObjectsSize() == 0)
		schematics->setPromptText("Choose a schematic to be added to the factory.");
	else {
		StringBuffer message;
		message << "Current Schematic Installed: ";

		if(getContainerObject(0)->getCustomObjectName().isEmpty())
			message << "@" << getContainerObject(0)->getObjectNameStringIdFile() << ":" << getContainerObject(0)->getObjectNameStringIdName();
		else
			message << getContainerObject(0)->getCustomObjectName().toString();

		schematics->setPromptText(message.toString());
	}

	schematics->setOkButton(true, "@use_schematic");
	schematics->setCancelButton(true, "@remove_schematic");

	/*
	 * Insert only the schematics that can be used in this type of factory
	 */
	ManagedReference<SceneObject* > datapad = player->getSlottedObject("datapad");

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {

		ManagedReference<ManufactureSchematic* > manSchem = (ManufactureSchematic*) datapad->getContainerObject(i);

		if(manSchem != NULL && manSchem->isManufactureSchematic() && manSchem->getDraftSchematic() != NULL){

			uint32 craftingTabId = manSchem->getDraftSchematic()->getToolTab();

			bool match = false;

			for(int j = 0; j < craftingTabsSupported.size(); ++j) {

				if(craftingTabId == craftingTabsSupported.get(j)) {
					match = true;
					break;
				}
			}

			if(!match)
				continue;

			String sendname;

			if(manSchem->getCustomObjectName().isEmpty())
				sendname = "@" + manSchem->getObjectNameStringIdFile() + ":" + manSchem->getObjectNameStringIdName();
			else
				sendname = manSchem->getCustomObjectName().toString();

			schematics->addMenuItem(sendname, manSchem->getObjectID());
		}
	}

	schematics->setUsingObjectID(getObjectID());
	player->addSuiBox(schematics);
	player->sendMessage(schematics->generateMessage());
}

void FactoryObjectImplementation::synchronizedUIListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature() || !isOnAdminList((CreatureObject*)player))
		return;

	if(getContainerObjectsSize() == 0) {
		stopFactory((PlayerCreature*)player);
		return;
	}

	addOperator((PlayerCreature*) player);

	updateInstallationWork();

	activateUiSync();
}

void FactoryObjectImplementation::synchronizedUIStopListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature())
		return;

	removeOperator((PlayerCreature*) player);
}

void FactoryObjectImplementation::updateInstallationWork() {
	Time timeToWorkTill;
	bool shutdownAfterWork = updateMaintenance(timeToWorkTill);

	updateHoppers(timeToWorkTill, shutdownAfterWork);
}

void FactoryObjectImplementation::updateHoppers(Time& workingTime, bool shutdownAfterUpdate) {

	ManagedReference<ManufactureSchematic* > schematic = (ManufactureSchematic*) getContainerObject(0);


	ManufactureSchematicObjectDeltaMessage7* msg = new ManufactureSchematicObjectDeltaMessage7(schematic->getObjectID());
	msg->updateQuantity(schematic->getManufactureLimit());
	broadcastToOperators(msg);

	/*FactoryCrateObjectDeltaMessage3* msg = new HarvesterObjectMessage7(_this);
	broadcastToOperators(msg);*/

}

/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendIngredientsNeededSui(PlayerCreature* player) {

	if(getContainerObjectsSize() == 0)
		return;

	SuiListBox* ingredientList = new SuiListBox(player, SuiWindowType::FACTORY_INGREDIENTS);
	ingredientList->setPromptTitle("STAR WARS GALAXIES");//found a SS with this as the title so....

	ingredientList->setPromptText("Ingredients required to manufacture an item at this station.");

	ingredientList->setOkButton(true, "@ok");

	/// List Ingredients
	ManagedReference<ManufactureSchematic* > schematic = (ManufactureSchematic*) getContainerObject(0);

	for (int i = 0; i < schematic->getFactoryIngredientsSize(); ++i) {

		ManagedReference<SceneObject* > ingredient = (SceneObject*) schematic->getFactoryIngredient(i);

		if (ingredient == NULL)
			continue;

		if (ingredient->isResourceContainer()) {
			ManagedReference<ResourceContainer*> rcno = (ResourceContainer*) ingredient.get();

			String sendstring = rcno->getSpawnObject()->getName() + ":\\>200" + rcno->getQuantity();

			ingredientList->addMenuItem(sendstring, 0);

		} else {

			ManagedReference<TangibleObject*> component = (TangibleObject*) ingredient.get();

			String sendstring;

			if (component->getCustomObjectName().isEmpty())
				sendstring = "@" + component->getObjectNameStringIdFile() + ":"
					+ component->getObjectNameStringIdName() + " ";
			else
				sendstring = component->getCustomObjectName().toString();

			sendstring += component->getCraftersSerial() + ":\\>200" + component->getUseCount();

			ingredientList->addMenuItem(sendstring, 0);
		}
	}

	ingredientList->setUsingObjectID(getObjectID());
	player->addSuiBox(ingredientList);
	player->sendMessage(ingredientList->generateMessage());

}

void FactoryObjectImplementation::sendIngredientHopper(PlayerCreature* player) {

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if(inputHopper == NULL) {
		return;
	}

	inputHopper->openContainerTo(player);
}

void FactoryObjectImplementation::sendOutputHopper(PlayerCreature* player) {

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL) {
		return;
	}

	outputHopper->openContainerTo(player);
}

void FactoryObjectImplementation::handleInsertFactorySchem(
		PlayerCreature* player, ManufactureSchematic* schematic) {

	/// pre: player and _this are locked
	if(schematic == NULL || !schematic->isManufactureSchematic()) {
		ParameterizedStringId message("manf_station", "schematic_not_added");

		if(schematic->getCustomObjectName().isEmpty())
			message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
		else
			message.setTT(schematic->getCustomObjectName().toString());

		player->sendSystemMessage(message);
		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	datapad->removeObject(schematic, true);
	schematic->sendDestroyTo(player);
	datapad->updateToDatabaseAllObjects(true);

	addObject(schematic, -1, true);
	updateToDatabaseAllObjects(true);

	ParameterizedStringId message("manf_station", "schematic_added");

	if(schematic->getCustomObjectName().isEmpty())
		message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
	else
		message.setTT(schematic->getCustomObjectName().toString());

	player->sendSystemMessage(message);
}

void FactoryObjectImplementation::handleRemoveFactorySchem(PlayerCreature* player) {

	/// pre: player and _this are locked

	if(getContainerObjectsSize() == 0) {
		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	ManagedReference<SceneObject*> schematic = getContainerObject(0);
	removeObject(schematic);

	if(!schematic->isManufactureSchematic())
		return;

	datapad->addObject(schematic, -1, true);
	datapad->updateToDatabaseAllObjects(true);

	updateToDatabaseAllObjects(true);

	ParameterizedStringId message("manf_station", "schematic_removed");

	if(schematic->getCustomObjectName().isEmpty())
		message.setTT(schematic->getObjectNameStringIdFile(), getContainerObject(0)->getObjectNameStringIdName());
	else
		message.setTT(schematic->getCustomObjectName().toString());

	player->sendSystemMessage(message);
}

void FactoryObjectImplementation::handleOperateToggle(PlayerCreature* player) {

	if(!operating)
		startFactory(player);
	 else
		stopFactory(player);
}

void FactoryObjectImplementation::startFactory(PlayerCreature* player) {

	if(getContainerObjectsSize() == 0) {
		return;
	}

	player->sendSystemMessage("manf_station", "activated");
	operating = true;

	timer = (int)((ManufactureSchematic*) getContainerObject(0))->getComplexity() * 2;

	// Add sampletask
	CreateFactoryObjectTask* createFactoryObjectTask = new CreateFactoryObjectTask(_this);
	createFactoryObjectTask->schedule(timer);
	addPendingTask("createFactoryObject", createFactoryObjectTask);

	updateToDatabaseAllObjects(false);
}

void FactoryObjectImplementation::stopFactory(PlayerCreature* player) {

	player->sendSystemMessage("manf_station", "deactivated");
	operating = false;

	removePendingTask("createFactoryObject");
}

void FactoryObjectImplementation::createNewObject() {

	if(getContainerObjectsSize() == 0) {
		operating = false;
		removePendingTask("createFactoryObject");
		return;
	}

	/*if(removeIngredientsFromHopper()) {

	} else {
		operating = false;
		removePendingTask("createFactoryObject");
	}*/

	//this->getPendingTask()->
	updateToDatabaseAllObjects(false);
}
