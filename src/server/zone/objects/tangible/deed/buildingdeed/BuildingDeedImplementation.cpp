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
#include "../../../player/Player.h"

#include "BuildingDeedImplementation.h"

BuildingDeedImplementation::BuildingDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: BuildingDeedServant(creature, objcrc, customname, stfname) {

	init();
}

BuildingDeedImplementation::BuildingDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: BuildingDeedServant(objid, objcrc, customname, stfname) {
	init();
}

BuildingDeedImplementation::~BuildingDeedImplementation() {

}

void BuildingDeedImplementation::init() {
	objectSubType = BUILDINGDEED;

	setTargetStfFile("building_name");

	setMaintenanceRate(30.0f);

	setSurplusMaintenance(0);

	setTargetConstructionObjectCRC(0);
	setTargetConditionMax(2000);

	setReclaimFee(1000);
	setCellCount(0);
	setLotSize(0);
}

int BuildingDeedImplementation::useObject(Player* player) {
	if (player->isInBuilding()) {
		player->sendSystemMessage("player_structure", "not_inside"); //You can not place a structure while you are inside a building.
		return 0;
	}

	if (player->isInANoBuildArea()) {
		player->sendSystemMessage("player_structure", "not_permitted"); //Building is not permitted here.
		return 0;
	}

	if (player->getLotsRemaining() < getLotSize()) {
		StfParameter* params = new StfParameter();
		params->addDI(getLotSize());
		player->sendSystemMessage("player_structure", "not_permitted", params); //This structure requires %DI lots.
		delete params;
		return 0;
	}

	EnterStructurePlacementModeMessage* espmm = new EnterStructurePlacementModeMessage(getObjectID(), getTargetObjectFile()); // targetFile
	player->sendMessage(espmm);

	return 1;
}

SceneObject* BuildingDeedImplementation::generateObject(Player* player) {
	return NULL;
}

void BuildingDeedImplementation::parseItemAttributes() {
	String attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "reclaimFee";
	setReclaimFee(itemAttributes->getIntAttribute(attr));

	attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "targetConstructionObjectCRC";
	setTargetConstructionObjectCRC(itemAttributes->getIntAttribute(attr));

	attr = "targetConditionMax";
	setTargetConditionMax(itemAttributes->getIntAttribute(attr));

	attr = "cellCount";
	setCellCount(itemAttributes->getIntAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));

	DeedObjectImplementation::parseItemAttributes();
}

void BuildingDeedImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer maintrate;
	maintrate << maintenanceRate << " / hour";
	alm->insertAttribute("examine_maintenance_rate", maintrate.toString()); //Base Maintenance Rate

	if (!isMaintenanceEmpty())
		alm->insertAttribute("examine_maintenance", (int) getSurplusMaintenance()); //Surplus Maintenance
}
