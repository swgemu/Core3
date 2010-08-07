/*
 * InstallationObjectImplementation.cpp
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

	if(operating)
		startFactory();

	setLoggingName("FactoryObject");
}

void FactoryObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {

	InstallationObjectImplementation::fillAttributeList(alm, object);

	if(operating && isOnAdminList(object) ) {
		alm->insertAttribute("test", 1);
	}
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

	ManagedReference<SuiListBox*> schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC);
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

		ManagedReference<SceneObject* > datapadObject = datapad->getContainerObject(i);

		if (datapadObject != NULL && datapadObject->isManufactureSchematic()) {

			ManagedReference<ManufactureSchematic* > manSchem = (ManufactureSchematic*) datapadObject.get();

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

	schematics->setUsingObjectID(getObjectID());
	player->addSuiBox(schematics);
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
void FactoryObjectImplementation::sendIngredientsNeededSui(PlayerCreature* player) {

	if(getContainerObjectsSize() == 0)
		return;

	ManagedReference<SuiListBox*> ingredientList = new SuiListBox(player, SuiWindowType::FACTORY_INGREDIENTS);
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
	datapad->updateToDatabase();

	addObject(schematic, -1, true);
	updateToDatabase();

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
	datapad->updateToDatabase();

	updateToDatabase();

	ParameterizedStringId message("manf_station", "schematic_removed");

	if(schematic->getCustomObjectName().isEmpty())
		message.setTT(schematic->getObjectNameStringIdFile(), getContainerObject(0)->getObjectNameStringIdName());
	else
		message.setTT(schematic->getCustomObjectName().toString());

	player->sendSystemMessage(message);
}

void FactoryObjectImplementation::handleOperateToggle(PlayerCreature* player) {

	if(!operating) {
		currentUser = player;
		currentRunCount = 0;
		startFactory();
		player->sendSystemMessage("manf_station", "activated");
	} else {

		stopFactory("manf_done", getObjectName()->getStringID(), "", currentRunCount);
		player->sendSystemMessage("manf_station", "deactivated");
		currentUser = NULL;
	}
}

void FactoryObjectImplementation::startFactory() {

	if(getContainerObjectsSize() == 0) {
		return;
	}

	Locker _locker(_this);

	operating = true;

	timer = (int)((ManufactureSchematic*) getContainerObject(0))->getComplexity() * 2;

	// Add sampletask
	Reference<CreateFactoryObjectTask* > createFactoryObjectTask = new CreateFactoryObjectTask(_this);
	createFactoryObjectTask->schedule(timer * 1000);
	createFactoryObjectTask->setReentrant();
	addPendingTask("createFactoryObject", createFactoryObjectTask);

	updateToDatabase();
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

	if (chatManager != NULL && currentUser != NULL) {
		ParameterizedStringId emailBody;
		emailBody.setStringId("@system_msg:" + message);
		if(tt != "")
			emailBody.setTT(tt);
		if(to != "")
			emailBody.setTO(to);
		if(di != -1)
			emailBody.setDI(di);
		UnicodeString subject = "@system_msg:manf_done_sub";
		chatManager->sendMail(getObjectName()->getStringID(), subject, emailBody, currentUser->getFirstName());
	}

	updateToDatabase();
}

void FactoryObjectImplementation::createNewObject() {

	/// Pre: _this locked
	if (getContainerObjectsSize() == 0) {
		stopFactory("manf_error", "", "", -1);
		return;
	}

	ManagedReference<ManufactureSchematic*> schematic =
			(ManufactureSchematic*) getContainerObject(0);

	if (schematic == NULL) {
		stopFactory("manf_error_4", "", "", -1);
		return;
	}

	ManagedReference<TangibleObject*> prototype =
			(TangibleObject*) schematic->getPrototype();

	if (prototype == NULL) {
		stopFactory("manf_error_2", "", "", -1);
		return;
	}

	try {

		if (removeIngredientsFromHopper(schematic)) {

			ManagedReference<FactoryCrate*> crate = locateCrateInOutputHopper(
					prototype);

			if (crate == NULL)
				crate = createNewFactoryCrate(prototype->getGameObjectType(),
						prototype);
			else
				crate->setUseCount(crate->getUseCount() + 1);

			if (crate == NULL) {
				stopFactory("manf_error_7", "", "", -1);
				return;
			}

			Reference<Task*> pending = getPendingTask("createFactoryObject");

			if (pending != NULL)
				pending->reschedule(timer * 1000);
			else
				stopFactory("manf_error", "", "", -1);

			currentRunCount++;
		}

		updateToDatabase();
	} catch (...) {
		error(
				"unhandled exception in FactoryObjectImplementation::createNewObject()");
	}
}

FactoryCrate* FactoryObjectImplementation::locateCrateInOutputHopper(TangibleObject* prototype) {

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL || prototype == NULL) {
		stopFactory("manf_error_6", "", "", -1);
		return false;
	}

	for (int i = 0; i < outputHopper->getContainerObjectsSize(); ++i) {

		ManagedReference<SceneObject* > object = outputHopper->getContainerObject(i);

		if(object == NULL || !object->isFactoryCrate())
			continue;

		FactoryCrate* crate = (FactoryCrate*) object.get();

		if(crate->getPrototype() != NULL && crate->getPrototype()->getCraftersSerial() ==
				prototype->getCraftersSerial() && crate->getUseCount() < FactoryCrate::MAXCAPACITY) {

			return crate;
		}

	}
	return NULL;
}

FactoryCrate* FactoryObjectImplementation::createNewFactoryCrate(uint32 type, TangibleObject* prototype) {

	String file;

	if(type & SceneObject::ARMOR)
		file = "object/factory/factory_crate_armor.iff";
	else if(type == SceneObject::CHEMICAL || type == SceneObject::PHARMACEUTICAL || type == SceneObject::PETMEDECINE)
		file = "object/factory/factory_crate_chemicals.iff";
	else if(type & SceneObject::CLOTHING)
		file = "object/factory/factory_crate_clothing.iff";
	else if(type == SceneObject::ELECTRONICS)
		file = "object/factory/factory_crate_electronics.iff";
	else if(type == SceneObject::FOOD || type == SceneObject::DRINK)
		file = "object/factory/factory_crate_food.iff";
	else if(type == SceneObject::FURNITURE)
		file = "object/factory/factory_crate_furniture.iff";
	else if(type & SceneObject::INSTALLATION)
		file = "object/factory/factory_crate_installation.iff";
	else if(type == SceneObject::WEAPON)
		file = "object/factory/factory_crate_weapon.iff";
	else
		file = "object/factory/factory_crate_generic_items.iff";

	ObjectManager* objectManager = ObjectManager::instance();

	FactoryCrate* crate = (FactoryCrate*) server->getZoneServer()->createObject(file.hashCode(), 2);

	if (crate == NULL) {
		stopFactory("manf_error_7", "", "", -1);
		return NULL;
	}

	ManagedReference<TangibleObject*> protoclone = (TangibleObject*) objectManager->cloneObject(prototype);

	if (protoclone == NULL) {
		stopFactory("manf_error", "", "", -1);
		return NULL;
	}

	crate->setPrototype(protoclone);

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if(outputHopper == NULL) {
		stopFactory("manf_error_6", "", "", -1);
		return false;
	}

	outputHopper->addObject(crate, -1, false);
	broadcastObject(crate, true);

	return crate;
}

bool FactoryObjectImplementation::removeIngredientsFromHopper(ManufactureSchematic* schematic) {
	/// List Ingredients

	VectorMap<SceneObject*, int> alteredObjects;
	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if(inputHopper == NULL)
		return false;

	for (int i = 0; i < schematic->getFactoryIngredientsSize(); ++i) {

		ManagedReference<SceneObject*> ingredient =
				(SceneObject*) schematic->getFactoryIngredient(i);

		if (ingredient == NULL)
			return false;

		bool found = false;

		for(int i = 0; i < inputHopper->getContainerObjectsSize(); ++i) {

			ManagedReference<SceneObject* > object = inputHopper->getContainerObject(i);

			if(object == NULL)
				continue;

			if(ingredient->isResourceContainer() && object->isResourceContainer()) {

				ResourceContainer* rcnoIngredient = (ResourceContainer*) ingredient.get();
				ResourceContainer* rcnoObject = (ResourceContainer*) object.get();

				if(rcnoIngredient == NULL || rcnoObject == NULL) {
					error("NULL ingredient in removeIngredientsFromHopper");
					continue;
				}

				if(rcnoIngredient->getSpawnObject() == NULL || rcnoObject->getSpawnObject() == NULL) {
					error("NULL resource SpawnObject in removeIngredientsFromHopper");
					continue;
				}

				if(rcnoIngredient->getSpawnName() == rcnoObject->getSpawnName()) {
System::out << "Needs: " << rcnoIngredient->getSpawnName() << ":" << rcnoIngredient->getQuantity() << " Found: " << rcnoObject->getSpawnName() << " " << rcnoObject->getQuantity() << endl;

					int neededQuantity = rcnoIngredient->getQuantity();

					if(alteredObjects.contains(rcnoObject))
						neededQuantity += alteredObjects.get(rcnoObject);

					if(neededQuantity > rcnoObject->getQuantity()) {

						if(rcnoObject->getSpawnName() != "")
							stopFactory("manf_no_named_resource", getObjectName()->getStringID(), rcnoObject->getSpawnName(), -1);
						else
							stopFactory("manf_no_unknown_resource", getObjectName()->getStringID(), "", -1);

						return false;
					}

					found = true;
					alteredObjects.put(rcnoObject, neededQuantity);
					break;
				}

			} else {

				if(ingredient->isTangibleObject() && object->isTangibleObject()) {

					TangibleObject* tanoIngredient = (TangibleObject*) ingredient.get();
					TangibleObject* tanoObject = (TangibleObject*) object.get();

					if(tanoIngredient->getCraftersSerial() == tanoObject->getCraftersSerial()) {
System::out << tanoObject->getObjectNameStringIdName() << " " << tanoObject->getUseCount() << endl;

						int neededQuantity = tanoIngredient->getUseCount();

						if(alteredObjects.contains(tanoObject))
							neededQuantity += alteredObjects.get(tanoObject);

						if(neededQuantity >= tanoObject->getUseCount()) {

							if(tanoObject->getCustomObjectName().toString() == "")
								stopFactory("manf_no_component", getObjectName()->getStringID(), tanoObject->getObjectName()->getStringID(), -1);
							else
								stopFactory("manf_no_component", getObjectName()->getStringID(), tanoObject->getCustomObjectName().toString(), -1);

							return false;
						}

						found = true;
						alteredObjects.put(tanoObject, neededQuantity);
						break;
					}
				}
			}
		}

		if(!found)
			return false;
	}

	for(int i = 0; i < alteredObjects.size(); ++i) {

		ManagedReference<SceneObject* > object = alteredObjects.elementAt(i).getKey();
		int quantity = alteredObjects.get(i);

		if(object->isResourceContainer()) {

			ResourceContainer* rcnoObject = (ResourceContainer*) object.get();
			int currentQuantity = rcnoObject->getQuantity();
			rcnoObject->setQuantity(currentQuantity - quantity);
System::out << rcnoObject->getSpawnName() << " " << currentQuantity << "->" << rcnoObject->getQuantity() << endl;
			ResourceContainerObjectDeltaMessage3* rcnod3 = new ResourceContainerObjectDeltaMessage3(rcnoObject);
			rcnod3->setQuantity(rcnoObject->getQuantity());
			rcnod3->close();
			broadcastMessage(rcnod3, true);

		} else {

			TangibleObject* tanoObject = (TangibleObject*) object.get();
			int currentQuantity = tanoObject->getUseCount();
			tanoObject->setUseCount(currentQuantity - quantity);
System::out << tanoObject->getObjectNameStringIdName() << " " << currentQuantity << "->" << tanoObject->getUseCount() << endl;
			TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(tanoObject);
			dtano3->setQuantity(tanoObject->getUseCount());
			dtano3->close();
			broadcastMessage(dtano3, true);
		}
	}

	return true;
}
