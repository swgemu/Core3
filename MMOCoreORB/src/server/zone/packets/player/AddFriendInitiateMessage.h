/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDFRIENDINITIATEMESSAGE_H_
#define ADDFRIENDINITIATEMESSAGE_H_

#include "engine/engine.h"

class AddFriendInitiateMessage : public BaseMessage {
public:
    AddFriendInitiateMessage() : BaseMessage() {
	
    	insertShort(0x03);
    	insertInt(0x2B2A0D94);  // CRC
    	insertLong(0);
    
	}
	
};

#endif /*ADDFRIENDINITIATEMESSAGE_H_*/
