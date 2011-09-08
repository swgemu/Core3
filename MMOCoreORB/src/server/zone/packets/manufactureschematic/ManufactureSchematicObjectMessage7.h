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

#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE7_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE7_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
//#include "server/zone/objects/draftschematic/DraftSchematic.h"

class ManufactureSchematicObjectMessage7: public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage7(ManufactureSchematic* schematic) :
		BaseLineMessage(schematic->getObjectID(), 0x4D53434F, 7, 0x15) {

		DraftSchematic* draftSchematic = schematic->getDraftSchematic();
		CraftingValues* craftingValues = schematic->getCraftingValues();

		int draftSlotCount = draftSchematic->getDraftSlotCount();
		int updateCount = draftSlotCount;

		insertSlotNames(draftSchematic, draftSlotCount, updateCount);
		insertSlotTypes(draftSchematic, draftSlotCount, updateCount);
		insertSlotObjectId(draftSlotCount, updateCount);
		insertSlotMaxQuantity(draftSlotCount, updateCount);
		insertSlotQuantity(draftSlotCount, updateCount);
		insertSlotClean(draftSlotCount, updateCount);
		insertSlotIndex(draftSlotCount, updateCount);

		/// Ingredient Counter
		insertByte(schematic->getIngredientCounter());

		/// Experimenting names
		int titleCount =
				craftingValues->getVisibleExperimentalPropertyTitleSize();

		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++) {
			String title = craftingValues->getVisibleExperimentalPropertyTitle(
					i);

			insertAscii("crafting");
			insertInt(0);
			insertAscii(title);
		}

		/// Experimenting values
		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++)
			insertFloat(0);

		/// Useless values - always 0 Experiment offset
		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++)
			insertInt(0);

		/// always 1 Max experimentation value
		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++)
			insertFloat(1);

		// Customization name
		insertInt(0);
		insertInt(0);

		/// Pallete List
		insertInt(0);
		insertInt(0);

		/// Pallete Start Index
		insertInt(0);
		insertInt(0);

		/// Pallete End index
		insertInt(0);
		insertInt(0);

		/// Pallete List
		insertInt(0);
		insertInt(0);

		/// Pallete List
		insertInt(0);
		insertInt(0);

		insertInt(0);

		/// Customization Counter
		insertByte(0);

		//ready
		insertByte(1);

		setSize();
	}

	void insertSlotNames(DraftSchematic* draftSchematic, int draftSlotCount,
			int updateCount) {

		insertInt(draftSlotCount);
		insertInt(updateCount);

		for (int i = 0; i < draftSlotCount; i++) {
			DraftSlot* slot = draftSchematic->getDraftSlot(i);
			if (slot != NULL) {
				insertAscii(slot->getStringId().getFile());
				insertInt(0);
				insertAscii(slot->getStringId().getStringID());
			}
		}
	}

	void insertSlotTypes(DraftSchematic* draftSchematic, int draftSlotCount,
			int updateCount) {

		// Send slot type
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++) {
			DraftSlot* slot = draftSchematic->getDraftSlot(i);
			if (slot != NULL)
				insertInt(slot->getSlotType());
		}
	}

	void insertSlotObjectId(int draftSlotCount, int updateCount) {
		// Send Resource ID per slot - initially empty
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++)
			insertInt(0);
	}

	void insertSlotMaxQuantity(int draftSlotCount, int updateCount) {
		// Send Resource quantity per slot - initially empty
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++)
			insertInt(0);
	}

	void insertSlotQuantity(int draftSlotCount, int updateCount) {
		// SlotQuality
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++)
			insertInt(0);
	}

	void insertSlotClean(int draftSlotCount, int updateCount) {
		// Unused
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++)
			insertInt(0);
	}

	void insertSlotIndex(int draftSlotCount, int updateCount) {
		// Index
		insertInt(draftSlotCount);
		insertInt(updateCount);
		for (int i = 0; i < draftSlotCount; i++)
			insertInt(i);
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
