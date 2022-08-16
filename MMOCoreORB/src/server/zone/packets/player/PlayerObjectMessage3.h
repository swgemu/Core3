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
		/*insertFloat(1);

		insertAscii("String_id_table");
		insertInt(0);
		insertAscii("");

		insertInt(0);
		insertInt(0);
		insertInt(0);*/

		ghost->info(true) << " PlayerObjectMessage3 called ";

		insertInt(0x04);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);

		insertInt(0x04);
		insertInt(1);
		insertInt(1);
		insertInt(1);
		insertInt(1);

		insertAscii(ghost->getTitle());

		insertInt(0x6C2);
		insertInt(0xDC62);
		insertInt(0x23);

		setSize();
	}

};

#endif /*PLAYEROBJECTMESSAGE3_H_*/
