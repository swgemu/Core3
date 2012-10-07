/*
 * CellObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "CellObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/cell/CellObjectMessage3.h"
#include "server/zone/packets/cell/CellObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"

void CellObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("CellObject");
}

void CellObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	//containerVolumeLimit = 0xFFFFFFFF;

	//containerType = 2;
}

void CellObjectImplementation::notifyLoadFromDatabase() {
	// objects are added to the container twice because if insertToZone() called while the objects are loaded into the map

	//temproary fix

	//info("CellObjectImplementation::notifyLoadFromDatabase()", true);


	Vector<ManagedReference<SceneObject*> > tempObjects;

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* containerObject = getContainerObject(j);

		tempObjects.add(containerObject);
	}

	containerObjects.removeAll();

	for (int i = 0; i < tempObjects.size(); ++i) {
		SceneObject* obj = tempObjects.get(i);

		putInContainer(obj, obj->getObjectID());
	}


	SceneObjectImplementation::notifyLoadFromDatabase();
}

void CellObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	//SceneObjectImplementation::sendContainerObjectsTo(player);
	//info("sending cell containers", true);
	/*BuildingObject* building = dynamic_cast<BuildingObject*>(parent.get());
	bool publicStructure = (building != NULL) ? building->isPublicStructure() : true;



	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* containerObject = getContainerObject(j);

		if ((containerObject->isCreatureObject() && publicStructure) || player == containerObject)
			containerObject->sendTo(player, true);
	}*/
}

/*void CellObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	SceneObjectImplementation::sendTo(player, true);
}*/

void CellObjectImplementation::sendBaselinesTo(SceneObject* player) {
	BaseMessage* cellMsg3 = new CellObjectMessage3(getObjectID(), cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(getObjectID());
	player->sendMessage(cellMsg6);

	bool allowEntry = true;

	if (player->isCreatureObject() && parent != NULL && getParent().get()->isBuildingObject()) {
		ManagedReference<CreatureObject*> creature = cast<CreatureObject*>( player);

		allowEntry = (cast<BuildingObject*>(parent.get().get()))->isAllowedEntry(creature);
	}

	BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), allowEntry);
	player->sendMessage(perm);
}

int CellObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (parent != NULL && getParent().get()->isBuildingObject()) {
		ManagedReference<BuildingObject*> building = cast<BuildingObject*>( parent.get().get());

		int count = 1;

		if (object->isContainerObject())
			count += object->getContainedObjectsRecursive();

		if (building->getCurrentNumberOfPlayerItems() + count > building->getMaximumNumberOfPlayerItems()) {
			errorDescription = "@container_error_message:container13";

			return TransferErrorCode::TOOMANYITEMSINHOUSE;
		}
	}

	return SceneObjectImplementation::canAddObject(object, containmentType, errorDescription);
}

bool CellObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient) {
	//Locker locker(_this);

	Zone* zone = getZone();

	Locker* locker = NULL;

	if (zone != NULL) {
//		locker = new Locker(zone);
	}

	bool ret = false;

	ManagedReference<SceneObject*> oldParent = object->getParent();

	try {
		ret = SceneObjectImplementation::transferObject(object, containmentType, notifyClient);

		if (zone != NULL)
			zone->updateActiveAreas(object);
	} catch (...) {

	}

	if (oldParent == NULL) {
		BuildingObject* building = cast<BuildingObject*>(parent.get().get());
		CreatureObject* creo = cast<CreatureObject*>(object);

		if (building != NULL && creo != NULL)
			building->onEnter(creo);
	}

	if (locker != NULL)
		delete locker;

	return ret;
}

int CellObjectImplementation::getCurrentNumberOfPlayerItems() {
	int count = 0;

	if (parent != NULL) {
		for (int j = 0; j < getContainerObjectsSize(); ++j) {
			ManagedReference<SceneObject*> containerObject = getContainerObject(j);

			if (!getParent().get()->containsChildObject(containerObject) && !containerObject->isCreatureObject()) {

				if (containerObject->isContainerObject())
					count += containerObject->getContainedObjectsRecursive();

				++count;
			}
		}
	}

	return count;
}

void CellObjectImplementation::destroyAllPlayerItems() {
	if (parent == NULL)
		return;

	int containerSize = getContainerObjectsSize();

	for (int j = containerSize - 1; j >= 0; --j) {
		ManagedReference<SceneObject*> containerObject = getContainerObject(j);

		if (getParent().get()->containsChildObject(containerObject))
			continue;

		if (containerObject->isCreatureObject())
			continue;

		containerObject->destroyObjectFromWorld(true);
		//containerObject->broadcastDestroy(containerObject, false);
		//removeObject(containerObject, false);

		containerObject->destroyObjectFromDatabase(true);
	}
}

void CellObjectImplementation::sendPermissionsTo(CreatureObject* creature, bool allowEntry) {
	if (!containerPermissions.hasInheritPermissionsFromParent() && !checkContainerPermission(creature, ContainerPermissions::MOVEIN)) {
		BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), false);
		creature->sendMessage(perm);
	} else {
		BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), allowEntry);
		creature->sendMessage(perm);
	}
}
