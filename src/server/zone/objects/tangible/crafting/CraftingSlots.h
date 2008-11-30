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

#ifndef CRAFTINGSLOTS_H_
#define CRAFTINGSLOTS_H_

#include "craftingslots/CraftingSlot.h"
#include "craftingslots/ResourceSlot.h"
#include "craftingslots/IdenticalSlot.h"
#include "craftingslots/MixedSlot.h"
#include "craftingslots/OptionalIdenticalSlot.h"
#include "craftingslots/OptionalMixedSlot.h"

#include "../../draftschematic/DraftSchematicIngredient.h"

class CraftingSlots {

	Vector<CraftingSlot*> slots;

public:
	CraftingSlots() {

	}
	~CraftingSlots() {

		cleanup();
	}

	inline void init(DraftSchematic* draftSchematic) {

		cleanup();

		CraftingSlot* slot = NULL;
		DraftSchematicIngredient* ingredient = NULL;

		int size = draftSchematic->getIngredientListSize();

		int slotsize;

		String name;

		for (int i = 0; i < size; ++i) {

			ingredient = draftSchematic->getIngredient(i);

			name = ingredient->getResourceType();

			switch (ingredient->getSlotType()) {
			case CraftingSlot::RESOURCESLOT:
				slot = new ResourceSlot();
				break;
			case CraftingSlot::IDENTICALSLOT:
				slot = new IdenticalSlot();
				break;
			case CraftingSlot::MIXEDSLOT:
				slot = new MixedSlot();
				break;
			case CraftingSlot::OPTIONALIDENTICALSLOT:
				slot = new OptionalIdenticalSlot();
				break;
			case CraftingSlot::OPTIONALMIXEDSLOT:
				slot = new OptionalMixedSlot();
				break;
			}

			slots.add(slot);
		}
	}

	inline void cleanup() {

		CraftingSlot* slot = NULL;

		while (slots.size() > 0) {

			slot = slots.get(0);
			slots.remove(0);
			if (slot != NULL) {
				slot->cleanup();
				delete slot;
			}
		}
	}

	inline int size() {

		return slots.size();

	}

	inline bool putIngredientInSlot(int slot, TangibleObject* tano) {

		CraftingSlot* theslot = slots.get(slot);

		if (theslot != NULL)
			return theslot->add(tano);

		return false;
	}

	inline void clearIngredientInSlot(int slot) {

		CraftingSlot* theslot = slots.get(slot);

		if (theslot != NULL)
			theslot->clear();
	}

	inline TangibleObject* getIngredientInSlot(int slot) {

		CraftingSlot* theslot = slots.get(slot);

		if (theslot != NULL)
			return theslot->get();
		else
			return NULL;
	}

	inline int getIngredientCount(int slot) {

		CraftingSlot* theslot = slots.get(slot);

		if (theslot != NULL)
			return theslot->size();
		else
			return 0;
	}

	void toString() {

		CraftingSlot* tano;
		for (int i = 0; i < slots.size(); ++i) {

			tano = slots.get(i);

			System::out << "Slot " << i << " *******************" << endl;

			if (tano == NULL) {

				System::out << "Slot is NULL" << endl;

			} else {

				tano->toString();

			}
		}
	}
};
#endif /*CRAFTINGSLOTS_H_*/
