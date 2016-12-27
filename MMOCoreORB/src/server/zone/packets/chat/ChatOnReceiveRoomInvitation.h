/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONRECEIVEROOMINVITATION_H_
#define CHATONRECEIVEROOMINVITATION_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnReceiveRoomInvitation : public BaseMessage {
public:
	ChatOnReceiveRoomInvitation(const String& galaxy, const String& moderator, const String& roomPath) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xC17EB06D);  // Opcode
		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy
		insertAscii(moderator); //Moderator name
		insertAscii(roomPath); //Chat room path

	}

};

#endif /*CHATONRECEIVEROOMINVITATION_H_*/
