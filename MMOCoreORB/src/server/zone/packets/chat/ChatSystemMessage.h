/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATSYSTEMMESSAGE_H_
#define CHATSYSTEMMESSAGE_H_

#include "engine/engine.h"
#include "server/chat/StringIdChatParameter.h"

class ChatSystemMessage : public BaseMessage {

public:
	enum {
		DISPLAY_CHATANDSCREEN = 0x00,
		DISPLAY_CHATONLY      = 0x02
	};

public:

	ChatSystemMessage(const UnicodeString& message, byte displayType = DISPLAY_CHATANDSCREEN) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x6D2A6413); //ChatSystemMessage

		insertByte(displayType);

		insertUnicode(message);
		insertInt(0); //No params

		setCompression(true);
	}

	ChatSystemMessage(StringIdChatParameter& sid, byte displayType = DISPLAY_CHATANDSCREEN) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x6D2A6413);

		insertByte(displayType);
		insertInt(0);

		int offset = getOffset();

		insertInt(0);

		sid.insertToMessage(this);

		int size = (getOffset() - offset - 4) / 2;

		insertInt(offset, size);

		setCompression(true);
	}
};

#endif /*CHATSYSTEMMESSAGE_H_*/
