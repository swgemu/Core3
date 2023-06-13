/*
 * PobShipContainerComponent.cpp
 */

#include "PobShipContainerComponent.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

bool PobShipContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || creature == nullptr)
		return false;

	if (sceneObject->isPobShipObject()) {
		PobShipObject* pobShip = cast<PobShipObject*>(sceneObject);

		if (pobShip == nullptr)
			return false;

		if (pobShip->isOnAdminList(creature))
			return true;
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
