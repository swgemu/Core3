/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDIGNOREMESSAGE_H_
#define ADDIGNOREMESSAGE_H_

#include "engine/engine.h"

class AddIgnoreMessage : public BaseMessage {
public:
    AddIgnoreMessage(uint64 oid, const String& name, const String& server, bool add) : BaseMessage() {
	
    	insertShort(0x06);
    	insertInt(0x70E9DA0F);  // CRC
		insertLong(oid);
		
		insertAscii("SWG");
    	insertAscii(server);
    	insertAscii(name);
    	
    	insertInt(0);
    	insertByte(add);
    	insertInt(0);
	}
	
};

#endif /*ADDIGNOREMESSAGE_H_*/
