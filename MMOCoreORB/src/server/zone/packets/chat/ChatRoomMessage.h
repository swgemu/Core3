/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATROOMMESSAGE_H_
#define CHATROOMMESSAGE_H_

#include "engine/engine.h"

class ChatRoomMessage : public BaseMessage {
public:
	ChatRoomMessage(const String& sender, const UnicodeString& message, uint32 channelid) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xCD4CE444);  // Opcode
		insertAscii("SWG");
		insertAscii("Core3");
		
		insertAscii(sender);
		
		insertInt(channelid); //Channel ID, Long converted to an Int.
		
		insertUnicode(message);
		insertInt(0);
		
		setCompression(true);

	} 

};
#endif /*CHATROOMMESSAGE_H_*/
