/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FRIENDSTATUSCHANGEMESSAGE_H_
#define FRIENDSTATUSCHANGEMESSAGE_H_

#include "engine/engine.h"

class FriendStatusChangeMessage : public BaseMessage {
public:
	FriendStatusChangeMessage(const String& name, const String& server, bool online) : BaseMessage() {
	
    	insertShort(0x03);
    	insertInt(0x6CD2FCD8);  // CRC

    	insertAscii("SWG");
    	insertAscii(server);
    	insertAscii(name);

    	insertByte(online);
    
	}
	
};

#endif /*FRIENDSTATUSCHANGMESSAGE_H_*/
