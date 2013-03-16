/*
 * PlaceableLootContainerComponent.cpp
 *
 *  Created on: Mar 13, 2013
 *      Author: root
 */
#include "PlaceableLootContainerComponent.h"
#include "server/zone/objects/tangible/Container.h"

bool PlaceableLootContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if(!sceneObject->isContainerObject())
		return false;

	ManagedReference<Container*> container = cast<Container*>(sceneObject);

	if(permission == ContainerPermissions::MOVEIN)
		return false;
	else if (permission == ContainerPermissions::MOVEOUT ){
		return true;
	} else if ( permission == ContainerPermissions::OPEN  ) {
		return !container->isContainerLocked();
	}

	return false;
}

int PlaceableLootContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {

	if(sceneObject->getContainerObjectsSize() >= 0){
		errorDescription = "@event_perk:chest_can_not_add"; //You do not have permission to add items to this container.
		 return TransferErrorCode::INVALIDTYPE;
	}

	return 1;
}





