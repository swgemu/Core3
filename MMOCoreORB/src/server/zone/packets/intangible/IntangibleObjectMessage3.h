/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTANGIBLEOBJECTMESSAGE3_H_
#define INTANGIBLEOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/intangible/IntangibleObject.h"

class IntangibleObjectMessage3 : public BaseLineMessage {
public:
	IntangibleObjectMessage3(IntangibleObject* itno, uint32 objType = 0x4F4E5449, uint16 opcnt = 5)
			: BaseLineMessage(itno->getObjectID(), objType , 3, opcnt) {

		insertFloat(1);
		insertStringId(itno->getObjectName());
		insertCustomName(itno->getCustomObjectName());

		insertInt(0); // ?
		insertInt(itno->getStatus());

		setSize();
	}

};

#endif /*INTANGIBLEOBJECTMESSAGE3_H_*/
