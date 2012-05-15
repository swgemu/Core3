/*
 * DeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include "VehicleDeed.h"
#include"server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/templates/tangible/VehicleDeedTemplate.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/creature/VehicleObject.h"

void VehicleDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	VehicleDeedTemplate* deedData = dynamic_cast<VehicleDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
}

void VehicleDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("hit_points", hitPoints);
}

void VehicleDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("VehicleDeed");
}

void VehicleDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 *
	 * hitpoints			varies, integrity of vehicle
	 */

	hitPoints = (int) values->getCurrentValue("hit_points");
}

void VehicleDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_generate");
}

int VehicleDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	if (generated || !isASubChildOf(player))
		return 1;

	if (player->isInCombat() || player->getParentRecursively(SceneObjectType::BUILDING) != NULL) {
		player->sendSystemMessage("@pet/pet_menu:cant_call_vehicle"); //You can only unpack vehicles while Outside and not in Combat.
		return 1;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL) {
		player->sendSystemMessage("Datapad doesn't exist when trying to create vehicle");
		return 1;
	}

	VehicleControlDevice* vehicleControlDevice = dynamic_cast<VehicleControlDevice*>(server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1));
	VehicleObject* vehicle = dynamic_cast<VehicleObject*>(server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), 1));

	if (vehicle == NULL) {
		player->sendSystemMessage("wrong vehicle object template " + generatedObjectTemplate);
		return 1;
	}

	vehicle->createChildObjects();
	vehicle->setMaxCondition(hitPoints);
	vehicle->setConditionDamage(0);
	vehicleControlDevice->setControlledObject(vehicle);
	datapad->transferObject(vehicleControlDevice, -1);

	datapad->broadcastObject(vehicleControlDevice, true);
	vehicleControlDevice->generateObject(player);

	//Remove the deed from it's container.
	ManagedReference<SceneObject*> deedContainer = getParent();

	if (deedContainer != NULL) {
		/*deedContainer->removeObject(_this, true);
		broadcastDestroy(_this, false);*/
		destroyObjectFromWorld(true);
	}

	generated = true;

	return 0;
}

