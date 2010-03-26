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
#include "../../objects/draftschematic/DraftSchematicExpPropGroup.h"
#include "../../objects/draftschematic/DraftSchematicValues.h"

class ManufactureSchematicObjectMessage7 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage7(DraftSchematic* draftSchematic)
			: BaseLineMessage(draftSchematic->getObjectID(), 0x4D53434F, 7, 0x15) {

		int ingredientListSize = draftSchematic->getIngredientListSize();
		int updateCount = ingredientListSize;

		insertInt(ingredientListSize);
		insertInt(updateCount);

		for (int i = 0; i < ingredientListSize; i++) {
			DraftSchematicIngredient* dsi = draftSchematic->getIngredient(i);
			if (dsi != NULL) {
				insertAscii(dsi->getTemplateName());
				insertInt(0);
				insertAscii(dsi->getTitleName());
			} else {
				System::out << "\n\nInvalid dsi: MSCO7 line 63.\n\n";
			}
		}

		// NO IDEA WTF THIS IS FOR (doing this cause they were in live's logs)
		for (int i = 0; i < 6; i++) {
			insertInt(ingredientListSize);
			if (i == 5) {
				insertInt(updateCount * 2);
			} else {
				insertInt(updateCount);
			}

			for (int j = 0; j < ingredientListSize; j++) {
				if (i == 3) {
					if (j == 0) {
						insertInt(0);
					} else {
						insertFloat(1);
					}
				} else if (i == 4) {
					insertInt(0xFFFFFFFF);
				} else if (i == 5) {
					insertInt(j);
				} else {
					insertInt(0);
				}
			}
		}
		insertByte(0x0C); 	// no idea

		DraftSchematicValues * craftingValues = draftSchematic->getCraftingValues();

		int titleCount = craftingValues->getExperimentalPropertyTitleSize();

		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++) {
			String title = craftingValues->getExperimentalPropertyTitle(i);

			insertAscii("crafting");  // I think this is always "crafting"
			insertInt(0);
			insertAscii(title);

		}

		// NO IDEA WTF THIS IS FOR (doing this cause they were in live's logs)
		for (int i = 0; i < 4; i++) {
			insertInt(titleCount);
			insertInt(titleCount);
			for (int j = 0; j < titleCount; j++) {
				insertInt(0);
			}

			//insertInt(4);
			//insertInt(4);
			/*for (int j = 0; j < 4; j++) {
				insertInt(0);
			}*/
		}

		for (int i = 0; i < 4; i++) {
			insertInt(0);
			insertInt(0);
		}

		insertByte(0x00);

		insertInt(0);

		insertInt(0);
		insertInt(0);

		insertByte(0x01);

		setSize();
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
