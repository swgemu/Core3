/*
 * FactoryObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: kyle
 */

#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "server/zone/objects/installation/factory/FactoryHopperObserver.h"
#include "sui/InsertSchematicSuiCallback.h"
#include "tasks/CreateFactoryObjectTask.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneClientSession.h"
#include "server/chat/ChatManager.h"
#include "server/zone/packets/factory/FactoryCrateObjectDeltaMessage3.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/ClientOpenContainerMessage.h"
#include "server/zone/managers/object/ObjectManager.h"

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

#include "templates/installation/FactoryObjectTemplate.h"
#include "server/zone/objects/transaction/TransactionLog.h"

//#define DEBUG_FACTORIES

void FactoryObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	InstallationObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isFactoryObjectTemplate())
		return;

	FactoryObjectTemplate* factory = dynamic_cast<FactoryObjectTemplate*>(templateData);

	craftingTabsSupported = factory->getCraftingTabsSupported();
}

void FactoryObjectImplementation::notifyLoadFromDatabase() {
	InstallationObjectImplementation::notifyLoadFromDatabase();

	FactoryObject* thisFactory = _this.getReferenceUnsafeStaticCast();

	setLoggingName("FactoryObject");

	if (isActive()) {
		Core::getTaskManager()->executeTask([factory = WeakReference<FactoryObject*>(_this.getReferenceUnsafeStaticCast())]() {
			auto factoryStrong = factory.get();

			if (factoryStrong != nullptr) {
				Locker lock(factoryStrong);
				factoryStrong->startFactory();
			}
		}, "StartFactoryLambda");
	}

	hopperObserver = new FactoryHopperObserver(_this.getReferenceUnsafeStaticCast());
	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (inputHopper != nullptr) {
		Locker lock(inputHopper, thisFactory);

		inputHopper->registerObserver(ObserverEventType::OPENCONTAINER, hopperObserver);
		inputHopper->registerObserver(ObserverEventType::CLOSECONTAINER, hopperObserver);

		inputHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
	}

	if (outputHopper != nullptr) {
		Locker lock(outputHopper, thisFactory);

		outputHopper->registerObserver(ObserverEventType::OPENCONTAINER, hopperObserver);
		outputHopper->registerObserver(ObserverEventType::CLOSECONTAINER, hopperObserver);

		outputHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
	}
}

void FactoryObjectImplementation::createChildObjects() {
	FactoryObject* thisFactory = _this.getReferenceUnsafeStaticCast();

	// Create the observer for the hoppers
	hopperObserver = new FactoryHopperObserver(_this.getReferenceUnsafeStaticCast());

	if (hopperObserver == nullptr) {
		error() << "Factory has a nullptr to its hopper observer - FactoryID: " << getObjectID();
		return;
	}

	// Create ingredient hopper
	String ingredientHopperName = "object/tangible/hopper/manufacture_installation_ingredient_hopper_1.iff";
	ManagedReference<SceneObject*> ingredientHopper = server->getZoneServer()->createObject(ingredientHopperName.hashCode(), getPersistenceLevel());

	if (ingredientHopper == nullptr) {
		error() << "Factory has a nullptr to its ingredient hopper - FactoryID: " << getObjectID();
		return;
	}

	Locker ilocker(ingredientHopper, thisFactory);

	ingredientHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);

	transferObject(ingredientHopper, 4);

	ingredientHopper->registerObserver(ObserverEventType::OPENCONTAINER, hopperObserver);
	ingredientHopper->registerObserver(ObserverEventType::CLOSECONTAINER, hopperObserver);

	ilocker.release();

	// Create Output hopper
	String outputHopperName = "object/tangible/hopper/manufacture_installation_output_hopper_1.iff";
	ManagedReference<SceneObject*> outputHopper = server->getZoneServer()->createObject(outputHopperName.hashCode(), getPersistenceLevel());

	if (outputHopper == nullptr) {
		error() << "Factory has a nullptr to its output hopper - FactoryID: " << getObjectID();
		return;
	}

	Locker olocker(outputHopper, thisFactory);
	outputHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);

	transferObject(outputHopper, 4);

	outputHopper->registerObserver(ObserverEventType::OPENCONTAINER, hopperObserver);
	outputHopper->registerObserver(ObserverEventType::CLOSECONTAINER, hopperObserver);
}

void FactoryObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	InstallationObjectImplementation::fillAttributeList(alm, object);

	if (isActive() && object != nullptr && isOnAdminList(object)) {
		if (getContainerObjectsSize() == 0)
			return;

		ManagedReference<ManufactureSchematic*> schematic = getContainerObject(0).castTo<ManufactureSchematic*>();

		if (schematic == nullptr)
			return;

		ManagedReference<TangibleObject*> prototype = dynamic_cast<TangibleObject*>(schematic->getPrototype());

		if (prototype != nullptr) {
			alm->insertAttribute("manufacture_object", prototype->getDisplayedName());
		}

		alm->insertAttribute("manufacture_time", timer);

		ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

		if (outputHopper != nullptr) {
			alm->insertAttribute("manf_limit", schematic->getManufactureLimit());
			alm->insertAttribute("manufacture_count", currentRunCount); // Manufactured Items:
		}
	}
}

void FactoryObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	if (player == nullptr || player->getClient() == nullptr)
		return;

#ifdef DEBUG_FACTORIES
	info(true) << "sendTo - Player: " << player->getDisplayedName();
#endif

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	link(player, containmentType);

	try {
		sendBaselinesTo(player);
	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (doClose) {
		SceneObjectImplementation::close(player);
	}
}

/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendInsertManuSui(CreatureObject* player) {
	ManagedReference<SuiListBox*> schematics = nullptr;

	if (getContainerObjectsSize() == 0) {
		schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC2BUTTON, SuiListBox::HANDLETWOBUTTON);
		schematics->setPromptText("Choose a schematic to be added to the factory.");
	} else {
		schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC3BUTTON, SuiListBox::HANDLETHREEBUTTON);

		StringBuffer message;
		message << "Current Schematic Installed: ";

		if (getContainerObject(0)->getCustomObjectName().isEmpty())
			message << "@" << getContainerObject(0)->getObjectNameStringIdFile() << ":" << getContainerObject(0)->getObjectNameStringIdName();
		else
			message << getContainerObject(0)->getCustomObjectName().toString();

		schematics->setPromptText(message.toString());

		schematics->setOtherButton(true, "@remove_schematic");
	}

	schematics->setHandlerText("handleUpdateSchematic");
	schematics->setPromptTitle("SCHEMATIC MANAGEMENT"); // found a SS with this as the title so...

	schematics->setOkButton(true, "@use_schematic");
	schematics->setCancelButton(true, "@cancel");

	/*
	 * Insert only the schematics that can be used in this type of factory
	 */
	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> datapadObject = datapad->getContainerObject(i);

		if (datapadObject != nullptr && datapadObject->isManufactureSchematic()) {
			ManagedReference<ManufactureSchematic*> manSchem = dynamic_cast<ManufactureSchematic*>(datapadObject.get());

			if (manSchem->getDraftSchematic() == nullptr)
				continue;

			uint32 craftingTabId = manSchem->getDraftSchematic()->getToolTab();

			bool match = false;

			for (int j = 0; j < craftingTabsSupported.size(); ++j) {
				if (craftingTabId == craftingTabsSupported.get(j)) {
					match = true;
					break;
				}
			}

			if (!match)
				continue;

			String sendname;

			if (manSchem->getCustomObjectName().isEmpty())
				sendname = "@" + manSchem->getObjectNameStringIdFile() + ":" + manSchem->getObjectNameStringIdName();
			else
				sendname = manSchem->getCustomObjectName().toString();

			schematics->addMenuItem(sendname, manSchem->getObjectID());
		}
	}

	schematics->setCallback(new InsertSchematicSuiCallback(server->getZoneServer()));

	schematics->setUsingObject(_this.getReferenceUnsafeStaticCast());
	player->getPlayerObject()->addSuiBox(schematics);
	player->sendMessage(schematics->generateMessage());
}

/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendIngredientsNeededSui(CreatureObject* player) {
	if (getContainerObjectsSize() == 0)
		return;

	ManagedReference<SuiListBox*> ingredientList = new SuiListBox(player, SuiWindowType::FACTORY_INGREDIENTS);
	ingredientList->setPromptTitle("@base_player:swg"); // STAR WARS GALAXIES - found a SS with this as the title so....

	ingredientList->setPromptText("@manf_station:examine_prompt"); // Ingredients required to manufacture an item at this station.

	ingredientList->setOkButton(true, "@ok");

	ManagedReference<ManufactureSchematic*> schematic = getContainerObject(0).castTo<ManufactureSchematic*>();

	for (int i = 0; i < schematic->getBlueprintSize(); ++i) {
		BlueprintEntry* blueprintEntry = schematic->getBlueprintEntry(i);
		blueprintEntry->insertFactoryIngredient(ingredientList);
	}

	ingredientList->setUsingObject(_this.getReferenceUnsafeStaticCast());
	player->getPlayerObject()->addSuiBox(ingredientList);
	player->sendMessage(ingredientList->generateMessage());
}

void FactoryObjectImplementation::sendIngredientHopper(CreatureObject* player) {
	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if (inputHopper == nullptr) {
		return;
	}

#ifdef DEBUG_FACTORIES
	info(true) << "sendIngredientHopper - Player: " << player->getFirstName();
#endif

	inputHopper->sendWithoutContainerObjectsTo(player);
	inputHopper->openContainerTo(player);
	inputHopper->notifyObservers(ObserverEventType::OPENCONTAINER, player);
}

void FactoryObjectImplementation::sendOutputHopper(CreatureObject* player) {
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (outputHopper == nullptr) {
		return;
	}

#ifdef DEBUG_FACTORIES
	info(true) << "sendOutputHopper - Player: " << player->getFirstName();
#endif

	outputHopper->sendWithoutContainerObjectsTo(player);

	ClientOpenContainerMessage* cont = new ClientOpenContainerMessage(outputHopper);
	player->sendMessage(cont);

	int hopperSize = outputHopper->getContainerObjectsSize();

#ifdef DEBUG_FACTORIES
	info(true) << "sendOutputHopper - Hopper Size = " << hopperSize;
#endif

	for (int j = 0; j < hopperSize; ++j) {
		SceneObject* child = outputHopper->getContainerObject(j);

		if (child == nullptr) {
			continue;
		}

#ifdef DEBUG_FACTORIES
		child->info(true) << "Sending Object To Player: " << player->getDisplayedName() << " Object: " << child->getDisplayedName();
#endif

		child->sendTo(player, true, true);
	}
}

void FactoryObjectImplementation::openHopper(Observable* observable, ManagedObject* arg1) {
	if (observable == nullptr || arg1 == nullptr)
		return;

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(arg1);
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");
	ManagedReference<SceneObject*> sceneObserv = cast<SceneObject*>(observable);

	if (player == nullptr || outputHopper == nullptr || sceneObserv == nullptr)
		return;

#ifdef DEBUG_FACTORIES
	info(true) << "openHopper - Player: " << player->getFirstName();
#endif

	Locker clock(player, _this.getReferenceUnsafeStaticCast());

	addOperator(player);
}

void FactoryObjectImplementation::closeHopper(Observable* observable, ManagedObject* arg1) {
#ifdef DEBUG_FACTORIES
	info(true) << "closeHopper";
#endif

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(arg1);
	ManagedReference<SceneObject*> hopper = cast<SceneObject*>(observable);

	if (player == nullptr || hopper == nullptr)
		return;

#ifdef DEBUG_FACTORIES
	info(true) << "closeHopper - Player: " << player->getFirstName();
#endif

	FactoryObject* thisFactory = _this.getReferenceUnsafeStaticCast();

	Locker lock(thisFactory);
	/*
	for (int i = 0; i < outputHopper->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> item = outputHopper->getContainerObject(i);

		if (item == nullptr)
			continue;

#ifdef DEBUG_FACTORIES
		info(true) << "closeHopper - Item sending destroy: " << item->getDisplayedName();
#endif
		item->sendDestroyTo(player);
	}

#ifdef DEBUG_FACTORIES
		info(true) << "closeHopper - Hopper sending destroy.";
#endif

	hopper->sendDestroyTo(player);*/

	Locker clock(player, thisFactory);

	removeOperator(player);
}

void FactoryObjectImplementation::handleInsertFactorySchem(CreatureObject* player, ManufactureSchematic* schematic) {
	if (player == nullptr || schematic == nullptr || !schematic->isASubChildOf(player))
		return;

	/// pre: player and _this.getReferenceUnsafeStaticCast() are locked
	if (!schematic->isManufactureSchematic()) {
		StringIdChatParameter message("manf_station", "schematic_not_added"); // Schematic %TT was not added to the station.

		if (schematic->getCustomObjectName().isEmpty())
			message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
		else
			message.setTT(schematic->getCustomObjectName().toString());

		player->sendSystemMessage(message);

		return;
	}

	TransactionLog trx(player, asSceneObject(), schematic, TrxCode::FACTORYOPERATION);

	if (transferObject(schematic, -1, true)) {
		StringIdChatParameter message("manf_station", "schematic_added"); // Schematic %TT has been inserted into the station. The station is now ready to manufacture items.

		if (schematic->getCustomObjectName().isEmpty())
			message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
		else
			message.setTT(schematic->getCustomObjectName().toString());

		player->sendSystemMessage(message);

		player->sendSystemMessage("This schematic limit is: " + String::valueOf(schematic->getManufactureLimit()));
	} else {
		trx.abort() << "transferObject failed.";

		StringIdChatParameter message("manf_station", "schematic_not_added"); // Schematic %TT was not added to the station

		if (schematic->getCustomObjectName().isEmpty())
			message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
		else
			message.setTT(schematic->getCustomObjectName().toString());

		player->sendSystemMessage(message);
	}
}

bool FactoryObjectImplementation::handleRemoveFactorySchem(CreatureObject* player) {
	if (player == nullptr)
		return false;

	/// pre: player and _this.getReferenceUnsafeStaticCast() are locked

	if (getContainerObjectsSize() == 0) {
		return false;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");
	ManagedReference<SceneObject*> schematic = getContainerObject(0);

	if (datapad == nullptr || schematic == nullptr || !schematic->isManufactureSchematic())
		return false;

	ManagedReference<ManufactureSchematic*> manuSchem = schematic.castTo<ManufactureSchematic*>();

	if (manuSchem == nullptr)
		return false;

	Locker locker(schematic);

	TransactionLog trx(asSceneObject(), player, schematic, TrxCode::FACTORYOPERATION);

	int dataSize = manuSchem->getDataSize();

	if ((dataSize + datapad->getContainerObjectsSize()) > datapad->getContainerVolumeLimit()) {
		trx.abort() << "Failed to transfer schematic out of factory due to full datapad.";

		sendRemoveFailureMessage(player, manuSchem);
		return false;
	}

	if (!datapad->transferObject(schematic, -1, false)) {
		trx.abort() << "Failed to transfer schematic out of factory.";

		sendRemoveFailureMessage(player, manuSchem);

		return false;
	}

	datapad->broadcastObject(schematic, true);

	StringIdChatParameter message("manf_station", "schematic_removed"); // Schematic %TT has been removed from the station and been placed in your datapad. Have a nice day!

	if (schematic->getCustomObjectName().isEmpty()) {
		message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
	} else {
		message.setTT(schematic->getCustomObjectName().toString());
	}

	player->sendSystemMessage(message);

	return true;
}

void FactoryObjectImplementation::handleOperateToggle(CreatureObject* player) {
	if (getContainerObjectsSize() == 0) {
		player->sendSystemMessage("No schematic, unable to start");
		return;
	}

	ManagedReference<ManufactureSchematic*> schematic = getContainerObject(0).castTo<ManufactureSchematic*>();

	if (schematic == nullptr) {
		player->sendSystemMessage("No schematic, unable to start");
		return;
	}

	if (!isActive()) {
		currentUserName = player->getFirstName();
		currentRunCount = 0;

		if (startFactory()) {
			player->sendSystemMessage("@manf_station:activated"); // Station activated
			player->sendSystemMessage("This schematic limit is: " + String::valueOf(schematic->getManufactureLimit()));
		}
	} else {
		stopFactory("manf_done", getDisplayedName(), "", currentRunCount);
		player->sendSystemMessage("@manf_station:deactivated"); // Station deactivated
		currentUserName = "";
	}
}

bool FactoryObjectImplementation::startFactory() {
	if (getContainerObjectsSize() == 0) {
		return false;
	}

#ifdef DEBUG_FACTORIES
	info(true) << "startFactory - called";
#endif

	ManagedReference<ManufactureSchematic*> schematic = getContainerObject(0).castTo<ManufactureSchematic*>();

	if (schematic == nullptr)
		return false;

	ManagedReference<TangibleObject*> prototype = schematic->getPrototype();

	if (prototype == nullptr)
		return false;

	if (prototype->isSliced() || prototype->hasAntiDecayKit())
		return false;

	if (prototype->isWeaponObject()) {
		WeaponObject* weapon = prototype.castTo<WeaponObject*>();

		if (weapon->hasPowerup())
			return false;
	}

#ifdef DEBUG_FACTORIES
	timer = 30;
	info(true) << "Factory Testing Timer Set To: " << timer;
#else
	timer = ((int)schematic->getComplexity()) * 8;
#endif

	if (!populateSchematicBlueprint(schematic))
		return false;

	// Add sampletask
	Reference<CreateFactoryObjectTask*> createFactoryObjectTask = new CreateFactoryObjectTask(_this.getReferenceUnsafeStaticCast());
	addPendingTask("createFactoryObject", createFactoryObjectTask, timer * 1000);

	setActive(true, true);

	return true;
}

bool FactoryObjectImplementation::populateSchematicBlueprint(ManufactureSchematic* schematic) {
	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if (inputHopper == nullptr) {
		error("Factory Ingredient Hopper missing.  WTF");
		return false;
	}

	for (int i = 0; i < schematic->getBlueprintSize(); ++i) {
		BlueprintEntry* entry = schematic->getBlueprintEntry(i);
		entry->setHopper(inputHopper);
		collectMatchesInInputHopper(entry, inputHopper);
	}
	return true;
}

void FactoryObjectImplementation::stopFactory(const String& message, const String& tt, const String& to, const int di) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());

#ifdef DEBUG_FACTORIES
	info(true) << "stopFactory - called";
#endif

	setActive(false, true);

	Reference<Task*> pending = getPendingTask("createFactoryObject");
	removePendingTask("createFactoryObject");

	if (pending != nullptr && pending->isScheduled())
		pending->cancel();

	// Send out email informing them why their factory stopped
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager != nullptr && currentUserName != "") {
		StringIdChatParameter emailBody;
		emailBody.setStringId("@system_msg:" + message);
		if (tt != "")
			emailBody.setTT(tt);
		if (to != "")
			emailBody.setTO(to);
		if (di != -1)
			emailBody.setDI(di);
		UnicodeString subject = "@system_msg:manf_done_sub";

		/*WaypointObject* newwaypoint = cast<WaypointObject*>( server->getZoneServer()->createObject(0xc456e788, 1));

		newwaypoint->setCustomName(UnicodeString(this->getDisplayedName()));
		newwaypoint->setPlanetCRC(Planet::getPlanetCRC(getZone()->getPlanetName()));
		newwaypoint->setPosition(this->getPositionX(), this->getPositionZ(), this->getPositionY());
		newwaypoint->setColor(WaypointObject::COLOR_BLUE);
		newwaypoint->setActive(false);

		chatManager->sendMail(getDisplayedName(), subject, emailBody, currentUserName, newwaypoint);*/

		chatManager->sendMail(getDisplayedName(), subject, emailBody, currentUserName);
	}
}

void FactoryObjectImplementation::stopFactory(String& type, String& displayedName) {
	if (type == "resource") {
		if (displayedName == "")
			stopFactory("manf_no_unknown_resource", getDisplayedName(), "", -1);
		else
			stopFactory("manf_no_named_resource", getDisplayedName(), displayedName, -1);

	} else {
		stopFactory("manf_no_component", getDisplayedName(), displayedName, -1);
	}
}

void FactoryObjectImplementation::createNewObject() {
	/// Pre: _this.getReferenceUnsafeStaticCast() locked

#ifdef DEBUG_FACTORIES
	info(true) << "createNewObject - called";
#endif

	if (getContainerObjectsSize() == 0) {
		stopFactory("manf_error", "", "", -1);
		return;
	}

	ManagedReference<ManufactureSchematic*> schematic = getContainerObject(0).castTo<ManufactureSchematic*>();

	if (schematic == nullptr || !schematic->isManufactureSchematic()) {
		stopFactory("manf_error_4", "", "", -1);
		return;
	}

	ManagedReference<TangibleObject*> prototype = cast<TangibleObject*>(schematic->getPrototype());

	if (prototype == nullptr) {
		stopFactory("manf_error_2", "", "", -1);
		return;
	}

	/// Shutdown when out of power or maint
	Time timeToWorkTill;
	bool shutdownAfterWork = updateMaintenance(timeToWorkTill);

	if (shutdownAfterWork) {
		Time currentTime;

		float elapsedTime = (currentTime.getTime() - lastMaintenanceTime.getTime());

		float energyAmount = (elapsedTime / 3600.0) * getBasePowerRate();
		if (energyAmount > surplusPower) {
			stopFactory("manf_no_power", getDisplayedName(), "", -1);
			return;
		}

		stopFactory("manf_done_sub", "", "", -1);
		return;
	}

	verifyOperators();

	String type = "";
	String displayedName = "";

	schematic->canManufactureItem(type, displayedName);

	if (displayedName != "") {
		stopFactory(type, displayedName);
		return;
	}

	int crateSize = schematic->getFactoryCrateSize();

	if (crateSize <= 0) {
		stopFactory("manf_error", "", "", -1);
		return;
	}

	if (crateSize > 1) {
		String crateType = schematic->getFactoryCrateType();

		ManagedReference<FactoryCrate*> crate = locateCrateInOutputHopper(prototype);

		if (crate == nullptr)
			crate = createNewFactoryCrate(prototype, crateSize, crateType);
		else {
			Locker clocker(crate, _this.getReferenceUnsafeStaticCast());
			crate->setUseCount(crate->getUseCount() + 1, true);
		}

		if (crate == nullptr) {
			return;
		}

		FactoryCrateObjectDeltaMessage3* dfcty3 = new FactoryCrateObjectDeltaMessage3(crate);
		dfcty3->setQuantity(crate->getUseCount());
		dfcty3->close();

		broadcastToOperators(dfcty3);
	} else {
		ManagedReference<TangibleObject*> newItem = createNewUncratedItem(prototype);

		if (newItem == nullptr)
			return;
	}

	Locker clocker(schematic, _this.getReferenceUnsafeStaticCast());

	schematic->manufactureItem(_this.getReferenceUnsafeStaticCast());
	currentRunCount++;

	if (schematic->getManufactureLimit() < 1) {
		schematic->destroyObjectFromWorld(true);
		schematic->destroyObjectFromDatabase(true);
		stopFactory("manf_done", getDisplayedName(), "", currentRunCount);
		return;
	}

	Reference<Task*> pending = getPendingTask("createFactoryObject");

	if (pending != nullptr)
		pending->reschedule(timer * 1000);
	else
		stopFactory("manf_error", "", "", -1);
}

FactoryCrate* FactoryObjectImplementation::locateCrateInOutputHopper(TangibleObject* prototype) {
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (outputHopper == nullptr || prototype == nullptr) {
		stopFactory("manf_error_6", "", "", -1);
		return nullptr;
	}

	for (int i = 0; i < outputHopper->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = outputHopper->getContainerObject(i);

		if (object == nullptr || !object->isFactoryCrate())
			continue;

		FactoryCrate* crate = cast<FactoryCrate*>(object.get());

		if (crate->getPrototype() != nullptr && crate->getPrototype()->getSerialNumber() == prototype->getSerialNumber() && crate->getUseCount() < crate->getMaxCapacity()) {
			return crate;
		}
	}

	return nullptr;
}

FactoryCrate* FactoryObjectImplementation::createNewFactoryCrate(TangibleObject* prototype, int maxSize, String& type) {
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (outputHopper == nullptr) {
		stopFactory("manf_error_6", "", "", -1);
		return nullptr;
	}

	if (outputHopper->isContainerFull()) {
		stopFactory("manf_output_hopper_full", getDisplayedName(), "", -1);
		return nullptr;
	}

	ManagedReference<FactoryCrate*> crate = prototype->createFactoryCrate(maxSize, type, false);

	if (crate == nullptr) {
		stopFactory("manf_error_7", "", "", -1);
		return nullptr;
	}

	outputHopper->transferObject(crate, -1, true);

	return crate;
}

TangibleObject* FactoryObjectImplementation::createNewUncratedItem(TangibleObject* prototype) {
	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (outputHopper == nullptr) {
		stopFactory("manf_error_6", "", "", -1);
		return nullptr;
	}

	if (outputHopper->isContainerFull()) {
		stopFactory("manf_output_hopper_full", getDisplayedName(), "", -1);
		return nullptr;
	}

	ObjectManager* objectManager = ObjectManager::instance();
	ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>(objectManager->cloneObject(prototype->asTangibleObject()));

	if (protoclone == nullptr) {
		stopFactory("manf_error_8", "", "", -1);
		return nullptr;
	}

	protoclone->setParent(nullptr);
	outputHopper->transferObject(protoclone, -1, true);

	return protoclone;
}

void FactoryObjectImplementation::collectMatchesInInputHopper(BlueprintEntry* entry, SceneObject* inputHopper) {
	entry->clearMatches();
	for (int i = 0; i < inputHopper->getContainerObjectsSize(); ++i) {
		ManagedReference<TangibleObject*> object = inputHopper->getContainerObject(i).castTo<TangibleObject*>();

		if (object == nullptr) {
			error("nullptr hopper object in FactoryObjectImplementation::countItemInInputHopper");
			continue;
		}

		String key = "";
		String serial = "";

		if (object->isResourceContainer()) {
			ResourceContainer* rcnoObject = cast<ResourceContainer*>(object.get());

			key = rcnoObject->getSpawnName();

			if (entry->getKey() == key) {
				entry->addMatch(object);
				continue;
			}

		} else {
			TangibleObject* prototype = nullptr;

			if (object->isFactoryCrate()) {
				FactoryCrate* crate = cast<FactoryCrate*>(object.get());
				prototype = crate->getPrototype();
			} else {
				prototype = object;
			}

			key = String::valueOf(prototype->getServerObjectCRC());
			serial = prototype->getSerialNumber();

			if (entry->getKey() == key) {
				if (entry->needsIdentical()) {
					if (entry->getSerial() != serial)
						continue;
				}

				entry->addMatch(object);
			}
		}
	}
}

String FactoryObjectImplementation::getRedeedMessage() {
	if (isActive())
		return "deactivate_factory_for_delete";

	if (getContainerObjectsSize() > 0)
		return "remove_schematic_for_delete";

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if (inputHopper != nullptr && inputHopper->getContainerObjectsSize() > 0) {
		return "clear_input_hopper_for_delete";
	}

	ManagedReference<SceneObject*> outputHopper = getSlottedObject("output_hopper");

	if (outputHopper != nullptr && outputHopper->getContainerObjectsSize() > 0) {
		return "clear_output_hopper_for_delete";
	}

	return "";
}

void FactoryObjectImplementation::sendRemoveFailureMessage(CreatureObject* player, ManufactureSchematic* schematic) {
	if (player == nullptr || schematic == nullptr)
		return;

	StringIdChatParameter message("manf_station", "schematic_not_removed"); // Schematic %TT was not removed from the station and been placed in your datapad. Have a nice day!

	if (schematic->getCustomObjectName().isEmpty()) {
		message.setTT(schematic->getObjectNameStringIdFile(), schematic->getObjectNameStringIdName());
	} else {
		message.setTT(schematic->getCustomObjectName().toString());
	}

	player->sendSystemMessage(message);
}
