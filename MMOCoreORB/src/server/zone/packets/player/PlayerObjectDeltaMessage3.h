/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTDELTAMESSAGE3_H_
#define PLAYEROBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/player/PlayerObject.h"

class PlayerObjectDeltaMessage3 : public DeltaMessage {
	PlayerObject* ghost;

public:
	PlayerObjectDeltaMessage3(PlayerObject* pl) : DeltaMessage(pl->getObjectID(), 0x504C4159, 3) {
		ghost = pl;
	}

	void updatePlayerBitmasks() {
		startUpdate(0x05);
		insertInt(0x04);

		ghost->info(true) << " PlayerObjectDeltaMessage3 called ";

		//setCompression(true);

		const PlayerBitmasks* playerBits = ghost->getPlayerBitmasks();

		for (int i = 0; i < 4; ++i) {
			insertInt(playerBits->getBitmask(i));
		}
	}

	void setCurrentTitle(const String& pTitle) {
		startUpdate(0x07);
		insertAscii(pTitle);
	}

	void setTotalPlayTime(int value) {
		startUpdate(0x09);
		insertInt(value);
	}
};
#endif /*PLAYEROBJECTDELTAMESSAGE3_H_*/
