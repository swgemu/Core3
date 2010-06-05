/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerCreature.h"

#include "../../templates/tangible/SharedBuildingObjectTemplate.h"


#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
}

void BuildingObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedBuildingObjectTemplate* buildingData = dynamic_cast<SharedBuildingObjectTemplate*>(templateData);

	totalCellNumber = buildingData->getTotalCellNumber();

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;

	lotSize = buildingData->getLotSize();
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (!isStaticBuilding()) { // send Baselines etc..
		info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose);
	} else { // just send the objects that are in the building, without the cells because they are static in the client
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				SceneObject* childStub = cell->getContainerObject(j);
				childStub->sendTo(player, true);
			}
		}
	}
}

void BuildingObjectImplementation::removeFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		while (cell->getContainerObjectsSize() > 0) {
			SceneObject* obj = cell->getContainerObject(0);

			obj->removeFromZone();
		}
	}

	TangibleObjectImplementation::removeFromZone();
}

void BuildingObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (!isStaticBuilding()) {
		info("sending building object destroy");

		SceneObjectImplementation::destroy(player->getClient());
	}
}

void BuildingObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
	info("sending building baselines");

	BaseMessage* buio3 = new TangibleObjectMessage3(_this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new TangibleObjectMessage6(_this);
	player->sendMessage(buio6);
}

void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone");
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		creoImpl->addInRangeObject(obj, true);
		obj->addInRangeObject(creoImpl, true);
	}

	creoImpl->addInRangeObject(this, false);
	addInRangeObject(creoImpl, false);

}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);

			if (!childStub->isCreatureObject())
				continue;

			SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

			child->addInRangeObject(obj, false);
			obj->addInRangeObject(child, false);
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	SceneObject* scnoStub = (SceneObject*) scno->_getStub();

	removeNotifiedSentObject(scnoStub);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);
			SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

			child->removeInRangeObject(obj);
			obj->removeInRangeObject(child);
		}
	}
}

void BuildingObjectImplementation::insert(QuadTreeEntry* entry) {
	QuadTree::insert(entry);
}

void BuildingObjectImplementation::remove(QuadTreeEntry* entry) {
	QuadTree::remove(entry);
}

void BuildingObjectImplementation::update(QuadTreeEntry* entry) {
	QuadTree::update(entry);
}

void BuildingObjectImplementation::inRange(QuadTreeEntry* entry, float range) {
	QuadTree::inRange(entry, range);
}

void BuildingObjectImplementation::addCell(CellObject* cell) {
	cells.add(cell);

	cell->setCellNumber(cells.size());

	if (!addObject(cell, -1))
		error("could not add cell");
}
