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
		//insertInt(4);

		ghost->info(true) << " PlayerObjectDeltaMessage3 called ";

		const DeltaVector<uint16>* playerBitmasks = ghost->getPlayerBitmasks();
		playerBitmasks->insertToMessage(this);

		setSize(playerBitmasks->size());
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
