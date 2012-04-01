/*
 * StructureContainerComponent.cpp
 *
 *  Created on: 09/02/2012
 *      Author: victor
 */

#include "StructureContainerComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

bool StructureContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	StructureObject* building = dynamic_cast<StructureObject*>(sceneObject);

	if (building->isOwnerOf(creature) || building->isOnAdminList(creature))
		return true;

	if (permission == ContainerPermissions::OPEN && building->isStaticObject())
		return true;

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
