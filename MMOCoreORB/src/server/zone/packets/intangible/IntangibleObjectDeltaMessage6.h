/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef INTANGIBLEOBJECTDELTAMESSAGE6_H_
#define INTANGIBLEOBJECTDELTAMESSAGE6_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/intangible/IntangibleObject.h"

class IntangibleObjectDeltaMessage6 : public DeltaMessage {
	IntangibleObject* itno;

public:
IntangibleObjectDeltaMessage6(IntangibleObject* it) : DeltaMessage(it->getObjectID(), 0x4F4E5449, 6) {
		itno = it;
	}

	void updateItemIdentifier(const UnicodeString& itemName) {
		addUnicodeUpdate(0x0C, itemName);
	}
};

#endif /*INTANGIBLEOBJECTDELTAMESSAGE6_H_*/
