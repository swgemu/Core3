/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTDELTAMESSAGE3_H_
#define PLAYEROBJECTDELTAMESSAGE3_H_

#include "../DeltaMessage.h"

#include "server/zone/objects/player/PlayerObject.h"

class PlayerObjectDeltaMessage3 : public DeltaMessage {
	PlayerObject* play;
	
public:
	PlayerObjectDeltaMessage3(PlayerObject* pl)
			: DeltaMessage(pl->getObjectID(), 0x504C4159, 3) {
		play = pl;
	}

	void setCurrentTitle(const String& pTitle) {
		startUpdate(7);
		insertAscii(pTitle);
	}
	
	void setUpdateTypeNine(int value) {
		startUpdate(9);
		insertInt(value);
	}
	
	void updateCharacterBitmask(uint32 bitmask) {
		startUpdate(5);
		insertInt(4);
		insertInt(bitmask);
		insertInt(0);
		insertInt(0);
		insertInt(0);
	}
	
};
#endif /*PLAYEROBJECTDELTAMESSAGE3_H_*/
