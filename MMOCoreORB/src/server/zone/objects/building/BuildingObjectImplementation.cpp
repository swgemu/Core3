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
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathNode.h"
#include "server/zone/templates/appearance/PathGraph.h"

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	StructureObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
}

void BuildingObjectImplementation::loadTemplateData(
		SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	SharedBuildingObjectTemplate* buildingData =
			dynamic_cast<SharedBuildingObjectTemplate*> (templateData);

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;

	totalCellNumber = buildingData->getTotalCellNumber();

	PortalLayout* portalLayout = templateData->getPortalLayout();

	if (portalLayout != NULL)
		totalCellNumber = portalLayout->getFloorMeshNumber() - 1; //remove the exterior floor

	optionsBitmask = 0x00000100;

	publicStructure = buildingData->isPublicStructure();
}

void BuildingObjectImplementation::createContainerComponent() {
	TangibleObjectImplementation::createContainerComponent();
}

void BuildingObjectImplementation::notifyLoadFromDatabase() {
	StructureObjectImplementation::notifyLoadFromDatabase();

	/*for (int i = 0; i < cel)
	getRootParent()->notifyObjectInsertedToChild(_this, getParent(), NULL);*/
}

void BuildingObjectImplementation::notifyInsertToZone(Zone* zone) {
	StructureObjectImplementation::notifyInsertToZone(zone);

	Locker locker(zone);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* child = cell->getContainerObject(j);

			notifyObjectInsertedToZone(child);
		}
	}
}

int BuildingObjectImplementation::getCurrentNumberOfPlayerItems() {
	int items = 0;

	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = cells.get(i);

		items += cell->getCurrentNumberOfPlayerItems();
	}

	return items;
}

void BuildingObjectImplementation::createCellObjects() {
	for (int i = 0; i < totalCellNumber; ++i) {
		SceneObject* newCell = getZoneServer()->createObject(0xAD431713,
				getPersistenceLevel());

		if (!transferObject(newCell, -1))
			error("could not add cell");

		addCell(cast<CellObject*>(newCell), i + 1);
	}

	updateToDatabase();
}

void BuildingObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		cell->sendTo(player, true);
	}
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	//info("building sendto..", true);

	if (!isStaticBuilding()) { // send Baselines etc..
		//info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose);
	} //else { // just send the objects that are in the building, without the cells because they are static in the client

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = player->getCloseObjects();


	// for some reason client doesnt like when you send cell creatures while sending cells?
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* containerObject = cell->getContainerObject(j);

			if ((containerObject->isCreatureObject() && publicStructure) || player == containerObject
					|| (closeObjects != NULL && closeObjects->contains(containerObject)))
				containerObject->sendTo(player, true);
		}
	}
	//}
}

Vector3 BuildingObjectImplementation::getEjectionPoint() {
	/*
	Vector3 ejectionPoint = getWorldPosition();

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return ejectionPoint;

	FloorMesh* fmOutside = portalLayout->getFloorMesh(0);

	if (fmOutside == NULL)
		return ejectionPoint;

	PathGraph* pgOutside = fmOutside->getPathGraph();
	Vector<PathNode*> pnOutside = pgOutside->getGlobalNodes();

	FloorMesh* fmInside = portalLayout->getFloorMesh(1);

	if (fmInside == NULL)
		return ejectionPoint;

	PathGraph* pgInside = fmInside->getPathGraph();

	for (int i = 0; i < pnOutside.size(); ++i) {
		PathNode* outsideNode = pnOutside.get(i);
		PathNode* insideNode = pgInside->getNode(outsideNode->getGlobalGraphNodeID());

		if (insideNode != NULL) {
			ejectionPoint = outsideNode->getPosition() + Vector3::UNIT_Y;
			WorldCoordinates coords(ejectionPoint, cells.get(0));
			return coords.getWorldPosition();
		}
	}

	return ejectionPoint;*/

	if (signObject == NULL)
		return getWorldPosition();

	return signObject->getPosition();
}

void BuildingObjectImplementation::notifyRemoveFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		//cell->resetCurrentNumerOfPlayerItems();

		while (cell->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);

			/*obj->removeFromZone();

			cell->removeObject(obj);*/
			obj->destroyObjectFromWorld(true);

			VectorMap<uint64, ManagedReference<SceneObject*> >* cont =
					cell->getContainerObjects();

			//cont->drop(obj->getObjectID());

			if (cont->size() > 0) {
				SceneObject* test = cell->getContainerObject(0);

				if (test == obj) {
					cont->remove(0);
				}
			}
		}

		if (signObject != NULL) {
			signObject->destroyObjectFromWorld(true);
		}
	}

	TangibleObjectImplementation::notifyRemoveFromZone();
}

void BuildingObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (!isStaticBuilding()) {
		info("sending building object destroy");

		SceneObjectImplementation::sendDestroyTo(player);
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

void BuildingObjectImplementation::notifyObjectInsertedToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone", true);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* obj = cast<SceneObject*>(closeObjects->get(i).get());

		if ((obj->isCreatureObject() && isPublicStructure()) || isStaticBuilding()) {

			if (obj->getRootParent() != _this) {

				if (object->getCloseObjects() != NULL)
					object->addInRangeObject(obj, false);
				else
					object->notifyInsert(obj);
				//object->sendTo(obj, true);

				if (obj->getCloseObjects() != NULL)
					obj->addInRangeObject(object, false);
				else
					obj->notifyInsert(object);
				//obj->sendTo(object, true);
			}
		}
	}

	notifyInsert(object);

	if (object->getCloseObjects() != NULL)
		object->addInRangeObject(_this, false);

	addInRangeObject(object, false);

	if (getZone() != NULL) {
		getZone()->updateActiveAreas(object);

		object->notifyInsertToZone(getZone());
	}

	//this->sendTo(object, true);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	//remove when done
	//return;

	SceneObject* scno = cast<SceneObject*>( obj);
	bool objectInThisBuilding = scno->getRootParent() == _this;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* child = cell->getContainerObject(j);

			if (child != obj && child != NULL) {
				if ((objectInThisBuilding || (child->isCreatureObject() && isPublicStructure())) || isStaticBuilding()) {
					//if (is)

					if (child->getCloseObjects() != NULL)
						child->addInRangeObject(obj, false);
					else
						child->notifyInsert(obj);

					child->sendTo(scno, true);//sendTo because notifyInsert doesnt send objects with parent

					if (scno->getCloseObjects() != NULL)
						scno->addInRangeObject(child, false);
					else
						scno->notifyInsert(child);

					if (scno->getParent() != NULL)
						scno->sendTo(child, true);
				} else if (!scno->isCreatureObject() && !child->isCreatureObject()) {
					child->notifyInsert(obj);
					obj->notifyInsert(child);
				}
			}
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObject* scno = cast<SceneObject*>( obj);
	//remove when done
	//return;


	//	removeNotifiedSentObject(scno);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* child = cell->getContainerObject(j);

			if (child->getCloseObjects() != NULL)
				child->removeInRangeObject(obj);

			if (obj->getCloseObjects() != NULL)
				obj->removeInRangeObject(child);
		}
	}
}

void BuildingObjectImplementation::insert(QuadTreeEntry* entry) {
	//return;
}

void BuildingObjectImplementation::remove(QuadTreeEntry* entry) {
}

void BuildingObjectImplementation::update(QuadTreeEntry* entry) {
}

void BuildingObjectImplementation::inRange(QuadTreeEntry* entry, float range) {
}

void BuildingObjectImplementation::addCell(CellObject* cell, uint32 cellNumber) {
	cells.put(cellNumber, cell);
#ifdef DEBUG_CELL_ORDER
	int n = cells.size();
	// Before 3373 it was assumed that cells came in order from snapshots but it turned out there was a CellId in the snapshot
	if(n != cellNumber) {
		StringBuffer buf;

		buf << "WARNING: oid:" << cell->getObjectID() << " [poid: " << getObjectID() << " " << getObjectNameStringIdName() << " " << getWorldPosition().toString() << "] Cell# " << cellNumber << " may have been " << n << " prior to 3373.";

		info(buf.toString(), true);
	}
#endif
	cell->setCellNumber(cellNumber);
}

void BuildingObjectImplementation::destroyObjectFromDatabase(
		bool destroyContainedObjects) {
	StructureObjectImplementation::destroyObjectFromDatabase(
			destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(
			deedObjectID);

	if (deed != NULL)
		deed->destroyObjectFromDatabase(true);

	if (signObject != NULL)
		signObject->destroyObjectFromDatabase(true);

	//Loop through the cells and delete all objects from the database.
}

void BuildingObjectImplementation::broadcastCellPermissions() {
	Locker _lock(zone);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects->get(i).get());

		if (obj->isPlayerCreature())
			updateCellPermissionsTo(cast<CreatureObject*>(obj.get()));
		else if (obj->isVehicleObject()) {
			SceneObject* rider = obj->getSlottedObject("rider");

			if (rider != NULL) {
				updateCellPermissionsTo(cast<CreatureObject*>(rider));
			}
		}
	}
}

void BuildingObjectImplementation::updateCellPermissionsTo(CreatureObject* creature) {
	bool allowEntry = isAllowedEntry(creature->getFirstName());

	//If they are inside, and aren't allowed to be, then kick them out!
	if (!allowEntry && creature->getRootParent() == _this) {
		ejectObject(creature);
	}

	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = cells.get(i);

		if (cell == NULL)
			continue;

		BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), allowEntry);
		creature->sendMessage(perm);
	}
}

void BuildingObjectImplementation::ejectObject(SceneObject* obj) {
	Vector3 ejectionPoint = getEjectionPoint();

	float x = ejectionPoint.getX();
	float y = ejectionPoint.getY();
	float z = 0;

	if (zone != NULL)
		zone->getHeight(x, y);

	obj->teleport(x, z, y);
}

void BuildingObjectImplementation::onEnter(CreatureObject* player) {
	if (player == NULL)
		return;

	if (getZone() == NULL)
		return;

	int i = 0;

	//If they are inside, and aren't allowed to be, then kick them out!
	if (!isStaticObject() && (!isAllowedEntry(player->getFirstName()) || isCondemned())) {
		i = 1;
		ejectObject(player);

		if (isCondemned()) {
			//Handle condemned messages.
			CreatureObject* owner = getOwnerCreatureObject();

			if (owner != NULL && owner->getFirstName() == player->getFirstName()) {
				//Owner trying to enter building.
				ManagedReference<Zone* >zone = getZone();
				if (zone != NULL) {
					ManagedReference<StructureManager*> structureManager = zone->getStructureManager();
					if (structureManager != NULL) {
						structureManager->promptPayUncondemnMaintenance(player, _this);
					}
				}
			} else {
				//Other player than the owner trying to enter the building.
				StringIdChatParameter message("@player_structure:structure_condemned_not_owner");
				player->sendSystemMessage(message);
			}
		}
	}

	addTemplateSkillMods(player);

	notifyObservers(ObserverEventType::ENTEREDBUILDING, player, i);
}

void BuildingObjectImplementation::onExit(CreatureObject* player, uint64 parentid) {
	if (player == NULL)
		return;

	if (getZone() == NULL)
		return;

	removeTemplateSkillMods(player);

	notifyObservers(ObserverEventType::EXITEDBUILDING, player, parentid);
}

uint32 BuildingObjectImplementation::getMaximumNumberOfPlayerItems() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*> (templateObject.get());

	if (ssot == NULL)
		return 0;

	uint8 lots = ssot->getLotSize();

	//Buildings that don't cost lots have MAXPLAYERITEMS storage space.
	if (lots == 0)
		return MAXPLAYERITEMS;

	return MIN(MAXPLAYERITEMS, lots * 100);
}

bool BuildingObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient) {
	return StructureObjectImplementation::transferObject(object, containmentType, notifyClient);
}

int BuildingObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	//if ()

	ManagedReference<Zone*> zone = getZone();

	Locker* _locker = NULL;

	if (zone != NULL)
		_locker = new Locker(zone);

	try {
		if (object->getCloseObjects() != NULL)
			object->addInRangeObject(object, false);
		//info("SceneObjectImplementation::insertToBuilding");

		//parent->transferObject(_this, 0xFFFFFFFF);

		if (object->getParent()->isCellObject()) {

			bool runInRange = true;

			if ((oldParent == NULL || !oldParent->isCellObject()) || oldParent == object->getParent()) {
				//insert(object);

				if (oldParent == NULL || (oldParent != NULL && dynamic_cast<Zone*>(oldParent) == NULL && !oldParent->isCellObject())) {
					notifyObjectInsertedToZone(object);
					runInRange = false;
				}

				if (!object->isPlayerCreature()) {
					broadcastDestroy(object, true);
					broadcastObject(object, false);
				}

				//notifyObjectInsertedToZone(object);
			}

			if (runInRange) {
				CellObject* cell = cast<CellObject*>(object->getParent());

				if (cell != NULL) {
					for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
						SceneObject* child = cell->getContainerObject(j);

						if (child != object) {
							//if (is)

							if (child->getCloseObjects() != NULL) {
								if (!child->getCloseObjects()->contains(object)) {
									child->addInRangeObject(object, false);
									object->sendTo(child, true);
								}
							} else
								child->notifyInsert(object);

							if (object->getCloseObjects() != NULL) {
								if (!object->getCloseObjects()->contains(child)) {
									object->addInRangeObject(child, false);
									child->sendTo(object, true);//sendTo because notifyInsert doesnt send objects with parent
								}
							} else {
								object->notifyInsert(child);
							}

						}
					}
				}
			}

		}

		//sceneObject->broadcastMessage(sceneObject->link(parent->getObjectID(), 0xFFFFFFFF), true, false);

		//info("sent cell link to everyone else");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (zone != NULL)
		delete _locker;

	if (getZone() != NULL)
		getZone()->updateActiveAreas(object);

	return 0;
}

int BuildingObjectImplementation::notifyObjectRemovedFromChild(SceneObject* object, SceneObject* child) {
	/*SceneObject* parent = sceneObject->getParent();
	Zone* zone = sceneObject->getZone();

	if (!parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

    sceneObject->broadcastMessage(sceneObject->link((uint64)0, (uint32)0xFFFFFFFF), true, false);*/

	//parent->removeObject(sceneObject, false);


	remove(object);

	//    	building->removeNotifiedSentObject(sceneObject);


	return 0;
}

void BuildingObjectImplementation::destroyAllPlayerItems() {
	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = cells.get(i);

		cell->destroyAllPlayerItems();
	}
}

void BuildingObjectImplementation::updateSignName(bool notifyClient)  {
	//TODO: Fix sign object to handle string id's.
	String condemned = "@player_structure:fix_condemned_title";
	UnicodeString signNameToSet = StringIdManager::instance()->getStringId(condemned.hashCode());
	if (!isCondemned()){
		signNameToSet = signName;
	}

	if (signObject != NULL) {
		signObject->setCustomObjectName(signNameToSet, notifyClient);
	}
}
