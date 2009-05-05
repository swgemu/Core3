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
#include "engine/engine.h"
#include "../../../packets.h"

#include "../../../managers/planet/PlanetManager.h"
#include "../../../managers/structure/StructureManager.h"

#include "../events/StructureStatusPollEvent.h"

#include "../../player/sui/inputbox/SuiInputBox.h"
#include "../../player/sui/transferbox/SuiTransferBox.h"

#include "InstallationObjectImplementation.h"


InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid)
	: InstallationObjectServant(oid, INSTALLATION) {
	init();
}

InstallationObjectImplementation::InstallationObjectImplementation(uint64 oid, InstallationDeed* deed)
	: InstallationObjectServant(oid, INSTALLATION) {
	objectCRC = deed->getTargetObjectCRC();
	customName = deed->getCustomName();
	stfFile = deed->getTargetStfFile();
	stfName = deed->getTargetStfName();
	objectSubType = deed->getTargetObjectSubType();

	init();
}

InstallationObjectImplementation::~InstallationObjectImplementation() {
}

void InstallationObjectImplementation::init() {
	structureID = 0; //Should get set in the loading that takes place in StructureManager.

	complexity = 1.0f;

	stfFile = "installation_n";

	deedCRC = 0;
	deedStfName = "default";
	objectFile = "";

	optionsBitmask = 0x00000100; //TODO: What does this flag represent? 256 in decimal

	unknownByte = 0;

	setLotSize(0); //Some installations might take zero lots.

	setPowerReserves(0);
	setPowerRate(45);

	setMaintenancePool(0);
	setMaintenanceRate(45);

	setReclaimFee(1000);

	setOperating(false);

	maxCondition = 1000;

	//Initialize to zero. This will get set when a destroy attempt is requested.
	destroyCode = 0;

	updateCounter = 0;
	//hopperUpdateCounter = 1;

	//Initialize the Structure Permission List
	permissionList = new StructurePermissionList(NULL);

	//Gets set on insertToZone().
	structureStatusPollEvent = NULL;
}

void InstallationObjectImplementation::serialize() {
	System::out << "Serializing installation with objectid " << getObjectID() << endl;
}

void InstallationObjectImplementation::deserialize() {
}

void InstallationObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();

	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	BaseMessage* inso3 = new InstallationObjectMessage3(_this);
	client->sendMessage(inso3);

	BaseMessage* inso6 = new InstallationObjectMessage6(_this);
	client->sendMessage(inso6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(inso6);
	}

	if (doClose)
		SceneObjectImplementation::close(client);
}

void InstallationObjectImplementation::sendPermissionListTo(Player* player, const String& listname) {
	permissionList->sendTo(player, listname);
}

void InstallationObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->finish();
	player->sendMessage(omr);
}

void InstallationObjectImplementation::sendCustomNamePromptTo(Player* player) {
	SuiInputBox* namepromptbox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0);
	namepromptbox->setUsingObjectID(getObjectID());
	namepromptbox->setPromptTitle("@player_structure:structure_name_prompt "); //Name The Object
	namepromptbox->setPromptText("@sui:set_name_prompt"); //Please enter the new name you would like for this object.
	namepromptbox->setDefaultInput(getCustomName().toString());
	namepromptbox->setCancelButton(true, "");
	namepromptbox->setMaxInputSize(255);

	player->addSuiBox(namepromptbox);
	player->sendMessage(namepromptbox->generateMessage());
}

void InstallationObjectImplementation::updateCustomName(Player* player, const String& value) {
	InstallationObjectDeltaMessage3* delta3 = new InstallationObjectDeltaMessage3(_this);
	delta3->updateName(value);
	delta3->close();
	player->broadcastMessage(delta3, 128);

	player->sendSystemMessage("@player_structure:structure_renamed"); //Structure renamed.
}

void InstallationObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::insertToZone(zone);

	permissionList->setParentStructure(_this);

	structureStatusPollEvent = new StructureStatusPollEvent(_this);
	server->addEvent(structureStatusPollEvent, 3600000); //TODO: once per hour.

	if (isOperating()) {
		System::out << "Setting installation to operating" << endl;
		//Start up the harvester, send deltas to anyone who might be nearby...
		InstallationObjectDeltaMessage3* dinso3 = new InstallationObjectDeltaMessage3(_this);
		dinso3->updateOperating(true);
		dinso3->close();
		broadcastMessage(dinso3);

		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(_this);
		dinso7->updateOperating(true);
		dinso7->updateExtractionRate(getExtractionRate());
		dinso7->close();
		broadcastMessage(dinso7);
	}
}

void InstallationObjectImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void InstallationObjectImplementation::parseItemAttributes() {
	String attr = "operating";
	setOperating(itemAttributes->getBooleanAttribute(attr));

	attr = "deedCRC";
	setDeedCRC(itemAttributes->getIntAttribute(attr));

	attr = "deedStfName";
	setDeedStfName(itemAttributes->getStringAttribute(attr));

	attr = "objectFile";
	setObjectFile(itemAttributes->getStringAttribute(attr));

	attr = "reclaimFee";
	setReclaimFee(itemAttributes->getIntAttribute(attr));

	attr = "maintenancePool";
	setMaintenancePool(itemAttributes->getFloatAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "powerReserves";
	setPowerReserves(itemAttributes->getFloatAttribute(attr));

	attr = "powerRate";
	setPowerRate(itemAttributes->getFloatAttribute(attr));

	attr = "publicStructure";
	setPublicStructure(itemAttributes->getBooleanAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));
}

void InstallationObjectImplementation::addAttributes(AttributeListMessage* alm) {
}

/**
 * Starts up operation of the installation. Starting up
	System::out << "target object crc is " << getTargetObjectCRC() << endl; operation can fail if criteria are not met.
 * NOTE: Installation should be wlocked with player.
 * \param player The player who is attempting to start the operation.
 * \return bool Returns false if the harvester fails to start and true if it starts.
 */
bool InstallationObjectImplementation::start(Player* player) {
	if (isOperating())
		return false;

	if (isOutOfMaintenance()) {
		StringBuffer entry;
		entry << "@shared:harvester_no_maint_" << (System::random(3) + 1);
		player->sendSystemMessage(entry.toString()); //Chooses a random no maintenace string to display.
		shutdown(ERR_OUTOFMAINTENANCE, false);
		return false;
	}

	if (isOutOfPower() && !isGenerator()) {
		player->sendSystemMessage("@shared:harvester_no_power"); //No power available. Shutting down. (Choose "deposit power" to add power.)"
		shutdown(ERR_OUTOFPOWER, false);
		return false;
	}

	if (isHopperFull()) {
		player->sendSystemMessage("@shared:harvester_hopper_full"); //Output hopper full. Shutting down.
		shutdown(ERR_HOPPERFULL, false);
		return false;
	}

	setOperating(true);

	//TODO: broadcast this
	InstallationObjectDeltaMessage3* dinso3 = new InstallationObjectDeltaMessage3(_this);
	dinso3->updateOperating(true);
	dinso3->close();
	broadcastMessage(dinso3);

	InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(_this);
	dinso7->updateOperating(true);
	dinso7->updateExtractionRate(getExtractionRate());
	dinso7->close();
	broadcastMessage(dinso7);

	return true;
}

/**
 * Method shuts down the installation. Takes an error code which specifies the reason it shut down.
 * Also sends out mail to the owner informing him of the shutdown and the reason.
 * \param errorcode The code specifying why the harvester shutdown. Defaults to 0 which is none.
 */
void InstallationObjectImplementation::shutdown(uint8 errorcode, bool sendmail) {
	//TODO: Send mails for the following shutdown reasons.
	if (sendmail) {
		switch (errorcode) {
		case ERR_OUTOFPOWER:
			break;
		case ERR_OUTOFMAINTENANCE:
			break;
		case ERR_HOPPERFULL:
			break;
		case ERR_NONE:
		default:
			break;
		}
	}

	setOperating(false);

	//Update nearby clients
	InstallationObjectDeltaMessage3* dinso3 = new InstallationObjectDeltaMessage3(_this);
	dinso3->updateOperating(false);
	dinso3->close();
	broadcastMessage(dinso3);

	InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(_this);
	dinso7->updateOperating(false);
	dinso7->close();
	broadcastMessage(dinso7);
}

/**
 * Attempting to destroy the structure. If conditions are met, player will receive a deed
 * representing the structure in their inventory; otherwise, the structure is destroyed.
 * \note this takes place after sendDestroyConfirmTo has been approved.
 * \param player The player whom is destroying the structure.
 */
bool InstallationObjectImplementation::destroyStructure(Player* player) {
	if (isOperating()) {
		player->sendSystemMessage("player_structure", "destroy_deactivate_first"); //You must first deactivate the harvester before you may destroy it or reclaim the deed.
		return false;
	}

	if (!isHopperEmpty()) {
		player->sendSystemMessage("player_structure", "destroy_hopper"); //You must first empty the harvester's hopper before you may destroy it or reclaim the deed.
		return false;
	}

	player->sendSystemMessage("@player_structure:processing_destruction"); //Processing confirmed structure destruction...

	//If their is still a surplus of maintenance, then we can redeed the structure.
	if (isRedeedable()) {
		InstallationDeed* deed = redeed(player);

		if (deed != NULL) {
			player->getZone()->getZoneServer()->addObject(deed);
			System::out << "Deed has the following crc : " << deed->getObjectCRC() << endl;
			player->addInventoryItem(deed);
			deed->sendTo(player);
			player->sendSystemMessage("@player_structure:deed_reclaimed"); //Structure destroyed and deed reclaimed.
		} else {
			//TODO: Output some error message about an error in the redeed process.
		}
	} else {
		player->sendSystemMessage("@player_structure:structure_destroyed"); //Structure destroyed.
	}

	//Refund lots.
	int lots = player->getLotsRemaining() + getLotSize();
	player->setLotsRemaining(lots);

	//Remove structure from zone, and maps.
	StructureManager* structureManager = zone->getPlanetManager()->getStructureManager();
	structureManager->deleteStructure(_this);

	//TODO: Perhaps we should update the players lot count now to make sure that it saves.

	return true;
}

/**
 * This method will redeed the Installation into an InstallationDeed.
 * \param player The player whom has requested the redeed of the installation.
 * \return Returns an InstallationDeed representing this structure.
 */
InstallationDeed* InstallationObjectImplementation::redeed(Player* player) {
	//TODO: Generate the proper installation deed from this structure.
	//Stop the installation from operating, turn off the structure status poll event.
	//Subtract due maintenance.
	return NULL;
}


/**
 * Adds or removes an entry from the specified permission list.
 * \param player The player attempting to modify the permission list.
 * \param listname The name of the list being modified. BAN, ENTRY, ADMIN, HOPPER, VENDOR.
 * \param entryname The name of the entry being removed or added to the list.
 * \param add Is the entry being removed or added to the list.
 */
void InstallationObjectImplementation::modifyPermissionList(Player* player, const String& listname, const String& entryname, bool add) {
	if (add)
		permissionList->grantPermission(player, entryname, listname);
	else
		permissionList->revokePermission(player, entryname, listname);
}



/**
 * Polls the structure to see if maintenance, power, or taxes need to be paid. This should occur
 * every hour.
 * NOTE: Installation should be locked prior to this method.
 */
void InstallationObjectImplementation::pollStatus(bool reschedule) {
	consumeMaintenance();

	if (isOperating() && !isGenerator())
		consumePower();

	payTaxes();

	lastStatusPoll.update();

	if (reschedule)
		server->addEvent(structureStatusPollEvent, 10000); //TODO: set to 1 hour
}

/**
 * Consumes maintenance based on the current maintenance rate. If the maintenance pool runs out
 * then the installation is shut down and appropriate messages are sent.
 * NOTE: This is primarily for use with the status poll event.
 */
void InstallationObjectImplementation::consumeMaintenance() {
	changeMaintenancePool(-getMaintenanceRate());

	if (isOutOfMaintenance() && isOperating())
		shutdown(ERR_OUTOFMAINTENANCE);
}

/**
 * Consumes power based on the current power rate. If the power runs out, then the installation
 * shuts down and the appropriate emails are sent.
 * NOTE: This is primarily for use with the status poll event.
 */
void InstallationObjectImplementation::consumePower() {
	if (isOperating())
		changePowerReserves(-getPowerRate());

	if (isOutOfPower() && isOperating())
		shutdown(ERR_OUTOFPOWER);
}

/**
 * Pay any city taxes due.
 */
void InstallationObjectImplementation::payTaxes() {
	//TODO: Paying taxes when cities are implemented.
}

/**
 * Deposits an amount of maintenance into the installation.
 * \param player The player depositing maintenance.
 * \param amount How much maintenance is being deposited.
 */
void InstallationObjectImplementation::depositMaintenance(Player* player, uint32 amount) {
	if (player->verifyCashCredits(amount)) {
		StfParameter* params = new StfParameter();
		params->addDI(amount);
		params->addTO(getObjectID());
		player->sendSystemMessage("base_player", "prose_pay_acct_success", params); //You successfully make a payment of %DI credits to %TO.
		player->subtractCashCredits(amount);
		changeMaintenancePool(amount);
		delete params;
		return;
	}

	player->sendSystemMessage("player_structure", "no_money"); //You do not have any money to pay maintenance.
}

/**
 * Deposits an amount of power into the installation.
 * \param player The player depositing power.
 * \param amount The amount of power to deposit.
 */
void InstallationObjectImplementation::depositPower(Player* player, uint32 amount) {
	if (player->getTotalInventoryPower() >= amount) {
		StfParameter* params = new StfParameter();
		params->addDI(amount);
		player->sendSystemMessage("player_structure", "deposit_successful", params); //You successfully deposit %DI units of energy.
		player->subtractInventoryPower(amount);
		changePowerReserves(amount);
		return;
	}
}


void InstallationObjectImplementation::addOperator(Player* player) {
	//Do we really need to check to see if the player already exists in the list?
	for (int i = 0; i < operatorsList.size(); i++) {
		if (player == operatorsList.get(i))
			return;
	}

	InstallationObjectMessage7* inso7 = new InstallationObjectMessage7(_this);
	player->sendMessage(inso7);

	operatorsList.add(player);
}

void InstallationObjectImplementation::removeOperator(Player* player) {
	for (int i = 0; i < operatorsList.size(); i++) {
		if (operatorsList.get(i) == player) {
			operatorsList.remove(i);
			return;
		}
	}
}



/**
 * This method sends the installations status sui to the requesting player.
 * \param player The player whom has requested the status sui.
 */
void InstallationObjectImplementation::sendStatusTo(Player* player) {
	StringBuffer prompttext;
	prompttext << "@player_structure:structure_name_prompt ";

	if (getCustomName().isEmpty())
		prompttext << "@" << getStfFile() << ":" << getStfName();
	else
		prompttext << getCustomName().toString();

	//TODO: Send the status sui to the requesting player.
	SuiListBox* statusbox = new SuiListBox(player, 0);
	statusbox->setPromptTitle("@player_structure:structure_status_t"); //Structure Status
	statusbox->setPromptText(prompttext.toString());
	statusbox->addMenuItem("@player_structure:owner_prompt " + getOwnerName());
	statusbox->addMenuItem("@player_structure:structure_private"); //This structure is private

	StringBuffer entry;

	entry << "@player_structure:condition_prompt " << ((int) (((maxCondition - conditionDamage) / maxCondition) * 100)) << "%";
	statusbox->addMenuItem(entry.toString());

	//TODO: Add in estimated time remaining.
	entry.removeAll();
	entry << "@player_structure:maintenance_pool_prompt " << getMaintenancePool();
	statusbox->addMenuItem(entry.toString());

	entry.removeAll();
	entry << "@player_structure:maintenance_rate_prompt " << getMaintenanceRate() << " cr/hr";
	statusbox->addMenuItem(entry.toString());

	if (!isGenerator()) {
		//TODO: Add in estimated time remaining.
		entry.removeAll();
		entry << "@player_structure:power_reserve_prompt " << getPowerReserves();
		statusbox->addMenuItem(entry.toString());

		entry.removeAll();
		entry << "@player_structure:power_consumption_prompt " << getPowerRate() << " units/hr";
		statusbox->addMenuItem(entry.toString());
	}

	player->sendMessage(statusbox->generateMessage());
}

/**
 * Sends the maintenance transfer sui box, allowing the player to deposit or withdraw maintenance.
 * \param player The player making the transaction.
 */
void InstallationObjectImplementation::sendManageMaintenanceTo(Player* player) {
	StringBuffer entry;
	entry << "@player_structure:select_maint_amount \n\n @player_structure:current_maint_pool " << getMaintenancePool() << "cr.";
	SuiTransferBox* maintenancebox = new SuiTransferBox(player, SuiWindowType::MANAGE_MAINTENANCE);
	maintenancebox->setUsingObjectID(getObjectID());
	maintenancebox->setPromptTitle("@player_structure:select_amount"); //Select Amount
	maintenancebox->setPromptText(entry.toString());

	maintenancebox->addFrom("@player_structure:total_funds", String::valueOf(player->getCashCredits()), String::valueOf(player->getCashCredits()), "1");
	maintenancebox->addTo("@player_structure:to_pay", String::valueOf(getMaintenancePool()), String::valueOf(getMaintenancePool()), "1");

	player->addSuiBox(maintenancebox);
	player->sendMessage(maintenancebox->generateMessage());
}

/**
 * Sends the power management sui box, allowing the player to deposit or withdraw power.
 * \param player The player making the transaction.
 */
void InstallationObjectImplementation::sendManagePowerTo(Player* player) {
	StringBuffer entry;
	entry << "@player_structure:select_power_amount \n\n @player_structure:current_power_value " << getPowerReserves();

	SuiTransferBox* powerbox = new SuiTransferBox(player, SuiWindowType::ADD_ENERGY);
	powerbox->setUsingObjectID(getObjectID());
	powerbox->setPromptTitle("@player_structure:add_power");
	powerbox->setPromptText(entry.toString());

	//TODO: Get players power from inventory.

	powerbox->addFrom("@player_structure:total_energy", String::valueOf(player->getTotalInventoryPower()), String::valueOf(player->getTotalInventoryPower()), "1");
	powerbox->addTo("@player_structure:to_deposit", String::valueOf(getPowerReserves()), String::valueOf(getPowerReserves()), "1");

	player->addSuiBox(powerbox);
	player->sendMessage(powerbox->generateMessage());
}


/**
 * Sends a confirmation box to the player asking them if they are sure they want to destroy the structure.
 * \param player The player attempting to destroy the structure.
 */
void InstallationObjectImplementation::sendConfirmDestroyTo(Player* player) {
	if (!isOwner(player->getCharacterID())) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return;
	}

	StringBuffer title;
	if (getCustomName().isEmpty())
		title << "@" << getStfFile() << ":" << getStfName();
	else
		title << getCustomName().toString();

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:can_redeed_no_suffix " + close;
	String yes = green + " @player_structure:can_redeed_yes_suffix " + close;

	String redeed = (isRedeedable()) ? yes : no;

	StringBuffer maint;
	maint << "@player_structure:redeed_maintenance " << ((isRedeedable()) ? green : red) << getMaintenancePool() << "/" << getReclaimFee() << close;

	StringBuffer entry;
	entry << "@player_structure:confirm_destruction_d1 ";
	entry << "@player_structure:confirm_destruction_d2 \n\n";
	entry << "@player_structure:confirm_destruction_d3a ";
	entry << green << " @player_structure:confirm_destruction_d3b " << close << " ";
	entry << "@player_structure:confirm_destruction_d4 \n";
	entry << "@player_structure:redeed_confirmation " << redeed;

	SuiListBox* destroybox = new SuiListBox(player, SuiWindowType::STRUCTURE_DESTROY);
	destroybox->setCancelButton(true, "@no");
	destroybox->setOkButton(true, "@yes");
	destroybox->setUsingObjectID(getObjectID());
	destroybox->setPromptTitle(title.toString());
	destroybox->setPromptText(entry.toString());
	destroybox->addMenuItem("@player_structure:can_redeed_alert " + redeed);
	destroybox->addMenuItem("@player_structure:redeed_condition \\#32CD32 1000/1000\\#.");
	destroybox->addMenuItem(maint.toString());

	player->addSuiBox(destroybox);
	player->sendMessage(destroybox->generateMessage());
}

/**
 * Sends a second confirmation box requestions a destory code be entered.
 * \param player The player requesting destroy.
 */
void InstallationObjectImplementation::sendDestroyCodeTo(Player* player) {
	//Get a new destroy code.
	generateDestroyCode();

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:will_not_redeed_confirm " + close;
	String yes = green + " @player_structure:will_redeed_confirm " + close;

	String redeed = (isRedeedable()) ? yes : no;

	StringBuffer entry;
	entry << "@player_structure:your_structure_prefix ";
	entry << redeed << " @player_structure:will_redeed_suffix \n\n";
	entry << "Code: " << destroyCode;

	SuiInputBox* destroycodebox = new SuiInputBox(player, SuiWindowType::STRUCTURE_DESTROY_CODE, 0);
	destroycodebox->setUsingObjectID(getObjectID());
	destroycodebox->setPromptTitle("@player_structure:confirm_destruction_t"); //Confirm Structure Deletion
	destroycodebox->setPromptText(entry.toString());
	destroycodebox->setCancelButton(true, "@cancel");
	destroycodebox->setMaxInputSize(6);

	player->addSuiBox(destroycodebox);
	player->sendMessage(destroycodebox->generateMessage());
}
