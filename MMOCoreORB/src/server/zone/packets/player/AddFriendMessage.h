/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDFRIENDMESSAGE_H_
#define ADDFRIENDMESSAGE_H_

#include "engine/engine.h"

class AddFriendMessage : public BaseMessage {
public:
    AddFriendMessage(uint64 oid, const String& name, const String& server, bool add) : BaseMessage() {
	
    	insertShort(0x06);
    	insertInt(0x54336726);  // CRC
    	insertLong(oid);
    	
    	insertAscii("SWG");
    	insertAscii(server);
    	insertAscii(name);
    	
    	insertInt(0);
    	insertInt(add);
    	insertByte(0);
    
	}
	
};

#endif /*ADDFRIENDMESSAGE_H_*/
