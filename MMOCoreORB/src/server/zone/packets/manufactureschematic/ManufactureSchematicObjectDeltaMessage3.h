/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE3_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"

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
