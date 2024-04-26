/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTIDMESSAGE_H_
#define CLIENTIDMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ClientIDMessage : public BaseMessage {
public:
	ClientIDMessage(uint32 accountID, uint32 sessionKey) : BaseMessage() {
		std::cout << "ClientIDMessage -- called";

		insertShort(0x03);
		insertInt(0xD5899226);

		insertInt(0); // Spacer
		insertInt(0); // dataLen
		insertInt(sessionKey); // Session Key
		insertInt(accountID); // Account ID
	}

};


#endif /*CLIENTIDMESSAGE_H_*/
