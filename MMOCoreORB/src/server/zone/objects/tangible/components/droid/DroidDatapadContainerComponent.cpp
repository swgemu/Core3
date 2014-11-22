/*
 * DroidContainerComponent.cpp
 */

#include "DroidDatapadContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/player/PlayerObject.h"

bool DroidDatapadContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
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
int DroidDatapadContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	if (!object->isManufactureSchematic()) {
		errorDescription = "@container_error_message:container12";
		return TransferErrorCode::INVALIDTYPE;
	}
	return 0;
}
