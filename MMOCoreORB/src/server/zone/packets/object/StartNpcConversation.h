/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTNPCCONVERSATION_H_
#define STARTNPCCONVERSATION_H_

#include "ObjectControllerMessage.h"

class StartNpcConversation : public ObjectControllerMessage {

public:

	StartNpcConversation(CreatureObject* creo, uint64 npcID, byte starter, const String& ascii, uint32 crc = 0)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDD) {

		insertLong(npcID); // LongID of Conversing NPC
		insertByte(starter); // Conversation Starter (0 - player or 1 - npc)
		insertAscii(ascii.toCharArray());
		insertInt(crc); //Mobile CRC for JTL convos

	}
};
#endif
