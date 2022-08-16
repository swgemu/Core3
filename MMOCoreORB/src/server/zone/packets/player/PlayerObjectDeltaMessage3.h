/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTDELTAMESSAGE3_H_
#define PLAYEROBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/PlayerBitmasks.h"

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

		//TODO: Loop through a vector of bitmasks.
		for (int i = 0; i < 4; ++i) {
			insertInt(playerBits->getBitmask(i));
		}


		insertInt(011121);
		insertInt(0);
		insertInt(0);
		insertInt(0);

		/*const DeltaBitArray* playerBitmasks = ghost->getPlayerBitmasks();
		playerBitmasks->insertToMessage(this);

		int size = playerBitmasks->bitCount();

		ghost->info(true) << " bit array size = " << size;

		if (size < 128) {
			int diff = (128 - size) / 8;

			for (int i = 1; i < diff; i++) {
				ghost->info(true) << " adding byte #" << i;
				insertByte(0);
			}
		}*/
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
