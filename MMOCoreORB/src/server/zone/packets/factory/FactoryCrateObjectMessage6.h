/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FACTORYCRATEOBJECTMESSAGE6_H_
#define FACTORYCRATEOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class FactoryCrateObjectMessage6 : public BaseLineMessage {
public:
	FactoryCrateObjectMessage6(TangibleObject* tano) 
			: BaseLineMessage(tano->getObjectID(), 0x46435954, 6, 0x06) {
		
		insertShort(3);

		insertInt(0);
		insertInt(0);

		insertInt(0);
		insertInt(0);

		insertInt(0);
		insertInt(0);

		insertInt(0);
		insertInt(0);

		insertByte(0);

		setSize();
	}
	
};

#endif /*FACTORYCRATEOBJECTMESSAGE6_H_*/
