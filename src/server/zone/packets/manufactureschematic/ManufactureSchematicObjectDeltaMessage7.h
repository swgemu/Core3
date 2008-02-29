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

class ManufactureSchematicObjectDeltaMessage7 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage7(uint64 sceneObjSchematic, DraftSchematic* ds, uint64 resourceID) 
			: DeltaMessage(sceneObjSchematic, 0x4D53434F, 7) {

			startUpdate(0);
			
			int ingredientListSize = ds->getIngredientListSize();
			insertInt(ingredientListSize);
			insertInt(ingredientListSize);
			
			for(int i = 0; i < ingredientListSize; i++) {
				DraftSchematicIngredient* dsi = ds->getIngredient(i);
				if(dsi != NULL) {
				insertByte(1);
				insertShort(i);
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
				} else {
					cerr << "\n\nError DMSCO7: line 65\n";
				}
			}
			
			// Next Part *************************************************
			
			startUpdate(1);
			insertInt(ingredientListSize+1);
			insertInt(ingredientListSize+1);
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0);
			}
			removeListIntElement(0, 4);
			
			// Next Part **************************************************
			
			startUpdate(2);
			insertInt(ingredientListSize+1);
			insertInt(ingredientListSize+1);
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0);
			}
			removeListIntElement(0, 1);
			insertLong(resourceID);
			
			// Next Part **************************************************

			startUpdate(3);
			insertInt(ingredientListSize+1);
			insertInt(ingredientListSize+1);
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0);
			}
			removeListIntElement(0, 1);
			insertInt(3); // Resource Quantity
			
			// Next Part **************************************************

			startUpdate(4);
			insertInt(ingredientListSize);
			insertInt(ingredientListSize);
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0);
			}
			
			// Next Part **************************************************

			startUpdate(5);
			insertInt(ingredientListSize+1);
			insertInt(ingredientListSize+1);			
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0xFFFFFFFF);
			}
			removeListIntElement(0, 0);
			
			
			// Next Part (maybe)**************************************************
			
			startUpdate(6);
			insertInt(ingredientListSize*2);
			insertInt(ingredientListSize*2);			
			
			for(int i = 0; i < ingredientListSize; i++){
				addListIntElement(i, 0xFFFFFFFF);
				removeListIntElement(i, i);
			}

			// Next Part (maybe)**************************************************
			
			startUpdate(7);
			insertByte(16);  // No clue, was Decimal 24 for Scatter and 16 for Bofa
			
			// Next Part *********************************************************
			
			startUpdate(8);
			insertInt(4);
			insertInt(4);			
			
			
			// HARDCODED UNTIL FIXED
			
			insertByte(1);
			insertShort(0);
			insertAscii("crafting");
			insertInt(0);
			insertAscii("exp_filling");
			
			insertByte(1);
			insertShort(1);
			insertAscii("crafting");
			insertInt(0);
			insertAscii("exp_flavor");
			
			insertByte(1);
			insertShort(2);
			insertAscii("crafting");
			insertInt(0);
			insertAscii("exp_nutrition");
			
			
			insertByte(1);
			insertShort(3);
			insertAscii("crafting");
			insertInt(0);
			insertAscii("exp_quantity");
			
			// Next Part *********************************************************
			
			startUpdate(9);
			insertInt(1);
			insertInt(1);
			
			addListIntElement(0, 0);
			
			// Next Part **************************************************
			
			startUpdate(10);
			insertInt(1);
			insertInt(1);
			
			addListIntElement(0, 0);
			
			// Next Part **************************************************
			
			startUpdate(11);
			insertInt(1);
			insertInt(1);
			
			addListIntElement(0, 0);
			
			// Next Part **************************************************
			
			startUpdate(12);
			insertInt(1);
			insertInt(1);
			
			addListIntElement(0, 0);
			
			// Next Part (???)**************************************************
			
			startUpdate(0x14);
			insertByte(1);
			
			// Next Part **************************************************
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
