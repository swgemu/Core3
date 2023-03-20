/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef COMPONENTSLOT_H_
#define COMPONENTSLOT_H_

#include "IngredientSlot.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"

// #define DEBUG_COMPONENT_SLOT

class ComponentSlot: public IngredientSlot {
	/// Indexed by <object, parent>
	Vector<ManagedReference<TangibleObject*> > contents;

public:
	ComponentSlot() : IngredientSlot() {

		clientSlotType = 2;
		setLoggingName("ComponentSlot");
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
		FactoryCrate* crate = nullptr;

#ifdef DEBUG_COMPONENT_SLOT
		info(true) << "add component with required quantity: " << requiredQuantity << " and current quantity: " << currentQuantity << " Content Type: " << contentType;
#endif // DEBUG_COMPONENT_SLOT

		/// If Full, don't add
		if (currentQuantity >= requiredQuantity)
			return false;

		/// Get template
		Reference<SharedObjectTemplate*> baseTemplate = incomingTano->getObjectTemplate();

		/// Get prototype's template for check
		if (incomingTano->isFactoryCrate()) {
			crate = cast<FactoryCrate*>(incomingTano.get());

			TangibleObject* prototype = crate->getPrototype();

			if (prototype == nullptr) {
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
			TangibleObject* tano = contents.elementAt(0);

			if (tano == nullptr) {
				error("Null items in contents when checking serial number");
				return false;
			}

			String tanoSerial = tano->getSerialNumber();

			if (crate != nullptr && crate->getPrototype()->getSerialNumber() != tanoSerial) {
				return false;
			} else if (incomingTano->getSerialNumber() != tanoSerial) {
				return false;
			}
		}

		/// Total needed to fill slot
		int totalNeeded = requiredQuantity - currentQuantity;
		Vector<ManagedReference<TangibleObject*> > itemsForSlot;

		/// Extract tano from crate and set it to the incoming object
		if (crate != nullptr) {
			// calculate total available. This will handle items like grenades that have a use count. Some items have 0 use count, so default to 1.
			int prototypeUses = crate->getPrototypeUseCount();

			if (prototypeUses < 1)
				prototypeUses = 1;

			int extractionAmount = ceil(((float)totalNeeded / prototypeUses));
			int crateSize = crate->getUseCount();

			if (extractionAmount > crateSize)
				extractionAmount = crateSize;

#ifdef DEBUG_COMPONENT_SLOT
			int amountAvailable = crate->getUseCount() * prototypeUses;

			info(true) << "Factory Crate Gross Total available = " << amountAvailable << " Amount needed from crate = " << extractionAmount << " Crate Size = " << crateSize;
#endif // DEBUG_COMPONENT_SLOT

			// Extract the max amount needed from the crate to fulfill the component slot.
			for (int i = 0; i < extractionAmount; i++) {
				ManagedReference<TangibleObject*> extractedProto = crate->extractObject();

#ifdef DEBUG_COMPONENT_SLOT
				info(true) << "Extracted prototype for itemsForSlot #" << i;
#endif // DEBUG_COMPONENT_SLOT

				if (extractedProto == nullptr) {
#ifdef DEBUG_COMPONENT_SLOT
					info(true) << "Prototype #" << i << " is a nullptr!";
#endif // DEBUG_COMPONENT_SLOT
					continue;
				}

				itemsForSlot.add(extractedProto.get());
			}
		// Single item for slot
		} else if (incomingTano != nullptr) {
			itemsForSlot.add(incomingTano);
		}

		if (itemsForSlot.size() <= 0) {
			error() << "No components added to ingredient slot. itemsToAdd.size() <= 0";
			return false;
		}

		ObjectManager* objectManager = ObjectManager::instance();

#ifdef DEBUG_COMPONENT_SLOT
		info(true) << "Items Vector Size = " << itemsForSlot.size();
#endif // DEBUG_COMPONENT_SLOT

		// Place items in component slot
		while (itemsForSlot.size() > 0 && objectManager != nullptr) {
			ManagedReference<TangibleObject*> component = itemsForSlot.remove(0);

			if (component == nullptr)
				continue;

			Locker compLock(component);

			// Check for ADK's again, just in case
			if (component->hasAntiDecayKit()) {
				component->removeAntiDecayKit();
			}

#ifdef DEBUG_COMPONENT_SLOT
			info(true) << "Items for slot item " << component->getDisplayedName() << " Use Count: " << component->getUseCount();
#endif // DEBUG_COMPONENT_SLOT

			// Account for items that have multiple uses -- Example: grenades. Always leave 1 use, for the original component
			if (component->getUseCount() > 1) {
				int addUses = ((totalNeeded - component->getUseCount()) > 0 ? component->getUseCount() : totalNeeded);

#ifdef DEBUG_COMPONENT_SLOT
				info(true) << "Coponent use is greater than 1. Adding uses: " << addUses;
#endif // DEBUG_COMPONENT_SLOT

				for (int i = 0; i < addUses; i++) {
					ManagedReference<TangibleObject*> compClone = cast<TangibleObject*>(objectManager->cloneObject(component));

					if (compClone == nullptr)
						continue;

					Locker cloneLock(compClone);

					compClone->setUseCount(1, false);

					if (compClone->hasAntiDecayKit()) {
						compClone->removeAntiDecayKit();
					}

					if (satchel->transferObject(compClone, -1, true)) {
						// Required so component shows in slot
						compClone->sendTo(player, true);
						compClone->sendAttributeListTo(player);

						contents.add(compClone);
						totalNeeded--;

#ifdef DEBUG_COMPONENT_SLOT
						info(true) << "New Component Clone created - added to slot";
#endif // DEBUG_COMPONENT_SLOT
					}

					component->decreaseUseCount();
#ifdef DEBUG_COMPONENT_SLOT
					info(true) << "Component Uses: " << component->getUseCount();
#endif // DEBUG_COMPONENT_SLOT
				}

				if (component->getUseCount() > 0) {
					component->sendTo(player, true);
				}
			} else {
				ManagedReference<TangibleObject*> itemToUse = cast<TangibleObject*>(objectManager->cloneObject(component));

				if (itemToUse != nullptr) {
					Locker lock(itemToUse, component);

					if (itemToUse->hasAntiDecayKit()) {
						itemToUse->removeAntiDecayKit();
					}

					itemToUse->setParent(nullptr);
					itemToUse->setUseCount(0, false);

					satchel->transferObject(itemToUse, -1, true);
					contents.add(itemToUse);

					// Required so component shows in slot
					itemToUse->sendTo(player, true);
					itemToUse->sendAttributeListTo(player);

					component->destroyObjectFromWorld(true);
					component->destroyObjectFromDatabase(true);
				}
#ifdef DEBUG_COMPONENT_SLOT
				info(true) << "Component added to slot";
#endif // DEBUG_COMPONENT_SLOT
			}
		}

		return true;
	}

	bool returnToParents(CreatureObject* player) {
		for(int i = 0; i < contents.size(); ++i) {
			TangibleObject* object = contents.get(i);

			if(object == nullptr) {
				warning("Can't return object, object is null");
				continue;
			}

			SceneObject* parent = player->getSlottedObject("inventory");

			if(parent == nullptr) {
				warning("Can't return object, inventory is null");
				continue;
			}

			parent->transferObject(object, -1, true, true);
			object->sendTo(player, true);
		}

		contents.removeAll();

		return true;
	}


	int getSlotQuantity() {
		int quantity = 0;
		for(int i = 0; i < contents.size(); ++i) {
			TangibleObject* tano =  contents.elementAt(i);
			if(tano != nullptr) {
				uint32 useCount = tano->getUseCount();

				// Objects with 0 uses that have not been destroyed are still valid and "usable" one time only
				if(useCount == 0)
					useCount++;

				quantity += useCount;
			}

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
			return nullptr;

		return contents.elementAt(0);
	}

	SceneObject* getFactoryIngredient() {
		return getPrototype();
	}

	bool isComponentSlot() {
		return true;
	}

	Vector<uint64> getOIDVector() {
		Vector<uint64> oids;
		for (int i = 0; i < getSlotQuantity(); ++i) {
			uint64 oid = contents.get(i)->getObjectID();

			if (!oids.contains(oid))
				oids.add(oid);
		}

		return oids;
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
