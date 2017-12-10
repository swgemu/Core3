/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

#include "templates/building/SharedBuildingObjectTemplate.h"
#include "templates/appearance/PortalLayout.h"

#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"

#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/collision/CollisionManager.h"


#include "server/zone/objects/player/sui/callbacks/StructurePayAccessFeeSuiCallback.h"
#include "server/zone/objects/building/tasks/RevokePaidAccessTask.h"
#include "server/zone/objects/region/CityRegion.h"
#include "tasks/EjectObjectEvent.h"
#include "server/zone/managers/gcw/GCWManager.h"

#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

#include "server/zone/objects/building/components/GCWBaseContainerComponent.h"
#include "server/zone/objects/building/components/EnclaveContainerComponent.h"
#include "templates/appearance/AppearanceTemplate.h"
#include "templates/appearance/MeshData.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	StructureObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
	updatePaidAccessList();
	registeredPlayerIdList.removeAll();
}

void BuildingObjectImplementation::loadTemplateData(
		SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;

	optionsBitmask = 0x00000100;

	SharedBuildingObjectTemplate* buildingData =
			dynamic_cast<SharedBuildingObjectTemplate*> (templateData);

	if (buildingData == NULL)
		return;

	totalCellNumber = buildingData->getTotalCellNumber();

	PortalLayout* portalLayout = templateData->getPortalLayout();

	if (portalLayout != NULL)
		totalCellNumber = portalLayout->getFloorMeshNumber() - 1; //remove the exterior floor

	publicStructure = buildingData->isPublicStructure();

	factionBaseType = buildingData->getFactionBaseType();
}

void BuildingObjectImplementation::createContainerComponent() {
	TangibleObjectImplementation::createContainerComponent();
}

void BuildingObjectImplementation::notifyInsertToZone(Zone* zone) {
	StructureObjectImplementation::notifyInsertToZone(zone);

	Locker locker(zone);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		cell->onBuildingInsertedToZone(asBuildingObject());
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

		if (newCell == NULL || !newCell->isCellObject()) {
			error("could not create cell");
			continue;
		}

		Locker clocker(newCell, asBuildingObject());

		if (!transferObject(newCell, -1))
			error("could not add cell");

		addCell(cast<CellObject*>(newCell.get()), i + 1);
	}

	updateToDatabase();
}

void BuildingObjectImplementation::sendContainerObjectsTo(SceneObject* player, bool forceLoad) {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		cell->sendTo(player, true);
	}
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	//info("building sendto..", true);

	if (!isStaticBuilding()) { // send Baselines etc..
		//info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose, forceLoadContainer);
	} //else { // just send the objects that are in the building, without the cells because they are static in the client

	auto closeObjects = player->getCloseObjects();

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

		if (!cell->isContainerLoaded())
			continue;

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			ManagedReference<SceneObject*> containerObject = cell->getContainerObject(j);

			if (containerObject != NULL && ((containerObject->isCreatureObject() && publicStructure) || player == containerObject
							|| (closeObjects != NULL && closeObjects->contains(containerObject.get()))))
						containerObject->sendTo(player, true, false);
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

	Vector3 worldPosition = getWorldPosition();

	if (hasTemplateEjectionPoint()) {
		Vector3 templateEjectionPoint = getTemplateEjectionPoint();
		Vector3 ejectionPoint;

		ejectionPoint.setX(worldPosition.getX() + templateEjectionPoint.getX());
		ejectionPoint.setY(worldPosition.getY() + templateEjectionPoint.getY());
		auto zone = getZone();

		if (zone != nullptr) {
			ejectionPoint.setZ(CollisionManager::getWorldFloorCollision(ejectionPoint.getX(), ejectionPoint.getY(), zone, false));
		} else {
			ejectionPoint.setZ(worldPosition.getZ() + templateEjectionPoint.getZ());
		}

		return ejectionPoint;
	} else {
		SharedObjectTemplate *shot = getObjectTemplate();

		if (shot != NULL && shot->isSharedBuildingObjectTemplate()) {
			SharedBuildingObjectTemplate *templateData = static_cast<SharedBuildingObjectTemplate*>(shot);
			PortalLayout* portalLayout = templateData->getPortalLayout();

			if (portalLayout != NULL) {
				const Vector<Reference<CellProperty*> >& cells = portalLayout->getCellProperties();
				if(cells.size() > 0) {
					const CellProperty* cell = cells.get(0);
					for (int i=0; i<cell->getNumberOfPortals(); i++) {
						const CellPortal* portal = cell->getPortal(0);
						const AABB& box = portalLayout->getPortalBounds(portal->getGeometryIndex());
						const MeshData *geom = portalLayout->getPortalGeometry(portal->getGeometryIndex());

						if (geom == NULL)
							continue;

						const Vector<MeshTriangle>& tris = *geom->getTriangles();
						const Vector<Vector3>& verts = *geom->getVerts();
						if (tris.size() == 0)
							continue;

						const MeshTriangle& tri = tris.get(0);
						const int* ind = tri.getVerts();
						Vector3 normal;
						Vector3 v[3] = { verts.get(ind[0]), verts.get(ind[1]), verts.get(ind[2]) };
						if (!portal->isWindingCCW()) {
							normal = (v[0] - v[1]).crossProduct(v[0]-v[2]);
						} else {
							normal = (v[0] - v[2]).crossProduct(v[0]-v[1]);
						}
						normal.normalize();

						Vector3 floor = box.center() - Vector3(0, box.extents().getY(), 0);
						floor += normal * 2.5f;

						Matrix4 transform;

						transform.setRotationMatrix(direction.toMatrix3());
						transform.setTranslation(getPositionX(), getPositionZ(), getPositionY());

						// this works, i have no idea why we need it. I give up.
						// Matrix4 transpose
						Matrix4 orig = transform;
						transform[0][1] = orig[1][0];
						transform[0][2] = orig[2][0];
						transform[1][0] = orig[0][1];
						transform[1][2] = orig[2][1];
						transform[2][0] = orig[0][2];
						transform[2][1] = orig[1][2];

						Vector3 flipped = transform * floor;
						return Vector3(flipped[0], flipped[2], CollisionManager::getWorldFloorCollision(flipped[0], flipped[2], flipped[1], getZone(), false));
					}
				}
			}
		}
	}

	if(signObject)
		return signObject->getPosition();

	return worldPosition;
}

void BuildingObjectImplementation::notifyRemoveFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		//cell->resetCurrentNumerOfPlayerItems();

		while (cell->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);

			Locker objLocker(obj);

			if (obj->isVendor()) {
				VendorManager::instance()->destroyVendor(obj->asTangibleObject());
			} else {
				obj->destroyObjectFromWorld(true);
			}

			objLocker.release();

			Locker contLocker(cell->getContainerLock());

			VectorMap<uint64, ManagedReference<SceneObject*> >* cont =
					cell->getContainerObjects();

			if (cont->size() > 0) {
				Reference<SceneObject*> test = cell->getContainerObject(0);

				if (test == obj) {
					cont->remove(0);
				}
			}
		}
	}

	childObjects.removeAll();
	childCreatureObjects.removeAll();

	if (signObject != NULL) {
		Locker signLocker(signObject);

		signObject->destroyObjectFromWorld(true);
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

	BaseMessage* buio3 = new TangibleObjectMessage3(asBuildingObject());
	player->sendMessage(buio3);

	BaseMessage* buio6 = new TangibleObjectMessage6(asBuildingObject());
	player->sendMessage(buio6);
}

bool BuildingObjectImplementation::isCityBanned(CreatureObject* player) {
	ManagedReference<CityRegion*> thisRegion  = this->getCityRegion().get();

	if (thisRegion != NULL)
		if (thisRegion->isBanned(player->getObjectID()))
			return true;

	return false;
}

bool BuildingObjectImplementation::isAllowedEntry(CreatureObject* player) {
	GCWBaseContainerComponent* conComp = containerComponent.castTo<GCWBaseContainerComponent*>();

	if (conComp != NULL) {
		if (factionBaseType == GCWManager::STATICFACTIONBASE)
			return true;

		return checkContainerPermission(player,ContainerPermissions::WALKIN);
	}

	EnclaveContainerComponent* encComp = containerComponent.castTo<EnclaveContainerComponent*>();

	if (encComp != NULL) {
		return checkContainerPermission(player, ContainerPermissions::WALKIN);
	}

	if (!isClientObject()) {
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

	return true;
}

void BuildingObjectImplementation::notifyObjectInsertedToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone", true);

	auto closeObjects = getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects->get(i).get());

		if ((obj->isCreatureObject() && isPublicStructure()) || isStaticBuilding()) {

			if (obj->getRootParent() != _this.getReferenceUnsafe()) {

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
		object->addInRangeObject(asBuildingObject(), false);

	addInRangeObject(object, false);

	Zone* zone = getZone();

	if (zone != NULL) {
		if (object->isTangibleObject()) {
			TangibleObject* tano = object->asTangibleObject();
			zone->updateActiveAreas(tano);
		}

		object->notifyInsertToZone(zone);
	}

	//this->sendTo(object, true);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	//remove when done
	//return;

	SceneObject* scno = cast<SceneObject*>(obj);

	if (scno == NULL)
		return;

	bool objectInThisBuilding = scno->getRootParent() == asBuildingObject();

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		if (!cell->isContainerLoaded())
			continue;

		try {
			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				ManagedReference<SceneObject*> child = cell->getContainerObject(j);

				if (child != obj && child != NULL) {
					if ((objectInThisBuilding || (child->isCreatureObject() && isPublicStructure())) || isStaticBuilding()) {
						//if (is)

						if (child->getCloseObjects() != NULL)
							child->addInRangeObject(obj, false);
						else
							child->notifyInsert(obj);

						child->sendTo(scno, true, false);//sendTo because notifyInsert doesnt send objects with parent

						if (scno->getCloseObjects() != NULL)
							scno->addInRangeObject(child, false);
						else
							scno->notifyInsert(child);

						if (scno->getParent() != NULL)
							scno->sendTo(child, true, false);
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

		if (!cell->isContainerLoaded())
			continue;

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			ManagedReference<SceneObject*> child = cell->getContainerObject(j);

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

	Locker clocker(cell, asBuildingObject());

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
			ManagedReference<SceneObject*> child = cell->getContainerObject(j);

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
          
          	Locker locker(child);

		if (child->isAiAgent()) {
			AiAgent* ai = child->asAiAgent();
                  
			ai->setRespawnTimer(0);
		}

		child->destroyObjectFromDatabase(true);
	}

	//Loop through the cells and delete all objects from the database.
}

void BuildingObjectImplementation::broadcastCellPermissions() {
	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) getCloseObjects();

	SortedVector<QuadTreeEntry*> closeObjects;
	closeObjectsVector->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects.get(i));

		if (obj->isPlayerCreature())
			updateCellPermissionsTo(cast<CreatureObject*>(obj.get()));
		else if (obj->isVehicleObject() || obj->isMount()) {
			SceneObject* rider = obj->getSlottedObject("rider");

			if (rider != NULL && rider->isPlayerCreature()) {
				updateCellPermissionsTo(cast<CreatureObject*>(rider));
			}
		}
	}
}

void BuildingObjectImplementation::broadcastCellPermissions(uint64 objectid) {
	ManagedReference<SceneObject*> obj = getZoneServer()->getObject(objectid);

	if (obj == NULL || !obj->isCellObject() || obj->getParent() != asBuildingObject())
		return;

	CellObject* cell = obj.castTo<CellObject*>();

	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) getCloseObjects();

	SortedVector<QuadTreeEntry*> closeObjects;
	closeObjectsVector->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects.get(i));

		if (obj->isPlayerCreature()) {
			CreatureObject* creo = obj.castTo<CreatureObject*>();
			cell->sendPermissionsTo(creo, isAllowedEntry(creo));
		} else if (obj->isVehicleObject() || obj->isMount()) {
			SceneObject* rider = obj->getSlottedObject("rider");

			if (rider != NULL && rider->isPlayerCreature()) {
				CreatureObject* creo = cast<CreatureObject*>(rider);
				cell->sendPermissionsTo(creo, isAllowedEntry(creo));
			}
		}
	}
}

void BuildingObjectImplementation::updateCellPermissionsTo(CreatureObject* creature) {
	bool allowEntry = isAllowedEntry(creature);

	//If they are inside, and aren't allowed to be, then kick them out!
	if (!allowEntry && creature->getRootParent() == asBuildingObject()) {
		ejectObject(creature);
	}

	for (int i = 0; i < cells.size(); ++i) {
		ManagedReference<CellObject*> cell = cells.get(i);

		if (cell == NULL)
			continue;

		cell->sendPermissionsTo(creature, allowEntry);
	}
}

void BuildingObjectImplementation::ejectObject(CreatureObject* creature) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost != NULL && ghost->hasGodMode())
		return;

	Vector3 ejectionPoint = getEjectionPoint();

	float x = ejectionPoint.getX();
	float y = ejectionPoint.getY();
	float z = ejectionPoint.getZ();

	Reference<Task*> task = new EjectObjectEvent(creature, x, z, y);
	task->execute();
}

void BuildingObjectImplementation::onEnter(CreatureObject* player) {
	if (player == NULL || !player->isPlayerCreature())
		return;

	if (getZone() == NULL)
		return;

	addTemplateSkillMods(player);

	Locker accessLock(&paidAccessListMutex);

	if (isGCWBase() && factionBaseType != GCWManager::STATICFACTIONBASE) {
		if (!checkContainerPermission(player, ContainerPermissions::WALKIN)) {
			ejectObject(player);
			return;
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
	if (!isClientObject() && (!isAllowedEntry(player) || isCondemned())) {
		i = 1;
		ejectObject(player);

		//TODO: Redo this.
		if (isCondemned()) {
			//Handle condemned messages.
			//CreatureObject* owner = getOwnerCreatureObject();
			uint64 ownerOid = getOwnerObjectID();

			if (ownerOid == player->getObjectID()) {
				StructureManager::instance()->promptPayUncondemnMaintenance(player, asBuildingObject());
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

	auto maxItems = MAXPLAYERITEMS;

	return Math::min(maxItems, lots * 100);
}

int BuildingObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	ManagedReference<Zone*> zone = getZone();

	Locker* _locker = NULL;

	if (zone != NULL)
		_locker = new Locker(zone);

	try {
		if (object->getCloseObjects() != NULL)
			object->addInRangeObject(object, false);

		if (child->isCellObject()) {
			bool runInRange = true;

			if ((oldParent == NULL || !oldParent->isCellObject()) || oldParent == child) {

				if (oldParent == NULL || (oldParent != NULL && dynamic_cast<Zone*>(oldParent) == NULL && !oldParent->isCellObject())) {
					notifyObjectInsertedToZone(object);
					runInRange = false;
				}

				if (!object->isPlayerCreature()) {
					broadcastDestroy(object, true);
					broadcastObject(object, false);
				}
			}

			if (runInRange) {
				ManagedReference<CellObject*> cell = cast<CellObject*>(child);

				if (cell != NULL) {
					for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
						ManagedReference<SceneObject*> cobj = cell->getContainerObject(j);

						if (cobj != object) {

							if (cobj->getCloseObjects() != NULL) {
								if (!cobj->getCloseObjects()->contains(object)) {
									cobj->addInRangeObject(object, false);
									object->sendTo(cobj, true, false);
								}
							} else
								cobj->notifyInsert(object);

							if (object->getCloseObjects() != NULL) {
								if (!object->getCloseObjects()->contains(cobj.get())) {
									object->addInRangeObject(cobj.get(), false);
									cobj->sendTo(object, true, false);//sendTo because notifyInsert doesnt send objects with parent
								} else {
									if (object->getClient() != NULL && cobj->isCreatureObject()) {
										object->sendMessage(cobj->link(cell->getObjectID(), -1));
									}
								}
							} else {
								object->notifyInsert(cobj.get());
							}

						}
					}
				}
			}
		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (zone != NULL) {
		delete _locker;

		if (object->isTangibleObject()) {
			TangibleObject* tano = object->asTangibleObject();
			zone->updateActiveAreas(tano);
		}
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
	if (!isCondemned()) {
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

	if (categoryName == "imperial_hq" || categoryName == "rebel_hq") {
		SharedBuildingObjectTemplate* buildingTemplate = cast<SharedBuildingObjectTemplate*>(getObjectTemplate());

		if (buildingTemplate == NULL) {
			return false;
		}

		if (buildingTemplate->getSkillMod("private_medical_rating") > 0 || buildingTemplate->getSkillMod("private_med_battle_fatigue") > 0) {
			return true;
		}
	}

	return false;
}

void BuildingObjectImplementation::registerProfessional(CreatureObject* player) {
	if(!player->isPlayerCreature() || getZone() == NULL)
		return;

	if(!registeredPlayerIdList.contains(player->getObjectID())) {

		// Check for improper faction situations ...
		if (player->isNeutral() && (!this->isNeutral())) {
			// "Neutrals may only register at neutral (non-aligned) locations."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_neutrals");
			return;
		}

		if ((player->isImperial() && this->isRebel()) || (player->isRebel() && this->isImperial())) {
			// "You may not register at a location that is factionally opposed."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_opposition");
			return;
		}

		if (getZone()->isObjectRegisteredWithPlanetaryMap(asBuildingObject())) {

			// Update the planetary map icon if needed
			if (registeredPlayerIdList.size() == 0) {
				getZone()->updatePlanetaryMapIcon(asBuildingObject(), 2);
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
			if (getZone()->isObjectRegisteredWithPlanetaryMap(asBuildingObject())) {
				// Last Entertainer/Doctor out, set icon from star to a moon.
				getZone()->updatePlanetaryMapIcon(asBuildingObject(), 1);
			}
		}

		player->sendSystemMessage("You have been unregistered from your previously registered location.");
	}
}

void BuildingObjectImplementation::promptPayAccessFee(CreatureObject* player) {
	if(!player->isPlayerCreature())
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::STRUCTURE_CONSENT_PAY_ACCESS_FEE))
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::STRUCTURE_CONSENT_PAY_ACCESS_FEE);
	box->setPromptTitle("@player_structure:access_fee_t");
	box->setPromptText("You must pay a fee of " + String::valueOf(accessFee) + " credits to enter this building");
	box->setUsingObject(asBuildingObject());
	box->setForceCloseDistance(30.f);
	box->setCallback(new StructurePayAccessFeeSuiCallback(server->getZoneServer()));

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void BuildingObjectImplementation::payAccessFee(CreatureObject* player) {
	Locker accessLock(&paidAccessListMutex);

	if (paidAccessList.contains(player->getObjectID())) {
		uint32 expireTime = paidAccessList.get(player->getObjectID());

		if(expireTime > time(0)) {
			return;
		}
	}

	if (player->getCashCredits() < accessFee) {
		player->sendSystemMessage("@player/player_utility:not_enough_money");
		return;
	}

	player->subtractCashCredits(accessFee);

	ManagedReference<CreatureObject*> owner = getOwnerCreatureObject();

	if (owner != NULL) {
		Locker clocker(owner, player);
		owner->addBankCredits(accessFee, true);
	} else {
		error("Unable to pay access fee credits to owner");
	}

	if (paidAccessList.contains(player->getObjectID()))
		paidAccessList.drop(player->getObjectID());

	paidAccessList.put(player->getObjectID(), time(0) + (accessDuration * 60));

	accessLock.release();

	if (owner != NULL && owner->isPlayerCreature()) {
		Locker clocker(owner, player);

		PlayerObject* ghost = owner->getPlayerObject();

		if (ghost != NULL)
			ghost->addExperience("merchant", 50, true);
	}

	updatePaidAccessList();

	player->sendSystemMessage("@player/player_utility:access_granted");
}

void BuildingObjectImplementation::setAccessFee(int fee, int duration) {
	Locker accessLock(&paidAccessListMutex);

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

	Locker accessLock(&paidAccessListMutex);

	for (int i = 0; i < paidAccessList.size(); ++i) {
		uint32 expirationTime = paidAccessList.elementAt(i).getValue();
		if (expirationTime <= time(0)) {
			ejectList.add(paidAccessList.elementAt(i).getKey());
		}

		if (nextExpirationTime == 0 || nextExpirationTime > expirationTime)
			nextExpirationTime = expirationTime;
	}

	for (int i = 0; i < ejectList.size(); ++i) {
		paidAccessList.drop(ejectList.get(i));
		ManagedReference<CreatureObject*> creature = server->getZoneServer()->getObject(ejectList.get(i)).castTo<CreatureObject*>();
		if (creature != NULL && creature->getRootParent() == asBuildingObject()) {
			creature->sendSystemMessage("@player_structure:turnstile_expire"); // You have been ejected because your access expired
			ejectObject(creature);
		}
	}

	Reference<Task*> pendingTask = getPendingTask("revokepaidstructureaccess");

	if (paidAccessList.isEmpty()) {
		if(pendingTask != NULL && pendingTask->isScheduled()) {
			pendingTask->cancel();
		}
		removePendingTask("revokepaidstructureaccess");
		return;
	}

	int timeToSchedule = (nextExpirationTime - time(0)) * 1000;

	if (pendingTask == NULL) {
		pendingTask = new RevokePaidAccessTask(asBuildingObject());
		addPendingTask("revokepaidstructureaccess", pendingTask, timeToSchedule);
	} else {
		pendingTask->reschedule(timeToSchedule);
	}
}

void BuildingObjectImplementation::createChildObjects() {
	if (isGCWBase()) {
		int controlIndex = 0;

		SharedObjectTemplate* serverTemplate = getObjectTemplate();

		if (serverTemplate == NULL)
			return;

		Vector3 position = getPosition();

		ZoneServer* server = getZoneServer();

		if (server == NULL)
			return;

		Zone* thisZone = asBuildingObject()->getZone();

		if (thisZone == NULL)
			return;

		GCWManager* gcwMan = thisZone->getGCWManager();

		for (int i = 0; i < serverTemplate->getChildObjectsSize();i++) {
			ChildObject* child = serverTemplate->getChildObject(i);

			if (child == NULL)
				continue;

			SharedObjectTemplate* thisTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());

			if (thisTemplate == NULL || thisTemplate->getGameObjectType() == SceneObjectType::NPCCREATURE || thisTemplate->getGameObjectType() == SceneObjectType::CREATURE)
				continue;


			String dbString = "sceneobjects";
			if (thisTemplate->getGameObjectType() == SceneObjectType::MINEFIELD || thisTemplate->getGameObjectType() == SceneObjectType::DESTRUCTIBLE || thisTemplate->getGameObjectType() == SceneObjectType::STATICOBJECT) {
				dbString = "playerstructures";
			}

			ManagedReference<SceneObject*> obj = server->createObject(child->getTemplateFile().hashCode(), dbString, getPersistenceLevel());

			if (obj == NULL)
				continue;

			Locker crossLocker(obj, asBuildingObject());

			if (obj->isCreatureObject()) {
				obj->destroyObjectFromDatabase(true);
				continue;
			}

			Vector3 childPosition = child->getPosition();
			childObjects.put(obj);
			obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
			obj->setDirection(child->getDirection());
			obj->initializeChildObject(asBuildingObject());

			// if it's inside
			if (child->getCellId() > 0) {
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
				if ((obj->isTurret() || obj->isMinefield() || obj->isDetector()) && gcwMan != NULL && !gcwMan->shouldSpawnDefenses()) {
					if (obj->isTurret())
						gcwMan->addTurret(asBuildingObject(), NULL);
					else if (obj->isMinefield())
						gcwMan->addMinefield(asBuildingObject(), NULL);
					else if (obj->isDetector())
						gcwMan->addScanner(asBuildingObject(), NULL);

					obj->destroyObjectFromDatabase(true);
					continue;
				}

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

				if (obj->isTurret() || obj->isMinefield())
					obj->createChildObjects();

				thisZone->transferObject(obj, -1, false);
			}

			if (obj->isTurretControlTerminal()) {
				DataObjectComponentReference* data  = obj->getDataObjectComponent();
				if (data != NULL) {
					TurretControlTerminalDataComponent* controlData = cast<TurretControlTerminalDataComponent*>(data->get());
					if (controlData != NULL) {
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

			if (obj->isTurret() || obj->isMinefield() || obj->isDetector()) {
				TangibleObject* tano = cast<TangibleObject*>(obj.get());
				if (tano != NULL) {
					tano->setFaction(getFaction());
					tano->setDetailedDescription("DEFAULT BASE TURRET");
					tano->setPvpStatusBitmask(getPvpStatusBitmask() | tano->getPvpStatusBitmask());
				}

				InstallationObject* installation = cast<InstallationObject*>(obj.get());
				if (installation != NULL) {
					installation->setOwner(getObjectID());
				}

				if (gcwMan != NULL) {
					if (obj->isTurret())
						gcwMan->addTurret(asBuildingObject(), obj);
					else if (obj->isMinefield())
						gcwMan->addMinefield(asBuildingObject(), obj);
					else if (obj->isDetector())
						gcwMan->addScanner(asBuildingObject(), obj);

				} else {
					info("ERROR: Unable to add faction installation to gCWmanager",true);
				}
			}
		}
	} else {
		StructureObjectImplementation::createChildObjects();
	}
}

void BuildingObjectImplementation::spawnChildSceneObject(String& templatePath, float x, float z, float y, unsigned long long cellID, float dw, float dx, float dy, float dz) {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == NULL)
		return;

	Zone* zone = asBuildingObject()->getZone();

	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> object = zoneServer->createObject(templatePath.hashCode(), getPersistenceLevel());

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

	object->createChildObjects();

	childObjects.put(object);
}

void BuildingObjectImplementation::spawnChildCreaturesFromTemplate() {
	SharedBuildingObjectTemplate* buildingTemplate = cast<SharedBuildingObjectTemplate*>(getObjectTemplate());

	if (buildingTemplate == NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();
	if (creatureManager == NULL)
		return;

	for (int i = 0; i < buildingTemplate->getChildCreatureObjectsSize(); i++) {
		ChildCreatureObject* child = buildingTemplate->getChildCreatureObject(i);
		CreatureObject* creature = NULL;

		if (child != NULL) {
			Vector3 childPosition = child->getPosition();

			// if it's inside
			if (child->getCellId() > 0) {
				int totalCells = getTotalCellNumber();

				try {
					if (totalCells >= child->getCellId()) {
						ManagedReference<CellObject*> cellObject = getCell(child->getCellId());
						if (cellObject != NULL) {
							creature = creatureManager->spawnCreatureWithAi(child->getMobile().hashCode(), childPosition.getX(), childPosition.getZ(), childPosition.getY(), cellObject->getObjectID(), false);
						} else
							error("NULL CELL OBJECT");
					}

				} catch (Exception& e) {
						error("unreported exception caught in void BuildingObjectImplementation::spawnChildCreaturesFromTemplate()!");
						e.printStackTrace();
				}

			} // create the creature outside
			else {
				String mobilename = child->getMobile();
				float angle = getDirection()->getRadians();

				float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
				float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

				x += getPosition().getX();
				y += getPosition().getY();

				float z = getPosition().getZ() + childPosition.getZ();
				float degrees = getDirection()->getDegrees();

				creature = creatureManager->spawnCreatureWithAi(mobilename.hashCode(), x, z, y, 0, false);
			}

			if (creature == NULL)
				continue;

			Locker clocker(creature, asBuildingObject());

			creature->updateDirection(child->getHeading());

			if (creature->isAiAgent()) {
				AiAgent* ai = cast<AiAgent*>(creature);
				ai->setRespawnTimer(child->getRespawnTimer());
			}

			childCreatureObjects.put(creature);
		}
	}
}

void BuildingObjectImplementation::spawnChildCreature(String& mobile, int respawnTimer, float x, float z, float y, float heading, unsigned long long cellID) {
	CreatureManager* creatureManager = zone->getCreatureManager();

	if (creatureManager == NULL)
		return;

	CreatureObject* creature = creatureManager->spawnCreatureWithAi(mobile.hashCode(), x, z, y, cellID, false);

	if (creature == NULL)
		return;

	Locker clocker(creature, asBuildingObject());

	creature->updateDirection(Math::deg2rad(heading));

	if (creature->isAiAgent()) {
		AiAgent* ai = cast<AiAgent*>(creature);
		ai->setRespawnTimer(respawnTimer);
	}

	childCreatureObjects.put(creature);
}

bool BuildingObjectImplementation::hasTemplateChildCreatures() {
	SharedBuildingObjectTemplate* buildingTemplate = cast<SharedBuildingObjectTemplate*>(getObjectTemplate());

	if (buildingTemplate == NULL)
		return false;

	return buildingTemplate->getChildCreatureObjectsSize() > 0;
}

void BuildingObjectImplementation::destroyChildObjects() {
	int size = childObjects.size();

	for (int i = 0; i < size; i++) {
		ManagedReference<SceneObject*> child = childObjects.get(0);

		if (child == NULL)
			continue;

		Locker clocker(child, asBuildingObject());

		childObjects.drop(child);
		child->destroyObjectFromDatabase(true);
		child->destroyObjectFromWorld(true);
	}

	size = childCreatureObjects.size();

	for (int i = 0; i < size; i++) {
		ManagedReference<CreatureObject*> child = childCreatureObjects.get(0);

		if (child == NULL)
			continue;

		Locker clocker(child, asBuildingObject());

		if (child->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(child.get());
			ai->setRespawnTimer(0);
		}

		childCreatureObjects.drop(child);
		child->destroyObjectFromDatabase(true);
	}
}

void BuildingObjectImplementation::changeSign(SignTemplate* signConfig) {
	if (signConfig == NULL)
		return;

	if (getZone() == NULL)
		return;

	ZoneServer* zoneServer = getZone()->getZoneServer();

	ManagedReference<SceneObject*> signSceno = zoneServer->createObject(signConfig->getTemplateFile().hashCode(), getPersistenceLevel());
	if (signSceno == NULL)
		return;

	if (!signSceno->isSignObject()) {
		signSceno->destroyObjectFromDatabase(true);
		return;
	}

	ManagedReference<SignObject*> signObject = signSceno.castTo<SignObject*>();
	if (signObject == NULL) {
		signSceno->destroyObjectFromDatabase(true);
		return;
	}

	Locker clocker(signObject, asBuildingObject());

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

	if (oldSign != NULL) {
		signName = oldSign->getCustomObjectName();

		Locker clock(oldSign, asBuildingObject());

		if (childObjects.contains(oldSign)) {
			childObjects.removeElement(oldSign);
		}

		oldSign->destroyObjectFromWorld(true);
		oldSign->destroyObjectFromDatabase(true);
	}

	Locker clocker2(signObject, asBuildingObject());

	// Finish initializing new sign
	signObject->initializeChildObject(asBuildingObject());  // should call BuildingObject::setSignObject

	// Set to old sign name
	setCustomObjectName( signName, true );
}

bool BuildingObjectImplementation::togglePrivacy() {
	// If the building is a cantina then we need to add/remove it from the planet's
	// mission map for performance locations.
	PlanetMapCategory* planetMapCategory = getPlanetMapCategory();
	if (planetMapCategory != NULL) {
		String planetMapCategoryName = planetMapCategory->getName();
		if (planetMapCategoryName == "cantina") {
			Zone* zone = getZone();
			if (zone != NULL) {
				PlanetManager* planetManager = zone->getPlanetManager();
				if (planetManager != NULL) {
					if (isPublicStructure()) {
						planetManager->removePerformanceLocation(asSceneObject());
					}
					else {
						planetManager->addPerformanceLocation(asSceneObject());
					}
				}
			}
		}
	}

	publicStructure = !publicStructure;
	return isPublicStructure();
}

BuildingObject* BuildingObject::asBuildingObject() {
	return this;
}

BuildingObject* BuildingObjectImplementation::asBuildingObject() {
	return _this.getReferenceUnsafeStaticCast();
}

Vector<Reference<MeshData*> > BuildingObjectImplementation::getTransformedMeshData(const Matrix4* parentTransform) {
	Vector<Reference<MeshData*> > data;

	Quaternion directionRecast(direction.getW(), direction.getX(), direction.getY(), -direction.getZ());

	Matrix4 transform;
	transform.setRotationMatrix(directionRecast.toMatrix3());
	transform.setTranslation(getPositionX(), getPositionZ(), -getPositionY());

	const auto fullTransform = transform * *parentTransform;

	PortalLayout *pl = getObjectTemplate()->getPortalLayout();
	if(pl) {
		if(pl->getCellTotalNumber() > 0) {
			AppearanceTemplate *appr = pl->getAppearanceTemplate(0);
			FloorMesh *floor = TemplateManager::instance()->getFloorMesh(appr->getFloorMesh());

			if (floor == NULL) {
				floor = pl->getFloorMesh(0);
			}

			if (floor != NULL) {
				data.addAll(floor->getTransformedMeshData(fullTransform));
			}

#ifndef RENDER_EXTERNAL_FLOOR_MESHES_ONLY
			data.addAll(appr->getTransformedMeshData(fullTransform));
#endif
			const CellProperty* tmpl = pl->getCellProperty(0);

			for (int i = 0; i < tmpl->getNumberOfPortals(); i++) {
				const CellPortal* portal = tmpl->getPortal(i);
				const MeshData* mesh = pl->getPortalGeometry(portal->getGeometryIndex());

				data.emplace(MeshData::makeCopyNegateZ(mesh, fullTransform));
			}

#ifdef RENDER_EXTERNAL_FLOOR_MESHES_ONLY
			return data;
#endif
		}
	}
	data.addAll(SceneObjectImplementation::getTransformedMeshData(parentTransform));
	return data;
}

const BaseBoundingVolume* BuildingObjectImplementation::getBoundingVolume() {
	PortalLayout *pl = getObjectTemplate()->getPortalLayout();

	if(pl) {
		if(pl->getCellTotalNumber() > 0) {
			AppearanceTemplate *appr = pl->getAppearanceTemplate(0);
			return appr->getBoundingVolume();
		}
	} else {
		return SceneObjectImplementation::getBoundingVolume();
	}

	return NULL;
}

bool BuildingObject::isBuildingObject() {
	return true;
}

bool BuildingObjectImplementation::isBuildingObject() {
	return true;
}

