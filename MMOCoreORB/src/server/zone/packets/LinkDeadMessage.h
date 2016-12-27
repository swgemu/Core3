/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LINKDEADMESSAGE_H_
#define LINKDEADMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class LinkDeadMessage : public BaseMessage {
public:
	LinkDeadMessage() : BaseMessage() {
		insertShort(0x05);
		insertInt(0xA16CF9AF); //opcode
	}

};

#endif /*LINKDEADMESSAGE_H_*/
