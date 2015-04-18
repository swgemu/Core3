/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "ContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

int ContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	if (sceneObject == object) {
		errorDescription = "@container_error_message:container02"; //You cannot add something to itself.

		return TransferErrorCode::CANTADDTOITSELF;
	}

	if ((object->isNoTrade() || object->containsNoTradeObjectRecursive()) && !object->isVendor()) {
		ManagedReference<SceneObject*> containerPlayerParent = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE);
		ManagedReference<SceneObject*> containerBuildingParent = sceneObject->getParentRecursively(SceneObjectType::BUILDING);
		ManagedReference<SceneObject*> containerFactoryParent = sceneObject->getParentRecursively(SceneObjectType::FACTORY);
		ManagedReference<SceneObject*> objPlayerParent = object->getParentRecursively(SceneObjectType::PLAYERCREATURE);
		ManagedReference<SceneObject*> objBuildingParent = object->getParentRecursively(SceneObjectType::BUILDING);


		if (containerFactoryParent != NULL) {
			errorDescription = "@container_error_message:container28";
			return TransferErrorCode::CANTADD;
		} else if (objPlayerParent == NULL && objBuildingParent != NULL && (containerPlayerParent != NULL || sceneObject->isPlayerCreature())) {
			ManagedReference<BuildingObject*> buio = cast<BuildingObject*>( objBuildingParent.get());

			if (buio != NULL && buio->getOwnerObjectID() != containerPlayerParent->getObjectID()) {

				errorDescription = "@container_error_message:container27";
				return TransferErrorCode::CANTREMOVE;
			}
		} else if (objPlayerParent != NULL && containerPlayerParent == NULL && containerBuildingParent != NULL && !sceneObject->isPlayerCreature()) {
			ManagedReference<BuildingObject*> buio = cast<BuildingObject*>( containerBuildingParent.get());

			if (buio != NULL && buio->getOwnerObjectID() != objPlayerParent->getObjectID()) {

				errorDescription = "@container_error_message:container28";
				return TransferErrorCode::CANTADD;
			}
		}

	} else if (object->isVendor()) {
		ManagedReference<SceneObject*> containerPlayerParent = sceneObject->getParentRecursively(SceneObjectType::PLAYERCREATURE);

		if (!sceneObject->isCellObject() && (!sceneObject->hasArrangementDescriptor("inventory") || containerPlayerParent == NULL)) {
			return TransferErrorCode::CANTADD;
		}
	}

	Locker contLocker(sceneObject->getContainerLock());

	VectorMap<String, ManagedReference<SceneObject*> >* slottedObjects = sceneObject->getSlottedObjects();
	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = sceneObject->getContainerObjects();

	if (containmentType >= 4) {
		Locker contLocker(sceneObject->getContainerLock());

		int arrangementGroup = containmentType - 4;

		if (object->getArrangementDescriptorSize() > arrangementGroup) {
			Vector<String> descriptors = object->getArrangementDescriptor(arrangementGroup);

			for (int i = 0; i < descriptors.size(); ++i){
				String childArrangement = descriptors.get(i);

				if (slottedObjects->contains(childArrangement)) {
					errorDescription = "@container_error_message:container04"; //This slot is already occupied.
					return TransferErrorCode::SLOTOCCUPIED;
				}
			}
		}
	} else if (containmentType == -1) {
		if (containerObjects->size() >= sceneObject->getContainerVolumeLimit()) {
			errorDescription = "@container_error_message:container03"; //This container is full.

			return TransferErrorCode::CONTAINERFULL;
		}

	} else {
		sceneObject->error("unknown containmentType in canAddObject type " + String::valueOf(containmentType));

		errorDescription = "DEBUG: cant move item unknown containmentType type";
		return TransferErrorCode::UNKNOWNCONTAIMENTTYPE;
	}

	return 0;
}

bool ContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if (permissions->getOwnerID() == creature->getObjectID()) {
		return permissions->hasOwnerPermission(permission);
	}

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return false;

	if (permission == ContainerPermissions::OPEN && ghost->isPrivileged())
		return true;

	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

	if (permission != ContainerPermissions::MOVECONTAINER && permissions->hasInheritPermissionsFromParent() && parent != NULL && parent != sceneObject) {
		return parent->checkContainerPermission(creature, permission);
	} else if (permission == ContainerPermissions::MOVECONTAINER && sceneObject->isStaticObject()) {
		return false;
	}

	SortedVector<String>* groups = ghost->getPermissionGroups();

	uint16 allowPermissions = 0, denyPermissions = 0;

	for (int i = 0; i < groups->size(); ++i) {
		String group = groups->get(i);

		uint16 allow = permissions->getAllowPermissions(group);

		allowPermissions |= allow;

		uint16 deny = permissions->getDenyPermissions(group);

		denyPermissions |= deny;
	}

	return permission & (allowPermissions & ~denyPermissions);
}

bool ContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow) {
	if (sceneObject == object) {
		return false;
	}

	ManagedReference<SceneObject*> objParent = object->getParent();
	ManagedReference<Zone*> objZone = object->getLocalZone();

	if (object->containsActiveSession(SessionFacadeType::SLICING)) {
		ManagedReference<Facade*> facade = object->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());
		if (session != NULL) {
			session->cancelSession();
		}
	}

	if (objParent != NULL || objZone != NULL) {
		if (objParent != NULL)
			objParent->removeObject(object, sceneObject, notifyClient);

		if (object->getParent() != NULL) {
			object->error("error removing from parent");

			return false;
		}

		if (objZone != NULL)
			objZone->remove(object);

		object->setZone(NULL);

		if (objParent == NULL)
			objParent = objZone;
	}

	bool update = true;

	VectorMap<String, ManagedReference<SceneObject*> >* slottedObjects = sceneObject->getSlottedObjects();
	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = sceneObject->getContainerObjects();

	//if (containerType == 1 || containerType == 5) {
	if (containmentType >= 4) {
		Locker contLocker(sceneObject->getContainerLock());

		int arrangementGroup = containmentType - 4;

		if (object->getArrangementDescriptorSize() > arrangementGroup) {
			Vector<String> descriptors = object->getArrangementDescriptor(arrangementGroup);

			for (int i = 0; i < descriptors.size(); ++i){
				String childArrangement = descriptors.get(i);
				if (slottedObjects->contains(childArrangement)) {
					return false;
				}
			}

			for (int i = 0; i < descriptors.size(); ++i)	{
				 slottedObjects->put(descriptors.get(i), object);
			}
		} else {
			return false;
		}

		object->setParent(sceneObject);
		object->setContainmentType(containmentType);
	} else if (containmentType == -1) { /* else if (containerType == 2 || containerType == 3) {*/
		Locker contLocker(sceneObject->getContainerLock());

		if (!allowOverflow && containerObjects->size() >= sceneObject->getContainerVolumeLimit()){
			return false;
		}

		/*if (containerObjects.contains(object->getObjectID()))
			return false*/

		if (containerObjects->put(object->getObjectID(), object) == -1)
			update = false;

		object->setParent(sceneObject);
		object->setContainmentType(containmentType);

	} else {
		sceneObject->error("unknown containment type " + String::valueOf(containmentType));
		StackTrace::printStackTrace();
		return false;
	}

	if ((containmentType >= 4) && objZone == NULL)
		sceneObject->broadcastObject(object, true);
	else if (notifyClient)
		sceneObject->broadcastMessage(object->link(sceneObject->getObjectID(), containmentType), true);

	notifyObjectInserted(sceneObject, object);

	if (update) {
		sceneObject->updateToDatabase();
		//object->updateToDatabaseWithoutChildren()();
	}

	ManagedReference<SceneObject*> rootParent = object->getRootParent();

	if (rootParent != NULL)
		rootParent->notifyObjectInsertedToChild(object, sceneObject, objParent);

	object->notifyObservers(ObserverEventType::PARENTCHANGED, sceneObject);

	return true;
}

bool ContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) {
	VectorMap<String, ManagedReference<SceneObject*> >* slottedObjects = sceneObject->getSlottedObjects();
	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = sceneObject->getContainerObjects();

	ManagedReference<SceneObject*> objectKeeper = object;

	if (object->getParent() != sceneObject && object->getParent() != NULL) {
		ManagedReference<SceneObject*> objParent = object->getParent();

		Locker contLocker(sceneObject->getContainerLock());

		containerObjects->drop(object->getObjectID());

		if (objParent->hasObjectInContainer(object->getObjectID()) || objParent->hasObjectInSlottedContainer(object)) {
			sceneObject->error("trying to remove an object that is in a different object");
			objParent->info("i am the parent", true);

			return false;
		} else
			object->setParent(NULL);
	}

	int containedType = object->getContainmentType();

	//info("trying to remove object with containedType " + String::valueOf(containedType), true);

//	if (containedType == 4 || containedType == 5) {
	Locker contLocker(sceneObject->getContainerLock());

	int arrangementSize = object->getArrangementDescriptorSize();

	int arrangementGroup = MAX(0, containedType - 4);

	if (object->getArrangementDescriptorSize() > arrangementGroup) {
		bool removeFromSlot = false;

		Vector<String> descriptors = object->getArrangementDescriptor(arrangementGroup);

		for (int i = 0; i < descriptors.size(); ++i){
			String childArrangement = descriptors.get(i);

			ManagedReference<SceneObject*> obj = slottedObjects->get(childArrangement);

			if (slottedObjects->get(childArrangement) == object) {
				removeFromSlot = true;
				break;
			}
		}

		if (removeFromSlot) {
			for (int i = 0; i < descriptors.size(); ++i)
				slottedObjects->drop(descriptors.get(i));
		}
	}


	//	} else if (containedType == -1) {
	//Locker contLocker(sceneObject->getContainerLock());

	if (containerObjects->contains(object->getObjectID())) {
		//info("containerObjects doesnt contain specified object", true);
		//object->setParent(NULL);

		//			return false;

		containerObjects->drop(object->getObjectID());
	}

	object->setParent(NULL);

	contLocker.release();
	/*

	} else {
		sceneObject->error("unknown contained type " + String::valueOf(containedType));
		StackTrace::printStackTrace();

		return false;
	}
	*/

	if (notifyClient)
		sceneObject->broadcastMessage(object->link((uint64) 0, 0xFFFFFFFF), true);

	notifyObjectRemoved(sceneObject, object, destination);

	sceneObject->updateToDatabase();
	object->updateToDatabase();

	if (sceneObject->getParent() == NULL) {
		sceneObject->notifyObjectRemovedFromChild(object, sceneObject);
	} else {
		ManagedReference<SceneObject*> rootParent = sceneObject->getRootParent();

		if (rootParent != NULL)
			rootParent->notifyObjectRemovedFromChild(object, sceneObject);
		else
			sceneObject->notifyObjectRemovedFromChild(object, sceneObject);
	}

	return true;
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int ContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
	return sceneObject->notifyObjectInserted(object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int ContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
	return sceneObject->notifyObjectRemoved(object);
}

