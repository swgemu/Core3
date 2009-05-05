/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "../../../packets/building/BuildingObjectMessage3.h"
#include "../../../packets/building/BuildingObjectMessage6.h"
#include "../../../packets/cell/CellObjectMessage3.h"
#include "../../../packets/cell/CellObjectMessage6.h"
#include "../../../packets/cell/CellObjectDeltaMessage3.h"
#include "../../../packets/cell/UpdateCellPermissionsMessage.h"
#include "../../../packets/scene/SceneObjectCreateMessage.h"
#include "../../../packets/scene/SceneObjectCloseMessage.h"
#include "../../../packets/scene/UpdateContainmentMessage.h"

#include "cell/CellObject.h"

#include "BuildingObjectImplementation.h"

BuildingObjectImplementation::BuildingObjectImplementation(uint64 objid, uint8 buildingtype, bool staticbuilding)
		: QuadTree(-1024, -1024, 1024, 1024), BuildingObjectServant(objid, BUILDING) {

	setBuildingType(buildingtype);
	setStaticBuilding(staticbuilding);

	init();
}

BuildingObjectImplementation::~BuildingObjectImplementation() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);
		server->getZoneServer()->removeObject(cell);
		cell->removeUndeploymentEvent();
		cell->finalize();
	}

	delete permissionList;
	permissionList = NULL;
}

void BuildingObjectImplementation::init() {
	StringBuffer name;
	name << "BuildingObject(" << objectType << ")  0x" << hex << objectID;

	SceneObjectImplementation::setLoggingName(name.toString());
	SceneObjectImplementation::setLogging(false);
	SceneObjectImplementation::setGlobalLogging(true);

	cells.setInsertPlan(SortedVector<SceneObject*>::NO_DUPLICATE);
	sceneObjects.setInsertPlan(SortedVector<SceneObject*>::NO_DUPLICATE);

	//Don't forget to set this later.
	permissionList = new StructurePermissionList(NULL);
}

void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	info("BuildingObjectImplementation::notifyInsertToZone");
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();
	if (creoImpl == NULL)
		return;

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		//if (objImpl->isPlayer() || objImpl->isNonPlayerCreature()) {
		creoImpl->addInRangeObject(obj, false);
		obj->addInRangeObject(creoImpl, true);
	}
}

void BuildingObjectImplementation::serialize() {

}

void BuildingObjectImplementation::deserialize() {

}

void BuildingObjectImplementation::removeFromZone(bool doLock) {
	try {
		//System::out << "SceneObjectImplementation::removeFromZone(bool doLock) Entered" << endl;
		if (zone == NULL || !isInQuadTree())
			return;

		//System::out << "SceneObjectImplementation::removeFromZone(bool doLock) After Zone/QuadTree check" << endl;
		//deaggro();

		zone->lock(doLock);

		putPlayersInWorld();

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;
			BuildingObject* building = (BuildingObject*)parent->getParent();

			removeFromBuilding(building);
		} else
			zone->remove(this);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);

			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->deleteObject(objectID);

		zone->unlock(doLock);
	} catch (...) {
		System::out << "exception SceneObjectImplementation::removeFromZone(bool doLock)\n";

		zone->unlock(doLock);
	}
}

void BuildingObjectImplementation::addSceneObject(SceneObject* sceneObject) {
	sceneObjects.put(sceneObject);
}

/**
 * This method is called when the structure is removed from the map, and players are inserted back into the world.
 */
void BuildingObjectImplementation::putPlayersInWorld() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getChildrenSize(); ++j) {
			SceneObject* child = cell->getChild(j);
			SceneObjectImplementation* childImpl = (SceneObjectImplementation*) child->_getImplementation();

			child->removeFromZone(false);

			if (child->isPlayer() || child->isNonPlayerCreature()) {
				child->setParent(NULL);
				child->initializePosition(positionX, positionZ, positionY);

				child->setZone(zone);

				zone->registerObject(child);

				zone->insert(childImpl);
				zone->inRange(childImpl, 128);
			}
		}
	}
}

/**
 * Adds a CellObject to the building. If cellnumber is not set prior to addition, then it will be set
 * to the current cell count plus one.
 * \param cell The CellObject to add.
 */
void BuildingObjectImplementation::addCell(CellObject* cell) {
	// Guess Cell Numbers
	if(cell->getCellNumber() == 0)
		cell->setCellNumber(cells.size()+1);

	cells.put(cell);
}

/**
 * Checks to see if the building contains a cell with a specific id.
 * \param cellid The objectID of the cell to check for.
 */
bool BuildingObjectImplementation::containsCell(uint64 cellid) {
	for (int i = 0; i < cells.size(); i++) {
		if (cells.get(i)->getObjectID() == cellid)
			return true;
	}

	return false;
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//When the building is inserted to zone, we go ahead and set the permission lists
	//building to this objects stub.
	permissionList->setParentStructure(_this);

	info("BuildingObjectImplementation::notifyInsert");
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	if (scno->isPlayer() || scno->isNonPlayerCreature()) {
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getChildrenSize(); ++j) {
				SceneObject* child = cell->getChild(j);

				if (child->isPlayer() || child->isNonPlayerCreature()) {
					child->addInRangeObject(obj, false);

					SceneObjectImplementation* a = (SceneObjectImplementation*) child->_getImplementation();
					if (a != NULL)
						obj->addInRangeObject(a, false);
				}
			}
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getChildrenSize(); ++j) {
			SceneObject* child = cell->getChild(j);

			child->removeInRangeObject(obj);

			SceneObjectImplementation* a = (SceneObjectImplementation*) child->_getImplementation();

			if (a != NULL)
				obj->removeInRangeObject(a);
		}
	}
}

void BuildingObjectImplementation::sendTo(Player* player, bool close) {
	info("BuildingObjectImplementation::sendTo");
	// send buio packets if not static

	ZoneClientSession* client = player->getClient();

	if (client == NULL)
		return;

	if (staticBuilding)
		return;

	SceneObjectImplementation::create(client);

	BaseMessage* buio3 = new BuildingObjectMessage3((BuildingObject*) _this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new BuildingObjectMessage6((BuildingObject*) _this);
	player->sendMessage(buio6);

	sendCellsTo(player, true);

	SceneObjectImplementation::close(client);

	//We also need to send the sign and terminal if this is a player structure.
}

void BuildingObjectImplementation::sendCellsTo(Player* player, bool close) {
	info("BuildingObjectImplementation::sendCellsTo");

	StringBuffer msg;
	msg << "BuildingObjectImplementation::sendCellsTo(): " << cells.size() << endl;
	info(msg.toString());

	UpdateContainmentMessage* link;
	CellObjectMessage3* cellMsg3;
	CellObjectMessage6* cellMsg6;
	UpdateCellPermissionsMessage* perm;
	CellObject * cell;

	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	for (int i = 1; i <= cells.size(); ++i) {
		cell = cells.get(i-1);

		BaseMessage* msg = new SceneObjectCreateMessage(cell);
		player->sendMessage(msg);

		link = new UpdateContainmentMessage(cell->getObjectID(), _this->getObjectID(), 0xFFFFFFFF);
		player->sendMessage(link);

		cellMsg3 = new CellObjectMessage3(cell->getObjectID(), cell->getCellNumber());
		player->sendMessage(cellMsg3);

		cellMsg6 = new CellObjectMessage6(cell->getObjectID());
		player->sendMessage(cellMsg6);

		bool allow = false;

		//Players can enter so long as the structure is public or they are on the entry list.
		//However, if they are on the ban list, they cannot enter.
		if ((isPublicStructure() || isOnEntryList(player)) && !isOnBanList(player))
			allow = true;

		perm = new UpdateCellPermissionsMessage(cell->getObjectID(), allow);
		player->sendMessage(perm);

		BaseMessage* close = new SceneObjectCloseMessage(cell);
		player->sendMessage(close);
	}
}


void BuildingObjectImplementation::sendCellUpdatesTo(Player* player) {
	info("BuildingObjectImplementation::sendCellUpdates");
	CellObjectDeltaMessage3* cdelta3;
	CellObject *cell;

	//System::out << "sending cells, size: " << cells.size() << endl;
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	for (int i = 1; i <= cells.size(); ++i) {
		//System::out << "sending cell cell: " << i << endl;
		cell = cells.get(i-1);

		CellObjectDeltaMessage3* msg = new CellObjectDeltaMessage3(cell);
		msg->updateCellNumber(i);
		msg->close();
		player->sendMessage(msg);
	}
}

/*
void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	info("BuildingObjectImplementation::notifyInsertToZone");
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();
	if (creoImpl == NULL)
		return;

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		//if (objImpl->isPlayer() || objImpl->isNonPlayerCreature()) {
			creoImpl->addInRangeObject(obj, false);
			obj->addInRangeObject(creoImpl, true);
		//}
	}
}*/

void BuildingObjectImplementation::parseItemAttributes() {
	String attr = "buildintType";
	setBuildingType(itemAttributes->getIntAttribute(attr));

	attr = "staticBuilding";
	setStaticBuilding(itemAttributes->getBooleanAttribute(attr));

	attr = "publicStructure";
	setPublicStructure(itemAttributes->getBooleanAttribute(attr));

}

/**
 * Sends this structures associated permission list to the player.
 * \param player The player requesting the permission list.
 * \param listname Which permission list to send. Can be BAN, ENTRY, ADMIN, HOPPER, VENDOR.
 */
void BuildingObjectImplementation::sendPermissionListTo(Player* player, const String& listname) {
	if (permissionList == NULL)
		return;

	permissionList->sendTo(player, listname);
}

/**
 * Sends the confirmation dialog box for destroying this structure to the player.
 * \param player The player requestion the structure destroy.
 */
void BuildingObjectImplementation::sendConfirmDestroyTo(Player* player) {
	//TODO: Add in sui confirm destroy code.
}


/**
 * Adds or removes an entry from the specified permission list.
 * \param player The player attempting to modify the permission list.
 * \param listname The name of the list being modified. BAN, ENTRY, ADMIN, HOPPER, VENDOR.
 * \param entryname The name of the entry being removed or added to the list.
 * \param add Is the entry being removed or added to the list.
 */
void BuildingObjectImplementation::modifyPermissionList(Player* player, const String& listname, const String& entryname, bool add) {
	//TODO: Add or remove a person from the specified permission list.
}
