/*
 * PobShipContainerComponent.cpp
 */

#include "PobShipContainerComponent.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

bool PobShipContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || creature == nullptr)
		return false;

	if (sceneObject->isPobShip()) {
		if (permission == ContainerPermissions::MOVEVENDOR)
			return false;

		PobShipObject* pobShip = sceneObject->asPobShip();

		if (pobShip == nullptr)
			return false;

		if (pobShip->isOnAdminList(creature))
			return true;
	}

	return ShipContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
