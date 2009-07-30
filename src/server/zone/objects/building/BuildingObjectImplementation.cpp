/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"


BuildingObjectImplementation::BuildingObjectImplementation(LuaObject* templateData) :
	TangibleObjectImplementation(templateData), QuadTree(-1024, -1024, 1024, 1024) {

	cells = new SortedVector<CellObject*>();

	staticBuilding = false;

	setLoggingName("BuildingObject");
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	if (!isStaticBuilding()) {
		info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose);
	}
}

void BuildingObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
}


void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	info("BuildingObjectImplementation::notifyInsertToZone");
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		//if (objImpl->isPlayer() || objImpl->isNonPlayerCreature()) {
			creoImpl->addInRangeObject(obj, false);
			obj->addInRangeObject(creoImpl, true);
		//}
	}
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	info("BuildingObjectImplementation::notifyInsert");
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells->size(); ++i) {
		CellObject* cell = cells->get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);
			SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

			child->addInRangeObject(obj, false);
			obj->addInRangeObject(child, false);
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells->size(); ++i) {
		CellObject* cell = cells->get(i);

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
