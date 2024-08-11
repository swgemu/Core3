/*
 * TurretContainerComponent.cpp
 *
 * Created on: 2024-07-27
 * Author: Hakry
 *
 */

#include "TurretContainerComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"

bool TurretContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	// sceneObject->info(true) << "TurretContainerComponent::checkContainerPermission -- called - Permissions: " << permission;

	if (sceneObject == nullptr || !sceneObject->isTangibleObject()) {
		return false;
	}

	// sceneObject->info(true) << "2";

	InstallationObject* turret = cast<InstallationObject*>(sceneObject);

	if (creature == nullptr || turret == nullptr) {
		return false;
	}

	// sceneObject->info(true) << "3";

	if (creature->getFaction() == Factions::FACTIONNEUTRAL || turret->getFaction() == Factions::FACTIONNEUTRAL) {
		return false;
	}

	// sceneObject->info(true) << "4";

	auto ghost = creature->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	if (permission == ContainerPermissions::OPEN || permission == ContainerPermissions::MOVEIN) {
		if (isPrivileged || (turret->getFaction() == creature->getFaction() && creature->getFactionStatus() != FactionStatus::ONLEAVE)) {
			return true;
		} else {
			return false;
		}
	} else if (permission == ContainerPermissions::MOVEOUT) {
		/*
		if ((creature->getFaction() != turret->getFaction()) && !isPrivileged) {
			return false;
		}

		return turret->isOnAdminList(creature);
		*/
		// turret->info(true) << "Failing here...";

		return false;
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}

int TurretContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
	// sceneObject->info(true) << "TurretContainerComponent::canAddObject -- called";

	if (sceneObject == nullptr || !sceneObject->isCreatureObject() || object == nullptr) {
		return 1;
	}

	auto creO = sceneObject->asCreatureObject();

	if (object->getGameObjectType() != SceneObjectType::MINE) {
		errorDescription = "You can only add Mines to this container";
		return 1;
	}

	if (sceneObject->getContainerObjectsSize() >= 20) {
		errorDescription = "The turret is at max capacity. You cannot donate more mines.";
		return 1;
	}

	return 0;
}

int TurretContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const {
	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr) {
		return 1;
	}

	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}

int TurretContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const {
	if (sceneObject == nullptr || object == nullptr) {
		return 1;
	}

	ManagedReference<TangibleObject*> installation = cast<TangibleObject*>(sceneObject);

	if (installation == nullptr) {
		return 1;
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
