/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONADDFRIEND_H_
#define CHATONADDFRIEND_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnAddFriend : public BaseMessage {
public:
	ChatOnAddFriend() : BaseMessage() {

		insertShort(0x03);
		insertInt(0x2B2A0D94);  // CRC
		insertLong(0);

	}

};

#endif /*CHATONADDFRIEND_H_*/
