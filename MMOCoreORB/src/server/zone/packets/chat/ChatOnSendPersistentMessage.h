/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONSENDPERSISTENTMESSAGE_H_
#define CHATONSENDPERSISTENTMESSAGE_H_

//Mail

#include "engine/engine.h"

class ChatOnSendPersistentMessage : public BaseMessage {
public:
	ChatOnSendPersistentMessage(uint32 seq, int returnCode) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x94E7A7AE);  // CRC

		insertInt(returnCode);
			
		insertInt(seq);
	} 
	
};

#endif /*CHATONSENDPERSISTENTMESSAGE_H_*/
