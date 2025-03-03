/*
 * DroidContainerComponent.cpp
 */

#include "DroidDatapadContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/creature/ai/DroidObject.h"


bool DroidDatapadContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

	if (parent == nullptr || !parent->isPetControlDevice()) {
		return false;
	}

	auto controlDevice = parent.castTo<PetControlDevice*>();

	if (controlDevice == nullptr) {
		return false;
	}

	auto rootParent = controlDevice->getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (rootParent == nullptr) {
		return false;
	}

	auto ghost = creature->getPlayerObject();

	if (ghost == nullptr) {
		return false;
	}

	if (!ghost->isPrivileged() && rootParent->getObjectID() != creature->getObjectID()) {
		return false;
	}

	if (permission == ContainerPermissions::MOVEIN || permission == ContainerPermissions::MOVEOUT || permission == ContainerPermissions::OPEN) {
		return true;
	}

	return false;
}

int DroidDatapadContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
	if (!object->isManufactureSchematic()) {
		errorDescription = "@container_error_message:container12";
		return TransferErrorCode::INVALIDTYPE;
	}

	return 0;
}
