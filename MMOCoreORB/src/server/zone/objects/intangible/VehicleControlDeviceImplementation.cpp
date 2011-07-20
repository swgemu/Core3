/*
 * VehicleControlDeviceImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "VehicleControlDevice.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/ZoneServer.h"

void VehicleControlDeviceImplementation::generateObject(CreatureObject* player) {
	if (player->getParent() != NULL)
		return;

	if (controlledObject->isInQuadTree())
		return;

	if (player->isInCombat() || player->isDead() || player->isIncapacitated())
		return;

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL)
		return;

	int currentlySpawned = 0;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isControlDevice()) {
			ControlDevice* device = (ControlDevice*) object.get();

			ManagedReference<SceneObject*> vehicle = device->getControlledObject();

			if (vehicle != NULL && vehicle->isInQuadTree()) {
				if (++currentlySpawned > 2)
					player->sendSystemMessage("You can only generate 3 vehicles"); // TODO:find appropiate string id

				return;
			}
		}
	}

	ZoneServer* zoneServer = getZoneServer();

	Locker clocker(controlledObject, player);

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());

	//TODO: Refactor
	if (controlledObject->isCreatureObject()) {
		((CreatureObject*)controlledObject.get())->setCreatureLink(player);
		((CreatureObject*)controlledObject.get())->setControlDevice(_this);
	}

	controlledObject->insertToZone(player->getZone());
	controlledObject->inflictDamage(player, 0, System::random(50), true);

	updateStatus(1);
}

void VehicleControlDeviceImplementation::storeObject(CreatureObject* player) {
	if (controlledObject == NULL)
		return;

	if (!controlledObject->isInQuadTree())
		return;

	if (player->isRidingMount() && player->getParent() == controlledObject) {
		player->executeObjectControllerAction(String("dismount").hashCode());

		if (player->isRidingMount())
			return;
	}

	controlledObject->removeFromZone();

	if (controlledObject->isCreatureObject())
		((CreatureObject*) controlledObject.get())->setCreatureLink(NULL);

	updateStatus(0);
}

void VehicleControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	if (controlledObject != NULL) {
		controlledObject->destroyObjectFromDatabase(true);
	}

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

int VehicleControlDeviceImplementation::canBeDestroyed(CreatureObject* player) {
	if (controlledObject != NULL) {
		if (controlledObject->isInQuadTree())
			return 1;
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}
