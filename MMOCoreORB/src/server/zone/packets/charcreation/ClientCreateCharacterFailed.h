/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCREATECHARACTERFAILED_H_
#define CLIENTCREATECHARACTERFAILED_H_

#include "engine/engine.h"

//This packet is sent when we verify the data (namely the charname) when the client sends ClientCreateCharacter
//If it fails we are sending the failure notice here:

class ClientCreateCharacterFailed : public BaseMessage {
public:
	ClientCreateCharacterFailed(String error_String) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xDF333C6E); //opcode: ClientCreateCharacterFailed
		insertInt(0x00); //Unicode String, used instead of stf file. We'll never use it.
		insertAscii("ui", 0x02); //ui file used for the client to pull the error message from - static
		insertInt(0x00); //static spacer
		insertAscii(error_String); 
		//Please note, error_String must be a specefic error String from table.
		//See: ClientCreateCharacterFailed

		setCompression(false);
	}
};

#endif /*CLIENTCREATECHARACTERFAILED_H_*/
