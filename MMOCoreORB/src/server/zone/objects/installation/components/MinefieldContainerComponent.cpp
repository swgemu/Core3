/*
 * MinefieldContainerComponent.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: root
 */

#include "MinefieldContainerComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/FactionStatus.h"

bool MinefieldContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || !sceneObject->isTangibleObject()) {
		return false;
	}

	if (permission == ContainerPermissions::MOVEIN) {
		return false;
	}

	ManagedReference<InstallationObject*> minefield = cast<InstallationObject*>(sceneObject);

	if (creature == nullptr || minefield == nullptr) {
		return false;
	}

	uint32 playerFaction = creature->getFaction();
	uint32 minefieldFaction = minefield->getFaction();
	int playerStatus = creature->getFactionStatus();

	if (playerFaction == Factions::FACTIONNEUTRAL || playerStatus == FactionStatus::ONLEAVE || minefieldFaction == Factions::FACTIONNEUTRAL) {
		return false;
	}

	auto zoneServer = minefield->getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	// GCW Base Parent
	auto baseParent = zoneServer->getObject(minefield->getOwnerObjectID());

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

		bool similarStatus = ((minefield->getPvpStatusBitmask() & ObjectFlag::OVERT) && (playerStatus == FactionStatus::OVERT));

		if (minefieldFaction != playerFaction || !similarStatus) {
			return false;
		}
	}

	if (permission == ContainerPermissions::OPEN || permission == ContainerPermissions::MOVEOUT) {
		return true;
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}

int MinefieldContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->getGameObjectType() != SceneObjectType::MINE) {
		errorDescription = "You can only add Mines to this container";
		return 1;
	}

	if (sceneObject->getContainerObjectsSize() >= 20) {
		errorDescription = "The minefield is at its 20 mine capacity. You cannot donate more mines.";
		return 1;
	}

	return 0;
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int MinefieldContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const {
	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr) {
		return 1;
	}

	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int MinefieldContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const {
	if (sceneObject == nullptr || object == nullptr)
		return 1;

	ManagedReference<TangibleObject*> installation = cast<TangibleObject*>(sceneObject);

	if (installation == nullptr) {
		return 1;
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
