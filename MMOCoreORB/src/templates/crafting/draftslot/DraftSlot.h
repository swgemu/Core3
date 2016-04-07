/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

	// Contribution level
	float contribution;

public:
	enum {
		RESOURCESLOT,
		IDENTICALSLOT,
		MIXEDSLOT,
		OPTIONALIDENTICALSLOT,
		OPTIONALMIXEDSLOT
	};

public:
	DraftSlot() : quantity(0), slotType(0), contribution(0) {

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
