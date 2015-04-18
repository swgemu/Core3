/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONCREATEROOM_H_
#define CHATONCREATEROOM_H_

#include "engine/engine.h"

#include "server/chat/room/ChatRoom.h"

class ChatOnCreateRoom : public BaseMessage {
public:

	ChatOnCreateRoom(ChatRoom* room, uint32 counter) : BaseMessage() {
		insertShort(4);
		insertInt(0x35D7CC9F); // opcode
		
		insertInt(0); //
		
		insertInt(room->getRoomID());
		insertInt(1); // ?
		insertByte(0); // ?
		
		insertAscii(room->getFullPath());
		
		insertAscii("SWG");
		insertAscii(room->getGalaxyName());
		insertAscii(room->getCreator());
		
		insertAscii("SWG");
		insertAscii(room->getGalaxyName());
		insertAscii(room->getCreator());
		
		insertUnicode(room->getTitle());

		addToUnknownListA(room);
		addToUnknownListB();
		
		
		insertInt(counter);	
		
	}
	
	void addToUnknownListA(ChatRoom* room) {
		insertInt(0);
		
		/*int size = room->playerList.size(); 
		insertInt(size);
		
		for (int i = 0; i < size; i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->playerList.get(i)->getFirstName());
		}*/
		
		/*insertInt(1); //List Count of Players in Room?
		insertAscii("SWG");
		insertAscii(serverName.toCharArray());
		insertAscii(name.toCharArray());*/
	}
	
	void addToUnknownListB() {
		insertInt(0); //List Count
		/*insertAscii("SWG");
		insertAscii(serverName.toCharArray());
		insertAscii(name);*/	
	}
};

#endif /*CHATONCREATEROOM_H_*/
