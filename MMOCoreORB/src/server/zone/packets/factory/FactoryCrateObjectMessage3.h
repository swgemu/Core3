/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FACTORYCRATEOBJECTMESSAGE3_H_
#define FACTORYCRATEOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"

class FactoryCrateObjectMessage3 : public BaseLineMessage {
public:
	FactoryCrateObjectMessage3(FactoryCrate* crate, uint32 objType = 0x46435954, uint16 opcnt = 0x0B)
		: BaseLineMessage(crate->getObjectID(), objType, 3, opcnt) {

		insertFloat(1.0);

		insertStringId(crate->getObjectName());
		insertCustomName(crate->getCustomObjectName());

		insertInt(crate->getVolume());

		String app;
		crate->getCustomizationString(app);
		insertAscii(app);

		insertInt(0);
		insertInt(0);

		Reference<TangibleObject*> proto = crate->getPrototype();

		if(proto == NULL)
			insertInt(crate->getOptionsBitmask());
		else
			insertInt(proto->getOptionsBitmask());

		int count = crate->getUseCount();

		insertInt(count); //item count

		insertInt(int(crate->getConditionDamage()));
		insertInt(crate->getMaxCondition());

		insertByte(crate->getObjectVisible());

		setSize();
	}

};

#endif /*FACTORYCRATEOBJECTMESSAGE3_H_*/
