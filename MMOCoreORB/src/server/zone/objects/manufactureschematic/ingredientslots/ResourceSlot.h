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

	ManagedReference<ResourceContainer* > contents;

public:
	ResourceSlot(SceneObject* tool, String t, int q) :
		IngredientSlot(t, q) {

		craftingTool = tool;
		slottype = RESOURCESLOT;
		contents = NULL;

		setLoggingName("ResourceSlot");

		optional = false;
	}

	ResourceSlot(const ResourceSlot& slot) : Object(), IngredientSlot(slot) {
		contents = slot.contents;

		setLoggingName("ResourceSlot");
	}

	~ResourceSlot() {

		cleanup();
	}


	Object* clone() {
		return new ResourceSlot(*this);
	}

	inline void cleanup() {
		contents = NULL;
	}

	inline int getQuantity() {

		if (contents != NULL)
			return contents->getQuantity();
		else
			return 0;
	}

	bool add(CreatureObject* player, TangibleObject* tano) {

		/// Must be a resource container to proceed
		if (tano->isResourceContainer() && getQuantity() < requiredQuantity) {

			previousParent = tano->getParent();

			ResourceContainer* incomingResource = cast<ResourceContainer*>( tano);

			/// Verify the resource is the right type
			if(!incomingResource->getSpawnObject()->isType(type))
				return false;

			if (contents != NULL) {

				int needs = requiredQuantity - contents->getQuantity();

				if(incomingResource->getQuantity() > needs) {

					incomingResource->setQuantity(incomingResource->getQuantity() - needs);
					contents->setQuantity(contents->getQuantity() + needs);

				} else {
					contents->setQuantity(contents->getQuantity() + incomingResource->getQuantity());
					incomingResource->setQuantity(0);
				}

			} else if (contents == NULL && incomingResource->getQuantity() > requiredQuantity) {

				ResourceSpawn* spawn = incomingResource->getSpawnObject();

				incomingResource->setQuantity(incomingResource->getQuantity() - requiredQuantity);

				contents = spawn->createResource(requiredQuantity);

				contents->setParent(NULL);
				craftingTool->transferObject(contents, -1, false);

				contents->sendTo(player, true);
				contents->sendAttributeListTo(player);

			} else {

				contents = incomingResource;

				/*if(contents->getParent() != NULL)
					contents->getParent()->removeObject(contents, true);*/
				craftingTool->transferObject(contents, -1, true);

				if(previousParent != NULL) {
					//previousParent->removeObject(incomingResource, true);
					incomingResource->destroyObjectFromWorld(true);
				}
			}

			return true;
		}

		return false;
	}

	inline bool remove(CreatureObject* player) {

		return returnObjectToParent();
	}

	inline TangibleObject* get() {

		return cast<TangibleObject*>( contents.get());
	}

	inline bool isComplete() {
		return (contents->getQuantity() == requiredQuantity);
	}

	inline bool hasItem() {
		return contents != NULL;
	}

	inline uint64 getObjectID() {
		if(contents == NULL)
			return 0;
		else
			return contents->getObjectID();
	}

	inline bool returnObjectToParent() {

		if(contents == NULL || previousParent == NULL || contents->getQuantity() > requiredQuantity)
			return false;

		if(contents->getParent() != NULL) {
			//contents->getParent()->removeObject(contents, true);
			contents->destroyObjectFromWorld(true);
		}

		// Check inventory for resource and add if existing
		for (int i = 0; i < previousParent->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object =
					previousParent->getContainerObject(i);

			if (object->isResourceContainer()) {
				ManagedReference<ResourceContainer*> resource = cast<ResourceContainer*>( object.get());

				if (resource->getSpawnName() == contents->getSpawnName()) {
					int newStackSize = resource->getQuantity() + contents->getQuantity();

					if(newStackSize <= ResourceContainer::MAXSIZE) {
						resource->setQuantity(newStackSize);
						contents = NULL;
						return true;
					} else {
						resource->setQuantity(ResourceContainer::MAXSIZE);
						contents->setQuantity(newStackSize - ResourceContainer::MAXSIZE);
					}

				}
			}
		}

		previousParent->transferObject(contents, -1, true);
		contents = NULL;
		return true;
	}

	void print() {
		if (contents == NULL) {

			System::out << "Slot is EMPTY" << endl;

		} else {

			System::out << "Name: "
					<< contents->getCustomObjectName().toString() << endl;
			System::out << "Quantity: " << contents->getQuantity() << endl;
		}
	}
};
#endif /*RESOURCESLOT_H_*/
