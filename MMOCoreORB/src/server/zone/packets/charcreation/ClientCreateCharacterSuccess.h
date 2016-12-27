/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCREATECHARACTERSUCCESS_H_
#define CLIENTCREATECHARACTERSUCCESS_H_

#include "engine/service/proto/BaseMessage.h"

//This packet is sent when we verify the data (namely the charname) when the client sends ClientCreateCharacter
//We are assigning an object id here. after this packet, continue with the ZONELOGIN sequence as usual

class ClientCreateCharacterSuccess : public BaseMessage {
public:
	ClientCreateCharacterSuccess(uint64 objid) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x1DB575CC); //opcode: ClientCreateCharacterSuccess
		insertLong(objid);
	}

};


#endif /*CLIENTCREATECHARACTERSUCCESS_H_*/
