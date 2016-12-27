/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONCREATEROOM_H_
#define CHATONCREATEROOM_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/chat/room/ChatRoom.h"

class ChatOnCreateRoom : public BaseMessage {
public:

	ChatOnCreateRoom(ChatRoom* room, int requestID, int error) : BaseMessage() {
		insertShort(4); // Op Count
		insertInt(0x35D7CC9F); // Opcode

		insertInt(error); // Error Code

		insertInt(room->getRoomID()); // ChatRoom ID

		if (room->isPublic())
			insertInt(0); // Private Flag. 0 = public? 1 = private? Client sends 1 for public room when creating in SUI.
		else
			insertInt(1);

		if(!room->isModerated())
			insertByte(0); // Moderated Flag. 0 = open, 1 = muted/moderated
		else
			insertByte(1);

		insertAscii(room->getFullPath()); // Room Full Address

		insertAscii("SWG"); // Game
		insertAscii(room->getGalaxyName()); // Galaxy
		insertAscii(room->getOwnerName()); // Owner

		insertAscii("SWG"); // Game
		insertAscii(room->getGalaxyName()); // Galaxy
		insertAscii(room->getCreator()); // Creator

		insertUnicode(room->getTitle()); //Room Title

		addToModeratorList(room);
		addToUserList(room);

		insertInt(requestID);	// Request ID

		setCompression(true);

	}

	void addToModeratorList(ChatRoom* room) {
		int size = room->getModeratorSize();
		insertInt(size);

		for (int i = 0; i < size; i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getModeratorName(i));
		}
	}
	
	void addToUserList(ChatRoom* room) {
		int size = room->getPlayerSize();
		insertInt(size);

		for (int i = 0; i < size; i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getPlayer(i)->getFirstName().toCharArray());
		}
	}

	ChatOnCreateRoom(CreatureObject* player, int requestID, int error) : BaseMessage() {
		insertShort(4); // Op Count
		insertInt(0x35D7CC9F); // Opcode
		insertInt(24); // Error Code (override to stop error spam due to autojoin client bug)

		insertInt(0); // ChatRoom ID
		insertInt(0); // Private Flag.
		insertByte(0); // Moderated Flag.
		insertAscii(""); // Room Full Address
		insertAscii("SWG"); // Game
		insertAscii(player->getZoneServer()->getGalaxyName()); // Galaxy
		insertAscii(player->getFirstName()); // Creator

		insertAscii("SWG"); // Game
		insertAscii(player->getZoneServer()->getGalaxyName()); // Galaxy
		insertAscii(player->getFirstName()); // Owner

		insertUnicode(""); //Room Title

		insertInt(0); //Moderator List Size
		insertInt(0); //User List Size

		insertInt(requestID);	// Request ID

	}

};

#endif /*CHATONCREATEROOM_H_*/
