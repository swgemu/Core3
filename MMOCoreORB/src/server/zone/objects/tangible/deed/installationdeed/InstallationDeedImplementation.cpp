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

#include "../../../../packets/player/EnterStructurePlacementModeMessage.h"
#include "../../../../packets/object/StfParameter.h"
#include "../../../structure/installation/InstallationObject.h"
#include "../../../structure/installation/harvester/HarvesterObject.h"
#include "../../../structure/installation/generator/GeneratorObject.h"
#include "../../../structure/installation/factory/FactoryObject.h"
#include "../../../player/Player.h"

#include "InstallationDeedImplementation.h"

InstallationDeedImplementation::InstallationDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: InstallationDeedServant(creature, objcrc, customname, stfname) {

	init();
}

InstallationDeedImplementation::InstallationDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: InstallationDeedServant(objid, objcrc, customname, stfname) {
	init();
}

InstallationDeedImplementation::~InstallationDeedImplementation() {

}

void InstallationDeedImplementation::init() {
	objectSubType = INSTALLATIONDEED;

	setTargetStfFile("installation_n");

	setMaintenanceRate(30.0f);
	setPowerRate(25.0f);

	setBaseExtractionRate(0.0f);
	setHopperSizeMax(0.0f);

	setSurplusMaintenance(0);
	setSurplusPower(0);

	setTargetConstructionObjectCRC(0);
	setTargetConditionMax(2000);

	setReclaimFee(1000);

	setLotSize(0);
}

int InstallationDeedImplementation::useObject(Player* player) {
	if (player->isMounted()) {
		player->sendSystemMessage("@player_structure:cant_place_mounted"); //You may not place a structure while mounted or riding in a vehicle.
		return 0;
	}

 	if (player->isInBuilding()) {
		player->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
		return 0;
	}

	if (player->isInANoBuildArea()) {
		player->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
		return 0;
	}

	if (player->getLotsRemaining() < getLotSize()) {
		StfParameter* params = new StfParameter();
		params->addDI(getLotSize());
		player->sendSystemMessage("player_structure", "not_enough_lots", params); //This structure requires %DI lots.
		delete params;
		return 0;
	}

	EnterStructurePlacementModeMessage* espmm = new EnterStructurePlacementModeMessage(getObjectID(), getTargetObjectFile()); // targetFile
	player->sendMessage(espmm);

	return 1;
}

SceneObject* InstallationDeedImplementation::generateObject(Player* player) {
	//This needs to create it depending on the target object sub type...
	InstallationObject* installation;
	uint64 objectid = player->getNewItemID();

	if (isHarvesterDeed()) {
		installation = new HarvesterObject(objectid);
	} else if (isGeneratorDeed()) {
		installation = new GeneratorObject(objectid);
	} else if (isFactoryDeed()) {
		installation = new FactoryObject(objectid);
	} else if (isTurretDeed()) {
		//installation = new TurretObject(objectid);
		return NULL;
	} else if (isMinefieldDeed()) {
		//installation = new MinefieldObject(objectid);
		return NULL;
	} else {
		installation = new InstallationObject(objectid);
	}

	installation->setOwnerCharacterID(player->getCharacterID());
	installation->setOwnerName(player->getFirstName().toLowerCase());

	installation->setObjectSubType(getTargetObjectSubType());
	installation->setObjectCRC(getTargetObjectCRC());

	installation->setStfFile(getTargetStfFile());
	installation->setStfName(getTargetStfName());
	installation->setCustomName(getTargetCustomName());

	installation->setDeedCRC(getObjectCRC());
	installation->setDeedStfName(getStfName());
	installation->setObjectFile(getTargetObjectFile());

	installation->setReclaimFee(getReclaimFee());
	installation->setMaintenancePool(getSurplusMaintenance());
	installation->setMaintenanceRate(getMaintenanceRate());
	installation->setPowerReserves(getSurplusPower());
	installation->setPowerRate(getPowerRate());

	installation->setBaseExtractionRate(getBaseExtractionRate());
	installation->setHopperSizeMax(getHopperSizeMax());
	installation->setHarvesterType(getHarvesterType());

	installation->setLotSize(getLotSize());

	return installation;
}

void InstallationDeedImplementation::parseItemAttributes() {
	String attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "reclaimFee";
	setReclaimFee(itemAttributes->getIntAttribute(attr));

	attr = "powerRate";
	setPowerRate(itemAttributes->getFloatAttribute(attr));

	attr = "baseExtractionRate";
	setBaseExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSizeMax";
	setHopperSizeMax(itemAttributes->getFloatAttribute(attr));

	attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getIntAttribute(attr));

	attr = "targetConstructionObjectCRC";
	setTargetConstructionObjectCRC(itemAttributes->getIntAttribute(attr));

	attr = "targetConditionMax";
	setTargetConditionMax(itemAttributes->getIntAttribute(attr));

	attr = "harvesterType";
	setHarvesterType(itemAttributes->getIntAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));

	DeedObjectImplementation::parseItemAttributes();
}

void InstallationDeedImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer maintrate;
	maintrate << maintenanceRate << " / hour";
	alm->insertAttribute("examine_maintenance_rate", maintrate.toString()); //Base Maintenance Rate
	alm->insertAttribute("examine_maintenance", (int) getSurplusMaintenance()); //Surplus Maintenance
	alm->insertAttribute("examine_power", (int) getSurplusPower()); //Surplus Power

	if (isHarvesterDeed() || isGeneratorDeed()) {
		alm->insertAttribute("examine_hoppersize", (int) getHopperSizeMax()); //Storage Capacity
		alm->insertAttribute("examine_extractionrate", (int) getBaseExtractionRate()); //Base Extraction Rate
	}
}
