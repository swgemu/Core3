/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONMESSAGE_H_
#define NPCCONVERSATIONMESSAGE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/StringIdChatParameter.h"

//TODO: This needs more research!

class NpcConversationMessage : public ObjectControllerMessage {
public:

	NpcConversationMessage(CreatureObject* creo, const UnicodeString& message)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		insertUnicode(message);
	}

	/*NpcConversationMessage(CreatureObject* creo, const String& file, const String& stringid)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		//insertUnicode(UnicodeString("@" + file + ":" + stringid));
		StringIdChatParameter params(file, stringid);
		params.addToPacketStream(this);

		insertInt(0);
	}*/

	NpcConversationMessage(CreatureObject* creo, StringIdChatParameter& stringid)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {
		int offset = getOffset();
		insertInt(0); //size

		insertShort(0); //unknown

		stringid.insertToMessage(this);

		int size = (getOffset() - offset - 4) / 2;

		insertInt(offset, size);
	}
};

#endif
