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

#include "../../../player/Player.h"
#include "../../../draftschematic/DraftSchematic.h"
#include "../../../../packets/object/ObjectMenuResponse.h"
#include "../../../creature/mount/MountCreature.h"
#include "../../../../managers/item/ItemManager.h"
#include "../../../intangible/IntangibleObject.h"

#include "VehicleDeedImplementation.h"

VehicleDeedImplementation::VehicleDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: VehicleDeedServant(creature, objcrc, customname, stfname) {

	init();
}

VehicleDeedImplementation::VehicleDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname)
		: VehicleDeedServant(objid, objcrc, customname, stfname) {

	init();
}

VehicleDeedImplementation::~VehicleDeedImplementation() {
}

void VehicleDeedImplementation::init() {
	objectSubType = VEHICLEDEED;

	setStfFile("pet_deed");

	setTargetObjectSubType(VEHICLE);

	setTargetConditionMax(2000);
	setTargetControlDeviceCRC(0);
}


int VehicleDeedImplementation::useObject(Player* player) {
	MountCreature* vehicle = (MountCreature*) generateObject(player);

	if (vehicle == NULL) {
		player->sendSystemMessage("Sorry, this vehicle deed is no longer usable.");
		return 0;
	}

	try {
		player->unlock();

		vehicle->wlock();

		vehicle->call();

		vehicle->unlock();

		player->wlock();

		_this->sendDestroyTo(player);

		Zone* zone = player->getZone();
		if (zone != NULL) {
			ZoneServer* zoneServer = zone->getZoneServer();

			ItemManager* itemManager;

			if (zoneServer != NULL && ((itemManager = zoneServer->getItemManager()) != NULL)) {
				player->removeInventoryItem(objectID);
				itemManager->deletePlayerItem(player, _this, false);

				_this->finalize();
			}
		}

		return 1;
	} catch (...) {
		vehicle->unlock();
		player->wlock();
	}

	return 0;
}

SceneObject* VehicleDeedImplementation::generateObject(Player* player) {
	Datapad* datapad = player->getDatapad();

	uint32 controldevicecrc = getTargetControlDeviceCRC();

	if (controldevicecrc == 0)
		return NULL;

	String customname = getTargetCustomName().toString();
	IntangibleObject* controldevice = new IntangibleObject(player->getNewItemID(), customname, getTargetStfFile(), getTargetStfName(), controldevicecrc, (SceneObject*) datapad);

	MountCreature* vehicle = new MountCreature(player->getNewItemID(), getTargetObjectCRC(), getTargetCustomName(), getTargetStfName(), player);
	vehicle->setStfFile(getTargetStfFile());
	vehicle->setStfName(getTargetStfName());
	vehicle->setDatapadItem(controldevice);
	vehicle->setMaxCondition(getTargetConditionMax());

	controldevice->setWorldObject(vehicle);
	controldevice->setParent((SceneObject*) datapad);

	player->addDatapadItem(controldevice);
	controldevice->sendTo(player, true);

	return vehicle;
}

void VehicleDeedImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->addRadialParent(20, 3, "@pet/pet_menu:menu_generate");

	omr->finish();

	player->sendMessage(omr);
}

void VehicleDeedImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	//TODO: Update the schematics to use targetConditonMax
	uint32 condmax = (uint32) craftingValues->getCurrentValue("hit_points");
	setTargetConditionMax(condmax);
}

void VehicleDeedImplementation::addAttributes(AttributeListMessage* alm) {
}

void VehicleDeedImplementation::parseItemAttributes(){
	DeedObjectImplementation::parseItemAttributes();

	String attr("targetConditionMax");
	targetConditionMax = itemAttributes->getIntAttribute(attr);

	attr = "targetControlDeviceCRC";
	targetControlDeviceCRC = itemAttributes->getIntAttribute(attr);
}
