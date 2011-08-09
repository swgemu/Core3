/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"

#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/objects/tangible/terminal/structure/StructureTerminal.h"

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/managers/object/ObjectManager.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	StructureObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
}

void BuildingObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	SharedBuildingObjectTemplate* buildingData = dynamic_cast<SharedBuildingObjectTemplate*>(templateData);

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;

	totalCellNumber = buildingData->getTotalCellNumber();

	PortalLayout* portalLayout = templateData->getPortalLayout();

	if (portalLayout != NULL)
		totalCellNumber = portalLayout->getFloorMeshNumber() - 1; //remove the exterior floor

	optionsBitmask = 0x00000100;

	publicStructure = buildingData->isPublicStructure();
}

void BuildingObjectImplementation::sendChangeNamePromptTo(CreatureObject* player) {
	if (signObject == NULL) {
		StructureObjectImplementation::sendChangeNamePromptTo(player);
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);
	inputBox->setPromptTitle("@sui:set_name_title");
	inputBox->setPromptText("@sui:set_name_prompt");
	inputBox->setUsingObject(signObject);
	inputBox->setMaxInputSize(255);
	inputBox->setDefaultInput(signObject->getCustomObjectName().toString());

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

void BuildingObjectImplementation::createContainerComponent() {
	TangibleObjectImplementation::createContainerComponent();
}

void BuildingObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	if (signObject != NULL) {
		signObject->setCustomObjectName(name, notifyClient);
	} else {
		TangibleObjectImplementation::setCustomObjectName(name, notifyClient);
	}
}

void BuildingObjectImplementation::notifyLoadFromDatabase() {
	SceneObjectImplementation::notifyLoadFromDatabase();

	if (isInQuadTree()) {
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				SceneObject* containerObject = cell->getContainerObject(j);

				containerObject->insertToZone(getZone());
			}
		}
	}
}

int BuildingObjectImplementation::getCurrentNumerOfPlayerItems() {
	int items = 0;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		items += cell->getCurrentNumerOfPlayerItems();
	}

	return items;
}

void BuildingObjectImplementation::createCellObjects() {
	for (int i = 0; i < totalCellNumber; ++i) {
		SceneObject* newCell = getZoneServer()->createObject(0xAD431713, getPersistenceLevel());

		if (!addObject(newCell, -1))
			error("could not add cell");
	}

	updateToDatabase();
}

void BuildingObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		if (cell->getParent() == NULL)
			cell->setParent(_this);

		cell->setCellNumber(i + 1);
		cell->sendTo(player, true);
	}
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	info("building sendto..");

	if (!isStaticBuilding()) { // send Baselines etc..
		info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose);
	} else { // just send the objects that are in the building, without the cells because they are static in the client
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				SceneObject* childStub = cell->getContainerObject(j);

				if (!childStub->isInQuadTree())
					childStub->sendTo(player, true);
			}
		}
	}
}

Vector3 BuildingObjectImplementation::getEjectionPoint() {
	/*
	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return;

	FloorMesh* floorMesh = portalLayout->getFloorMesh(0);

	if (floorMesh == NULL)
		return;
	 */

	Vector3 ejectionPoint = getWorldPosition();

	//TODO: Redo with portal layouts and floor meshes.
	/*float x = ejectionPoint.getX();
	float y = ejectionPoint.getY();

	float halfLength = ((float) (length) * 8.0f) / 2.0f; //Half the length of the structure in meters.
	float radians = getDirection()->getRadians() + Math::deg2rad(270); //Ejection point should be on south side of structure.

	ejectionPoint.setX(x + (Math::cos(radians) * halfLength));
	ejectionPoint.setY(y + (Math::sin(radians) * halfLength));*/

	return ejectionPoint;
}

void BuildingObjectImplementation::removeFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		//cell->resetCurrentNumerOfPlayerItems();

		while (cell->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);

			obj->removeFromZone();

			cell->removeObject(obj);

			VectorMap<uint64, ManagedReference<SceneObject*> >* cont = cell->getContainerObjects();

			//cont->drop(obj->getObjectID());

			if (cont->size() > 0) {
				SceneObject* test = cell->getContainerObject(0);

				if (test == obj) {
					cont->remove(0);
				}
			}
		}

		if (signObject != NULL) {
			signObject->removeFromZone();
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

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);

		object->addInRangeObject(obj, false);
		obj->addInRangeObject(object, false);
	}

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		if (isStaticBuilding()) {
			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				SceneObject* child = cell->getContainerObject(j);

				//if (childStub->isInRange(object, 128)) {
				child->addInRangeObject(object, false);

				if (child != object) {
					object->notifyInsert(child);
					//child->sendTo(object, true);
				}

				object->addInRangeObject(child, false);

				if (child != object) {
					//object->sendTo(childStub, true);
					child->notifyInsert(object);
				}

				//}
			}
		}
	}

	object->addInRangeObject(_this, false);
	addInRangeObject(object, false);
	//this->sendTo(object, true);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	SceneObject* scno = (SceneObject*) obj;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* child = cell->getContainerObject(j);

			/*if (childStub->isCreatureObject()
					|| (scno->getRootParent() == _this) && (scno->isInRange(childStub, 128))) {*/

			if (isStaticBuilding()) {
				child->addInRangeObject(obj, false);
				obj->addInRangeObject(child, false);
			}
			//}
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObject* scno = (SceneObject*) obj;

	removeNotifiedSentObject(scno);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* child = cell->getContainerObject(j);

			child->removeInRangeObject(obj);
			obj->removeInRangeObject(child);
		}
	}
}

void BuildingObjectImplementation::insert(QuadTreeEntry* entry) {
	quadTree->insert(entry);
}

void BuildingObjectImplementation::remove(QuadTreeEntry* entry) {
	if (entry->isInQuadTree())
		quadTree->remove(entry);
}

void BuildingObjectImplementation::update(QuadTreeEntry* entry) {
	quadTree->update(entry);
}

void BuildingObjectImplementation::inRange(QuadTreeEntry* entry, float range) {
	quadTree->inRange(entry, range);
}

void BuildingObjectImplementation::addCell(CellObject* cell) {
	cells.add(cell);

	cell->setCellNumber(cells.size());

	/*if (!addObject(cell, -1))
		error("could not add cell");*/
}

void BuildingObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	StructureObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);


	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(deedObjectID);

	if (deed != NULL)
		deed->destroyObjectFromDatabase(true);

	if (signObject != NULL)
		signObject->destroyObjectFromDatabase(true);

	//Loop through the cells and delete all objects from the database.
}

void BuildingObjectImplementation::updateCellPermissionsTo(SceneObject* player) {
	/*	if (!player->isInRange(_this, 256))
		return;*/

	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = getCell(i);

		if (cell == NULL)
			continue;

		BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), true);
		player->sendMessage(perm);
	}
}

void BuildingObjectImplementation::onEnter(CreatureObject* player) {
	if (getZone() == NULL)
		return;

	if (isStaticObject())
		return;

	Vector3 ejectionPoint = getEjectionPoint();
	float x = ejectionPoint.getX();
	float y = ejectionPoint.getY();

	if (isinf(x) || isnan(x) || isinf(y) || isnan(y))
		return;

	float z = getZone()->getHeight(x, y);

	//Locker _locker(zone);

	if (isOnBanList(player->getFirstName())) {
		player->teleport(x, z, y, 0);
		return;
	}

	if (!isPublicStructure()) {
		if (!isOnEntryList(player->getFirstName()))
			player->teleport(x, z, y, 0);
	} else {
		if (getAccessFee() > 0 && !isOnAccessList(player)) {
			//Send access fee popup menu.

			//Kick the player out.
			player->teleport(x, z, y, 0);
		}
	}
}

uint32 BuildingObjectImplementation::getMaximumNumberOfPlayerItems() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == NULL)
		return 0;

	uint8 lots = ssot->getLotSize();

	//Buildings that don't cost lots have MAXPLAYERITEMS storage space.
	if (lots == 0)
		return MAXPLAYERITEMS;

	return MIN(MAXPLAYERITEMS, lots * 100);
}

bool BuildingObjectImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	if (object->isCellObject()) {
		addCell((CellObject*) object);
		//return true;
	}

	return StructureObjectImplementation::addObject(object, containmentType, notifyClient);
}
