/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERTIMEMESSAGE_H_
#define SERVERTIMEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

#include "server/zone/Zone.h"

class ServerTimeMessage : public BaseMessage {
public:
	ServerTimeMessage(uint64 time) : BaseMessage(18) {
		insertShort(0x02);
		insertInt(0x2EBC3BD9);  // CRC
		insertLong(time);  // Galactic_Time
	}
	
	ServerTimeMessage(Zone* zone) : BaseMessage(18) {
		insertShort(0x02);
		insertInt(0x2EBC3BD9);  // CRC
		insertLong(zone->getGalacticTime());  // Galactic_Time
	}
	
};

#endif /*SERVERTIMEMESSAGE_H_*/
