/*
 * DroidContainerComponent.cpp
 */

#include "DroidContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/player/PlayerObject.h"

bool DroidContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {

	ManagedReference<SceneObject*> p = sceneObject->getParent();

	if (p == NULL || !p->isDroidObject()) {
		return false;
	}

	DroidObject* droid = p.castTo<DroidObject*>();

	if(droid == NULL){
		return false;
	}

	if (!creature->getPlayerObject()->isPrivileged() && droid->getLinkedCreature() != creature){
		return false;
	}

	if(permission == ContainerPermissions::MOVEIN){
		return true;
	}else if (permission == ContainerPermissions::MOVEOUT ){
		return true;
	} else if ( permission == ContainerPermissions::OPEN  ) {
		return true;
	}
	return false;
}
int DroidContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	if (object->isContainerObject() && !object->isResourceContainer()) {
		errorDescription = "@container_error_message:container12";
		return TransferErrorCode::INVALIDTYPE;
	}
	if (object->isControlDevice() || object->isInstallationObject() || object->isBuildingObject() || object->isCraftingStation()) {
		errorDescription = "@container_error_message:container12";
		return TransferErrorCode::INVALIDTYPE;
	}
	ManagedReference<SceneObject*> p = sceneObject->getParent();
	if (p) {
		DroidObject* droid = p.castTo<DroidObject*>();
		if (droid) {
			if(!object->isASubChildOf(droid->getLinkedCreature().get())) {
				errorDescription = "@container_error_message:container14";
				return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
			}
		}
	}

	return 0;
}
