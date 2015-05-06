/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef RESOURCESLOT_H_
#define RESOURCESLOT_H_

#include "IngredientSlot.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class ResourceSlot: public IngredientSlot {

	int quantity;
	VectorMap<ManagedReference<SceneObject*>, int> parents;
	ManagedReference<ResourceSpawn*> currentSpawn;

public:
	ResourceSlot() : IngredientSlot() {
		setLoggingName("ResourceSlot");
		quantity = 0;
		clientSlotType = 4;
		parents.setAllowDuplicateInsertPlan();
	}

	ResourceSlot(const ResourceSlot& slot) : Object(), IngredientSlot(slot) {
		setLoggingName("ResourceSlot");
		quantity = slot.quantity;
		parents.setAllowDuplicateInsertPlan();
		parents = slot.parents;
		currentSpawn = slot.currentSpawn;
	}

	~ResourceSlot() {

	}

	Object* clone() {
		return new ResourceSlot(*this);
	}

	bool add(CreatureObject* player, SceneObject* satchel, ManagedReference<TangibleObject*> tano) {

		/// Must be a resource container to proceed, and
		if (tano->isResourceContainer()) {

			ResourceContainer* incomingResource = cast<ResourceContainer*>(tano.get());

			/// Get spawn object
			ManagedReference<ResourceSpawn* > spawn = incomingResource->getSpawnObject();

			if(spawn == NULL)
				return false;

			if(currentSpawn != NULL && currentSpawn != spawn)
				return false;

			/// Verify the resource is the right type
			if(!incomingResource->getSpawnObject()->isType(contentType))
				return false;

			if (currentSpawn == NULL) {
				currentSpawn = spawn;
			}

			int slotNeeds = requiredQuantity - quantity;
			int currentQuantity = 0;

			ManagedReference<SceneObject*> parent = incomingResource->getParent().get();

			if(incomingResource->getQuantity() >= slotNeeds) {

				incomingResource->setQuantity(incomingResource->getQuantity() - slotNeeds, true);
				quantity += slotNeeds;
				currentQuantity = slotNeeds;

			} else {
				quantity += incomingResource->getQuantity();
				currentQuantity = incomingResource->getQuantity();
				incomingResource->setQuantity(0, true);
			}

			VectorMapEntry<ManagedReference<SceneObject*>, int > entry(parent, currentQuantity);
			parents.add(entry);

			return true;
		}

		return false;
	}

	bool returnToParents(CreatureObject* player) {

		if(parents.size() == 0)
			return true;

		if(currentSpawn == NULL) {
			warning("Spawn is null when trying to return resources");
			return false;
		}

		for(int i = 0; i < parents.size(); ++i) {

			SceneObject* parent = parents.elementAt(i).getKey();

			if(parent == NULL)
				continue;

			bool found = false;
			// Check inventory for resource and add if existing
			for (int j = 0; j < parent->getContainerObjectsSize(); ++j) {
				ManagedReference<SceneObject*> object = parent->getContainerObject(j);

				if (object->isResourceContainer()) {
					ManagedReference<ResourceContainer*> resource = cast<ResourceContainer*>( object.get());

					if (resource->getSpawnName() == currentSpawn->getName()) {
						resource->setQuantity(resource->getQuantity() + parents.get(i));
						found = true;
						break;
					}
				}
			}

			if(!found) {
				Locker locker(currentSpawn);

				ManagedReference<ResourceContainer*> newContainer = currentSpawn->createResource(parents.get(i));

				locker.release();

				if(newContainer != NULL && newContainer->getQuantity() > 0) {
					Locker locker(newContainer);

					if(parent->transferObject(newContainer, -1, false)) {
						parent->broadcastObject(newContainer, true);
					} else {
						error("Unable to return resource to parent, transfer failed");
						newContainer->destroyObjectFromDatabase(true);
					}
				} else {
					error("Unable to return resource to parent, NULL container");

					if (newContainer != NULL) {
						Locker locker(newContainer);

						newContainer->destroyObjectFromDatabase(true);
					}
				}

			}
		}

		parents.removeAll();
		currentSpawn = NULL;
		quantity = 0;
		return true;
	}

	int getSlotQuantity() {
		return quantity;
	}

	bool isFull() {
		return quantity == requiredQuantity;
	}

	bool isEmpty() {
		return quantity == 0;
	}

	bool isResourceSlot() {
		return true;
	}

	ResourceSpawn* getCurrentSpawn() {
		return currentSpawn;
	}

	SceneObject* getFactoryIngredient() {
		return getCurrentSpawn();
	}

	Vector<uint64> getOIDVector() {
		Vector<uint64> oid;
		if(currentSpawn != NULL)
			oid.add(currentSpawn->getObjectID());
		return oid;
	}

	Vector<int> getQuantityVector() {
		Vector<int> oid;

		oid.add(quantity);

		return oid;
	}

};
#endif /*RESOURCESLOT_H_*/
