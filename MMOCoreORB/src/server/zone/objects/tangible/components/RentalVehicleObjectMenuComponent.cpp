/*
 * RentalVehicleObjectMenuComponent.cpp
 *
 *  Created on: 5/22/2022
 *      Author: H
 */

#include "RentalVehicleObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include"server/zone/ZoneServer.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

void RentalVehicleObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || player == nullptr)
		return;

	if (sceneObject->isASubChildOf(player))
		menuResponse->addRadialMenuItem(186, 3, "@new_player:vehicle_coupon_menu_call");
}

int RentalVehicleObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr)
		return 0;

	if (selectedID == 186) {
		// create control device here

		if (player->isInCombat() || player->getParentRecursively(SceneObjectType::BUILDING) != nullptr) {
			player->sendSystemMessage("@pet/pet_menu:cant_call_vehicle"); //You can only unpack vehicles while Outside and not in Combat.
			return 1;
		}

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			player->sendSystemMessage("Datapad doesn't exist when trying to create vehicle");
			return 1;
		}

		// Check if this will exceed maximum number of vehicles allowed
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int vehiclesInDatapad = 0;
		int maxStoredVehicles = playerManager->getBaseStoredVehicles();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != nullptr && obj->isVehicleControlDevice() )
				vehiclesInDatapad++;
		}

		if (vehiclesInDatapad >= maxStoredVehicles) {
			player->sendSystemMessage("@pet/pet_menu:has_max_vehicle"); // You already have the maximum number of vehicles that you can own.
			return 1;
		}

		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return 1;

		Reference<VehicleControlDevice*> vehicleControlDevice = (zoneServer->createObject(STRING_HASHCODE("object/intangible/vehicle/speederbike_pcd.iff"), 1)).castTo<VehicleControlDevice*>();

		if (vehicleControlDevice == nullptr) {
			return 1;
		}

		Locker locker(vehicleControlDevice);

		Reference<VehicleObject*> vehicle = (zoneServer->createObject(STRING_HASHCODE("object/mobile/vehicle/speederbike.iff"), 1)).castTo<VehicleObject*>();

		if (vehicle == nullptr) {
			vehicleControlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

		Locker vlocker(vehicle, player);

		vehicle->createChildObjects();
		vehicle->setMaxCondition(1500);
		vehicle->setConditionDamage(0);

		vehicle->setRentalVehicle(true);
		vehicle->setUses(6);

		vehicleControlDevice->setControlledObject(vehicle);

		if (datapad->transferObject(vehicleControlDevice, -1)) {
			datapad->broadcastObject(vehicleControlDevice, true);

			StringIdChatParameter param("@pet/pet_menu:uses_left_new");
			param.setDI(5);
			player->sendSystemMessage(param);

			vehicleControlDevice->generateObject(player);

			// Destroy Rental device from players inventory
			sceneObject->destroyObjectFromWorld(true);
			sceneObject->destroyObjectFromDatabase(true);

			return 0;
		} else {
			vehicleControlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

	}

	return 0;
}