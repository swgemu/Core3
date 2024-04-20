/*
 * WarrenDiskContainerComponent.cpp
 *
 * Created: 2024-04-20
 * By: Hakry
 *
 *
*/

#include "server/zone/objects/intangible/components/WarrenDiskContainerComponent.h"

bool WarrenDiskContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || creature == nullptr) {
		return false;
	}

	if (permission != ContainerPermissions::MOVECONTAINER) {
		return false;
	}

	auto playerParent = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (playerParent == nullptr || playerParent->getObjectID() != creature->getObjectID()) {
		return false;
	}

	return true;
}