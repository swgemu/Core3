/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BAZAARDISPLAYUI_H_
#define BAZAARDISPLAYUI_H_

#include "engine/engine.h"

#include "../../objects/player/Player.h"
#include "../../objects/player/PlayerObject.h"

#include "../BaseLineMessage.h"

class BazaarDisplayUI : public BaseMessage {
	
public:
	BazaarDisplayUI(bool vendor, long bazaarId, Player* player) {
		insertShort(5);
		insertInt(0x80CE5E46);
		insertInt(0x0B);
		insertInt(0x0147);
		insertLong(player->getPlayerObject()->getObjectID());
		insertInt(0);
		insertLong(bazaarId);
		insertLong(player->getPlayerObject()->getObjectID());
		insertInt(2);
		insertShort(1);
		insertInt(0x012E);
		insertShort(0);
		insertShort(2);
		insertInt(0x0701);
		insertShort(0);

		if (vendor)
			insertByte(0x1F);
		else
			insertByte(1); 
	}
	
};

#endif /*BAZAARDISPLAYUI_H_*/
