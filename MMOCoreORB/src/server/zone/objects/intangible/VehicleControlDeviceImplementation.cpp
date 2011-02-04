/*
 * VehicleControlDeviceImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "VehicleControlDevice.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/ZoneServer.h"

void VehicleControlDeviceImplementation::generateObject(PlayerCreature* player) {
	if (player->getParent() != NULL)
		return;

	if (controlledObject->isInQuadTree())
		return;

	if (player->isInCombat() || player->isDead() || player->isIncapacitated())
		return;

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL)
		return;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = (ControlDevice*) object.get();

			ManagedReference<SceneObject*> vehicle = device->getControlledObject();

			if (vehicle != NULL && vehicle->isInQuadTree()) {
				player->sendSystemMessage("You can only generate one vehicle"); // TODO:find appropiate string id
				return;
			}
		}
	}

	ZoneServer* zoneServer = getZoneServer();

	Locker clocker(controlledObject, player);

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
	controlledObject->setCreatureLink(player);
	controlledObject->setControlDevice(_this);

	controlledObject->insertToZone(player->getZone());
	controlledObject->inflictDamage(player, 0, System::random(50), true);

	updateStatus(1);
}

void VehicleControlDeviceImplementation::storeObject(PlayerCreature* player) {
	if (controlledObject == NULL)
		return;

	if (!controlledObject->isInQuadTree())
		return;

	if (player->isRidingMount()) {
		player->executeObjectControllerAction(String("dismount").hashCode());

		if (player->isRidingMount())
			return;
	}

	controlledObject->removeFromZone();
	controlledObject->setCreatureLink(NULL);

	updateStatus(0);
}

void VehicleControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	if (controlledObject != NULL) {
		controlledObject->destroyObjectFromDatabase(true);
	}

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

int VehicleControlDeviceImplementation::canBeDestroyed(PlayerCreature* player) {
	if (controlledObject != NULL) {
		if (controlledObject->isInQuadTree())
			return 1;
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}
