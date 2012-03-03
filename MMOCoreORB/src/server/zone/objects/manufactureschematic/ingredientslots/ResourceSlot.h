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
	}

	~ResourceSlot() {

	}

	Object* clone() {
		return new ResourceSlot(*this);
	}

	bool add(CreatureObject* player, ManagedReference<TangibleObject*> tano) {

		/// Must be a resource container to proceed, and
		if (tano->isResourceContainer()) {

			ResourceContainer* incomingResource = cast<ResourceContainer*>(tano.get());

			/// Get spawn object
			ManagedReference<ResourceSpawn* > spawn = incomingResource->getSpawnObject();

			if(spawn == NULL)
				return false;

			/// Verify the resource is the right type
			if(!incomingResource->getSpawnObject()->isType(contentType))
				return false;

			if (currentSpawn == NULL) {
				currentSpawn = spawn;
			}

			int slotNeeds = requiredQuantity - quantity;
			int currentQuantity = 0;

			ManagedReference<SceneObject*> parent = incomingResource->getParent();

			if(incomingResource->getQuantity() >= slotNeeds) {

				incomingResource->setQuantity(incomingResource->getQuantity() - slotNeeds, true);
				quantity += slotNeeds;
				currentQuantity = slotNeeds;

			} else {
				quantity += incomingResource->getQuantity();
				incomingResource->setQuantity(0);
				currentQuantity = incomingResource->getQuantity();
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
				parent->transferObject(currentSpawn->createResource(parents.get(i)), -1, true);
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
