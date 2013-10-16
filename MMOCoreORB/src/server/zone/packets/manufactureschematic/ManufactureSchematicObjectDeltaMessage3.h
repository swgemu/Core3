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


#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE3_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/draftschematic/DraftSchematic.h"

class ManufactureSchematicObjectDeltaMessage3 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage3(SceneObject* schematic)
			: DeltaMessage(schematic->getObjectID(), 0x4D53434F, 3) {
	}

	void updateComplexity(float complexity) {
		addFloatUpdate(0, complexity);
	}

	void updateName(String name) {
		addUnicodeUpdate(2, name);
	}

	void updateCondition(int condition) {
		addIntUpdate(4, condition);
	}

	void updateManufactureLimit(int limit) {
		addIntUpdate(5, limit);
	}

	void updateCraftingValues(ManufactureSchematic* manufactureSchematic){

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		String name;
		float value;

		int count = craftingValues->getValuesToSendSize();

		startUpdate(5);

		startList(count, count);

		for (int i = 0; i < count; ++i){

			insertByte(0);
			insertAscii("crafting");
			insertInt(0);
			name = craftingValues->getValuesToSend(i);
			value = craftingValues->getCurrentValue(name);
			insertAscii(name);
			insertFloat(value);

		}
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE3_H_*/
