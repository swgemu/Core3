/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"

#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"

#include "server/zone/packets/cell/CellObjectMessage3.h"
#include "server/zone/packets/cell/CellObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"

#include "server/zone/packets/scene/UpdateContainmentMessage.h"
#include "../../packets/scene/SceneObjectCreateMessage.h"
#include "../../packets/scene/SceneObjectDestroyMessage.h"
#include "../../packets/scene/SceneObjectCloseMessage.h"

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
	info("sending building baselines");

	BaseMessage* buio3 = new TangibleObjectMessage3((BuildingObject*) _this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new TangibleObjectMessage6((BuildingObject*) _this);
	player->sendMessage(buio6);

	sendCellsTo(player);
}

void BuildingObjectImplementation::sendCellsTo(SceneObject* player) {
	info("BuildingObjectImplementation::sendCellsTo");

	StringBuffer msg;
	msg << "BuildingObjectImplementation::sendCellsTo(): " << cells->size() << endl;
	info(msg.toString());

	UpdateContainmentMessage* link;
	CellObjectMessage3* cellMsg3;
	CellObjectMessage6* cellMsg6;
	UpdateCellPermissionsMessage* perm;
	CellObject * cell;

	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	for (int i = 1; i <= cells->size(); ++i) {
		cell = cells->get(i-1);

		BaseMessage* msg = new SceneObjectCreateMessage(cell);
		player->sendMessage(msg);

		link = new UpdateContainmentMessage(cell->getObjectID(), _this->getObjectID(), 0xFFFFFFFF);
		player->sendMessage(link);

		cellMsg3 = new CellObjectMessage3(cell->getObjectID(), /*cell->getCellNumber()*/ i);
		player->sendMessage(cellMsg3);

		cellMsg6 = new CellObjectMessage6(cell->getObjectID());
		player->sendMessage(cellMsg6);

		/*bool allow = false;

		//Players can enter so long as the structure is public or they are on the entry list.
		//However, if they are on the ban list, they cannot enter.
		if ((isPublicStructure() || isOnEntryList(player)) && !isOnBanList(player))
			allow = true;*/

		perm = new UpdateCellPermissionsMessage(cell->getObjectID());
		player->sendMessage(perm);

		BaseMessage* close = new SceneObjectCloseMessage(cell);
		player->sendMessage(close);
	}
}


void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone");
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
	//info("BuildingObjectImplementation::notifyInsert");
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
