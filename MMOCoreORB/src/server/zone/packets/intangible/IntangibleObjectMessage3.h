/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTANGIBLEOBJECTMESSAGE3_H_
#define INTANGIBLEOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class IntangibleObjectMessage3 : public BaseLineMessage {
public:
	IntangibleObjectMessage3(IntangibleObject* itno, uint32 objType = 0x4F4E5449, uint16 opcnt = 5)
			: BaseLineMessage(itno->getObjectID(), objType , 3, opcnt) {

		// Complexity
		insertFloat(1);

		// STF File
		insertAscii("");

		// Int Spacer
		insertInt(0);

		// STF Name
		insertAscii(itno->getObjectName()->toString());

		// Custom Name
		insertUnicode(itno->getCustomObjectName());

		// Volume
		int volume = 0;

		if (itno->isTangibleObject())
			volume = itno->asTangibleObject()->getVolume();

		insertInt(volume);

		// Unused?
		insertInt(itno->getStatus());

		setSize();
	}

};

#endif /*INTANGIBLEOBJECTMESSAGE3_H_*/
