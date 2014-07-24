/*
 * MinefieldContainerComponent.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: root
 */
#include "MinefieldContainerComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/creature/CreatureFlag.h"

bool MinefieldContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission){
	if(sceneObject == NULL || !sceneObject->isTangibleObject())
		return false;

	InstallationObject* minefield = cast<InstallationObject*>(sceneObject);

	if(creature == NULL || minefield == NULL)
		return false;

	if(creature->getFaction() == 0 || minefield->getFaction() == 0)
		return false;

	PlayerObject* ghost = creature->getPlayerObject();
	if(ghost == NULL)
		return false;

	if(permission == ContainerPermissions::OPEN || permission == ContainerPermissions::MOVEIN){
		if(minefield->getFaction() == creature->getFaction() && ghost->getFactionStatus() != FactionStatus::ONLEAVE)
			return true;

	} else if (permission == ContainerPermissions::MOVEOUT){
		if(creature->getFaction() != minefield->getFaction())
			return false;

		return minefield->isOnAdminList(creature);
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);


}
int MinefieldContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if(object->getGameObjectType() != SceneObjectType::MINE){
		errorDescription = "You can only add Mines to this container";
		return 1;
	}

	if(sceneObject->getContainerObjectsSize() >= 20){
		errorDescription = "The minefield is at its 20 mine capacity.  You cannot donate more mines.";
		return 1;
	}
	return 0;
	//return ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int MinefieldContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);
	if(installation == NULL)
		return 1;

	// mine isn't attackable if it has mines
	if(installation->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE){
		int newbitmask = installation->getPvpStatusBitmask() - CreatureFlag::ATTACKABLE;
		installation->setPvpStatusBitmask(newbitmask);
	}

	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}
/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int MinefieldContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
	if(sceneObject == NULL || object == NULL)
		return 1;

	ManagedReference<TangibleObject*> installation = cast<TangibleObject*>(sceneObject);
	if(installation == NULL)
		return 1;

	if(installation->getContainerObjectsSize() == 0 && !(installation->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)){
		int newbitmask = installation->getPvpStatusBitmask() + CreatureFlag::ATTACKABLE;
		installation->setPvpStatusBitmask(newbitmask);
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}







