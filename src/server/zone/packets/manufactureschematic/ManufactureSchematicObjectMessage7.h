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

#include "../../objects/draftschematic/DraftSchematic.h"
#include "../../objects/draftschematic/DraftSchematicIngredient.h"

class ManufactureSchematicObjectMessage7 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage7(uint64 oid, DraftSchematic* ds) 
			: BaseLineMessage(oid, 0x4D53434F, 7, 0x15) {

		int ingredientListSize = ds->getIngredientListSize();
		insertInt(ingredientListSize);
		insertInt(ingredientListSize);
		
		for(int i = 0; i < ingredientListSize; i++) {
			DraftSchematicIngredient* dsi = ds->getIngredient(i);
			if(dsi != NULL) {
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
			} else {
				cerr << "\n\nInvalid dsi: MSCO7 line 63.\n\n";
			}
		}
		
		// NO IDEA WTF THIS IS FOR (doing this cause they were in live's logs)
		for(int i = 0; i < 6; i++) {
			insertInt(ingredientListSize);
			insertInt(ingredientListSize);
			for(int j = 0; j < ingredientListSize; j++) {
				if(j == 4) {
					insertFloat(1);
				} else if(j == 5) {
					insertInt(0xFFFFFFFF);
				} else if(j == 6){
					insertInt(j);
				} else {
					insertInt(0);
				}
			}
		}
		insertByte(0x0C); 	// no idea
		
		int expPropGroupListSize = ds->getExpPropGroupListSize();
		insertInt(expPropGroupListSize);
		insertInt(expPropGroupListSize);
		
		/*
		for(int i = 0; i < expPropGroupListSize; i++) {
			DraftSchematicExpPropGroup* dsEpg = ds->getExpPropGroup();
			if(dsi != NULL) {
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
			} else {
				cerr << "\n\nInvalid dsi: MSCO7 line 63.\n\n";
			}
		}*/
		
		// Hardcodeing these.  Above is what it should be
		insertAscii("crafting");
		insertInt(0);
		insertAscii("exp_filling");
		insertAscii("crafting");
		insertInt(0);
		insertAscii("exp_flavor");
		insertAscii("crafting");
		insertInt(0);
		insertAscii("exp_nutrition");
		insertAscii("crafting");
		insertInt(0);
		insertAscii("exp_quantity");
								
		
		// NO IDEA WTF THIS IS FOR (doing this cause they were in live's logs)
		for(int i = 0; i < 4; i++) {
			insertInt(expPropGroupListSize);
			insertInt(expPropGroupListSize);
			for(int j = 0; j < expPropGroupListSize; j++) {
				insertInt(0);
			}
		}
		
		for(int i = 0; i < 4; i++) {
			insertInt(0);
			insertInt(0);
		}
		
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
		
		insertByte(0x01);
					
		setSize();
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
