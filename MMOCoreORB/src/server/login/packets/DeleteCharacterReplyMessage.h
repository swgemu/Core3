/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELETECHARACTERREPLYMESSAGE_H_
#define DELETECHARACTERREPLYMESSAGE_H_

#include "engine/engine.h"

class DeleteCharacterReplyMessage : public BaseMessage {
public:
	DeleteCharacterReplyMessage(int Failure) : BaseMessage() {
    	insertShort(0x03);
		insertInt(0x8268989B); //DeleteCharacterReplyMessage
		insertInt(Failure);
      }
};


#endif /*DELETECHARACTERREPLYMESSAGE_H_*/
