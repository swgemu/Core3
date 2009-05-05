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

	setTargetStfFile("monster_name");

	setTargetConditionMax(2000);
}


int VehicleDeedImplementation::useObject(Player* player) {/*
	TODO: REVISIT THIS ASAP
	Datapad* datapad = player->getDatapad();

	String customname = getTargetCustomName().toString();


	IntangibleObject* datapaditem = new IntangibleObject(player->getNewItemID(), getTargetCustomName(), getTargetStfFile(),
			getTargetStfName(), getTargetObjectCRC(), (SceneObject*) datapad);


	MountCreature* vehicle = new MountCreature(player, getTargetStfName(), getTargetStfFile(),
			getTargetObjectCRC(), getTargetObjectCRC(), player->getNewItemID());

	//MountCreature* vehicle = new MountCreature(player, sname, targetFile.hashCode(), vehicleFile.hashCode(), player->getNewItemID());

	try {
		vehicle->setMaxCondition(getTargetConditionMax());
		vehicle->setObjectFileName(getTargetObjectFile());
		vehicle->setZoneProcessServer(player->getZoneProcessServer());
		vehicle->setCustomName(getTargetCustomName());
		vehicle->setDatapadItem(datapaditem);
		vehicle->setMaxCondition(getHitPoints());

		datapaditem->setWorldObject(vehicle);
		datapaditem->setParent(datapad);

		player->addDatapadItem(datapaditem);

		datapaditem->sendTo(player, true);

		player->unlock();

		vehicle->wlock();

		vehicle->call();

		vehicle->unlock();

		player->wlock();

		// Remove Deed
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
	} catch(...) {
		vehicle->unlock();

		player->wlock();

		System::out << "Unreported exception caught in VehicleDeedImplementation::useObject\n";
	}
	*/
	return 0;
}

SceneObject* VehicleDeedImplementation::generateObject(Player* player) {
	return NULL;
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
	addHeaderAttributes(alm);

}

void VehicleDeedImplementation::parseItemAttributes(){
	String attr("targetConditionMax");
	targetConditionMax = itemAttributes->getIntAttribute(attr);
}
