/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATROOMMESSAGE_H_
#define CHATROOMMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ChatRoomMessage : public BaseMessage {
public:
	ChatRoomMessage(const String& sender, const String& galaxyName, const UnicodeString& message, uint32 channelid) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xCD4CE444);  // Opcode
		insertAscii("SWG");
		insertAscii(galaxyName);
		
		insertAscii(sender.toLowerCase());
		
		insertInt(channelid); //Channel ID, Long converted to an Int.
		
		insertUnicode(message);
		insertInt(0);
		
		setCompression(true);
	} 

};

#endif /*CHATROOMMESSAGE_H_*/
