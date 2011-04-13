/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

#ifndef DRAFTSLOT_H_
#define DRAFTSLOT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/StringId.h"

class DraftSlot : public Object {
private:

	StringId stringId;

	// resource name in stf format
	String resourceType;

	// example: 3
	uint32 quantity;

	// example: 2 = Identical items required, 1 = optional, 0 = standard
	int slotType;

	// Math Type
	uint32 combineType;

	// Contribution level
	float contribution;

public:
	static const int RESOURCESLOT = 0;
	static const int IDENTICALSLOT = 1;
	static const int MIXEDSLOT = 2;
	static const int OPTIONALIDENTICALSLOT = 3;
	static const int OPTIONALMIXEDSLOT = 4;

public:
	DraftSlot() {

	}

	~DraftSlot() {

	}

	void insertToMessage(BaseMessage* msg) {
		msg->insertAscii(stringId.getFile()); // ex: craft_food_ingredients_n
		msg->insertInt(0);
		msg->insertAscii(stringId.getStringID()); // ex: dried_fruit

		if (slotType == OPTIONALIDENTICALSLOT || slotType == OPTIONALMIXEDSLOT)
			msg->insertByte(1);  // ex: additive is optional so insertByte(1);
		else
			msg->insertByte(0);

		msg->insertInt(1);

		msg->insertAscii(stringId.getFile()); // ex: craft_food_ingredients_n
		msg->insertInt(0);
		msg->insertAscii(stringId.getStringID()); // ex: dried_fruit

		UnicodeString uniResourceType(resourceType);
		msg->insertUnicode(uniResourceType); // ex: organic

		if (slotType == MIXEDSLOT || slotType == OPTIONALMIXEDSLOT) {
			msg->insertByte(5);  // Enables Components
			msg->insertInt(quantity); // ex: 3
		} else if (slotType == IDENTICALSLOT || slotType == OPTIONALIDENTICALSLOT) {
			msg->insertByte(2);
			msg->insertInt(quantity); // ex: 3
			msg->insertShort(0);
		} else if (slotType == RESOURCESLOT) {
			msg->insertByte(4);
			msg->insertInt(quantity); // ex: 3
		}
	}

    uint32 getCombineType() const
    {
        return combineType;
    }

    float getContribution() const
    {
        return contribution;
    }

    uint32 getQuantity() const
    {
        return quantity;
    }

    String getResourceType() const
    {
        return resourceType;
    }

    int getSlotType() const
    {
        return slotType;
    }

    StringId getStringId() const
    {
        return stringId;
    }

    void setCombineType(uint32 combineType)
    {
        this->combineType = combineType;
    }

    void setContribution(float contribution)
    {
        this->contribution = (contribution / 100.0f);
    }

    void setQuantity(uint32 quantity)
    {
        this->quantity = quantity;
    }

    void setResourceType(String resourceType)
    {
        this->resourceType = resourceType;
    }

    void setSlotType(int slotType)
    {
        this->slotType = slotType;
    }

    void setStringId(String file, String name)
    {
        stringId.setStringId(file, name);
    }
};

#endif /* DRAFTSLOT_H_ */
