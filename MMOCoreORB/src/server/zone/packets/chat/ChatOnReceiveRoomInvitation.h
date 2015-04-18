/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONRECEIVEROOMINVITATION_H_
#define CHATONRECEIVEROOMINVITATION_H_

#include "engine/engine.h"

class ChatOnReceiveRoomInvitation : public BaseMessage {
public:
	ChatOnReceiveRoomInvitation(const String& server, const String& channel) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xC17EB06D);  // Opcode
		insertAscii("SWG");
		insertAscii(server.toCharArray());
		insertAscii("system");
		insertAscii(channel);
	
	} 

};

#endif /*CHATONRECEIVEROOMINVITATION_H_*/
