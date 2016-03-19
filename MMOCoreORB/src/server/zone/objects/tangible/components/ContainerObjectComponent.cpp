/*
 * ContainerObjectComponent.cpp
 *
 *  Created on: 07/02/2012
 *      Author: victor
 */

#include "server/zone/objects/tangible/Container.h"
#include "ContainerObjectComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"

bool ContainerObjectComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	//if (permission == )

	Container* container = dynamic_cast<Container*>(sceneObject);

	if (container != NULL) {
		if (container->isContainerLocked() && container->isSliced()) {
			creature->sendSystemMessage("@slicing/slicing:broken");
			return false;
		} else if (container->isContainerLocked()) {
			creature->sendSystemMessage("@slicing/slicing:locked");
			return false;
		}
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
