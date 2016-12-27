/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATFRIENDSLISTUPDATE_H_
#define CHATFRIENDSLISTUPDATE_H_

#include "engine/service/proto/BaseMessage.h"

class ChatFriendsListUpdate : public BaseMessage {
public:
	ChatFriendsListUpdate(const String& name, const String& server, bool online) : BaseMessage() {

		insertShort(0x03);
		insertInt(0x6CD2FCD8);  // CRC

		insertAscii("SWG");
		insertAscii(server);
		insertAscii(name);

		insertByte(online);

	}

};

#endif /*CHATFRIENDSLISTUPDATE_H_*/
