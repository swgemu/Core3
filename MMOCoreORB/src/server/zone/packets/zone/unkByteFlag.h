/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNKBYTEFLAG_H_
#define UNKBYTEFLAG_H_

#include "engine/engine.h"

class unkByteFlag : public BaseMessage {
public:
	unkByteFlag() : BaseMessage(7) {
		insertShort(0x02);
		insertInt(0x7102B15F);
		insertByte(1);

	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}
	
};

#endif /*UNKBYTEFLAG_H_*/
