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

	Vector<ManagedReference<TangibleObject*> > contents;
	Vector<ManagedReference<SceneObject*> > contentsPreviousParent;

public:
	ComponentSlot(SceneObject* manu, String t, int quant, bool ident,
			bool option, int type) :
		IngredientSlot(t, quant) {

		craftingTool = manu;
		slottype = type;
		serial = "";
		requiresIdentical = ident;
		optional = option;

		setLoggingName("ComponentSlot");
		setLogging(false);

	}

	ComponentSlot(const ComponentSlot& slot) :
		Object(), IngredientSlot(slot) {
		contents = slot.contents;
		contentsPreviousParent = slot.contentsPreviousParent;

		setLoggingName("ComponentSlot");
		setLogging(false);
	}

	~ComponentSlot() {

		cleanup();
	}

	Object* clone() {
		return new ComponentSlot(*this);
	}

	inline void cleanup() {

		contents.removeAll();
		contentsPreviousParent.removeAll();
	}

	inline int getQuantity() {

		int count = 0;

		for (int i = 0; i < contents.size(); ++i) {
			TangibleObject* object = contents.get(i);

			if (object != NULL) {
				count += object->getUseCount();
			}
		}

		return count;
	}

	bool add(CreatureObject* player, TangibleObject* incomingTano) {

		int itemsInSlot = getQuantity();

		if (itemsInSlot >= requiredQuantity)
			return false;

		if (requiresIdentical && serial != "" && itemsInSlot > 0) {
			if (incomingTano->getCraftersSerial() != serial)
				return false;
		}

		int needs = requiredQuantity - itemsInSlot;
		SceneObject* incomingTanoParent = incomingTano->getParent();

		Reference<SharedObjectTemplate*> baseTemplate =
				incomingTano->getObjectTemplate();

		if (incomingTano->isFactoryCrate()) {

			FactoryCrate* crate = cast<FactoryCrate*>( incomingTano);

			TangibleObject* prototype = crate->getPrototype();

			if (prototype == NULL)
				return false;

			/// Check if prototype is correct type
			baseTemplate = prototype->getObjectTemplate();
		}

		if (!baseTemplate->isDerivedFrom(type))
			return false;

		if (incomingTano->isFactoryCrate()) {

			FactoryCrate* crate = cast<FactoryCrate*>( incomingTano);

			if (incomingTano->getUseCount() >= needs)
				incomingTano = crate->extractObject(needs);
			else
				incomingTano = crate->extractObject(incomingTano->getUseCount());
		}

		if(incomingTano == NULL)
			return false;

		ObjectManager* objectManager = ObjectManager::instance();

		if (contents.isEmpty()) {

			serial = incomingTano->getCraftersSerial();

			if (incomingTano->getUseCount() <= needs) {

				contents.add(incomingTano);
				contentsPreviousParent.add(incomingTanoParent);

				if (incomingTano->getParent() != NULL)
					incomingTano->getParent()->removeObject(incomingTano, true);

				craftingTool->addObject(incomingTano, -1, false);

				incomingTano->sendTo(player, true);
				incomingTano->sendAttributeListTo(player);

			} else {

				int newCount = incomingTano->getUseCount() - needs;
				incomingTano->setUseCount(newCount, true);

				TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(incomingTano);
				dtano3->setQuantity(newCount);
				dtano3->close();
				incomingTano->getParent()->broadcastMessage(dtano3, true);

				TangibleObject* newTano = cast<TangibleObject*>( objectManager->cloneObject(incomingTano));
				newTano->setUseCount(needs, false);
				newTano->setParent(NULL);

				if (contents.add(newTano)) {
					contentsPreviousParent.add(incomingTanoParent);
					craftingTool->addObject(newTano, -1, false);

					newTano->sendTo(player, true);
					newTano->sendAttributeListTo(player);
				}
			}

		} else {

			if (incomingTano->getUseCount() > needs) {

				incomingTano->setUseCount(incomingTano->getUseCount() - needs, true);

				TangibleObject* newTano = cast<TangibleObject*>( objectManager->cloneObject(incomingTano));
				newTano->setUseCount(needs, true);
				newTano->setParent(NULL);

				if(contents.add(newTano)) {
					contentsPreviousParent.add(incomingTanoParent);
					craftingTool->addObject(newTano, -1, false);
				}

			} else {

				if(contents.add(incomingTano)) {
					contentsPreviousParent.add(incomingTanoParent);

					if (incomingTano->getParent() != NULL)
						incomingTano->getParent()->removeObject(incomingTano, true);

					craftingTool->addObject(incomingTano, -1, false);
				}
			}
		}

		return true;
	}

	inline bool remove(CreatureObject* player) {

		return returnObjectToParent();
	}

	inline bool returnObjectToParent() {

		if (contents.size() < 1 || contentsPreviousParent.size() < 1
				|| getQuantity() > requiredQuantity)
			return false;

		while (contents.size() > 0) {

			ManagedReference<TangibleObject*> item = contents.remove(0);
			ManagedReference<SceneObject*> objectsOldParent =
					contentsPreviousParent.remove(0);

			if (item == NULL)
				continue;

			if (item->getParent() != NULL)
				item->getParent()->removeObject(item, true);

			Reference<SharedObjectTemplate*> baseTemplate =
					item->getObjectTemplate();
			if (!baseTemplate->isDerivedFrom(type))
				continue;

			TangibleObjectDeltaMessage3* dtano3 =
					new TangibleObjectDeltaMessage3(item);
			dtano3->setQuantity(item->getUseCount());
			dtano3->close();

			if (objectsOldParent != NULL) {
				objectsOldParent->addObject(item, -1, true);
				objectsOldParent->broadcastMessage(dtano3, true);
			} else {
				item->broadcastMessage(dtano3, true);
			}
		}

		return true;
	}

	/*inline TangibleObject* get() {

	 return cast<TangibleObject*>( contents);
	 }*/

	inline bool isComplete() {
		return (getQuantity() == requiredQuantity);
	}

	inline bool hasItem() {
		return contents.size() > 0;
	}

	inline TangibleObject* get() {
		if (contents.size() < 1)
			return NULL;
		else
			return contents.get(0);
	}

	inline uint64 getObjectID() {
		if (contents.size() < 1)
			return 0;
		else
			return contents.get(0)->getObjectID();
	}

	String toString() {
		StringBuffer str;

		if (contents.size() == 0) {

			str << "Slot is EMPTY" << endl;
		} else {
			for (int i = 0; i < contents.size(); ++i) {
				str << "Name: "
						<< contents.get(i)->getCustomObjectName().toString()
						<< endl;
				str << "Quantity: " << contents.get(i)->getUseCount() << endl;
			}
		}

		return str.toString();
	}
};
#endif /*COMPONENTSLOT_H_*/
