/*
 * CellObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/cell/CellObjectMessage3.h"
#include "server/zone/packets/cell/CellObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"

void CellObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("CellObject");

	if (isClientObject()) {
		containerObjects.setNormalLoadOperationMode();
		containerObjects.cancelUnloadTask();
	}
}

void CellObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	containerObjects.setDelayedLoadOperationMode();
}

void CellObjectImplementation::notifyLoadFromDatabase() {
	SceneObjectImplementation::notifyLoadFromDatabase();

	//Rebuild count to account for transient creos
	//TODO: modify server shutdown to despawn transient mobs before final db save
	if (!isClientObject() && (!containerObjects.hasDelayedLoadOperationMode() || hasForceLoadObject())) {
		containerObjects.setDelayedLoadOperationMode();
		forceLoadObjectCount.set(0);

		for (int j = 0; j < getContainerObjectsSize(); ++j) {
			SceneObject* child = getContainerObject(j);

			if (child->isCreatureObject() || child->isVendor() || child->getPlanetMapCategoryCRC() != 0 || child->getPlanetMapSubCategoryCRC() != 0)
				forceLoadObjectCount.increment();
		}
	}
}

void CellObjectImplementation::onContainerLoaded() {
	SceneObjectImplementation::onContainerLoaded();

	ManagedReference<BuildingObject*> building = parent.get().castTo<BuildingObject*>();

	if (building == NULL)
		return;

	Locker locker(building);

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* child = getContainerObject(j);

		building->notifyObjectInsertedToChild(child, asSceneObject(), NULL);
	}
}

void CellObjectImplementation::onBuildingInsertedToZone(BuildingObject* building) {
	if (!isContainerLoaded())
		return;

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* child = getContainerObject(j);

		building->notifyObjectInsertedToZone(child);
	}
}

void CellObjectImplementation::sendContainerObjectsTo(SceneObject* player, bool forceLoad) {

}

void CellObjectImplementation::sendBaselinesTo(SceneObject* player) {
	BaseMessage* cellMsg3 = new CellObjectMessage3(getObjectID(), cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(getObjectID());
	player->sendMessage(cellMsg6);

	bool allowEntry = true;

	ManagedReference<SceneObject*> strongParent = getParent().get();

	if (player->isCreatureObject() && strongParent != NULL && strongParent->isBuildingObject()) {
		CreatureObject* creature = player->asCreatureObject();

		allowEntry = strongParent->asBuildingObject()->isAllowedEntry(creature);
	}

	BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), allowEntry);
	player->sendMessage(perm);
}

int CellObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	ManagedReference<SceneObject*> strongParent = getParent().get();

	if (strongParent != NULL && strongParent->isBuildingObject()) {
		BuildingObject* building = strongParent->asBuildingObject();

		int count = 1;

		if (object->isVendor())
			count = 0;
		else if (object->isContainerObject())
			count += object->getCountableObjectsRecursive();

		if (building->getCurrentNumberOfPlayerItems() + count > building->getMaximumNumberOfPlayerItems()) {
			errorDescription = "@container_error_message:container13";

			return TransferErrorCode::TOOMANYITEMSINHOUSE;
		}
	}

	return SceneObjectImplementation::canAddObject(object, containmentType, errorDescription);
}

bool CellObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) {
	//Locker locker(_this);

	Zone* zone = getZone();

	Locker* locker = NULL;

	if (zone != NULL) {
//		locker = new Locker(zone);
	}

	bool ret = false;

	ManagedReference<SceneObject*> oldParent = object->getParent().get();

	try {
		ret = SceneObjectImplementation::transferObject(object, containmentType, notifyClient, allowOverflow, notifyRoot);

		if (zone != NULL && object->isTangibleObject()) {
			TangibleObject* tano = cast<TangibleObject*>(object);
			zone->updateActiveAreas(tano);
		}

		if (object->isCreatureObject() || object->isVendor() || object->getPlanetMapCategoryCRC() != 0 || object->getPlanetMapSubCategoryCRC() != 0)
			forceLoadObjectCount.increment();

	} catch (...) {

	}

	if (oldParent == NULL) {
		ManagedReference<BuildingObject*> building = parent.get().castTo<BuildingObject*>();
		CreatureObject* creo = object->asCreatureObject();

		if (building != NULL && creo != NULL)
			building->onEnter(creo);
	}

	if (locker != NULL)
		delete locker;

	return ret;
}

bool CellObjectImplementation::removeObject(SceneObject* object, SceneObject* destination, bool notifyClient) {
	bool ret = SceneObjectImplementation::removeObject(object, destination, notifyClient);

	if (object->isCreatureObject() || object->isVendor() || object->getPlanetMapCategoryCRC() != 0 || object->getPlanetMapSubCategoryCRC() != 0)
		forceLoadObjectCount.decrement();

	return ret;
}

int CellObjectImplementation::getCurrentNumberOfPlayerItems() {
	int count = 0;

	ManagedReference<SceneObject*> strongParent = getParent().get();

	if (strongParent != NULL) {
		for (int j = 0; j < getContainerObjectsSize(); ++j) {
			ManagedReference<SceneObject*> containerObject = getContainerObject(j);

			if (!strongParent->containsChildObject(containerObject) && !containerObject->isCreatureObject() && !containerObject->isVendor()) {

				if (containerObject->isContainerObject())
					count += containerObject->getCountableObjectsRecursive();

				++count;
			}
		}
	}

	return count;
}

void CellObjectImplementation::destroyAllPlayerItems() {
	ManagedReference<SceneObject*> strongParent = getParent().get();

	if (strongParent == NULL)
		return;

	int containerSize = getContainerObjectsSize();

	for (int j = containerSize - 1; j >= 0; --j) {
		ManagedReference<SceneObject*> containerObject = getContainerObject(j);

		if (strongParent->containsChildObject(containerObject))
			continue;

		if (containerObject->isCreatureObject())
			continue;

		Locker locker(containerObject);

		containerObject->destroyObjectFromWorld(true);
		containerObject->destroyObjectFromDatabase(true);
	}
}

void CellObjectImplementation::sendPermissionsTo(CreatureObject* creature, bool allowEntry) {
	if (!containerPermissions.hasInheritPermissionsFromParent() && !checkContainerPermission(creature, ContainerPermissions::WALKIN)) {
		BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), false);
		creature->sendMessage(perm);
	} else {
		BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), allowEntry);
		creature->sendMessage(perm);
	}
}
