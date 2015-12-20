/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONENTEREDROOM_H_
#define CHATONENTEREDROOM_H_

#include "engine/engine.h"

class ChatOnEnteredRoom : public BaseMessage {
public:
	ChatOnEnteredRoom(const String& server, const String& playername, uint32 roomID, int error, int requestID) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xE69BDC0A);  // Opcode
		
		insertAscii("SWG"); // Game name
		insertAscii(server.toCharArray()); // Galaxy name
		insertAscii(playername.toCharArray()); // Character name

		insertInt(error); // Success bitmask.
		/*0 = You have joined the channel.
		* 0x10 = You cannot join (room name) because you are not invited.
		* Default: Chatroom (roomname) join failed for an unknown reason.*/

		insertInt(roomID); // Room ID
		insertInt(requestID); // Request ID

		printf("\n======================");
		printf("\nSending ChatOnEnteredRoom packet to client.");
		printf("\nCharacter name = %s", playername.toCharArray());
		printf("\nroomID = %s", String::valueOf(roomID).toCharArray());
		printf("\nerror = %s", String::valueOf(error).toCharArray());
		printf("\nrequestID = %s", String::valueOf(requestID).toCharArray());
		printf("\n======================");

	} 

};

#endif /*CHATONENTEREDROOM_H_*/
