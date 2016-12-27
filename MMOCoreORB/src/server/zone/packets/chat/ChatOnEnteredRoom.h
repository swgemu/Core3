/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONENTEREDROOM_H_
#define CHATONENTEREDROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnEnteredRoom : public BaseMessage {
public:
	ChatOnEnteredRoom(const String& galaxy, const String& playername, uint32 roomID, int error, int requestID) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xE69BDC0A);  // Opcode

		insertAscii("SWG"); // Game name
		insertAscii(galaxy); // Galaxy name
		insertAscii(playername); // Character name

		insertInt(error);
		insertInt(roomID); // Room ID
		insertInt(requestID); // Request ID
	}

};

#endif /*CHATONENTEREDROOM_H_*/
