/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONGETFRIENDSLIST_H_
#define CHATONGETFRIENDSLIST_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/player/PlayerObject.h"

class ChatOnGetFriendsList : public BaseMessage {
public:
	ChatOnGetFriendsList(PlayerObject* ghost) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xE97AB594); // CRC

		insertLong(ghost->getParentID());

		setCompression(true);

		String serverName = ghost->getZoneServer()->getGalaxyName();

		DeltaVector<String>* friendList = ghost->getFriendList();
		insertInt(friendList->size());

		for (int i = 0; i < friendList->size(); ++i) {
			insertAscii("SWG");
			insertAscii(serverName);
			insertAscii(friendList->get(i));
		}

	}

};

#endif /*CHATONGETFRIENDSLIST_H_*/
