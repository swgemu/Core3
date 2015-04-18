/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTIDMESSAGE_H_
#define CLIENTIDMESSAGE_H_

#include "engine/engine.h"

class ClientIDMessage : public BaseMessage {
public:
	ClientIDMessage(uint32 accid, uint32 session) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xD5899226);

		insertInt(0); // unk
		insertInt(0); // dataLen
		insertInt(session); // session key
		insertInt(accid);
	}

};


#endif /*CLIENTIDMESSAGE_H_*/
