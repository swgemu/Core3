/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYMUSICMESSAGE_H_
#define PLAYMUSICMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class PlayMusicMessage : public BaseMessage {
public:

    PlayMusicMessage(const String& soundFile, uint64 target = 0, int unkInt = 1, bool unkBool = false) : BaseMessage() {
		insertShort(0x05);
		insertInt(0x04270D8A);  // CRC
        insertAscii(soundFile);
        
        //?
        insertLong(target);
        insertInt(unkInt);
        insertByte(unkBool);
        
	}
	
};

#endif /*PLAYMUSICMESSAGE_H_*/
