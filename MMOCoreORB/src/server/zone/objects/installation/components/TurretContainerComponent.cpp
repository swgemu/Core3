/*
 * TurretContainerComponent.cpp
 *
 * Created on: 2024-07-27
 * Author: Hakry
 *
 */

#include "TurretContainerComponent.h"
#include "server/zone/objects/installation/TurretObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/FactionStatus.h"

bool TurretContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || !sceneObject->isTurret()) {
		return false;
	}

	if (permission == ContainerPermissions::MOVEIN) {
		return false;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (creature == nullptr || turret == nullptr) {
		return false;
	}

	uint32 playerFaction = creature->getFaction();
	uint32 turretFaction = turret->getFaction();
	int playerStatus = creature->getFactionStatus();

	if (playerFaction == Factions::FACTIONNEUTRAL || playerStatus == FactionStatus::ONLEAVE || turretFaction == Factions::FACTIONNEUTRAL) {
		return false;
	}

	auto zoneServer = turret->getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	// GCW Base Parent
	auto baseParent = zoneServer->getObject(turret->getOwnerObjectID());

	if (baseParent == nullptr || !baseParent->isBuildingObject()) {
		return false;
	}

	auto baseBuilding = cast<BuildingObject*>(baseParent.get());

	if (baseBuilding == nullptr) {
		return false;
	}

	auto ghost = creature->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	if (!isPrivileged) {
		if (baseBuilding->getOwnerObjectID() != creature->getObjectID()) {
			return false;
		}

		bool similarStatus = ((turret->getPvpStatusBitmask() & ObjectFlag::OVERT) && (playerStatus == FactionStatus::OVERT));

		if (turretFaction != playerFaction || !similarStatus) {
			return false;
		}
	}

	if (permission == ContainerPermissions::OPEN || permission == ContainerPermissions::MOVEOUT) {
		return true;
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}

int TurretContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
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

	if (object->isWeaponObject() && object->getGameObjectType() != SceneObjectType::MINE) {
		Locker lock(object);

		object->destroyObjectFromWorld(true);
		object->destroyObjectFromDatabase(true);

		return 1;
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
