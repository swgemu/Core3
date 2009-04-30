#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "VehicleDeed.h"
#include "VehicleDeedImplementation.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

#include "../../../creature/mount/MountCreature.h"
#include "../../../creature/mount/MountCreatureImplementation.h"

#include "../../../creature/CreatureObjectImplementation.h"

#include "../../../tangible/DatapadImplementation.h"

#include "../../../../ZoneClientSessionImplementation.h"

#include "../../../../managers/item/ItemManager.h"

VehicleDeedImplementation::VehicleDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
		: VehicleDeedServant(creature, tempcrc, n, tempn, VEHICLEDEED) {
	objectID = creature->getNewItemID();

	objectCRC = tempcrc;

	customName = n;
	stfName = tempn;

	init();
}

VehicleDeedImplementation::VehicleDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
		: VehicleDeedServant(objid, tempcrc, n, tempn, VEHICLEDEED) {
	objectID = objid;

	objectCRC = tempcrc;

	customName = n;
	stfName = tempn;

	init();
}

VehicleDeedImplementation::~VehicleDeedImplementation() {
}

void VehicleDeedImplementation::init() {
	objectSubType = VEHICLEDEED;

	setHitPoints(1000);

	//speederbike_swoop is the old crafting lua's, swoop is the new crafting luas so remove speederbike_swoop after all old deeds are gone
	if (stfName == "speederbike_swoop" || stfName == "swoop") {
		targetName = UnicodeString("speederbike_swoop");
		targetFile = "object/intangible/vehicle/shared_speederbike_swoop_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_speederbike_swoop.iff";
	} else if (stfName == "speederbike") {
		targetName = UnicodeString("speederbike");
		targetFile = "object/intangible/vehicle/shared_speederbike_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_speederbike.iff";
	} else if (stfName == "landspeeder_x34"){
		targetName = UnicodeString("landspeeder_x34");
		targetFile = "object/intangible/vehicle/shared_landspeeder_x34_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_landspeeder_x34.iff";
	} else if (stfName == "speederbike_swoop_deed") {
		targetName = UnicodeString("speederbike_swoop");
		targetFile = "object/intangible/vehicle/shared_speederbike_swoop_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_speederbike_swoop.iff";
	} else if (stfName == "jetpack_deed") {
		targetName = UnicodeString("jetpack");
		targetFile = "object/intangible/vehicle/shared_jetpack_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_jetpack.iff";
	} else if (stfName == "landspeeder_av21_deed") {
		targetName = UnicodeString("landspeeder_av21");
		targetFile = "object/intangible/vehicle/shared_landspeeder_av21_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_landspeeder_av21.iff";
	} else if (stfName == "landspeeder_x31_deed") {
		targetName = UnicodeString("landspeeder_x31");
		targetFile = "object/intangible/vehicle/shared_landspeeder_x31_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_landspeeder_x31.iff";
	} else if (stfName == "landspeeder_x34_deed") {
		targetName = UnicodeString("landspeeder_x34");
		targetFile = "object/intangible/vehicle/shared_landspeeder_x34_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_landspeeder_x34.iff";
	} else if (stfName == "speederbike_deed") {
		targetName = UnicodeString("speederbike");
		targetFile = "object/intangible/vehicle/shared_speederbike_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_speederbike.iff";
	} else if (stfName == "speederbike_flash_deed") {
		targetName = UnicodeString("speederbike_flash");
		targetFile = "object/intangible/vehicle/shared_speederbike_flash_pcd.iff";
		vehicleFile = "object/mobile/vehicle/shared_speederbike_flash.iff";
	}
}

void VehicleDeedImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->addRadialParent(20, 3, "@pet/pet_menu:menu_generate");

	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->finish();

	player->sendMessage(omr);
}

void VehicleDeedImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	int hitPoints = (int)craftingValues->getCurrentValue("hit_points");
	setHitPoints(hitPoints);
}

void VehicleDeedImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	alm->insertAttribute("hit_points", getHitPoints());

	addFooterAttributes(alm);
}

void VehicleDeedImplementation::parseItemAttributes(){
	String temp = "hit_points";
	hitPoints = itemAttributes->getIntAttribute(temp);
}

int VehicleDeedImplementation::useObject(Player* player) {
	Datapad* datapad = player->getDatapad();

	String cName = "";
	String sname = targetName.toString();
	String sfile = "monster_name";

	IntangibleObject* datapadItem = new IntangibleObject(player->getNewItemID(), cName, sfile,
			sname, targetFile.hashCode(), (SceneObject*) datapad);

	MountCreature* vehicle = new MountCreature(player, sname,
			targetFile.hashCode(), vehicleFile.hashCode(), player->getNewItemID());

	try {
		vehicle->setMaxCondition(getHitPoints());
		//vehicle->setObjectFileName(vehicleFile);
		//vehicle->setZoneProcessServer(player->getZoneProcessServer());

		vehicle->setDatapadItem(datapadItem);
		datapadItem->setWorldObject(vehicle);
		datapadItem->setParent(datapad);

		player->addDatapadItem(datapadItem);

		datapadItem->sendTo(player, true);

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
		return 0;
	}
}
