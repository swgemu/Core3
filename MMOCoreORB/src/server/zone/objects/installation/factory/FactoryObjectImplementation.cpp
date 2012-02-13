/*
 * FactoryObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: kyle
 */

#include "FactoryObject.h"
#include "tasks/CreateFactoryObjectTask.h"

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/chat/ChatManager.h"

#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "server/zone/packets/factory/FactoryCrateObjectDeltaMessage3.h"
#include "server/zone/packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
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
#include "server/zone/objects/factorycrate/FactoryCrate.h"

#include "server/zone/templates/installation/FactoryObjectTemplate.h"

void FactoryObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	InstallationObjectImplementation::loadTemplateData(templateData);

	FactoryObjectTemplate* factory = dynamic_cast<FactoryObjectTemplate*>(templateData);

	craftingTabsSupported = factory->getCraftingTabsSupported();
}

void FactoryObjectImplementation::initializeTransientMembers() {
	InstallationObjectImplementation::initializeTransientMembers();

	/*if(operating)
		startFactory();*/

	setLoggingName("FactoryObject");
}

void FactoryObjectImplementation::createChildObjects() {

	String ingredientHopperName = "object/tangible/hopper/manufacture_installation_ingredient_hopper_1.iff";
	ManagedReference<SceneObject*> ingredientHopper = server->getZoneServer()->createObject(ingredientHopperName.hashCode(), 1);

	transferObject(ingredientHopper, 4);

	String outputHopperName = "object/tangible/hopper/manufacture_installation_output_hopper_1.iff";
	ManagedReference<SceneObject*> outputHopper = server->getZoneServer()->createObject(outputHopperName.hashCode(), 1);

	transferObject(outputHopper, 4);
}

void FactoryObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	InstallationObjectImplementation::fillAttributeList(alm, object);

	if (operating && isOnAdminList(object->getFirstName())) {
		ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

		if (outputHopper != NULL) {
			alm->insertAttribute("manufacture_count", currentRunCount); //Manufactured Items:
		}
	}
}

void FactoryObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player->getFirstName()))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);


	menuResponse->addRadialMenuItem(29, 3, "@manf_station:options"); //Options

	if(getContainerObjectsSize() > 0) {
		if(!operating)
			menuResponse->addRadialMenuItemToRadialID(29, 69, 3, "@manf_station:activate"); //Start manufacturing objects.
		else
			menuResponse->addRadialMenuItemToRadialID(29, 69, 3, "@manf_station:deactivate"); //Stop manufacturing objects.

		if(!operating)
			menuResponse->addRadialMenuItemToRadialID(29, 68, 3, "@manf_station:ingredients"); //List ingredients needed for station
	}

	if(!operating) {
		menuResponse->addRadialMenuItemToRadialID(29, 197, 3, "@manf_station:schematic"); //Access schematic slot.
		menuResponse->addRadialMenuItemToRadialID(29, 195, 3, "@manf_station:input_hopper"); //Access station ingredient hopper
		menuResponse->addRadialMenuItemToRadialID(29, 196, 3, "@manf_station:output_hopper"); //Access station output hopper
	}
}

int FactoryObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isOnAdminList(player->getFirstName()))
		return 1;

	switch (selectedID) {
	case 195: /// Send ingredient Hopper
		sendIngredientHopper(player);
		break;
	case 29:
	case 196: /// Send output Hopper
		sendOutputHopper(player);
		break;
	case 197: /// Schematic Slot
		sendInsertManuSui(player);
		break;
	case 68: /// Send ingredients list
		sendIngredientsNeededSui(player);
		break;
	case 69: /// Send schematic requirements
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
void FactoryObjectImplementation::sendInsertManuSui(CreatureObject* player){

	ManagedReference<SuiListBox*> schematics = NULL;
	if(getContainerObjectsSize() == 0) {
		schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC2BUTTON, SuiListBox::HANDLETWOBUTTON);
		schematics->setPromptText("Choose a schematic to be added to the factory.");
	} else {

		schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC3BUTTON, SuiListBox::HANDLETHREEBUTTON);

		StringBuffer message;
		message << "Current Schematic Installed: ";

		if(getContainerObject(0)->getCustomObjectName().isEmpty())
			message << "@" << getContainerObject(0)->getObjectNameStringIdFile() << ":" << getContainerObject(0)->getObjectNameStringIdName();
		else
			message << getContainerObject(0)->getCustomObjectName().toString();

		schematics->setPromptText(message.toString());

		schematics->setOtherButton(true, "@remove_schematic");
	}

	schematics->setHandlerText("handleUpdateSchematic");
	schematics->setPromptTitle("SCHEMATIC MANAGEMENT");//found a SS with this as the title so...

	schematics->setOkButton(true, "@use_schematic");
	schematics->setCancelButton(true, "@cancel");

	/*
	 * Insert only the schematics that can be used in this type of factory
	 */
	ManagedReference<SceneObject* > datapad = player->getSlottedObject("datapad");

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {

		ManagedReference<SceneObject* > datapadObject = datapad->getContainerObject(i);

		if (datapadObject != NULL && datapadObject->isManufactureSchematic()) {

			ManagedReference<ManufactureSchematic* > manSchem = dynamic_cast<ManufactureSchematic*>(datapadObject.get());

			 if (manSchem->getDraftSchematic() == NULL)
				 continue;

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

	schematics->setUsingObject(_this);
	player->getPlayerObject()->addSuiBox(schematics);
	player->sendMessage(schematics->generateMessage());
}

void FactoryObjectImplementation::updateInstallationWork() {
	Time timeToWorkTill;
	bool shutdownAfterWork = updateMaintenance(timeToWorkTill);

	if(shutdownAfterWork)
		stopFactory("", "", "", -1);
}
/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendIngredientsNeededSui(CreatureObject* player) {

	if(getContainerObjectsSize() == 0)
		return;

	ManagedReference<SuiListBox*> ingredientList = new SuiListBox(player, SuiWindowType::FACTORY_INGREDIENTS);
	ingredientList->setPromptTitle("@base_player:swg"); //STAR WARS GALAXIES - found a SS with this as the title so....

	ingredientList->setPromptText("@manf_station:examine_prompt"); //Ingredients required to manufacture an item at this station.

	ingredientList->setOkButton(true, "@ok");

	ManagedReference<ManufactureSchematic* > schematic = dynamic_cast<ManufactureSchematic*>(getContainerObject(0));

	for (int i = 0; i < schematic->getBlueprintSize(); ++i) {
		BlueprintEntry* blueprintEntry = schematic->getBlueprintEntry(i);
		blueprintEntry->insertFactoryIngredient(ingredientList);
	}

	ingredientList->setUsingObject(_this);
	player->getPlayerObject()->addSuiBox(ingredientList);
	player->sendMessage(ingredientList->generateMessage());

}

void FactoryObjectImplementation::sendIngredientHopper(CreatureObject* player) {

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if(inputHopper == NULL) {
		return;
	}

	inputHopper->closeContainerTo(player, true);
	inputHopper->sendDestroyTo(player);


	inputHopper->sendWithoutContainerObjectsTo(player);
	inputHopper->openContainerTo(player);
}

void FactoryObjectImplementation::sendOutputHopper(CreatureObject* player) {

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL) {
		return;
	}

	outputHopper->closeContainerTo(player, true);
	outputHopper->sendDestroyTo(player);

	outputHopper->sendWithoutContainerObjectsTo(player);
	outputHopper->openContainerTo(player);
}

void FactoryObjectImplementation::handleInsertFactorySchem(
		CreatureObject* player, ManufactureSchematic* schematic) {

	if (schematic == NULL)
		return;

	/// pre: player and _this are locked
	if (!schematic->isManufactureSchematic()) {
		StringIdChatParameter message("manf_station", "schematic_not_added"); //Schematic %TT was not added to the station.

		if(schematic->getCustomObjectName().isEmpty())
			message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
		else
			message.setTT(schematic->getCustomObjectName().toString());

		player->sendSystemMessage(message);

		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	//datapad->removeObject(schematic, true);

	transferObject(schematic, -1, true);

	StringIdChatParameter message("manf_station", "schematic_added"); //Schematic %TT has been inserted into the station. The station is now ready to manufacture items.

	if(schematic->getCustomObjectName().isEmpty())
		message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
	else
		message.setTT(schematic->getCustomObjectName().toString());

	player->sendSystemMessage(message);
}

void FactoryObjectImplementation::handleRemoveFactorySchem(CreatureObject* player) {

	/// pre: player and _this are locked

	if(getContainerObjectsSize() == 0) {
		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	ManagedReference<SceneObject*> schematic = getContainerObject(0);
	schematic->destroyObjectFromWorld(true);

	if(!schematic->isManufactureSchematic())
		return;

	datapad->transferObject(schematic, -1, true);
	datapad->broadcastObject(schematic, true);

	StringIdChatParameter message("manf_station", "schematic_removed"); //Schematic %TT has been removed from the station and been placed in your datapad. Have a nice day!

	if(schematic->getCustomObjectName().isEmpty())
		message.setTT(schematic->getObjectNameStringIdFile(), getContainerObject(0)->getObjectNameStringIdName());
	else
		message.setTT(schematic->getCustomObjectName().toString());

	player->sendSystemMessage(message);
}

void FactoryObjectImplementation::handleOperateToggle(CreatureObject* player) {

	if(!operating) {
		currentUserName = player->getFirstName();
		currentRunCount = 0;
		if(startFactory())
			player->sendSystemMessage("@manf_station:activated"); //Station activated
	} else {

		stopFactory("manf_done", getObjectName()->getDisplayedName(), "", currentRunCount);
		player->sendSystemMessage("@manf_station:deactivated"); //Station deactivated
		currentUserName = "";
	}
}

bool FactoryObjectImplementation::startFactory() {
	if (getContainerObjectsSize() == 0) {
		return false;
	}

	ManagedReference<ManufactureSchematic* > schematic = dynamic_cast<ManufactureSchematic*>(getContainerObject(0));

	timer = ((int)schematic->getComplexity()) * 2;

	if(!populateSchematicBlueprint(schematic))
		return false;

	// Add sampletask
	Reference<CreateFactoryObjectTask* > createFactoryObjectTask = new CreateFactoryObjectTask(_this);
	addPendingTask("createFactoryObject", createFactoryObjectTask, timer * 1000);

	operating = true;

	return true;
}

bool FactoryObjectImplementation::populateSchematicBlueprint(ManufactureSchematic* schematic) {

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if(inputHopper == NULL) {
		error("Factory Ingredient Hopper missing.  WTF");
		return false;
	}

	for(int i = 0; i < schematic->getBlueprintSize(); ++i) {
		BlueprintEntry* entry = schematic->getBlueprintEntry(i);
		entry->setHopper(inputHopper);
		collectMatchesInInputHopper(entry, inputHopper);
	}
	return true;
}

void FactoryObjectImplementation::stopFactory(const String& message, const String& tt, const String& to, const int di) {

	Locker _locker(_this);

	operating = false;
	Reference<Task* > pending = getPendingTask("createFactoryObject");
	removePendingTask("createFactoryObject");

	if(pending != NULL && pending->isScheduled())
		pending->cancel();

	//Send out email informing them why their factory stopped
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager != NULL && currentUserName != "") {
		StringIdChatParameter emailBody;
		emailBody.setStringId("@system_msg:" + message);
		if(tt != "")
			emailBody.setTT(tt);
		if(to != "")
			emailBody.setTO(to);
		if(di != -1)
			emailBody.setDI(di);
		UnicodeString subject = "@system_msg:manf_done_sub";

		/*WaypointObject* newwaypoint = cast<WaypointObject*>( server->getZoneServer()->createObject(0xc456e788, 1));

		newwaypoint->setCustomName(UnicodeString(this->getObjectName()->getDisplayedName()));
		newwaypoint->setPlanetCRC(Planet::getPlanetCRC(getZone()->getPlanetName()));
		newwaypoint->setPosition(this->getPositionX(), this->getPositionZ(), this->getPositionY());
		newwaypoint->setColor(WaypointObject::COLOR_BLUE);
		newwaypoint->setActive(false);

		chatManager->sendMail(getObjectName()->getDisplayedName(), subject, emailBody, currentUserName, newwaypoint);*/

		chatManager->sendMail(getObjectName()->getDisplayedName(), subject, emailBody, currentUserName);
	}
}

void FactoryObjectImplementation::stopFactory(String &type, String &displayedName) {

	if(type == "resource") {

		if(displayedName == "")
			stopFactory("manf_no_unknown_resource", getObjectName()->getDisplayedName(), "", -1);
		else
			stopFactory("manf_no_named_resource", getObjectName()->getDisplayedName(), displayedName, -1);

	} else {
		stopFactory("manf_no_component", getObjectName()->getDisplayedName(), displayedName, -1);
	}
}

void FactoryObjectImplementation::createNewObject() {

	/// Pre: _this locked
	if (getContainerObjectsSize() == 0) {
		stopFactory("manf_error", "", "", -1);
		return;
	}

	ManagedReference<ManufactureSchematic*> schematic =
			dynamic_cast<ManufactureSchematic*>(getContainerObject(0));

	if (schematic == NULL) {
		stopFactory("manf_error_4", "", "", -1);
		return;
	}

	ManagedReference<TangibleObject*> prototype =
			dynamic_cast<TangibleObject*>(schematic->getPrototype());

	if (prototype == NULL) {
		stopFactory("manf_error_2", "", "", -1);
		return;
	}

	String type = "";
	String displayedName = "";

	schematic->canManufactureItem(type, displayedName);

	if (displayedName != "") {
		stopFactory(type, displayedName);
		return;
	}

	ManagedReference<FactoryCrate*> crate =
			locateCrateInOutputHopper(prototype);

	if (crate == NULL)
		crate = createNewFactoryCrate(prototype);
	else {
		Locker locker(crate);
		crate->setUseCount(crate->getUseCount() + 1);
	}

	if (crate == NULL) {
		stopFactory("manf_error_7", "", "", -1);
		return;
	}

	schematic->manufactureItem();
	currentRunCount++;

	Reference<Task*> pending = getPendingTask("createFactoryObject");

	if (schematic->getManufactureLimit() == 0) {

		//removeObject(schematic);
		schematic->destroyObjectFromWorld(true);
		stopFactory("manf_done", getObjectName()->getDisplayedName(), "",
				currentRunCount);

	} else if (pending != NULL)
		pending->reschedule(timer * 1000);
	else
		stopFactory("manf_error", "", "", -1);
}

FactoryCrate* FactoryObjectImplementation::locateCrateInOutputHopper(TangibleObject* prototype) {

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL || prototype == NULL) {
		stopFactory("manf_error_6", "", "", -1);
		return NULL;
	}

	for (int i = 0; i < outputHopper->getContainerObjectsSize(); ++i) {

		ManagedReference<SceneObject* > object = outputHopper->getContainerObject(i);

		if(object == NULL || !object->isFactoryCrate())
			continue;

		FactoryCrate* crate = cast<FactoryCrate*>( object.get());

		if(crate->getPrototype() != NULL && crate->getPrototype()->getSerialNumber() ==
				prototype->getSerialNumber() && crate->getUseCount() < FactoryCrate::MAXCAPACITY) {

			return crate;
		}

	}
	return NULL;
}

FactoryCrate* FactoryObjectImplementation::createNewFactoryCrate(TangibleObject* prototype) {

	ManagedReference<FactoryCrate* > crate = prototype->createFactoryCrate(false);

	if (crate == NULL) {
		stopFactory("manf_error_7", "", "", -1);
		return NULL;
	}

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL) {
		stopFactory("manf_error_6", "", "", -1);
		return NULL;
	}

	outputHopper->transferObject(crate, -1, false);

	return crate;
}

void FactoryObjectImplementation::collectMatchesInInputHopper(
		BlueprintEntry* entry, SceneObject* inputHopper) {

	entry->clearMatches();
	for (int i = 0; i < inputHopper->getContainerObjectsSize(); ++i) {

		ManagedReference<TangibleObject*> object =
				cast<TangibleObject*>( inputHopper->getContainerObject(i));

		if (object == NULL) {
			error("NULL hopper object in FactoryObjectImplementation::countItemInInputHopper");
			continue;
		}

		String key = "";
		String serial = "";

		if (object->isResourceContainer()) {

			ResourceContainer* rcnoObject = cast<ResourceContainer*>( object.get());

			key = rcnoObject->getSpawnName();

			if(entry->getKey() == key) {
				entry->addMatch(object);
				continue;
			}

		} else {

			TangibleObject* prototype = NULL;

			if (object->isFactoryCrate()) {
				FactoryCrate* crate = cast<FactoryCrate*>( object.get());
				prototype = crate->getPrototype();
			} else {
				prototype = object;
			}

			key = String::valueOf(prototype->getServerObjectCRC());
			serial = prototype->getSerialNumber();

			if(entry->getKey() == key) {

				if(entry->needsIdentical()) {
					if(entry->getSerial() != serial)
						continue;
				}

				entry->addMatch(object);
			}
		}
	}
}
