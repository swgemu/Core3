/*
 * ChatQueryRoomResults.h
 *
 *  Created on: Oct 10, 2015
 *      Author: Anakis
 */

#ifndef CHATQUERYROOMRESULTS_H_
#define CHATQUERYROOMRESULTS_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/chat/room/ChatRoom.h"

class ChatQueryRoomResults : public BaseMessage {
public:

	ChatQueryRoomResults(ChatRoom* room, int requestID = 0) : BaseMessage() {
		insertShort(7); // Op Count
		insertInt(0xC4DE864E); // Opcode

		insertInt(room->getPlayerSize()); //List of players in the chat room.
		fillPlayerList(room);

		insertInt(room->getInvitedSize()); //List of invited players.
		fillInvitedList(room);

		insertInt(room->getModeratorSize()); //List of moderators.
		fillModeratorList(room);

		insertInt(room->getBannedSize()); //List of banned players.
		fillBannedList(room);

		insertInt(requestID);

		insertInt(room->getRoomID());

		if (room->isPublic())
			insertInt(0);
		else
			insertInt(1);

		if (!room->isModerated())
			insertByte(0);
		else
			insertByte(1);

		insertAscii(room->getFullPath());

		insertAscii("SWG");
		insertAscii(room->getGalaxyName());
		insertAscii(room->getOwnerName());

		insertAscii("SWG");
		insertAscii(room->getGalaxyName());
		insertAscii(room->getCreator());

		insertUnicode(room->getTitle());

		insertInt(0); //Don't fill duplicate moderator list.
		insertInt(0); //Don't fill duplicate player list.

		setCompression(true);
	}

	void fillPlayerList(ChatRoom* room) {
		for (int i = 0; i < room->getPlayerSize(); i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getPlayer(i)->getFirstName());
		}
	}

	void fillInvitedList(ChatRoom* room) {
		for (int i = 0; i < room->getInvitedSize(); i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getInvitedName(i));
		}
	}

	void fillModeratorList(ChatRoom* room) {
		for (int i = 0; i < room->getModeratorSize(); i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getModeratorName(i));
		}
	}

	void fillBannedList(ChatRoom* room) {
		for (int i = 0; i < room->getBannedSize(); i++) {
			insertAscii("SWG");
			insertAscii(room->getGalaxyName());
			insertAscii(room->getBannedName(i));
		}
	}

};

#endif /*CHATQUERYROOMRESULTS_H_*/
