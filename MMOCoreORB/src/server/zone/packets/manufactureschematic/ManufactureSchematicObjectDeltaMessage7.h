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

#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_

#include "../BaseLineMessage.h"

#include "../../objects/draftschematic/DraftSchematic.h"
#include "../../objects/draftschematic/DraftSchematic.h"

class ManufactureSchematicObjectDeltaMessage7 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage7(uint64 sceneObjSchematic) :
		DeltaMessage(sceneObjSchematic, 0x4D53434F, 7) {
	}

	void fullUpdate(ManufactureSchematic* manufactureSchematic, int slot) {

		int size = manufactureSchematic->getSlotCount();
		Reference<IngredientSlot* > ingredientSlot = manufactureSchematic->getIngredientSlot(slot);

		updateIngredientList(manufactureSchematic);
		updateSlot(size+1, size+1, slot);
		updateResource(size+1, size+1, slot, ingredientSlot);
		updateQuantity(size+1, size+1, slot, ingredientSlot);
		update4(size, size, slot);
		update5(size+1, size+1, slot);
		update6(size, size, slot);
		update7(manufactureSchematic->getIngredientCounter());
		//initializeExperimentalValues(draftSchematic);
		update14();
	}

	void partialUpdate(ManufactureSchematic* manufactureSchematic, int slot, int counter) {

		Reference<IngredientSlot* > ingredientSlot = manufactureSchematic->getIngredientSlot(slot);
		counter += manufactureSchematic->getSlotCount();

		updateSlot(1, counter, slot);
		updateResource(1, counter, slot, ingredientSlot);
		updateQuantity(1, counter, slot, ingredientSlot);
		update5(1, counter, slot);
		update7(manufactureSchematic->getIngredientCounter());
	}

	void removeResource(int slot, int counter, int ingredientCounter){
		startUpdate(1);
		startList(1, counter);
		removeListIntElement(slot, 0);

		startUpdate(2);
		startList(1, counter);
		removeListIntElement(slot, 0);

		startUpdate(3);
		startList(1, counter);
		removeListIntElement(slot, 0);

		startUpdate(5);
		startList(1, counter);
		removeListIntElement(slot, 0xFFFFFFFF);

		update7(ingredientCounter);
	}

	void updateForAssembly(ManufactureSchematic* manufactureSchematic, float failureRate){
		initialAssemblyUpdate(manufactureSchematic);
		update9(manufactureSchematic, true);
		//update0A(manufactureSchematic);
		update0B(manufactureSchematic);
		update0C(manufactureSchematic);
		update12(failureRate);
	}

	void updateCustomizationOptions(ManufactureSchematic* manufactureSchematic, int custpoints){
		update0D(manufactureSchematic);
		update0E(manufactureSchematic);
		update0F(manufactureSchematic);
		update10(manufactureSchematic, custpoints);
		update11();
	}

	void updateIngredientList(ManufactureSchematic* manufactureSchematic) {

		startUpdate(0);

		ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();

		int ingredientListSize = draftSchematic->getDraftSlotCount();

		startList(ingredientListSize, ingredientListSize);

		for (int i = 0; i < ingredientListSize; i++) {
			DraftSlot* draftSlot = draftSchematic->getDraftSlot(i);
			if (draftSlot != NULL) {
				insertByte(1);
				insertShort(i);
				insertAscii(draftSlot->getStringId().getFile());
				insertInt(0);
				insertAscii(draftSlot->getStringId().getStringID());
			} else {
				System::out << "\n\nError DMSCO7: line 65\n";
			}
		}
	}

	void updateSlot(int size, int counter, int slot) {

		startUpdate(1);

		startList(size, counter);

		for (int i = 0; i < size - 1; i++) {
			addListIntElement(i, 0);
		}
		removeListIntElement(slot, 4);
	}

	void updateResource(int size, int counter, int slot, Reference<IngredientSlot* > ingredientSlot) {
		startUpdate(2);

		startList(size, counter);

		for (int i = 0; i < size - 1; i++) {
			addListIntElement(i, 0);
		}

		if(ingredientSlot->isType(IngredientSlot::RESOURCESLOT)) {

			removeListIntElement(slot, 1);
			insertLong(ingredientSlot->getObjectID());

		} else {

			removeListIntElement(slot, ingredientSlot->getQuantity());

			for(int i = 1; i <= ingredientSlot->getQuantity(); ++i) {
				insertLong(ingredientSlot->getObjectID());
			}
		}
	}
	void updateQuantity(int size, int counter, int slot, Reference<IngredientSlot* > ingredientSlot) {

		startUpdate(3);

		startList(size, counter);

		for (int i = 0; i < size-1; i++) {
			addListIntElement(i, 0);
		}

		if(ingredientSlot->isType(IngredientSlot::RESOURCESLOT)) {

			removeListIntElement(slot, 1);
			insertInt(ingredientSlot->getQuantity());

		} else {

			removeListIntElement(slot, ingredientSlot->getQuantity());

			for(int i = 1; i <= ingredientSlot->getQuantity(); ++i) {
				insertInt(1);
			}
		}

		//removeListIntElement(slot, 1);
		//insertInt(quantity);

	}

	void updateQuantity(int quantity) {

		startUpdate(3);
		insertInt(quantity);
	}

	void update4(int size, int counter, int slot) {

		startUpdate(4);

		startList(size, counter);

		for (int i = 0; i < size; i++) {
			if (i == 0){
				addListIntElement(i, 0);
			} else {
				addListFloatElement(i, 1.0f);
			}
		}
	}

	void update5(int size, int counter, int slot) {
		startUpdate(5);

		startList(size, counter);

		for (int i = 0; i < size-1; i++) {
			addListIntElement(i, 0xFFFFFFFF);
		}
		removeListIntElement(slot, 0);
	}

	void update6(int size, int counter, int slot) {

		startUpdate(6);

		startList(size*2, counter*2);

		for (int i = 0; i < size; i++) {
			addListIntElement(i, 0xFFFFFFFF);
			removeListIntElement(i, i);
		}
	}
	void update7(int counter) {

		startUpdate(7);
		insertByte(counter);
	}

	// update 8
	void initialAssemblyUpdate(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(8);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();
		int counter = manufactureSchematic->getExperimentingCounter();

		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++) {
			String title = craftingValues->getVisibleExperimentalPropertyTitle(i);

			insertByte(1);
			insertShort(i);
			insertAscii("crafting");  // I think this is always "crafting"
			insertInt(0);
			insertAscii(title);
		}

		// Initialize update 9************
		startUpdate(9);

		startList(titleCount, titleCount);  // titleCount, counter

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0); //0
		}
		//!*********************************
		// Initialize update 0A************
		startUpdate(0x0A);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0B************
		startUpdate(0x0B);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0C************
		startUpdate(0x0C);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!**********************************

	}

	// This sends the experimental values shown in the Screen after hitting assemble
	void update9(ManufactureSchematic* manufactureSchematic, bool initial) {

		int count;

		startUpdate(9);

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		if (initial) {
			manufactureSchematic->setExperimentingCounter(titleCount * 2);
			manufactureSchematic->setExperimentingCounter(titleCount * 3);
		}

//System::out << "Visible: " << titleCount << "  Count: " << count << endl;

		count = manufactureSchematic->getExperimentingCounterPrevious();

		startList(titleCount, count);

		for (int i = 0; i < titleCount; i++) {

			String title = craftingValues->getVisibleExperimentalPropertyTitle(i);

			float value = craftingValues->getCurrentPercentageAverage(title);

			if(value > 0 && value < .01)
				value = .01f;

			removeListFloatElement(i, value);

		}
	}

	void update0A(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0A);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// I think this is usually 1.0
	void update0B(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0B);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// This is the MAX experimental value.  How many bars
	void update0C(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0C);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		float value;

		for (int i = 0; i < titleCount; i++) {

			value = craftingValues->getMaxPercentageAverage(i);

			removeListFloatElement(i, value);

		}
	}

	void update0D(ManufactureSchematic* manufactureSchematic) {

		ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
		if(draftSchematic == NULL)
			return;

		Vector<String>* customizationStringNames = draftSchematic->getCustomizationStringNames();

		startUpdate(0x0D);

		startList(customizationStringNames->size(), customizationStringNames->size());

		for (int i = 0; i < customizationStringNames->size(); ++i) {

			insertByte(0x01);
			insertShort(i);
			insertAscii(customizationStringNames->get(i));
		}
	}

	// Starting COlor chooser position
	void update0E(ManufactureSchematic* manufactureSchematic) {

		ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
		if(draftSchematic == NULL)
			return;

		Vector<byte>* customizationDefaultValues = draftSchematic->getCustomizationDefaultValues();

		startUpdate(0x0E);

		startList(customizationDefaultValues->size(), customizationDefaultValues->size());

		for (int i = 0; i < customizationDefaultValues->size(); ++i) {

			insertByte(0x01);
			insertShort(i);
			insertInt(customizationDefaultValues->get(i));
		}
	}

	void update0F(ManufactureSchematic* manufactureSchematic) {

		ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
		if(draftSchematic == NULL)
			return;

		Vector<byte>* customizationOptions = draftSchematic->getCustomizationOptions();

		startUpdate(0x0F);

		startList(customizationOptions->size(), customizationOptions->size());

		for (int i = 0; i < customizationOptions->size(); ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(0);
		}
	}

	// Number of palette colors
	void update10(ManufactureSchematic* manufactureSchematic, int custpoints) {

		ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
		if(draftSchematic == NULL)
			return;

		Vector<byte>* customizationOptions = draftSchematic->getCustomizationOptions();

		startUpdate(0x10);

		startList(customizationOptions->size(), customizationOptions->size());

		for (int i = 0; i < customizationOptions->size(); ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(custpoints);
		}
	}

	void update11() {

		startUpdate(0x11);
		insertByte(1);
	}

	void update12(float failureRate){
		startUpdate(0x12);
		insertFloat(failureRate);
	}

	void update14() {

		startUpdate(0x14);
		insertByte(1);
	}

};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
