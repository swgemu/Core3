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

	ManagedReference<TangibleObject* > contents;

public:
	ComponentSlot(SceneObject* manu, String t, int quant, bool ident, bool option, int type) : IngredientSlot(t, quant) {

		craftingTool = manu;
		slottype = type;
		contents = NULL;
		serial = "";
		requiresIdentical = ident;
		optional = option;

		setLoggingName("ComponentSlot");

	}

	~ComponentSlot() {

		cleanup();
	}

	inline void cleanup() {

		contents = NULL;
	}

	inline int getQuantity() {

		if (contents != NULL)
			return contents->getUseCount();
		else
			return 0;
	}

	inline bool add(PlayerCreature* player, TangibleObject* incomingTano) {

		int itemsInSlot = getQuantity();

		if(requiresIdentical && serial != "" && itemsInSlot > 0) {
			if(incomingTano->getCraftersSerial() != contents->getCraftersSerial())
				return false;
		}

		int needs = requiredQuantity - itemsInSlot;

		previousParent = incomingTano->getParent();

		if(incomingTano->isFactoryCrate()) {

			FactoryCrate* crate = (FactoryCrate*) incomingTano;

			if(incomingTano->getUseCount() >= needs)
				incomingTano = crate->extractObject(needs);
			else
				incomingTano = crate->extractObject(incomingTano->getUseCount());
		}

		if(serial = "")
			serial = incomingTano->getCraftersSerial();

		/// Must be a component to proceed
		if (incomingTano->isComponent() && itemsInSlot < requiredQuantity) {

			ObjectManager* objectManager = ObjectManager::instance();

			if (contents == NULL) {

				if (incomingTano->getUseCount() <= needs) {

					contents = incomingTano;

					if(contents->getParent() != NULL)
						contents->getParent()->removeObject(contents, true);
					craftingTool->addObject(contents, -1, false);

					previousParent->removeObject(incomingTano, true);

				} else {

					int newCount = incomingTano->getUseCount() - needs;
					incomingTano->setUseCount(newCount, true);

					TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(incomingTano);
					dtano3->setQuantity(newCount);
					dtano3->close();
					incomingTano->getParent()->broadcastMessage(dtano3, true);

					contents = (TangibleObject*) objectManager->cloneObject(incomingTano);

					contents->setParent(NULL);
					craftingTool->addObject(contents, -1, false);

					contents->setUseCount(needs, false);
				}

				contents->sendTo(player, true);
				contents->sendAttributeListTo(player);

			} else {

				if (incomingTano->getUseCount() <= needs) {

					incomingTano->setUseCount(incomingTano->getUseCount() - needs, true);
					contents->setUseCount(contents->getUseCount() + needs, true);

				} else {

					contents->setUseCount(contents->getUseCount() + incomingTano->getUseCount(), true);
					previousParent->removeObject(incomingTano, true);
				}
			}

			return true;
		}

		return false;
	}

	inline bool remove(PlayerCreature* player) {

		return returnObjectToParent();
	}

	inline bool returnObjectToParent() {

		if(contents == NULL || previousParent == NULL)
			return false;

		if(contents->getParent() != NULL)
			contents->getParent()->removeObject(contents, true);

		previousParent->addObject(contents, -1, true);

		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(contents);
		dtano3->setQuantity(contents->getUseCount());
		dtano3->close();
		previousParent->broadcastMessage(dtano3, true);

		contents = NULL;
		return true;
	}

	inline TangibleObject* get() {

		return (TangibleObject*) contents;
	}

	inline bool isComplete() {
		return (contents->getUseCount() == requiredQuantity);
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

	void toString() {
		if (contents == NULL) {

			System::out << "Slot is EMPTY" << endl;

		} else {

			System::out << "Name: " << contents->getCustomObjectName().toString() << endl;
			System::out << "Quantity: " << contents->getUseCount() << endl;
		}
	}
};
#endif /*COMPONENTSLOT_H_*/
