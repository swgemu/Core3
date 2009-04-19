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
#include "../../objects/draftschematic/DraftSchematicExpPropGroup.h"
#include "../../objects/draftschematic/DraftSchematicValues.h"

class ManufactureSchematicObjectDeltaMessage7 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage7(uint64 sceneObjSchematic) :
		DeltaMessage(sceneObjSchematic, 0x4D53434F, 7) {
	}

	void fullUpdate(DraftSchematic* draftSchematic, int size, int slot,
			uint64 resourceID, int quantity) {
		updateIngredientList(draftSchematic);
		updateSlot(size+1, size+1, slot);
		updateResource(size+1, size+1, slot, resourceID);
		updateQuantity(size+1, size+1, slot, quantity);
		update4(size, size, slot);
		update5(size+1, size+1, slot);
		update6(size, size, slot);
		update7();
		//initializeExperimentalValues(draftSchematic);
		update14();
	}

	void partialUpdate(int slot, int counter, uint64 resourceID, int quantity) {
		updateSlot(1, counter, slot);
		updateResource(1, counter, slot, resourceID);
		updateQuantity(1, counter, slot, quantity);
		update5(1, counter, slot);
		update7();
	}

	void removeResource(int slot, int counter){
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

		update7();
	}

	void updateForAssembly(DraftSchematic* draftSchematic){
		initializeExperimentalValues(draftSchematic);  // Temp
		update9(draftSchematic, true);
		update0B(draftSchematic);
		update0C(draftSchematic);
		update12(draftSchematic);
	}

	void updateCustomizationOptions(DraftSchematic* draftSchematic, int custpoints){
		update0D(draftSchematic);
		update0E(draftSchematic);
		update0F(draftSchematic);
		update10(draftSchematic, custpoints);
		update11();
	}

	void updateIngredientList(DraftSchematic* draftSchematic) {

		startUpdate(0);

		int ingredientListSize = draftSchematic->getIngredientListSize();

		startList(ingredientListSize, ingredientListSize);

		for (int i = 0; i < ingredientListSize; i++) {
			DraftSchematicIngredient* dsi = draftSchematic->getIngredient(i);
			if (dsi != NULL) {
				insertByte(1);
				insertShort(i);
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
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

	void updateResource(int size, int counter, int slot, uint64 resourceID) {
		startUpdate(2);

		startList(size, counter);

		for (int i = 0; i < size - 1; i++) {
			addListIntElement(i, 0);
		}
		removeListIntElement(slot, 1);
		insertLong(resourceID);

	}
	void updateQuantity(int size, int counter, int slot, int quantity) {

		startUpdate(3);

		startList(size, counter);

		for (int i = 0; i < size-1; i++) {
			addListIntElement(i, 0);
		}
		removeListIntElement(slot, 1);
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
	void update7() {

		startUpdate(7);
		insertByte(16); // No clue, was Decimal 24 for Scatter and 16 for Bofa

	}

	void initializeExperimentalValues(DraftSchematic* draftSchematic) {

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

		startUpdate(8);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();
		int counter = draftSchematic->getExpCounter();

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
		//*********************************
		// Initialize update 0A************
		startUpdate(0x0A);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************
		// Initialize update 0B************
		startUpdate(0x0B);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************
		// Initialize update 0C************
		startUpdate(0x0C);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************

	}

	// This sends the experimental values shown in the Screen after hitting assemble
	void update9(DraftSchematic* draftSchematic, bool initial) {
		startUpdate(9);

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();
		int count, linenum;
		String title, subtitle;
		float value;
		bool hidden;
		VectorMap<int, String> updatedLines;

		for (int i = 0; i < craftingValues->getValuesToSendSize(); ++i) {

			subtitle = craftingValues->getValuesToSend(i);

			title = craftingValues->getExperimentalPropertyTitle(subtitle);

			linenum = craftingValues->getTitleLine(title);

			hidden = craftingValues->isHidden(subtitle);

			if (((!initial && !hidden) || initial) && linenum != -1 && !updatedLines.contains(linenum)
					&& title != "" && title != "null") {
//System::out << "dmsco7 End: " << linenum << " " << title << endl;
				updatedLines.put(linenum, title);
			}
		}

		if (initial) {
			draftSchematic->setExpCounter(updatedLines.size() * 2);
			count = updatedLines.size() * 2;
		} else {
			count = draftSchematic->getExpCounter();
		}

		startList(updatedLines.size(), count);
//System::out << "dmsco7 updateLines: " << updatedLines.size() << " counter " << draftSchematic->getExpCounter() << " props " << craftingValues->getVisibleExperimentalPropertyTitleSize() << " count sent " << count << endl;
		for (int i = 0; i < updatedLines.size(); ++i) {

			linenum = updatedLines.elementAt(i)->getKey();

			value = craftingValues->getCurrentPercentageAverage(updatedLines.elementAt(i)->getValue());

			removeListFloatElement(linenum, value);
//System::out << "dmsco7 End: " << linenum << " " << value << endl;
		}

		updatedLines.removeAll();
	}

	void update0A(DraftSchematic* draftSchematic) {

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

		startUpdate(0x0A);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// I think this is usually 1.0
	void update0B(DraftSchematic* draftSchematic) {

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

		startUpdate(0x0B);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// This is the MAX experimental value.  How many bars
	void update0C(DraftSchematic* draftSchematic) {

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

		startUpdate(0x0C);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		float value;

		for (int i = 0; i < titleCount; i++) {

			value = craftingValues->getMaxPercentageAverage(i);

			removeListFloatElement(i, value);

		}
	}

	void update0D(DraftSchematic* draftSchematic) {

		int count = draftSchematic->getCustomizationOptionCount();

		startUpdate(0x0D);

		startList(count, count);

		for (int i = 0; i < count; ++i) {

			insertByte(0x01);
			insertShort(i);
			insertAscii(draftSchematic->getCustomizationOption(i));
		}

	}

	// Starting COlor chooser position
	void update0E(DraftSchematic* draftSchematic) {

		int count = draftSchematic->getCustomizationOptionCount();

		startUpdate(0x0E);

		startList(count, count);

		for (int i = 0; i < count; ++i) {

			insertByte(0x01);
			insertShort(i);
			insertInt(draftSchematic->getCustomizationDefaultValue(i));
		}
	}

	void update0F(DraftSchematic* draftSchematic) {

		int count = draftSchematic->getCustomizationOptionCount();

		startUpdate(0x0F);

		startList(count, count);

		for (int i = 0; i < count; ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(0);
		}
	}

	// Number of palette colors
	void update10(DraftSchematic* draftSchematic, int custpoints) {

		int count = draftSchematic->getCustomizationOptionCount();

		startUpdate(0x10);

		startList(count, count);

		for (int i = 0; i < count; ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(custpoints);
		}
	}

	void update11() {

		startUpdate(0x11);
		insertByte(1);
	}

	void update12(DraftSchematic* draftSchematic){
		startUpdate(0x12);
		insertFloat(draftSchematic->getExpFailure());
	}

	void update14() {

		startUpdate(0x14);
		insertByte(1);
	}

};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
