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

#ifndef COMPONENTSLOT_H_
#define COMPONENTSLOT_H_

#include "IngredientSlot.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"

class ComponentSlot: public IngredientSlot {

	/// Indexed by <object, parent>
	VectorMap<ManagedReference<TangibleObject*>, ManagedReference<SceneObject*> > contents;


public:
	ComponentSlot() : IngredientSlot() {

		clientSlotType = 2;
	}

	ComponentSlot(const ComponentSlot& slot) : Object(), IngredientSlot(slot) {
		contents = slot.contents;

		setLoggingName("ComponentSlot");
		setLogging(false);
	}

	~ComponentSlot() {

	}

	Object* clone() {
		return new ComponentSlot(*this);
	}

	bool add(CreatureObject* player, SceneObject* satchel, ManagedReference<TangibleObject*> incomingTano) {

		int currentQuantity = getSlotQuantity();
		FactoryCrate* crate = NULL;

		/// If Full, don't add
		if (currentQuantity >= requiredQuantity)
			return false;

		/// Get template
		Reference<SharedObjectTemplate*> baseTemplate = incomingTano->getObjectTemplate();

		/// Get prototype's template for check
		if (incomingTano->isFactoryCrate()) {

			crate = cast<FactoryCrate*>(incomingTano.get());

			TangibleObject* prototype = crate->getPrototype();

			if (prototype == NULL) {
				error("Factory crate doesn't contain a prototype");
				return false;
			}

			/// Check if prototype is correct type
			baseTemplate = prototype->getObjectTemplate();
		}

		/// Check types
		if (!baseTemplate->isDerivedFrom(contentType))
			return false;

		// Serial Number check
		if (requiresIdentical() && !contents.isEmpty()) {
			TangibleObject* tano = contents.elementAt(0).getKey();

			if(tano == NULL) {
				error("Null items in contents when checking serial number");
				return false;
			}

			if (crate != NULL && crate->getPrototype()->getSerialNumber() != tano->getSerialNumber()) {
				return false;
			} else {

				if (incomingTano->getSerialNumber() != tano->getSerialNumber())
					return false;
			}
		}

		/// How much do we need
		int slotNeeds = requiredQuantity - currentQuantity;

		/// Get parent
		ManagedReference<SceneObject*> parent = incomingTano->getParent();
		if(parent == NULL) {
			error("Object inserted didn't have a parent");
			return false;
		}
		/// Extract tano from crate and set it to the incoming object
		if (crate != NULL) {

			if (crate->getUseCount() >= slotNeeds)
				incomingTano = crate->extractObject(slotNeeds);
			else
				incomingTano = crate->extractObject(crate->getUseCount());
		}

		if(incomingTano == NULL) {
			error("Incoming object is NULL");
			return false;
		}

		incomingTano->sendAttributeListTo(player);

		ObjectManager* objectManager = ObjectManager::instance();
		ManagedReference<TangibleObject*> itemToUse = NULL;

		if(incomingTano->getUseCount() > slotNeeds) {

			int newCount = incomingTano->getUseCount() - slotNeeds;
			incomingTano->setUseCount(newCount, true);

			itemToUse = cast<TangibleObject*>( objectManager->cloneObject(incomingTano));
			itemToUse->setUseCount(slotNeeds, false);
			itemToUse->setParent(NULL);
			itemToUse->sendAttributeListTo(player);

		} else {

			itemToUse = incomingTano;
		}

		Vector<ManagedReference<TangibleObject*> > itemsToAdd;

		itemsToAdd.add(itemToUse);
		while(itemToUse->getUseCount() > 1) {

			ManagedReference<TangibleObject*> newTano = cast<TangibleObject*>( objectManager->cloneObject(itemToUse));
			newTano->setParent(NULL);
			newTano->setUseCount(1, false);
			itemsToAdd.add(newTano);

			itemToUse->decreaseUseCount();
		}

		while(itemsToAdd.size() > 0) {
			ManagedReference<TangibleObject*> tano = itemsToAdd.remove(0);
			if(!satchel->transferObject(tano, -1, true)) {
				error("cant transfer crafting component Has Items: " + String::valueOf(satchel->getContainerObjectsSize()));
				return false;
			}
			VectorMapEntry<ManagedReference<TangibleObject*>, ManagedReference<SceneObject*> > entry(tano, parent);

			if(!contents.isEmpty()) {
				parent->broadcastDestroy(tano, true);
			}

			contents.add(entry);
		}

		return true;
	}

	bool returnToParents(CreatureObject* player) {

		for(int i = 0; i < contents.size(); ++i) {
			TangibleObject* object = contents.elementAt(i).getKey();
			SceneObject* parent = contents.elementAt(i).getValue();

			if(parent == NULL) {
				warning("Can't return object, parent is null");
				continue;
			}

			if(object == NULL) {
				warning("Can't return object, object is null");
				continue;
			}

			parent->transferObject(object, -1, true);
			parent->broadcastObject(object, true);
		}

		contents.removeAll();

		return true;
	}


	int getSlotQuantity() {
		int quantity = 0;
		for(int i = 0; i < contents.size(); ++i) {
			TangibleObject* tano =  contents.elementAt(i).getKey();
			if(tano != NULL)
				quantity += tano->getUseCount();
		}
		return quantity;
	}

	bool isFull() {
		return requiredQuantity == getSlotQuantity();
	}

	bool isEmpty() {
		return getSlotQuantity() == 0;
	}

	TangibleObject* getPrototype() {

		if(contents.isEmpty())
			return NULL;

		return contents.elementAt(0).getKey();
	}

	SceneObject* getFactoryIngredient() {
		return getPrototype();
	}

	bool isComponentSlot() {
		return true;
	}

	Vector<uint64> getOIDVector() {
		Vector<uint64> oid;
		for(int i = 0; i < getSlotQuantity(); ++i) {
			oid.add(getPrototype()->getObjectID());
		}
		return oid;
	}

	// We add 1 for each item in the slot
	// NOT the quantity of each item, it's a vector
	// of 1's that equals how many items are in the slot
	Vector<int> getQuantityVector() {
		Vector<int> quant;
		for(int i = 0; i < getSlotQuantity(); ++i) {
			quant.add(1);
		}
		return quant;
	}
};
#endif /*COMPONENTSLOT_H_*/
