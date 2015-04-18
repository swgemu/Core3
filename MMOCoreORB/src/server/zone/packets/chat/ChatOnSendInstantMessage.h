/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONSENDINSTANTMESSAGE_H_
#define CHATONSENDINSTANTMESSAGE_H_

#include "engine/engine.h"

class ChatOnSendInstantMessage : public BaseMessage {
public:
	ChatOnSendInstantMessage(uint32 seq, int result = 0) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x88DBB381);  // CRC

		insertInt(result);
			
		insertInt(seq);
	} 
	
};

#endif /*CHATONSENDINSTANTMESSAGE_H_*/
