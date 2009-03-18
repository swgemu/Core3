/*
 * FactoryObjectImplementation.cpp
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"
#include "../../../Zone.h"
#include "../../../packets.h"
#include "../../../objects.h"

#include "FactoryObjectImplementation.h"
#include "../events/FactoryCreateItemEvent.h"


FactoryObjectImplementation::FactoryObjectImplementation(uint64 oid) : FactoryObjectServant(oid) {
	objectID = oid;

	//(InstallationObject*)_this
	InstallationObjectImplementation::init();
	init();
}


FactoryObjectImplementation::FactoryObjectImplementation(uint64 oid, FactoryDeed* deed) : FactoryObjectServant(oid, deed) {
	objectID = oid;

	InstallationObjectImplementation::init();
	init();

	objectCRC = deed->getTargetFile().hashCode();
	customName = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();


	setSurplusMaintenance(deed->getSurplusMaintenance());
	setMaintenanceRate(deed->getMaintenanceRate());
	setSurplusPower(deed->getSurplusPower());
	setPowerRate(deed->getPowerRate());
	setHopperSizeMax(deed->getHopperSize());
}

FactoryObjectImplementation::~FactoryObjectImplementation(){
	if (createItemEvent != NULL) {
		if (createItemEvent->isQueued())
			server->removeEvent(createItemEvent);

		delete createItemEvent;
		createItemEvent = NULL;
	}
}

void FactoryObjectImplementation::init() {
	objectSubType = TangibleObjectImplementation::FACTORY;

	inputHopper = NULL;
	outputHopper = NULL;

	createItemEvent = new FactoryCreateItemEvent(this);

	setOperating(false);
}

/*
 * This function creates the hoppers and loads the items for this factory.
 * if the Factory does not have a Zone, the containers will NOT get added to the zone,
 * therefore will not allow items to be inserted/removed
 * @param uint64 intputHopperID A new ID or loaded ID from the db
 * @param uint64 outputHopperID A new ID or loaded ID from the db
 */
void FactoryObjectImplementation::createHoppers(uint64 inputHopperID, uint64 outputHopperID){

	Container* input = new Container(inputHopperID);
	input->setParent(_this);
	input->setContainerVolumeLimit(50);
	Container* output = new Container(outputHopperID);
	output->setParent(_this);
	output->setContainerVolumeLimit(50);

	inputHopper = input;
	outputHopper = output;
	inputHopper->setObjectSubType(TangibleObjectImplementation::CONTAINER);
	//inputHopper->setSlots(100);
	outputHopper->setObjectSubType(TangibleObjectImplementation::CONTAINER);
	//outputHopper->setSlots(100);

	if(getZone()!=NULL){
		getZone()->getZoneServer()->addObject(inputHopper);
		getZone()->getZoneServer()->addObject(outputHopper);
	}
	serializeHoppers();
	loadItems();

}

/*
 * Sets up the radial menu for factory options and maintanence options
 * @param Player* player A reference to the player accessing this method
 * @param ObjectMenuResponse* omr A reference to the radial options
 */
void FactoryObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if(_this->getOwnerID() == player->getCharacterID()){

		RadialMenuParent* options = new RadialMenuParent(118, 3, "@manf_station:option");
		options->addRadialMenuItem(197, 3, "@manf_station:schematic");
		options->addRadialMenuItem(253, 3, "@manf_station:ingredients");
		options->addRadialMenuItem(195, 3, "@manf_station:input_hopper");
		options->addRadialMenuItem(196, 3, "@manf_station:output_hopper");
		if(_this->isOperating())
			options->addRadialMenuItem(254, 3, "@manf_station:deactivate");
		else
			options->addRadialMenuItem(254, 3, "@manf_station:activate");


		RadialMenuParent* management = new RadialMenuParent(117, 3, "@player_structure:management");
		management->addRadialMenuItem(128, 3, "@player_structure:permission_destroy");
		management->addRadialMenuItem(124, 3, "@player_structure:mangement_status");
		management->addRadialMenuItem(50, 3, "@player_structure:set_name");
		management->addRadialMenuItem(129, 3, "@player_structure:management_pay");
		management->addRadialMenuItem(77, 3, "@player_strucutre:management_power");

		omr->addRadialParent(options);
		omr->addRadialParent(management);
	}

	omr->finish();
	player->sendMessage(omr);
}

/*
 * Parses the attributes for a factory, including buildRate, inputHopperID, and outputHopperID.
 * After loading the hopperID's it attemps to create the hoppers and load items from the DB.
 */
void FactoryObjectImplementation::parseItemAttributes(){
	InstallationObjectImplementation::parseItemAttributes();

	String attr = "buildRate";
	setBuildRate(itemAttributes->getFloatAttribute(attr));

	if(inputHopper != NULL || outputHopper != NULL)
		return;

	attr = "inputHopperID";
	uint64 inputHopperID = itemAttributes->getUnsignedLongAttribute(attr);

	attr = "outputHopperID";
	uint64 outputHopperID = itemAttributes->getUnsignedLongAttribute(attr);

	createHoppers(inputHopperID, outputHopperID);
}

/*
 * Puts the inputHopperID and outputHopperID into the factories attributes so that they save/load from DB.
 */
void FactoryObjectImplementation::serializeHoppers(){
	String attr("inputHopperID");
	uint64 val = inputHopper->getObjectID();
	itemAttributes->setUnsignedLongAttribute(attr, val);

	attr = "outputHopperID";
	val = outputHopper->getObjectID();
	itemAttributes->setUnsignedLongAttribute(attr, val);
}

/*
 * Opens the input hopper to a player.
 * @param Player* player Reference of the player to send the input inventory screen to.
 */
void FactoryObjectImplementation::sendInputHopperTo(Player* player){
	if(inputHopper==NULL)
		return;
	inputHopper->sendTo(player);
	inputHopper->openTo(player);
}

/*
 * Opens the output hopper to a player.
 * @param Player* player Reference of the player to send the output inventory screen to.
 */
void FactoryObjectImplementation::sendOutputHopperTo(Player* player){
	if(outputHopper==NULL)
		return;
	outputHopper->sendTo(player);
	outputHopper->openTo(player);
}

/*
 * Sets the factory operation to the passed in state.
 * Begins or suspends item creation based on state.
 * @param bool state true or false.
 */
void FactoryObjectImplementation::setOperating(bool state){

	if(state == true)
		scheduleItemCreation();
	else{
		if(createItemEvent != NULL && createItemEvent->isQueued())
			server->removeEvent(createItemEvent);
	}

	InstallationObjectImplementation::setOperating(state);
}

/*
 * Schedules an item creation event for 8seconds * complexity of the item
 */
void FactoryObjectImplementation::scheduleItemCreation(){
	//if outputhopper is not full
	//schedule another event at 8*complexity seconds
	//else send an email to player saying it's finished
	int complexity = 1;

	ManufactureSchematic* manufSchem = _this->getManufactureSchem();
	if(manufSchem != NULL)
		complexity = manufSchem->getComplexity();

	if (createItemEvent != NULL && !createItemEvent->isQueued())
			server->addEvent(createItemEvent, 8000*complexity); // 8*complexity
}

/*
 * Creates an item in a factory crate if ingredients are present and places in output hopper
 */
void FactoryObjectImplementation::createItem(){

	ManufactureSchematic* linkedSchematic = _this->getManufactureSchem();

	if(linkedSchematic == NULL)
		return;
	if(_this->getZone() == NULL)
		return;
	ItemManager* itemManager = _this->getZone()->getZoneServer()->getItemManager();

	bool found = false;
	linkedSchematic->wlock();
	inputHopper->wlock();

	/*go through each ingredient and compare with the input hopper
	 *we cant take away the quantity on the first pass because we want to make sure
	 *that we have all the resources. otherwise if we used up all of a resource, we couldnt delete
	 *it in case we didnt have all the subsequent resources...therefore, we must check first.
	 */
	for (int i = 0; i < linkedSchematic->getIngredientSize(); ++i) {
		String ingredientName = linkedSchematic->getIngredientName(i);

		int j = 0;
		while ( j < inputHopper->getContainerObjectsSize() && !found) {
			SceneObject* scno = (SceneObject*) inputHopper->getObject(j);
			if(scno->isTangible()){
				TangibleObject* tano = (TangibleObject*) scno;

				if (tano->isResource()){
					ResourceContainer* rsco = (ResourceContainer*) scno;

					if (rsco->getResourceName() == ingredientName)
						found = true;
				}
				else if (tano->isComponent()){
					Component* comp = (Component*) scno;
					String name;

					if(comp->getCustomName().isEmpty())
						name = "@" + comp->getTemplateTypeName() + "#" + comp->getTemplateName() + " ";
					else
						name = comp->getCustomName().toString();

					name = name.concat(comp->getCraftedSerial());

					if(name == ingredientName)
						found = true;
				}
				else if (tano->isFactoryCrate()){
					FactoryCrate* crate = (FactoryCrate*) scno;
					TangibleObject* tano = crate->getTangibleObject();

					if(tano->isComponent()){
						Component* comp = (Component*) tano;
						String name;

						if(comp->getCustomName().isEmpty())
							name = "@" + comp->getTemplateTypeName() + "#" + comp->getTemplateName() + " ";
						else
							name = comp->getCustomName().toString();

						name = name.concat(comp->getCraftedSerial());

						if(name == ingredientName)
							found = true;
					}
				}
			}
			++j;
		}

		if(found == false){
			ChatManager* chatManager = _this->getZone()->getZoneServer()->getChatManager();

			String mailSender = _this->getCustomName().toString();

			StringBuffer bodyMsg;
			UnicodeString subjectSender("Ingredients Not Found");
			bodyMsg << "Your factory has run out of ingredients necessary to continue making items.";
			UnicodeString bodySender(bodyMsg.toString());

			chatManager->sendMail(mailSender, subjectSender, bodySender, _this->getOwner());

			inputHopper->unlock();
			return;
		}

		++i;
		found = false;
	}

	/*
	 * If we've made it this far, we know all of the resources are present. now we just need to take
	 * away the correct quantities. Unfortunately we have to search for the items again.
	 */
	for (int i = 0; i < linkedSchematic->getIngredientSize(); ++i) {
		String ingredientName = linkedSchematic->getIngredientName(i);
		int ingredientValue = linkedSchematic->getIngredientValue(i);

		int j = 0;
		while ( j < inputHopper->getContainerObjectsSize() && !found) {
			SceneObject* scno = (SceneObject*) inputHopper->getObject(j);

			if(scno->isTangible()){
				TangibleObject* tano = (TangibleObject*) scno;

				if (tano->isResource()){
					ResourceContainer* resco = (ResourceContainer*) scno;
					if (resco->getResourceName() == ingredientName){
						resco->setContents(resco->getContents() - ingredientValue);

						if(resco->getContents() < 1){
							inputHopper->removeObject(resco->getObjectID());
							//itemManager->deletePlayerStorageItem(rcno);
							//TODO:delete this item from player_storage table
							resco->finalize();
						}
					}
				}
				else if (tano->isComponent()){
					Component* comp = (Component*) scno;
					String name;

					if(comp->getCustomName().isEmpty())
						name = "@" + comp->getTemplateTypeName() + "#" + comp->getTemplateName() + " ";
					else
						name = comp->getCustomName().toString();

					name = name.concat(comp->getCraftedSerial());

					if(name == ingredientName){
						comp->setObjectCount(comp->getObjectCount() - ingredientValue);

						if(comp->getObjectCount() < 1){
							inputHopper->removeObject(comp->getObjectID());
							//itemManager->deletePlayerStorageItem(comp);
							//TODO:delete this item from player_storage table
							comp->finalize();
						}
					}
				}
				else if (tano->isFactoryCrate()){
					FactoryCrate* crate = (FactoryCrate*) scno;
					TangibleObject* tano = (TangibleObject*) crate->getTangibleObject();
					String name;

					if(tano->isComponent()){
						Component* comp = (Component*) tano;

						if(comp->getCustomName().isEmpty())
							name = "@" + comp->getTemplateTypeName() + "#" + comp->getTemplateName() + " ";
						else
							name = comp->getCustomName().toString();

						name = name.concat(comp->getCraftedSerial());

						if(name == ingredientName){
							crate->setObjectCount(crate->getObjectCount() - ingredientValue);

							if(crate->getObjectCount() < 1){
								inputHopper->removeObject(crate->getObjectID());
								//itemManager->deletePlayerStorageItem(comp);
								//TODO:delete this item from player_storage table
								crate->finalize();
							}
						}
					}
				}
			}
			++j;
		}
		++i;
	}

	/*
	 * Done with input hopper. Now it's time to use the output hopper.
	 * Now we have to create the item (clone it) if there isnt already a factory crate for it
	 */
	inputHopper->unlock();
	outputHopper->wlock();

	int i = 0;
	found = false;
	while ( i < outputHopper->getContainerObjectsSize() && !found) {
		SceneObject* scno = (SceneObject*) outputHopper->getObject(i);
		scno->wlock();

		if (scno->isTangible()){
			TangibleObject* tano = (TangibleObject*) scno;
			if(tano->isFactoryCrate()){
				FactoryCrate* crate = (FactoryCrate*) scno;
				TangibleObject* factObj = crate->getTangibleObject();
				TangibleObject* manfObj = linkedSchematic->getTangibleObject();
				factObj->wlock();
				manfObj->wlock();

				if ((factObj->getCraftedSerial() == manfObj->getCraftedSerial()) && crate->getObjectCount() < 25){
					found = true;
					if(crate->getObjectCount() == 0)
						crate->setObjectCount(2);
					else
						crate->setObjectCount(crate->getObjectCount() + 1);
				}
				factObj->unlock();
				manfObj->unlock();
			}
		}
		scno->unlock();
	}
	if (!found){//TODO:After 1 crate of 25 items is made, it freezes the server somewhere in here.
		TangibleObject* manfObj = linkedSchematic->getTangibleObject();
		manfObj->wlock();

		TangibleObject* clone = itemManager->clonePlayerObjectTemplate(_this->getZone()->getZoneServer()->getNextID(), manfObj);
		manfObj->unlock();

		//FactoryCrate* crate = new FactoryCrate(_this->getZone()->getZoneServer()->getNextID(), clone);
		FactoryCrate* crate = new FactoryCrate(_this->getZone()->getZoneServer()->getNextID(), 0x28D7B8E0, "A Factory Crate", "generic_items_crate");
		crate->setTangibleObject(clone);
		clone->setPersistent(true);
		crate->setPersistent(true);

		_this->getZone()->getZoneServer()->addObject(crate);
		outputHopper->addObject((SceneObject*)crate);
	}

	linkedSchematic->setManufacturingLimit(linkedSchematic->getManufacturingLimit() -1);
	if(linkedSchematic->getManufacturingLimit() < 1){
		linkedSchematic->finalize();
		linkedSchematic = NULL;
	}

	outputHopper->unlock();
	linkedSchematic->unlock();

}

/*
 * Opens a SUI with all manufacturing schematics available for the player to insert into factory
 */
void FactoryObjectImplementation::sendInsertManSchemTo(Player* player){

	SuiListBox* schematics = new SuiListBox(player, SuiWindowType::FACTORY_SCHEMATIC);
	schematics->setPromptTitle("STAR WARS GALAXIES");//found a SS with this as the title so....
	schematics->setPromptText("Choose a schematic to be added to the factory.");
	schematics->setCancelButton(true, "");

	/*
	 * Insert only the schematics that can be used in this type of factory
	 */
	Datapad* datapad = player->getDatapad();
	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		if(datapad->getObject(i)->isManufactureSchematic()){
			ManufactureSchematic* manSchem = (ManufactureSchematic*) datapad->getObject(i);

			TangibleObject* tano = manSchem->getTangibleObject();
			//TODO:make it only accept certain schematics
			//if (tano->getObjectType() & _this->getFactoryItemTypes()){
				String name;

				if(manSchem->getCustomName().isEmpty())
					name = "@" + tano->getTemplateTypeName() + "#" + tano->getTemplateName();
				else
					name = manSchem->getCustomName().toString();

				schematics->addMenuItem(name, manSchem->getObjectID());
			//}
		}
	}

	schematics->setUsingObjectID(_this->getObjectID());
	player->addSuiBox(schematics);
	player->sendMessage(schematics->generateMessage());
}

/*
 * Removes the current manufacture schematic from the facory and puts it back in the datapad of the player.
 */
void FactoryObjectImplementation::setManufactureSchem(ManufactureSchematic* manufactureSchem, Player* player) {
	if (_this->hasSchematic()) {
		SceneObject* scno = getObject(0);
		if (scno != NULL) {
			ManufactureSchematic* linkedSchematic = (ManufactureSchematic*) getObject(0);
			if (linkedSchematic->getManufacturingLimit() > 0){
				player->addDatapadItem(linkedSchematic);
			}
			else
				linkedSchematic->finalize();
		}
	}
	while(_this->getContainerObjectsSize() > 0)
		removeObject(0);

	addObject((SceneObject*)manufactureSchem);
}

/*
 * Opens a sui with the ingredients of the currently loaded manufacturing schematic.
 */
void FactoryObjectImplementation::sendViewIngredientsTo(Player* player){

	SuiListBox* ingredients = new SuiListBox(player, 0);
	ingredients->setPromptTitle("STAR WARS GALAXIES");//found a SS with this as the title so....
	if(_this->hasSchematic()){
		ingredients->setPromptText("@manf_station:examine_prompt");

		ManufactureSchematic* linkedSchematic = _this->getManufactureSchem();
		if(linkedSchematic == NULL)
			return;

		for (int i = 0; i < linkedSchematic->getIngredientSize(); ++i) {
			String ingredientName = linkedSchematic->getIngredientName(i);
			int ingredientValue = linkedSchematic->getIngredientValue(i);
			StringBuffer text;
			text <<  ingredientName << " : " << ingredientValue;

			ingredients->addMenuItem(text.toString());
		}
	}
	else
		ingredients->setPromptText("@manf_station:no_schematic_examine_prompt");

	player->sendMessage(ingredients->generateMessage());
	ingredients->finalize();
}

/*
 * Returns the factory type based on the object's objectCRC.
 */
int FactoryObjectImplementation::getFactoryType() {
	switch(objectCRC) {
	default:
		return 0;
	}
}

/*
 * Trying to use this so that you can gate which type of factory can make which items.
 */
int FactoryObjectImplementation::getFactoryItemTypes() {
	int items = 0;

	switch(objectCRC) {
	case 0xE9FB1618://wearables
		items = TangibleObjectImplementation::WEARABLECONTAINER | TangibleObjectImplementation::ARMOR
			| TangibleObjectImplementation::CLOTHING;
		break;
	case 0x5FE2FCB6://equipment
		break;
	case 0xC3ECD730://food
		break;
	case 0x5F850B0://structure
		break;
	default:
		break;
	}

	return items;
}

/*
 * Loads the items for this factory for the inputHopper and outputHopper.
 */
void FactoryObjectImplementation::loadItems(){
	if(getZone()!=NULL){
		if(getZone()->getZoneServer()!=NULL){
			ItemManager* itemManager = getZone()->getZoneServer()->getItemManager();
			if(itemManager!=NULL){
				itemManager->loadFactoryContainerItems(_this, inputHopper);
				itemManager->loadFactoryContainerItems(_this, outputHopper);
			}
		}
	}
}
