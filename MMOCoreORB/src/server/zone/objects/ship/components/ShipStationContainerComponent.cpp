/*
 * ShipStationContainerComponent.cpp
 *
 * Container component for POB ship stations (pilot chair, operations chair, turret ladder).
 * Prevents premature broadcastObject during zone transfers where notifyClient is false.
 */

#include "ShipStationContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/Zone.h"

bool ShipStationContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) const {
	if (sceneObject == object) {
		return false;
	}

	if (!object->canBeTransferred(sceneObject))
		return false;

	if (object->containsActiveSession(SessionFacadeType::SLICING)) {
		ManagedReference<Facade*> facade = object->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session != nullptr) {
			session->cancelSession();
		}
	}

	ManagedReference<SceneObject*> objParent = object->getParent().get();

	ManagedReference<Zone*> objZone = object->getLocalZone();
	ManagedReference<Zone*> oldRootZone = object->getZone();

	if (objParent != nullptr || objZone != nullptr) {
		bool nullifyParent = (sceneObject == nullptr);

		if (objParent != nullptr) {
			objParent->removeObject(object, sceneObject, false, nullifyParent);
		}

		if (nullifyParent && object->getParent() != nullptr) {
			object->error() << "Failed to remove object from old parent: " << object->getDisplayedName() << " ID: " << object->getObjectID() << " to container: " << sceneObject->getDisplayedName() << " ID: " << sceneObject->getObjectID();

			return false;
		}

		if (objZone != nullptr) {
			objZone->remove(object);
		}

		object->setZone(nullptr);

		if (objParent == nullptr) {
			objParent = objZone;
		}
	}

	Locker contLocker(sceneObject->getContainerLock());

	VectorMap<String, ManagedReference<SceneObject*> >* slottedObjects = sceneObject->getSlottedObjects();
	VectorMap<uint64, ManagedReference<SceneObject*> >* containerObjects = sceneObject->getContainerObjects();

	bool update = true;

	if (containmentType >= 4) {
		int arrangementGroup = containmentType - 4;

		if (object->getArrangementDescriptorSize() > arrangementGroup) {
			const Vector<String>* descriptors = object->getArrangementDescriptor(arrangementGroup);

			for (int i = 0; i < descriptors->size(); ++i) {
				const String& childArrangement = descriptors->get(i);

				if (slottedObjects->contains(childArrangement)) {
					return false;
				}
			}

			for (int i = 0; i < descriptors->size(); ++i) {
				if (slottedObjects->put(descriptors->get(i), object) == -1)
					update = false;
			}
		} else {
			return false;
		}

		object->setParent(sceneObject);
		object->setContainmentType(containmentType);
	} else if (containmentType == -1) {
		if (!allowOverflow && containerObjects->size() >= sceneObject->getContainerVolumeLimit()) {
			return false;
		}

		if (containerObjects->put(object->getObjectID(), object) == -1)
			update = false;

		object->setParent(sceneObject);
		object->setContainmentType(containmentType);
	} else {
		return false;
	}

	contLocker.release();

	// Key difference from base ContainerComponent:
	// Only broadcast slotted object creates when notifyClient is true.
	// During zone transfers (hyperspace), notifyClient is false and the proper
	// create/baseline sequence is handled by sendToOwner + notifyObjectInsertedToChild.
	// The base ContainerComponent always calls broadcastObject for containmentType >= 4
	// when objZone is null, regardless of notifyClient — this causes premature creates
	// that crash the client during hyperspace.
	if (notifyClient) {
		if ((containmentType >= 4) && (objZone == nullptr)) {
			sceneObject->broadcastObject(object, true);
		} else {
			sceneObject->broadcastMessage(object->link(sceneObject->getObjectID(), containmentType), true);
		}
	}

	notifyObjectInserted(sceneObject, object);

	if (update) {
		sceneObject->updateToDatabase();
	}

	ManagedReference<SceneObject*> rootParent = object->getRootParent();

	if (rootParent != nullptr && notifyRoot) {
		rootParent->notifyObjectInsertedToChild(object, sceneObject, objParent);
	}

	object->notifyObservers(ObserverEventType::PARENTCHANGED, sceneObject);

	return true;
}
