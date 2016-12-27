/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SELECTCHARACTER_H_
#define SELECTCHARACTER_H_

#include "engine/service/proto/BaseMessage.h"

class SelectCharacter : public BaseMessage {
public:
	SelectCharacter(uint64 charid) {
		insertShort(0x02);
		insertInt(0xB5098D76);

		insertLong(charid);
	}

	static uint64 parse(Packet* pack) {
		return pack->parseInt(10);
	}

};

#endif /*SELECTCHARACTER_H_*/
