/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTMESSAGE3_H_
#define PLAYEROBJECTMESSAGE3_H_

#include "server/zone/packets/intangible/IntangibleObjectMessage3.h"
#include "server/zone/objects/player/PlayerObject.h"

class PlayerObjectMessage3 : public IntangibleObjectMessage3 {
public:
	PlayerObjectMessage3(PlayerObject* ghost) : IntangibleObjectMessage3(ghost, 0x504C4159, 0x0B) {
		// Player Bitmasks
		insertInt(0x04);
		const PlayerBitmasks* playerBits = ghost->getPlayerBitmasks();

		for (int i = 0; i < 4; ++i) {
			insertInt(playerBits->getBitmask(i));
		}

		// Profile Settings
		insertInt(0x04);
		const PlayerBitmasks* profileBits = ghost->getProfileBitmasks();

		for (int i = 0; i < 4; ++i) {
			insertInt(profileBits->getBitmask(i));
		}

		// Skill Title
		insertAscii(ghost->getTitle());

		// Born Date
		insertInt(ghost->getBirthDate());

		// Total Play Time
		insertInt(ghost->getTotalPlayedTime());

		insertInt(0x6C2);
		insertInt(0xDC62);
		insertInt(0x23);

		setSize();
	}

};

#endif /*PLAYEROBJECTMESSAGE3_H_*/
