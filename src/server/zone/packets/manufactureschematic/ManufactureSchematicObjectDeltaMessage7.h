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

class ManufactureSchematicObjectDeltaMessage7 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage7(uint64 sceneObjSchematic) :
		DeltaMessage(sceneObjSchematic, 0x4D53434F, 7) {
	}

	void fullUpdate(DraftSchematic* ds, int size, int slot,
			uint64 resourceID, int quantity) {
		updateIngredientList(ds);
		updateSlot(size+1, size+1, slot);
		updateResource(size+1, size+1, slot, resourceID);
		updateQuantity(size+1, size+1, slot, quantity);
		update4(size, size, slot);
		update5(size+1, size+1, slot);
		update6(size, size, slot);
		update7();
		initializeExperimentalValues(ds);
	}
	
	void partialUpdate(int slot, int counter, uint64 resourceID, int quantity) { 
		updateSlot(1, counter, slot);
		updateResource(1, counter, slot, resourceID);
		updateQuantity(1, counter, slot, quantity);
		update5(1, counter, slot);
		update7();	
	}
	
	void updateForAssembly(){
		sendWeirdCrap();
		update9();
		update0B();
		update0C();
		update12();
	}

	void updateIngredientList(DraftSchematic * ds) {

		startUpdate(0);

		int ingredientListSize = ds->getIngredientListSize();
		
		startList(ingredientListSize, ingredientListSize);

		for (int i = 0; i < ingredientListSize; i++) {
			DraftSchematicIngredient* dsi = ds->getIngredient(i);
			if (dsi != NULL) {
				insertByte(1);
				insertShort(i);
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
			} else {
				cerr << "\n\nError DMSCO7: line 65\n";
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
//			if(i == slot){
				addListIntElement(i, 0);
//			} else {
//				addListFloatElement(i, 1.0f);
//			}
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
		insertByte(0x10); // No clue, was Decimal 24 for Scatter and 16 for Bofa

	}

	void initializeExperimentalValues(DraftSchematic* ds) {

		startUpdate(8);
		
		int expPropGroupListSize = ds->getExpPropTitlesListSize();
		
		insertInt(expPropGroupListSize);
		insertInt(expPropGroupListSize);
		
		
		for(int i = 0; i < expPropGroupListSize; i++) {
			string title = ds->getExpPropTitle(i);
			
			insertByte(1);
			insertShort(i);
			insertAscii("crafting");  // I think this is always "crafting"
			insertInt(0);
			insertAscii(title);
		}
				
		// Initialize update 9************
		startUpdate(9);

		startList(4, 4);

		for (int i = 0; i < 4; i++) {
			addListFloatElement(i, 0); 
		}
		//*********************************
		// Initialize update 0A************
		startUpdate(10);

		startList(4, 4);

		for (int i = 0; i < 4; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************
		// Initialize update 0B************
		startUpdate(11);

		startList(4, 4);

		for (int i = 0; i < 4; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************
		// Initialize update 0C************
		startUpdate(12);

		startList(4, 4);

		for (int i = 0; i < 4; i++) {
			addListFloatElement(i, 0);
		}
		//*********************************
		
	}
	
	// This should send the experimental values shown in the Screen after hitting assemble
	void update9() {
		startUpdate(9);

		startList(4, 8);

		for (int i = 0; i < 4; i++) {
			removeListFloatElement(i, 0.15);
		}
	}

	void update0A() {

		startUpdate(0x0A);

		startList(4, 8);

		for (int i = 0; i < 4; i++) {
			removeListFloatElement(i, 1.0);
		}
	}

	void update0B() {

		startUpdate(0x0B);

		startList(4, 8);

		for (int i = 0; i < 4; i++) {
			removeListFloatElement(i, 1.0);
		}
	}
	void update0C() {

		startUpdate(0x0C);

		startList(4, 8);

		for (int i = 0; i < 4; i++) {
			removeListFloatElement(i, 0.50);
		}
	}

	void update12(){
		startUpdate(0x12);
		insertFloat(0x42BFAAAB);
	}
	
	void update14() {

		startUpdate(0x14);
		insertByte(1);
	}
	
	void sendWeirdCrap(){
		startUpdate(0);
		startList(1,4);
		insertByte(0);
		insertShort(2);
		
		startUpdate(1);
		startList(1,6);
		insertByte(0);
		insertShort(2);
		
		startUpdate(2);
		startList(1,6);
		insertByte(0);
		insertShort(2);
		
		startUpdate(3);
		startList(1,6);
		insertByte(0);
		insertShort(2);
		
		startUpdate(4);
		startList(1,4);
		insertByte(0);
		insertShort(2);
		
		startUpdate(5);
		startList(1,6);
		insertByte(0);
		insertShort(2);
		
		startUpdate(6);
		startList(1,7);
		insertByte(0);
		insertShort(2);
		
		update7();
		
	}

};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
