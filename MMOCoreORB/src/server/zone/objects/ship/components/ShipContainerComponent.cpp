/*
 * ShipContainerComponent.cpp
 */

#include "ShipContainerComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

bool ShipContainerComponent::checkContainerPermission(SceneObject* shipContainer, CreatureObject* creature, uint16 permission) const {
	return ContainerComponent::checkContainerPermission(shipContainer, creature, permission);
}

bool ShipContainerComponent::transferObject(SceneObject* shipContainer, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	// Cannot transfer an object into itself
	if (shipContainer == object) {
		return false;
	}

	if (!object->canBeTransferred(shipContainer))
		return false;


	// info(true) << shipContainer->getDisplayedName() << " attempting to transfer in Object: " << object->getDisplayedName() << " Containment Type: " << containmentType;

	ManagedReference<SceneObject*> objParent = object->getParent().get();

	ManagedReference<Zone*> objZone = object->getLocalZone();
	ManagedReference<Zone*> oldRootZone = object->getZone();

	// We will still check for slicing session
	if (object->containsActiveSession(SessionFacadeType::SLICING)) {
		ManagedReference<Facade*> facade = object->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session != nullptr) {
			session->cancelSession();
		}
	}

	if (objParent != nullptr || objZone != nullptr) {
		// Remove object from current parent
		if (objParent != nullptr) {
			// Don't notify client yet, if you do here it confuses the client and drops from toolbar etc.
			objParent->removeObject(object, shipContainer, false);
		}

		// Ensure the removal occurred
		if (object->getParent() != nullptr) {
			object->error("error removing from parent");

			return false;
		}

		// Remove object from the zone
		if (objZone != nullptr) {
			objZone->remove(object);
		}

		// Set the zone nullptr
		object->setZone(nullptr);

		//??
		//if (objParent == nullptr)
		//	objParent = objZone;
	}

	bool update = true;

	Locker contLocker(shipContainer->getContainerLock());

	VectorMap<String, ManagedReference<SceneObject*> >* slottedObjects = shipContainer->getSlottedObjects();
	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = shipContainer->getContainerObjects();

	// This is a ship container, player arrangement for ships is 5 and greater, ship droid/navicomputer arragement is 4.
	if (containmentType >= 4) {
		int arrangementGroup = containmentType - 4;

		//info(true) << shipContainer->getDisplayedName() << " Arrangement Group = " << arrangementGroup << " (containmentType - 4) Arrangment Descriptor Size: " << object->getArrangementDescriptorSize();

		if (object->getArrangementDescriptorSize() > arrangementGroup) {
			const Vector<String>* descriptors = object->getArrangementDescriptor(arrangementGroup);

			// We iterate them once and then again??
			for (int i = 0; i < descriptors->size(); ++i){
				const String& childArrangement = descriptors->get(i);

				// info(true) << shipContainer->getDisplayedName() << " Checking Child Arrangment #" << i << " - " << childArrangement;

				if (slottedObjects->contains(childArrangement)) {
					return false;
				}
			}

			for (int i = 0; i < descriptors->size(); ++i)	{
				// info(true) << shipContainer->getDisplayedName() << " inserting " << object->getDisplayedName() << " into slottedObject: " << descriptors->get(i);

				 if (slottedObjects->put(descriptors->get(i), object) == -1)
				 	update = false;
			}

			object->setContainmentType(containmentType);
			object->setParent(shipContainer);
		} else {
			return false;
		}
	// This will handle players transferred into a Cell on a ship
	} else if (containmentType == -1) {
		if (!allowOverflow && containerObjects->size() >= shipContainer->getContainerVolumeLimit()){
			return false;
		}

		if (containerObjects->put(object->getObjectID(), object) == -1)
			update = false;

		object->setParent(shipContainer);
		object->setContainmentType(containmentType);
	} else {
		error() << "unknown containment type " << containmentType;
		StackTrace::printStackTrace();

		return false;
	}

	contLocker.release();

	if ((containmentType >= 5) && (objZone == nullptr)) {
		shipContainer->broadcastObject(object, true);
	} else if (notifyClient) {
		shipContainer->broadcastMessage(object->link(shipContainer->getObjectID(), containmentType), true);
	}

	notifyObjectInserted(shipContainer, object);

	if (update) {
		shipContainer->updateToDatabase();
	}

	ManagedReference<SceneObject*> rootParent = object->getRootParent();

	if (rootParent != nullptr && notifyRoot)
		rootParent->notifyObjectInsertedToChild(object, shipContainer, objParent);

	object->notifyObservers(ObserverEventType::PARENTCHANGED, shipContainer);

	return true;
}
