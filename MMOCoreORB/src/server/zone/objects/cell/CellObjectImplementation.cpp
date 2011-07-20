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

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		SceneObject* containerObject = getContainerObject(j);

		/*if (containerObject->getParent() == NULL)
			containerObject->setParent(_this);*/

		if (!containerObject->isInQuadTree() /*&& !containerObject->isPlayerCreature()*/)
			containerObject->sendTo(player, true);
	}
}

/*void CellObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	SceneObjectImplementation::sendTo(player, true);
}*/

void CellObjectImplementation::sendBaselinesTo(SceneObject* player) {
	/*StringBuffer msg;
	msg << "sending cell number " << cellNumber << " baselines";
	info(msg.toString(), true);*/

	BaseMessage* cellMsg3 = new CellObjectMessage3(getObjectID(), cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(getObjectID());
	player->sendMessage(cellMsg6);

	BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID(), true);
	player->sendMessage(perm);
}

int CellObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (parent != NULL && parent->isBuildingObject()) {
		ManagedReference<BuildingObject*> building = (BuildingObject*) parent.get();

		if (building->getCurrentNumerOfPlayerItems() >= building->getMaximumNumberOfPlayerItems()) {
			errorDescription = "@container_error_message:container13";

			return TransferErrorCode::TOOMANYITEMSINHOUSE;
		}
	}

	return SceneObjectImplementation::canAddObject(object, containmentType, errorDescription);
}

bool CellObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	Locker locker(_this);

	/*bool count = false;

	if (!object->isTerminal() && !object->isCreatureObject() && !containerObjects.contains(object->getObjectID()))
		count = true;*/

	bool ret = SceneObjectImplementation::addObject(object, containmentType, notifyClient);

	/*if (count && ret) {
		++currentNumberOfItems;
	}*/

	return ret;
}

bool CellObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	Locker locker(_this);

	bool ret = SceneObjectImplementation::removeObject(object, notifyClient);

	/*if (ret && !object->isTerminal() && !object->isCreatureObject()) {
		if (currentNumberOfItems > 0)
			--currentNumberOfItems;
	}*/

	return ret;
}

int CellObjectImplementation::getCurrentNumerOfPlayerItems() {
	int count = 0;

	for (int j = 0; j < getContainerObjectsSize(); ++j) {
		ManagedReference<SceneObject*> containerObject = getContainerObject(j);

		if (!containerObject->isCreatureObject() && !containerObject->isTerminal())
			++count;
	}

	return count;
}
