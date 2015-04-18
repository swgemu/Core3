/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FRIENDSLISTMESSAGE_H_
#define FRIENDSLISTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
/*#include "../../objects/player/Player.h"
#include "../../objects/player/FriendsList.h"*/

class FriendsListMessage : public BaseMessage {
public:
	FriendsListMessage(PlayerObject* ghost) : BaseMessage() {
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

#endif /*FRIENDSLISTMESSAGE_H_*/
