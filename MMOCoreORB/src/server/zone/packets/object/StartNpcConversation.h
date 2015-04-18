/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTNPCCONVERSATION_H_
#define STARTNPCCONVERSATION_H_

#include "ObjectControllerMessage.h"

class StartNpcConversation : public ObjectControllerMessage {
	
public:

	StartNpcConversation(CreatureObject* creo, uint64 npcID, const String& ascii)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDD) {
	
		insertLong(npcID);
		insertByte(0);
		insertAscii(ascii.toCharArray());
		insertInt(0);		
		
	}
};
#endif
