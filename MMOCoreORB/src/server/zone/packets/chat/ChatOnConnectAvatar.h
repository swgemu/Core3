/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONCONNECTAVATAR_H_
#define CHATONCONNECTAVATAR_H_

//Mail - "You got mail"
//ChatOnConnectAvatar

#include "engine/service/proto/BaseMessage.h"

class ChatOnConnectAvatar : public BaseMessage {
public:
	ChatOnConnectAvatar() : BaseMessage() {
		insertShort(0x01);
		insertInt(0xD72FE9BE);  // CRC
	} 
	
};

#endif /*CHATONCONNECTAVATAR_H_*/
