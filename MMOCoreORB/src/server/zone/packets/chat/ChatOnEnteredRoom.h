/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONENTEREDROOM_H_
#define CHATONENTEREDROOM_H_

#include "engine/engine.h"

class ChatOnEnteredRoom : public BaseMessage {
public:
	ChatOnEnteredRoom(const String& server, const String& playername, uint64 channelid) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xE69BDC0A);  // Opcode
		insertAscii("SWG");
		insertAscii(server.toCharArray());
		
		insertAscii(playername);
		insertInt(0);
		insertLong(channelid);
	} 

};

#endif /*CHATONENTEREDROOM_H_*/
