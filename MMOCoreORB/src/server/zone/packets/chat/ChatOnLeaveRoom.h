/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONLEAVEROOM_H_
#define CHATONLEAVEROOM_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/chat/room/ChatRoom.h"
#include "server/zone/objects/creature/CreatureObject.h"

class ChatOnLeaveRoom : public BaseMessage {
public:

	ChatOnLeaveRoom(ChatRoom* room, CreatureObject* player) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x60B5098B);  // Opcode

		insertAscii("SWG");
		insertAscii(room->getGalaxyName());
		insertAscii(player->getFirstName());

		insertInt(0); //Error Code
		insertInt(room->getRoomID()); //Room ID
		insertInt(0); //Request ID. Always seen 0.
	}
};

#endif /*CHATONLEAVEROOM_H_*/
