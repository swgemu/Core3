/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONSENDROOMMESSAGE_H_
#define CHATONSENDROOMMESSAGE_H_

#include "engine/engine.h"

class ChatOnSendRoomMessage : public BaseMessage {
public:
	ChatOnSendRoomMessage(uint32 seq) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xE7B61633);  // Opcode
		insertInt(0);
		insertInt(seq);
	} 

};
#endif /*CHATONSENDROOMMESSAGE_H_*/
