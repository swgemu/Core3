/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "server/zone/objects/building/BuildingObject.h"
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
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
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
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayAccessFeeSuiCallback.h"
#include "server/zone/objects/building/tasks/RevokePaidAccessTask.h"
#include "server/zone/objects/region/CityRegion.h"
#include "tasks/EjectObjectEvent.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/player/FactionStatus.h"

#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"

#include "server/zone/managers/planet/MapLocationType.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	StructureObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
	
	updatePaidAccessList();
	
	registeredPlayerIdList.removeAll();
	
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

	factionBaseType = buildingData->getFactionBaseType();
}

void BuildingObjectImplementation::createContainerComponent() {
	TangibleObjectImplementation::createContainerComponent();
}

void BuildingObjectImplementation::notifyLoadFromDatabase() {
	StructureObjectImplementation::notifyLoadFromDatabase();

	if (zone != NULL) {
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				ReadLocker rlocker(cell->getContainerLock());

				SceneObject* child = cell->getContainerObject(j);

				rlocker.release();

				if (child->isTangibleObject()) {
					TangibleObject* tano = cast<TangibleObject*>(child);
					zone->updateActiveAreas(tano);
				}
			}
		}
	}
}

void BuildingObjectImplementation::notifyInsertToZone(Zone* zone) {
	StructureObjectImplementation::notifyInsertToZone(zone);

	Locker locker(zone);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			ReadLocker rlocker(cell->getContainerLock());

			SceneObject* child = cell->getContainerObject(j);

			rlocker.release();

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

		Reference<SceneObject*> newCell = getZoneServer()->createObject(0xAD431713, getPersistenceLevel());

		if (!transferObject(newCell, -1))
			error("could not add cell");

		addCell(cast<CellObject*>(newCell.get()), i + 1);
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


		ContainerPermissions* perms = cell->getContainerPermissions();

		if (!perms->hasInheritPermissionsFromParent()) {
			CreatureObject* creo = cast<CreatureObject*>(player);

			if (creo != NULL && !cell->checkContainerPermission(creo, ContainerPermissions::WALKIN)) {
				BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), false);
				player->sendMessage(perm);
			}
		}

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			ReadLocker rlocker(cell->getContainerLock());

			ManagedReference<SceneObject*> containerObject = cell->getContainerObject(j);

			rlocker.release();

			if (containerObject != NULL && ((containerObject->isCreatureObject() && publicStructure) || player == containerObject
							|| (closeObjects != NULL && closeObjects->contains(containerObject.get()))))
						containerObject->sendTo(player, true);

		}
	}
	//}
}

bool BuildingObjectImplementation::hasTemplateEjectionPoint() {
	SharedBuildingObjectTemplate* buildingTemplate = templateObject.castTo<SharedBuildingObjectTemplate*>();

	if (buildingTemplate == NULL)
		return false;

	Vector3 ejectionPoint = buildingTemplate->getEjectionPoint();

	if (ejectionPoint.getX() == 0 && ejectionPoint.getY() == 0)
		return false;
	else
		return true;
}

Vector3 BuildingObjectImplementation::getTemplateEjectionPoint() {
	SharedBuildingObjectTemplate* buildingTemplate = templateObject.castTo<SharedBuildingObjectTemplate*>();

	return buildingTemplate->getEjectionPoint();
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

	Vector3 worldPosition = getWorldPosition();

	if (hasTemplateEjectionPoint()) {
		Vector3 templateEjectionPoint = getTemplateEjectionPoint();
		Vector3 ejectionPoint;

		ejectionPoint.setX(worldPosition.getX() + templateEjectionPoint.getX());
		ejectionPoint.setY(worldPosition.getY() + templateEjectionPoint.getY());
		ejectionPoint.setZ(zone->getHeight(ejectionPoint.getX(), ejectionPoint.getY()));

		return ejectionPoint;
	} else if (signObject == NULL)
		return worldPosition;

	return signObject->getPosition();
}

void BuildingObjectImplementation::notifyRemoveFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		//cell->resetCurrentNumerOfPlayerItems();

		while (cell->getContainerObjectsSize() > 0) {
			ReadLocker rlocker(cell->getContainerLock());
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);
			rlocker.release();

			/*obj->removeFromZone();

			cell->removeObject(obj);*/
			Locker objLocker(obj);

			obj->destroyObjectFromWorld(true);

			objLocker.release();

			VectorMap<uint64, ManagedReference<SceneObject*> >* cont =
					cell->getContainerObjects();

			//cont->drop(obj->getObjectID());

			if (cont->size() > 0) {
				Reference<SceneObject*> test = cell->getContainerObject(0);

				if (test == obj) {
					Locker contLocker(cell->getContainerLock());
					cont->remove(0);
				}
			}
		}

		if (signObject != NULL) {
			Locker signLocker(signObject);

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
	//info("sending building baselines",true);

	BaseMessage* buio3 = new TangibleObjectMessage3(_this.get());
	player->sendMessage(buio3);

	BaseMessage* buio6 = new TangibleObjectMessage6(_this.get());
	player->sendMessage(buio6);
}


bool BuildingObjectImplementation::isCityBanned(CreatureObject* player){

	ManagedReference<CityRegion*> thisRegion  = this->getCityRegion();

	if (thisRegion != NULL)
		if (thisRegion->isBanned(player->getObjectID()))
			return true;

	return false;
}



bool BuildingObjectImplementation::isAllowedEntry(CreatureObject* player) {

	if(isGCWBase()) {
		if (factionBaseType == GCWManager::STATICFACTIONBASE)
			return true;

		return checkContainerPermission(player,ContainerPermissions::WALKIN);
	}

	if (getLotSize() > 0) {
		PlayerObject* ghost = player->getPlayerObject().get();

		if (ghost != NULL && ghost->hasPvpTef()) {
			return false;
		}
	}

	if (getOwnerObjectID() == player->getObjectID())
		return true;

	if (isOnBanList(player))
		return false;

	if (isPrivateStructure() && !isOnEntryList(player))
		return false;

	/*
	if(accessFee > 0 && !isOnEntryList(player)) {

		if(paidAccessList.contains(player->getObjectID())) {

			uint32 expireTime = paidAccessList.get(player->getObjectID());

			if(expireTime > time(0))
				return true;

			paidAccessList.drop(player->getObjectID());
		}

		promptPayAccessFee(player);

		ejectObject(player);
	}
*/
	return true;
}

void BuildingObjectImplementation::notifyObjectInsertedToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone", true);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* obj = cast<SceneObject*>(closeObjects->get(i).get());

		if ((obj->isCreatureObject() && isPublicStructure()) || isStaticBuilding()) {

			if (obj->getRootParent().get() != _this.get()) {

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
		object->addInRangeObject(_this.get(), false);

	addInRangeObject(object, false);

	if (getZone() != NULL) {
		if (object->isTangibleObject()) {
			TangibleObject* tano = cast<TangibleObject*>(object);
			getZone()->updateActiveAreas(tano);
		}

		object->notifyInsertToZone(getZone());
	}

	//this->sendTo(object, true);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	//remove when done
	//return;

	SceneObject* scno = cast<SceneObject*>( obj);
	bool objectInThisBuilding = scno->getRootParent() == _this.get();

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		try {
			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				ReadLocker rlocker(cell->getContainerLock());
				ManagedReference<SceneObject*> child = cell->getContainerObject(j);
				rlocker.release();

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
		} catch (...) {

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

			ReadLocker rlocker(cell->getContainerLock());
			ManagedReference<SceneObject*> child = cell->getContainerObject(j);
			rlocker.release();

			if (child == NULL)
				continue;

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

CellObject* BuildingObjectImplementation::getCell(const String& cellName) {
	SharedBuildingObjectTemplate* buildingTemplate = templateObject.castTo<SharedBuildingObjectTemplate*>();

	if (buildingTemplate == NULL)
		return NULL;

	PortalLayout* portalLayout = buildingTemplate->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	int index = portalLayout->getCellID(cellName);

	if (index == -1 || index == 0)
		return NULL;

	return getCell(index);
}

void BuildingObjectImplementation::destroyObjectFromDatabase(
	bool destroyContainedObjects) {

	float x = getPositionX();
	float y = getPositionY();
	float z = 0;

	if (zone != NULL)
		z = zone->getHeight(x, y);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = cell->getContainerObjectsSize() - 1; j >= 0 ; --j) {
			ReadLocker rlocker(cell->getContainerLock());
			ManagedReference<SceneObject*> child = cell->getContainerObject(j);
			rlocker.release();

			if (child->isPlayerCreature()) {
				child->teleport(x, z, y);

				if (cell->hasObjectInContainer(child->getObjectID())) {
					cell->removeObject(child, NULL, true);
				}
			}
		}
	}

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

	//Remove all child creature objects from database
	for (int i = 0; i < childCreatureObjects.size(); ++i) {
		ManagedReference<CreatureObject*> child = childCreatureObjects.get(i);

		if (child == NULL)
			continue;

		if (child->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(child.get());
			ai->setRespawnTimer(0);
		}

		child->destroyObjectFromDatabase(true);
	}

	//Loop through the cells and delete all objects from the database.
}

void BuildingObjectImplementation::broadcastCellPermissions() {
	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	closeObjectsVector->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects.get(i).get());

		if (obj->isPlayerCreature())
			updateCellPermissionsTo(cast<CreatureObject*>(obj.get()));
		else if (obj->isVehicleObject() || obj->isMount()) {
			SceneObject* rider = obj->getSlottedObject("rider");

			if (rider != NULL) {
				updateCellPermissionsTo(cast<CreatureObject*>(rider));
			}
		}
	}
}

void BuildingObjectImplementation::broadcastCellPermissions(uint64 objectid) {
	ManagedReference<SceneObject*> obj = getZoneServer()->getObject(objectid);

	if (obj == NULL || !obj->isCellObject() || obj->getParent() != _this.get())
		return;

	CellObject* cell = obj.castTo<CellObject*>();

	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	closeObjectsVector->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects.get(i).get());

		if (obj->isPlayerCreature()) {
			CreatureObject* creo = obj.castTo<CreatureObject*>();
			cell->sendPermissionsTo(creo, isAllowedEntry(creo));
		} else if (obj->isVehicleObject() || obj->isMount()) {
			SceneObject* rider = obj->getSlottedObject("rider");

			if (rider != NULL) {
				CreatureObject* creo = cast<CreatureObject*>(rider);
				cell->sendPermissionsTo(creo, isAllowedEntry(creo));
			}
		}
	}
}

void BuildingObjectImplementation::updateCellPermissionsTo(CreatureObject* creature) {
	bool allowEntry = isAllowedEntry(creature);

	//If they are inside, and aren't allowed to be, then kick them out!
	if (!allowEntry && creature->getRootParent() == _this.get()) {
		ejectObject(creature);
	}

	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = cells.get(i);

		if (cell == NULL)
			continue;

		//cell->sendPermissionsTo(creature,false);
		cell->sendPermissionsTo(creature, allowEntry);
	}
}

void BuildingObjectImplementation::ejectObject(CreatureObject* creature) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost != NULL && ghost->isPrivileged())
		return;

	Vector3 ejectionPoint = getEjectionPoint();

	float x = ejectionPoint.getX();
	float y = ejectionPoint.getY();
	float z = 0;

	if (zone != NULL)
		z = zone->getHeight(x, y);

	Reference<Task*> task = new EjectObjectEvent(creature, x, z, y);
	task->execute();
}

void BuildingObjectImplementation::onEnter(CreatureObject* player) {
	if (player == NULL || !player->isPlayerCreature())
		return;

	if (getZone() == NULL)
		return;

	addTemplateSkillMods(player);

	Locker acessLock(&paidAccessListMutex);

	
	if(isGCWBase() && factionBaseType != GCWManager::STATICFACTIONBASE){
		if(!checkContainerPermission(player,ContainerPermissions::WALKIN)){
			ejectObject(player);
		}
	}
	

	if (accessFee > 0 && !isOnEntryList(player)) {
		//thread safety issues!
		if (paidAccessList.contains(player->getObjectID())) {
			uint32 expireTime = paidAccessList.get(player->getObjectID());

			if(expireTime <= time(0)) {
				paidAccessList.drop(player->getObjectID());

				promptPayAccessFee(player);

				ejectObject(player);

				return;
			}
		} else {
			promptPayAccessFee(player);

			ejectObject(player);

			return;
		}
	}

	int i = 0;

	notifyObservers(ObserverEventType::ENTEREDBUILDING, player, i);

	//If they are inside, and aren't allowed to be, then kick them out!
	if (!isStaticObject() && (!isAllowedEntry(player) || isCondemned())) {
		i = 1;
		ejectObject(player);

		//TODO: Redo this.
		if (isCondemned()) {
			//Handle condemned messages.
			//CreatureObject* owner = getOwnerCreatureObject();
			uint64 ownerOid = getOwnerObjectID();

			if (ownerOid == player->getObjectID()) {
					StructureManager::instance()->promptPayUncondemnMaintenance(player, _this.get());
			} else {
				//Other player than the owner trying to enter the building.
				StringIdChatParameter message("@player_structure:structure_condemned_not_owner");
				player->sendSystemMessage(message);
			}

		}
	}

	if (isCivicStructure() && isCityBanned(player)) {
		ejectObject(player);

		player->sendSystemMessage("@city/city:youre_city_banned"); // you are banned from this city and may not use any of its public services and structures
	}
}

void BuildingObjectImplementation::onExit(CreatureObject* player, uint64 parentid) {
	if (player == NULL)
		return;

	if (getZone() == NULL)
		return;

	removeTemplateSkillMods(player);

	unregisterProfessional(player);

	notifyObservers(ObserverEventType::EXITEDBUILDING, player, parentid);
}

uint32 BuildingObjectImplementation::getMaximumNumberOfPlayerItems() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*> (templateObject.get());
	if (isCivicStructure() )
		return 250;

	if (ssot == NULL)
		return 0;
	//This sets the item limit for City Halls and Cloning Centers to 250 like they were during live, instead of 400 like they are now from the line below.

	uint8 lots = ssot->getLotSize();

	//Buildings that don't cost lots have MAXPLAYERITEMS storage space.
	if (lots == 0)
		return MAXPLAYERITEMS;

	return MIN(MAXPLAYERITEMS, lots * 100);
}

bool BuildingObjectImplementation::transferObject(SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow) {
	return StructureObjectImplementation::transferObject(object, containmentType, notifyClient, allowOverflow);
}

int BuildingObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	ManagedReference<Zone*> zone = getZone();

	Locker* _locker = NULL;

	if (zone != NULL)
		_locker = new Locker(zone);

	try {
		if (object->getCloseObjects() != NULL)
			object->addInRangeObject(object, false);
		//info("SceneObjectImplementation::insertToBuilding");

		//parent->transferObject(_this.get(), 0xFFFFFFFF);

		if (object->getParent().get()->isCellObject()) {

			bool runInRange = true;

			if ((oldParent == NULL || !oldParent->isCellObject()) || oldParent == object->getParent().get()) {
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
				ManagedReference<CellObject*> cell = cast<CellObject*>(object->getParent().get().get());

				if (cell != NULL) {
					for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {

						ReadLocker rlocker(cell->getContainerLock());
						ManagedReference<SceneObject*> child = cell->getContainerObject(j);
						rlocker.release();

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
								if (!object->getCloseObjects()->contains(child.get())) {
									object->addInRangeObject(child.get(), false);
									child->sendTo(object, true);//sendTo because notifyInsert doesnt send objects with parent
								} else {
									if (object->getClient() != NULL && child->isCreatureObject()) {
										object->sendMessage(child->link(cell->getObjectID(), -1));
									}
								}
							} else {
								object->notifyInsert(child.get());
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

	if (getZone() != NULL && object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);
		getZone()->updateActiveAreas(tano);
	}

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

bool BuildingObjectImplementation::isInPlayerCity() {
	ManagedReference<CityRegion*> city = this->getCityRegion().get();
	if (city != NULL) {
		return (!city->isClientRegion());
	}
	return false;
}

bool BuildingObjectImplementation::canPlayerRegisterWithin() {
	PlanetMapCategory* pmc = getPlanetMapSubCategory();

	if (pmc == NULL)
		pmc = getPlanetMapCategory();

	if (pmc == NULL)
		return false;

	String categoryName = pmc->getName();
	if (categoryName == "medicalcenter" || categoryName == "hotel" || categoryName == "cantina" || categoryName == "theater" || categoryName == "guild_theater" || categoryName == "tavern")
		return true;

	return false;
}

void BuildingObjectImplementation::registerProfessional(CreatureObject* player) {

	if(!player->isPlayerCreature() || getZone() == NULL)
		return;

	if(!registeredPlayerIdList.contains(player->getObjectID())) {

		// Check for improper faction situations ...
		if ( player->isNeutral() && (!this->isNeutral())) {
			// "Neutrals may only register at neutral (non-aligned) locations."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_neutrals");
			return;
		}

		if ( (player->isImperial() && this->isRebel()) || (player->isRebel() && this->isImperial())) {
			// "You may not register at a location that is factionally opposed."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_opposition");
			return;
		}

		if (getZone()->isObjectRegisteredWithPlanetaryMap(_this.get())) {

			// Update the planetary map icon if needed
			if (registeredPlayerIdList.size() == 0) {
				getZone()->updatePlanetaryMapIcon(_this.get(), 2);
			}

			registeredPlayerIdList.put(player->getObjectID());

			// "You successfully register with this location."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:success");
		} else {
			// "You cannot register at a location that is not registered with the planetary map."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:cannot_register");
		}

	}
	else {
		// "But you are already registered at this location."
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:already_registered");
	}

}

void BuildingObjectImplementation::unregisterProfessional(CreatureObject* player) {
	if(!player->isPlayerCreature() || getZone() == NULL)
		return;

	if (registeredPlayerIdList.drop(player->getObjectID())) {
		if (registeredPlayerIdList.size() == 0) {
			if (getZone()->isObjectRegisteredWithPlanetaryMap(_this.get())) {
				// Last Entertainer/Doctor out, set icon from star to a moon.
				getZone()->updatePlanetaryMapIcon(_this.get(), 1);
			}
		}

		player->sendSystemMessage("You have been unregistered from your previously registered location.");
	}

}

void BuildingObjectImplementation::promptPayAccessFee(CreatureObject* player) {
	if(!player->isPlayerCreature())
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost->hasSuiBoxWindowType(SuiWindowType::STRUCTURE_CONSENT_PAY_ACCESS_FEE))
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::STRUCTURE_CONSENT_PAY_ACCESS_FEE);
	box->setPromptTitle("@player_structure:access_fee_t");
	box->setPromptText("You must pay a fee of " + String::valueOf(accessFee) + " credits to enter this building");
	box->setUsingObject(_this.get());
	box->setForceCloseDistance(30.f);
	box->setCallback(new StructurePayAccessFeeSuiCallback(server->getZoneServer()));

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void BuildingObjectImplementation::payAccessFee(CreatureObject* player) {
	Locker acessLock(&paidAccessListMutex);

	if (paidAccessList.contains(player->getObjectID())) {
		uint32 expireTime = paidAccessList.get(player->getObjectID());

		if(expireTime > time(0)) {
			return;
		}
	}

	if(player->getCashCredits() < accessFee) {
		player->sendSystemMessage("@player/player_utility:not_enough_money");
		return;
	}

	player->subtractCashCredits(accessFee);

	ManagedReference<CreatureObject*> owner = getOwnerCreatureObject();

	if(owner != NULL) {
		Locker clocker(owner, player);
		owner->addBankCredits(accessFee, true);
	} else {
		error("Unable to pay access fee credits to owner");
	}


	if(paidAccessList.contains(player->getObjectID()))
		paidAccessList.drop(player->getObjectID());

	paidAccessList.put(player->getObjectID(), time(0) + (accessDuration * 60));

	acessLock.release();

	if(owner != NULL && owner->isPlayerCreature()) {
		Locker clocker(owner, player);
		owner->getPlayerObject()->addExperience("merchant", 50, true);
	}

	updatePaidAccessList();

	player->sendSystemMessage("@player/player_utility:access_granted");

}

void BuildingObjectImplementation::setAccessFee(int fee, int duration) {
	accessFee = fee;
	accessDuration = duration;
	lastAccessFeeChange = time(0);
}

bool BuildingObjectImplementation::canChangeAccessFee() {
	// 10 Minutes between changes
	return lastAccessFeeChange + 600  < time(0);
}

int BuildingObjectImplementation::getAccessFeeDelay() {
	int secondsLeft = lastAccessFeeChange + 600  - time(0);
	return (secondsLeft / 60) + 1;
}

void BuildingObjectImplementation::updatePaidAccessList() {

	Vector<uint64> ejectList;
	uint32 nextExpirationTime = 0;

	Locker acessLock(&paidAccessListMutex);

	for(int i = 0; i < paidAccessList.size(); ++i) {
		uint32 expirationTime = paidAccessList.elementAt(i).getValue();
		if(expirationTime <= time(0)) {
			ejectList.add(paidAccessList.elementAt(i).getKey());
		}

		if(nextExpirationTime == 0 || nextExpirationTime > expirationTime)
			nextExpirationTime = expirationTime;
	}

	for(int i = 0; i < ejectList.size(); ++i)
	{
		paidAccessList.drop(ejectList.get(i));
		ManagedReference<CreatureObject*> creature = server->getZoneServer()->getObject(ejectList.get(i)).castTo<CreatureObject*>();
		if(creature != NULL && creature->getRootParent() == _this.get()) {
			creature->sendSystemMessage("@player_structure:turnstile_expire"); // You have been ejected because your access expired
			ejectObject(creature);
		}
	}

	Reference<Task*> pendingTask = getPendingTask("revokepaidstructureaccess");

	if(paidAccessList.isEmpty()) {
		if(pendingTask != NULL && pendingTask->isScheduled()) {
			pendingTask->cancel();
		}
		removePendingTask("revokepaidstructureaccess");
		return;
	}

	int timeToSchedule = (nextExpirationTime - time(0)) * 1000;

	if(pendingTask == NULL) {
		pendingTask = new RevokePaidAccessTask(_this.get());
		addPendingTask("revokepaidstructureaccess", pendingTask, timeToSchedule);
	} else {
		pendingTask->reschedule(timeToSchedule);
	}

}


void BuildingObjectImplementation::createChildObjects(){
	if(isGCWBase()){


		int controlIndex = 0;

		SharedObjectTemplate* serverTemplate = getObjectTemplate();

		if(serverTemplate == NULL)
			return;

		Vector3 position = getPosition();

		ZoneServer* server = getZoneServer();

		if(server == NULL)
			return;

		GCWManager* gcwMan = zone->getGCWManager();

		for(int i = 0; i < serverTemplate->getChildObjectsSize();i++){
			//info("iterating child",true);
			ChildObject* child = serverTemplate->getChildObject(i);

			if(child == NULL)
				continue;

			SharedObjectTemplate* thisTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());
			//info("tried to get " + child->getTemplateFile(),true);

			if(thisTemplate == NULL || thisTemplate->getGameObjectType() == SceneObjectType::NPCCREATURE || thisTemplate->getGameObjectType() == SceneObjectType::CREATURE)
				continue;


			String dbString = "sceneobjects";
			if(thisTemplate->getGameObjectType() == SceneObjectType::MINEFIELD || thisTemplate->getGameObjectType() == SceneObjectType::TURRET || thisTemplate->getGameObjectType() == SceneObjectType::STATICOBJECT ){
				dbString = "playerstructures";
			}

			ManagedReference<SceneObject*> obj = server->createObject(child->getTemplateFile().hashCode(),dbString,1);

			if (obj == NULL )
				continue;

			if(obj->isCreatureObject()) {
				obj->destroyObjectFromDatabase(true);
				continue;
			}

			Vector3 childPosition = child->getPosition();
			childObjects.put(obj);
			obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
			obj->setDirection(child->getDirection());
			obj->initializeChildObject(_this.get());


			// if it's inside
			if(child->getCellId() > 0){
				int totalCells = getTotalCellNumber();
				try {
					if (totalCells >= child->getCellId()) {
						ManagedReference<CellObject*> cellObject = getCell(child->getCellId());

						if (cellObject != NULL) {
							if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
								obj->destroyObjectFromDatabase(true);
							}
						} else {
							obj->destroyObjectFromDatabase(true);
							error("NULL CELL OBJECT");
						}
					}
				} catch (Exception& e) {
					error("unreported exception caught in void BuildingObjectImplementation::createChildObjects()!");
					e.printStackTrace();
				}

			} else {

				if( (obj->isTurret() || obj->isMinefield() || obj->isDetector()) && !gcwMan->shouldSpawnDefenses() ){

					if(obj->isTurret())
						gcwMan->addTurret(_this.get(),NULL);
					else if (obj->isMinefield())
						gcwMan->addMinefield(_this.get(),NULL);
					else if (obj->isDetector())
						gcwMan->addScanner(_this.get(), NULL);

					obj->destroyObjectFromDatabase(true);
					continue;
				}

				SharedObjectTemplate* thisTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());

				if(thisTemplate == NULL || thisTemplate->getGameObjectType() == SceneObjectType::NPCCREATURE){
					obj->destroyObjectFromDatabase(true);
					continue;
				}

				Vector3 childPosition = child->getPosition();
				float angle = getDirection()->getRadians();
				float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
				float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));
				x += position.getX();
				y += position.getY();

				float z = position.getZ() + childPosition.getZ();
				float degrees = getDirection()->getDegrees();

				Quaternion dir = child->getDirection();

				obj->initializePosition(x, z, y);
				obj->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));


				if(obj->isTurret() || obj->isMinefield())
					obj->createChildObjects();


				if (getZone())
					getZone()->transferObject(obj, -1, false);
			}

			if(obj->isTurretControlTerminal()){
				DataObjectComponentReference* data  = obj->getDataObjectComponent();
				if(data != NULL){
					TurretControlTerminalDataComponent* controlData = cast<TurretControlTerminalDataComponent*>(data->get());
					if(controlData != NULL){
						controlData->setTurretIndex(controlIndex);
						controlIndex++;
					}

				}

			}
			ContainerPermissions* permissions = obj->getContainerPermissions();
			permissions->setOwner(getObjectID());
			permissions->setInheritPermissionsFromParent(false);
			permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
			permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

			if(obj->isTurret() || obj->isMinefield() || obj->isDetector()){
				TangibleObject* tano = cast<TangibleObject*>(obj.get());
				tano->setFaction(getFaction());
				tano->setDetailedDescription("DEFAULT BASE TURRET");
				tano->setPvpStatusBitmask(getPvpStatusBitmask() | tano->getPvpStatusBitmask());

				InstallationObject* installation = cast<InstallationObject*>(obj.get());
				if(installation != NULL){
					installation->setOwner(getObjectID());
				}

				if(gcwMan != NULL){
					if(obj->isTurret())
						gcwMan->addTurret(_this.get(),obj);
					else if (obj->isMinefield())
						gcwMan->addMinefield(_this.get(),obj);
					else if (obj->isDetector())
						gcwMan->addScanner(_this.get(),obj);

				} else {
					info("ERROR: Unable to add faction installation to gCWmanager",true);
				}
			}


		}
	} else {

		StructureObjectImplementation::createChildObjects();
	}


}

void BuildingObjectImplementation::spawnChildSceneObject(String& templatePath, float x, float z, float y, unsigned long long cellID, float dw, float dx, float dy, float dz){
	ZoneServer* zoneServer = getZoneServer();

	if(zoneServer == NULL)
		return;

	Zone* zone = _this.get()->getZone();

	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> object = zoneServer->createObject(templatePath.hashCode(), 0);

	if (object == NULL || object->isCreatureObject())
		return;

	Locker objLocker(object);

	object->initializePosition(x, z, y);
	object->setDirection(dw, dx, dy, dz);

	Reference<SceneObject*> cell = NULL;

	if (cellID != 0) {
		cell = zoneServer->getObject(cellID);

		if (cell != NULL && !cell->isCellObject()) {
			cell = NULL;
		}
	}

	if (cell != NULL) {
		cell->transferObject(object, -1);
	} else {
		zone->transferObject(object, -1, true);
	}

	objLocker.release();

	object->createChildObjects();

	childObjects.put(object);
}

void BuildingObjectImplementation::spawnChildCreaturesFromTemplate(){
	SharedBuildingObjectTemplate* buildingTemplate = cast<SharedBuildingObjectTemplate*>(getObjectTemplate());

	if(buildingTemplate == NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();
	if(creatureManager == NULL)
		return;

	for(int i = 0; i < buildingTemplate->getChildCreatureObjectsSize();i++){

		ChildCreatureObject* child = buildingTemplate->getChildCreatureObject(i);
		CreatureObject* creature = NULL;
		if(child != NULL){

			// if it's inside
			if(child->getCellId() > 0){
				int totalCells = getTotalCellNumber();
				try {

					if (totalCells >= child->getCellId()) {

						ManagedReference<CellObject*> cellObject = getCell(child->getCellId());
						if (cellObject != NULL) {
							creature = creatureManager->spawnCreatureWithAi(child->getMobile().hashCode(),child->getPosition().getX(),child->getPosition().getZ(),child->getPosition().getY(),cellObject->getObjectID(),false);
						} else
							error("NULL CELL OBJECT");
					}

				} catch (Exception& e) {
						error("unreported exception caught in void SceneObjectImplementation::createChildObjects()!");
						e.printStackTrace();
				}

			} // create the creature outside
			else {
					String mobilename = child->getMobile();

					Vector3 childPosition = child->getPosition();
					float angle = getDirection()->getRadians();

					float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
					float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

					x += getPosition().getX();
					y += getPosition().getY();

					float z = getPosition().getZ() + childPosition.getZ();
					float degrees = getDirection()->getDegrees();

					creature = creatureManager->spawnCreatureWithAi(mobilename.hashCode(),x,z,y,0,false);

			}

			if(creature == NULL)
				continue;

			Locker clocker(creature, _this.get());

			creature->updateDirection(child->getHeading());

			if(creature->isAiAgent()){
				AiAgent* ai = cast<AiAgent*>(creature);
				ai->setRespawnTimer(child->getRespawnTimer());
			}

			childCreatureObjects.put(creature);
		}
	}
}

void BuildingObjectImplementation::spawnChildCreature(String& mobile, int respawnTimer, float x, float z, float y, float heading, unsigned long long cellID){
	CreatureManager* creatureManager = zone->getCreatureManager();

	if(creatureManager == NULL)
		return;

	CreatureObject* creature = creatureManager->spawnCreatureWithAi(mobile.hashCode(),x,z,y,cellID,false);

	if(creature == NULL)
		return;

	Locker clocker(creature, _this.get());

	creature->updateDirection(Math::deg2rad(heading));

	if(creature->isAiAgent()){
		AiAgent* ai = cast<AiAgent*>(creature);
		ai->setRespawnTimer(respawnTimer);
	}

	childCreatureObjects.put(creature);
}

bool BuildingObjectImplementation::hasTemplateChildCreatures(){
	SharedBuildingObjectTemplate* buildingTemplate = cast<SharedBuildingObjectTemplate*>(getObjectTemplate());

	if(buildingTemplate == NULL)
		return false;

	return buildingTemplate->getChildCreatureObjectsSize() > 0;
}

void BuildingObjectImplementation::destroyChildObjects() {

	int size = childObjects.size();

	for (int i = 0; i < size; i++) {
		ManagedReference<SceneObject*> child = childObjects.get(0);

		if (child == NULL)
			continue;

		childObjects.drop(child);
		child->destroyObjectFromDatabase(true);
		child->destroyObjectFromWorld(true);
	}

	size = childCreatureObjects.size();

	for (int i = 0; i < size; i++) {
		ManagedReference<CreatureObject*> child = childCreatureObjects.get(0);

		if (child == NULL)
			continue;

		if (child->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(child.get());
			ai->setRespawnTimer(0);
		}

		childCreatureObjects.drop(child);
		child->destroyObjectFromDatabase(true);
	}
}

void BuildingObjectImplementation::changeSign( SignTemplate* signConfig ){

	if (signConfig == NULL)
		return;

	if (getZone() == NULL)
		return;

	ZoneServer* zoneServer = getZone()->getZoneServer();

	ManagedReference<SceneObject*> signSceno = zoneServer->createObject(signConfig->getTemplateFile().hashCode(), 1);
	if (signSceno == NULL)
		return;

	if ( !signSceno->isSignObject() ) {
		signSceno->destroyObjectFromDatabase(true);
		return;
	}

	ManagedReference<SignObject*> signObject = signSceno.castTo<SignObject*>();
	if( signObject == NULL ) {
		signSceno->destroyObjectFromDatabase(true);
		return;
	}

	Locker clocker(signObject, _this.get());

	Vector3 signPosition = signConfig->getPosition();
	childObjects.put(signSceno);
	signObject->initializePosition(signPosition.getX(), signPosition.getZ(), signPosition.getY());
	signObject->setDirection(signConfig->getDirection());

	//Create the object outdoors in relation to parent structure.
	Vector3 position = getPosition();

	float angle = direction.getRadians();

	float x = (Math::cos(angle) * signPosition.getX()) + (signPosition.getY() * Math::sin(angle));
	float y = (Math::cos(angle) * signPosition.getY()) - (signPosition.getX() * Math::sin(angle));

	x += position.getX();
	y += position.getY();

	float z = position.getZ() + signPosition.getZ();

	float degrees = direction.getDegrees();

	Quaternion dir = signConfig->getDirection();

	signObject->initializePosition(x, z, y);
	signObject->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));

	getZone()->transferObject(signObject, -1, false);

	// Set sign permissions
	ContainerPermissions* permissions = signSceno->getContainerPermissions();
	permissions->setOwner(getObjectID());
	permissions->setInheritPermissionsFromParent(false);
	permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
	permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

	clocker.release();

	// Remove old sign (but save its name)
	UnicodeString signName = "@sign_name:sign";
	SignObject* oldSign = getSignObject();
	if( oldSign != NULL ){
		signName = oldSign->getCustomObjectName();

		Locker clock( oldSign, _this.get() );
		if( childObjects.contains(oldSign) ){
			childObjects.removeElement(oldSign);
		}
		oldSign->destroyObjectFromWorld(true);
		oldSign->destroyObjectFromDatabase(true);

	}

	Locker clocker2(signObject, _this.get());

	// Finish initializing new sign
	signObject->initializeChildObject(_this.get());  // should call BuildingObject::setSignObject

	// Set to old sign name
	setCustomObjectName( signName, true );
}
