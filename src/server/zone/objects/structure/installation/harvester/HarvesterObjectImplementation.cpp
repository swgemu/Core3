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

#include "HarvesterObjectImplementation.h"
#include "../../../../managers/resource/ResourceManager.h"
#include "../../../../managers/resource/ResourceHarvestType.h"
#include "../events/HarvestResourceEvent.h"
#include "../../../../packets.h"

HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 objid)
		: HarvesterObjectServant(objid) {

	init();
}


HarvesterObjectImplementation::HarvesterObjectImplementation(uint64 objid, InstallationDeed* deed)
		: HarvesterObjectServant(objid) {

	objectCRC = deed->getTargetObjectCRC();
	customName = deed->getCustomName();
	stfFile = deed->getTargetStfFile();
	stfName = deed->getTargetStfName();

	setMaintenancePool(deed->getSurplusMaintenance());
	setMaintenanceRate(deed->getMaintenanceRate());
	setPowerReserves(deed->getSurplusPower());
	setPowerRate(deed->getPowerRate());
	setHopperSizeMax(deed->getHopperSizeMax());
	setBaseExtractionRate(deed->getBaseExtractionRate());

	init();
}

HarvesterObjectImplementation::~HarvesterObjectImplementation(){
	if (harvestEvent != NULL && harvestEvent->isQueued())
		server->removeEvent(harvestEvent);

	delete harvestEvent;
	harvestEvent = NULL;
}

void HarvesterObjectImplementation::serialize() {
	StringBuffer query;

	String customname = getCustomName().toString();
	MySqlDatabase::escapeString(customname);

	String stffile = getStfFile();
	MySqlDatabase::escapeString(stffile);

	String stfname = getStfName();
	MySqlDatabase::escapeString(stfname);

	String attributes = getAttributes();
	MySqlDatabase::escapeString(attributes);

	String permissionlist = getPermissionsString();
	MySqlDatabase::escapeString(permissionlist);

	query << "UPDATE `structures` SET";
	query << "`ownerID` = " << getOwnerCharacterID() << ", ";
	query << "`zoneID` = " << zone->getZoneID() << ", ";
	query << "`objectCRC` = " << getObjectCRC() << ", ";
	query << "`customName` = '" << customname << "', ";
	query << "`stfFile` = '" << stffile << "', ";
	query << "`stfName` = '" << stfname << "', ";
	query << "`objectSubType` = " << getObjectSubType() << ", ";
	query << "`x` = " << getPositionX() << ", ";
	query << "`z` = " << getPositionY() << ", "; //TODO: Update this to be getPositionZ when the global change is made.
	query << "`oX` = " << getDirectionX() << ", ";
	query << "`oY` = " << getDirectionY() << ", ";
	query << "`oZ` = " << getDirectionZ() << ", ";
	query << "`oW` = " << getDirectionW() << ", ";
	query << "`attributes` = '" << attributes << "', ";
	query << "`permissionList` = '" << permissionlist << "' ";
	query << "WHERE `structureID` = " << getObjectID() << ";";

	try {
		ServerDatabase::instance()->executeStatement(query.toString());
	} catch (DatabaseException& ex) {
		info("Database Exception in HarvesterObjectImplementation::serialize", true);
	}

	//TODO: When serialization makes it in, move this to the hopper object, and use its serialize method.
	StringBuffer resourceString;

	for (int i = 0; i < resourceHopper.size(); i++) {
		VectorMapEntry<uint64, float>* entry = resourceHopper.elementAt(i);
		resourceString << entry->getKey() << "=" << entry->getValue() << ":";
	}

	String hopperString = resourceString.toString();

	if (!hopperString.isEmpty()) {
		query.removeAll();
		query << "INSERT INTO `harvester_hoppers` (`structureID`, `hopper`) VALUES (" << getObjectID() << ", '" << hopperString << "') ON DUPLICATE KEY UPDATE `hopper` = '" << hopperString << "';";

		try {
			ServerDatabase::instance()->executeStatement(query.toString());
		} catch (DatabaseException& ex) {
			info("Database Exception in HarvesterObjectImplementation::serialize", true);
		}
	}

}

void HarvesterObjectImplementation::deserialize() {
}

void HarvesterObjectImplementation::loadHopper(const String& hopperstring) {
	if (!hopperstring.isEmpty()) {
		StringTokenizer tokenizer(hopperstring);
		tokenizer.setDelimeter(":");

		while (tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			if (token.isEmpty())
				continue;

			StringTokenizer keyvalue(token);
			keyvalue.setDelimeter("=");

			String key;
			String value;

			keyvalue.getStringToken(key);
			keyvalue.getStringToken(value);

			resourceHopper.put(Long::valueOf(key), Float::valueOf(value));
		}
	}
}

void HarvesterObjectImplementation::init() {
	InstallationObjectImplementation::init();

	StringBuffer logname;
	logname << "HarvesterObject " << hex << objectID;

	setLoggingName(logname.toString());
	setLogging(false);
	setGlobalLogging(true);

	objectSubType = TangibleObjectImplementation::HARVESTER;

	resourceHopper.setInsertPlan(SortedVector<uint64>::NO_DUPLICATE);

	setHopperSizeMax(59000.0f);
	setSelectedResourceID(0);
	setBaseExtractionRate(3.0f);
	setOperating(false);

	harvesterType = ResourceHarvestType::MINERAL;

	harvestEvent = new HarvestResourceEvent(this);
}


void HarvesterObjectImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (isOnAdminList(player) || isOnHopperList(player)) {
		RadialMenuParent* management = new RadialMenuParent(118, 3, "@player_structure:management"); //Structure Management

		if (isOnAdminList(player)) {
			management->addRadialMenuItem(128, 3, "@player_structure:permission_destroy"); //Destroy Structure
			management->addRadialMenuItem(124, 3, "@player_structure:management_status"); //Status
			management->addRadialMenuItem(129, 3, "@player_structure:management_pay"); //Pay Maintenance
			management->addRadialMenuItem(50, 3, "@player_structure:management_name_structure"); //Name Structure
			if (!isGenerator())
				management->addRadialMenuItem(77, 3, "@player_structure:management_power"); //Deposit Power
		}

		management->addRadialMenuItem(78, 3, "@harvester:manage "); //Operate Machinery

		omr->addRadialParent(management);

		if (isOnAdminList(player)) {
			RadialMenuParent* permission = new RadialMenuParent(117, 3, "@player_structure:permissions"); //Structure Permissions
			permission->addRadialMenuItem(121, 3, "@player_structure:permission_admin"); //Admin List
			permission->addRadialMenuItem(123, 3, "@player_structure:permission_hopper"); //Hopper List

			omr->addRadialParent(permission);
		}
	}
	omr->finish();
	player->sendMessage(omr);
}

void HarvesterObjectImplementation::sendHopperUpdatesToOperators() {
	if (!hasOperators())
		return;

	//Remove players who are no longer logged in, or non-players.
	cleanOperatorsList();

	//Increment the counter
	getNewUpdateCounter(1);

	for (int i = 0; i < operatorsList.size(); i++) {
		Player* player = operatorsList.get(i);

		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7((InstallationObject*)_this);
		dinso7->updateHopper();
		dinso7->updateHopperItem(getSelectedResourceID());
		dinso7->updateHopperSize();
		dinso7->close();
		player->sendMessage(dinso7);
	}
}

void HarvesterObjectImplementation::parseItemAttributes() {
	InstallationObjectImplementation::parseItemAttributes();

	String attr = "hopperSizeMax";
	setHopperSizeMax(itemAttributes->getFloatAttribute(attr));

	attr = "baseExtractionRate";
	setBaseExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "selectedResourceID";
	setSelectedResourceID(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "spawnDensity";
	setSpawnDensity(itemAttributes->getIntAttribute(attr));

	attr = "resourceHopper";
	String hopper = itemAttributes->getStringAttribute(attr);

	attr = "harvesterType";
	setHarvesterType(itemAttributes->getIntAttribute(attr));
	//unserializeResourceHopper(hopper);
}

/**
 * Ensures that only online players are in the operators list.
 */
void HarvesterObjectImplementation::cleanOperatorsList() {
	if (!hasOperators())
		return;

	int i = 0;
	while (i < operatorsList.size()) {
		SceneObject* obj = operatorsList.get(i);

		if (!obj->isPlayer() || (obj->isPlayer() && !((Player*)obj)->isOnline()))
			operatorsList.remove(i);
		else
			i++;
	}
}

void HarvesterObjectImplementation::insertToZone(Zone* zone) {
	InstallationObjectImplementation::insertToZone(zone);

	if (isOperating())
		rescheduleHarvestEvent(10000);
}

/**
 * Starts the operation of the harvester. Overrides InstallationObjectImplementation::start().
 * \param player The player attempting to start the installation.
 * \return bool Returns true if the installation starts and false if it fails.
 */
bool HarvesterObjectImplementation::start(Player* player) {
	if (getSelectedResourceID() == 0) {
		player->sendSystemMessage("@shared:harvester_no_resource"); //No resource selected. Shutting down.
		return false;
	}

	if (!isSelectedResourceSpawning()) {
		player->sendSystemMessage("@shared:harvester_resource_depleted"); //Resource has been depleted. Shutting down.
		return false;
	}

	if (InstallationObjectImplementation::start(player)) {
		rescheduleHarvestEvent(10000);
		return true;
	}
	return false;
}

void HarvesterObjectImplementation::shutdown(uint8 errorcode) {
	clearHarvestEvent();

	if (!isOperating())
		return;

	//Tell everyone whos listening that it has stopped operating.
	for (int i = 0; i < operatorsList.size(); i++) {
		Player* player = operatorsList.get(i);
		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7((InstallationObject*)_this);
		dinso7->updateOperating(false);
		dinso7->close();
		player->sendMessage(dinso7);
	}

	InstallationObjectImplementation::shutdown(errorcode);
}

/**
 * This method changes the currently active resource to harvest. This is called when a response message is
 * handled by the server after a player selects the appropriate action through the UI menu.
 * \param resourceid The ID of the resource that was chosen from the list dislayed on the client UI.
 */
void HarvesterObjectImplementation::changeSelectedResourceID(uint64 resourceid) {
	if (getSelectedResourceID() == resourceid)
		return;

	// Logic:
	// 1) If operating, and already has an active resource ID - make sure the hopper gets updated
	// 2) Get the spawn information & set the active resource id
	// 3) If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

	clearHarvestEvent();

	if (isOperating() && getSelectedResourceID() != 0)
		harvestResource(false);

	setSelectedResourceID(resourceid);

	ResourceManager* resourceManager = getZone()->getZoneServer()->getResourceManager();

	if (resourceManager == NULL) {
		info("ResourceManager NULL in changeActiveResourceID in zone " + getZone()->getZoneID());
		setSpawnDensity(0);
		return;
	}

	//TODO: Needs Vector3 Update
	ResourceList* list = resourceManager->getResourceListAtLocation(getZone()->getZoneID(), getPositionX(), getPositionY(), getHarvesterType());

	for (int i = 0; i < list->size(); i++) {
		ResourceItem* ri = list->get(i);

		if (ri->getObjectID() == resourceid)
			setSpawnDensity(ri->getDensity());
	}

	if (isOperating())
		rescheduleHarvestEvent(10000);
}


/**
 * Harvest the currently active resource at the BER adjusted for density. (extraction rate)
 * NOTE: Should extract every minute.
 */
void HarvesterObjectImplementation::harvestResource(bool reschedule) {
	if (!isOperating()) {
		shutdown(); //Make sure to clear the event this way if its what fired this.
		return;
	}

	if (isOutOfMaintenance()) {
		shutdown(ERR_OUTOFMAINTENANCE);
		return;
	}

	if (isOutOfPower() && !isGenerator()) {
		shutdown(ERR_OUTOFPOWER);
		return;
	}

	if (isHopperFull()) {
		shutdown(ERR_HOPPERFULL);
		return;
	}

	if (!isSelectedResourceSpawning()) {
		shutdown();
		return;
	}

	//Only add what the harvesters has room for.
	float remainingcapacity = getHopperSizeMax() - getHopperSize();

	//Find out what fraction of a minute has passed, and multiple that by the extraction rate.
	//float amount = getExtractionRate() * (60 / (lastHarvestTime.miliDifference() / 1000));
	float amount = getExtractionRate() / 6;

	addHopperItem(getSelectedResourceID(), ((amount > remainingcapacity) ? remainingcapacity : amount));

	//Send out updates to operators
	sendHopperUpdatesToOperators();

	if (reschedule)
		rescheduleHarvestEvent(10000);
}

void HarvesterObjectImplementation::rescheduleHarvestEvent(uint32 miliseconds) {
	clearHarvestEvent();
	server->addEvent(harvestEvent, miliseconds);
}

void HarvesterObjectImplementation::clearHarvestEvent() {
	if (harvestEvent != NULL && harvestEvent->isQueued())
		server->removeEvent(harvestEvent);
}

/**
 * Checks to make sure that the selected resource is still spawning.
 * \return bool Returns true if the currently selected resource is spawning and false if it isn't.
 */
bool HarvesterObjectImplementation::isSelectedResourceSpawning() {
	ResourceManager* resourceManager = getZone()->getZoneServer()->getResourceManager();

	if (resourceManager == NULL)
		return false;

	ResourceList* list = resourceManager->getResourceListAtLocation(getZoneID(), getPositionX(), getPositionY(), getHarvesterType());

	for (int i = 0; i < list->size(); i++) {
		ResourceItem* ri = list->get(i);

		if (ri->getObjectID() == getSelectedResourceID())
			return true;
	}

	return false;
}

/**
 * A player is trying to retrieve an amount of resource from the hopper.
 * \param player The player retrieving the resource.
 * \param resourceid The resource to retrieve.
 * \param amount How much of the resource is being retrieved.
 */
bool HarvesterObjectImplementation::retrieveResource(Player* player, uint64 resourceid, float amount) {
	if (!isOnHopperList(player))
		return false;

	if (!resourceHopper.contains(resourceid))
		return false;

	if (amount < 1)
		return false;

	//Make sure inventory isn't full.
	if (player->getInventory()->getUnequippedItemCount() >= InventoryImplementation::MAXUNEQUIPPEDCOUNT) {
		player->sendSystemMessage("error_message", "inv_full"); //Inventory is full.
		return false;
	}

	amount = removeHopperItem(resourceid, amount);

	//Create a resource and give it to the player.
	ResourceManager* resourcemanager = zone->getZoneServer()->getResourceManager();
	ResourceContainer* resource = new ResourceContainer(player->getNewItemID());

	resource->setResourceName(resourcemanager->getResourceNameByID(resourceid));
	resource->setContents(amount);
	resourcemanager->setResourceData(resource, false);
	player->addInventoryResource(resource);

	//Send updates to our operators.
	sendHopperUpdatesToOperators();

	return true;
}

/**
 * Removes an amount of a particular resource from the harvester
 * \param player The player discarding the resource.
 * \param resourceid The resource being discarded.
 * \param amount How much is being discarded.
 */
bool HarvesterObjectImplementation::discardResource(Player* player, uint64 resourceid, float amount) {
	if (!isOnHopperList(player))
		return false;

	if (!resourceHopper.contains(resourceid))
		return false;

	if (amount < 1)
		return false;

	amount = removeHopperItem(resourceid, amount);

	sendHopperUpdatesToOperators();

	return true;
}

/**
 * Empties all the hopper contents of the harvester.
 * \param player The player emptying the harvester.
 * \return Returns true on success.
 */
bool HarvesterObjectImplementation::emptyHarvester(Player* player) {
	if (!isOnHopperList(player))
		return false;

	//Can't empty an empty harvester...
	if (isHopperEmpty())
		return false;

	//Remove all entries.
	resourceHopper.removeAll();

	cleanOperatorsList();

	getNewUpdateCounter(1);

	//Tell everyone listening...
	for (int i = 0; i < operatorsList.size(); i++) {
		Player* playop = operatorsList.get(i);

		InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(_this);
		dinso7->updateHopper();
		dinso7->resetHopperItemList();
		dinso7->updateHopperSize();
		dinso7->close();
		playop->sendMessage(dinso7);
	}

	return true;
}

InstallationDeed* HarvesterObjectImplementation::redeed(Player* player) {
	InstallationDeed* installationdeed = new InstallationDeed(player->getNewItemID(), getDeedCRC(), getDeedCustomName(), getDeedStfName());
	installationdeed->setTargetStfFile(getStfFile());
	installationdeed->setTargetStfName(getStfName());
	installationdeed->setTargetCustomName(getCustomName());
	installationdeed->setTargetConstructionObjectCRC(getConstructionObjectCRC());
	installationdeed->setTargetObjectFile(getObjectFile());
	installationdeed->setTargetObjectSubType(getObjectSubType());

	installationdeed->setMaintenanceRate(getMaintenanceRate());
	installationdeed->setPowerRate(getPowerRate());
	installationdeed->setSurplusMaintenance(getMaintenancePool());
	installationdeed->setSurplusPower(getPowerReserves());
	installationdeed->setBaseExtractionRate(getBaseExtractionRate());
	installationdeed->setHopperSizeMax(getHopperSizeMax());

	installationdeed->setHarvesterType(getHarvesterType());
	installationdeed->setLotSize(getLotSize());

	return installationdeed;
}
