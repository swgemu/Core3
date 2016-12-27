/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ERRORMESSAGE_H_
#define ERRORMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ErrorMessage : public BaseMessage {
public:
	ErrorMessage(const String& errorType, const String& errorMsg, uint8 fatal) : BaseMessage() {
    	insertShort(0x03);
    	insertInt(0xB5ABF91A);
    	
        insertAscii(errorType);
        insertAscii(errorMsg);
        insertByte(fatal);
      }

};

#endif /*ERRORMESSAGE_H_*/
