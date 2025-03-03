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

	void updateItemIdentifier(const String& itemName) {
		addAsciiUpdate(0x00, itemName);
	}
	/* Raw Message:

	00 09 00 00
	05 00 // opcode
	53 21 86 12 // DeltasMessage
	6D 92 D7 05
	00 00
	01 00
	49 54 4E 4F 06 22 00 00 00 01 00 00 00 1C 00 64 72 6F 69 64 63 6F 6D 6D 61 6E 64 5F 77 65 61 70 63 61 70 65 71 75 61 6C 69 7A 65


	CreatureObjectDeltaMessage6 -- Raw Message: Stream [43]
	00 09 00 00
	05 00
	53 21 86 12 // DeltasMessage
	EF E0 C2 01
	00 00
	01 00
	4F 45 52 43 06 10 00 00 00 02 00 0A 00 00 04 00 07 00 6E 65 75 74 72 61 6C

	*/
};

#endif /*INTANGIBLEOBJECTDELTAMESSAGE6_H_*/
