/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BADGESRESPONSEMESSAGE_H_
#define BADGESRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/badges/Badges.h"

class BadgesResponseMessage : public BaseMessage {
public:
    BadgesResponseMessage(SceneObject* player, Badges* badges) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x6D89D25B);  // CRC
		insertLong(player->getObjectID()); //Player ID

		//TODO: Ensure that number of bitmasks doesn't exceed the highest idx settable in the badgeMap.
		//insertInt(0x05); //Number of bitmasks to send

		insertInt(0x0F); // from docs seems like if its not 0x0F badges dont show in the client

		setCompression(true);

		//TODO: Loop through a vector of bitmasks.
		for (int i = 0; i < 5; ++i) {
			insertInt(badges->getBitmask(i));
		}

		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
	}

};

#endif /*BADGESRESPONSEMESSAGE_H_*/
