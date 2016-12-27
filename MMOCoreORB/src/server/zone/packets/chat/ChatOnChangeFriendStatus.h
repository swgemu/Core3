/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATONCHANGEFRIENDSTATUS_H_
#define CHATONCHANGEFRIENDSTATUS_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnChangeFriendStatus : public BaseMessage {
public:
	ChatOnChangeFriendStatus(uint64 oid, const String& name, const String& server, bool add) : BaseMessage() {

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

#endif /*CHATONCHANGEFRIENDSTATUS_H_*/
