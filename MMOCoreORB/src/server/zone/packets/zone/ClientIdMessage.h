/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTIDMESSAGE_H_
#define CLIENTIDMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ClientIdMessage : public BaseMessage {
public:
	ClientIdMessage(uint32 accountID, uint32 sessionKey) : BaseMessage() {
		insertShort(0x03);
		insertInt(STRING_HASHCODE("ClientIdMessage"));

		insertInt(0x00); // Spacer
		insertInt(0x00); // dataLen
		insertInt(sessionKey); // Session Key
		insertInt(accountID); // Account ID
	}
};

#endif /*CLIENTIDMESSAGE_H_*/
