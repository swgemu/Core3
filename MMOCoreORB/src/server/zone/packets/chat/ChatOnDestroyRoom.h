/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONDESTROYROOM_H_
#define CHATONDESTROYROOM_H_

class ChatOnDestroyRoom : public BaseMessage {
public:
	
	ChatOnDestroyRoom(const String& game, const String& server, uint32 channelid) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xE8EC5877);  // Opcode
		insertAscii(game.toCharArray());
		insertAscii(server.toCharArray());
		insertAscii("system");
		insertInt(0);
		insertInt(channelid);
		insertInt(0);
	}

};

#endif /*CHATONDESTROYROOM_H_*/

