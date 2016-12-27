/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTRANDOMNAMERESPONSE_H_
#define CLIENTRANDOMNAMERESPONSE_H_

#include "engine/service/proto/BaseMessage.h"

class ClientRandomNameResponse : public BaseMessage {
public:
	ClientRandomNameResponse(String raceIff, String name) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xE85FB868); //opcode: ClientRandomNameReponse
		insertAscii(raceIff);
		insertUnicode(UnicodeString(name)); //Insert a randomly generated name here, dont need to do that now..
		insertAscii("ui", 0x02); //STF file to use loading the desciption for Approval_Type. Pretty much static unless we really need a custom approval_type message
		insertInt(0x00); //spacer
		insertAscii("name_approved", 0x0D); //needed for the generated name to display.

		setCompression(false);
	}
	
};

#endif /*CLIENTRANDOMNAMERESPONSE_H_*/
