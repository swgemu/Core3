/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SPATIALCHAT_H_
#define SPATIALCHAT_H_

#include "ObjectControllerMessage.h"

#include "server/chat/StringIdChatParameter.h"

class SpatialChat: public ObjectControllerMessage {
public:
	SpatialChat(uint64 senderID, uint64 targetID, uint64 chatTargetID, const UnicodeString& message, uint16 volume, uint32 spatialChatType, uint32 moodType, uint32 chatFlags, uint8 languageID) :
		ObjectControllerMessage(targetID, 0x0B, 0xF4) {
		insertLong(senderID);
		insertLong(chatTargetID);
		insertUnicode(message);

		insertShort(volume);
		insertShort((uint16) spatialChatType);
		insertShort((uint16) moodType);
		insertByte(chatFlags);
		insertByte(languageID);

		insertLong(0);
		insertInt(0);
		insertInt(0);

		setCompression(true);
	}

	SpatialChat(uint64 senderID, uint64 targetID, uint64 chatTargetID, const String& file, const String& stringid, uint16 volume, uint32 spatialChatType, uint32 moodType, uint32 chatFlags, uint8 languageID) :
		ObjectControllerMessage(targetID, 0x0B, 0xF4) {
		insertLong(senderID);
		insertLong(chatTargetID);
		insertUnicode(UnicodeString("@" + file + ":" + stringid));

		insertShort(volume);
		insertShort((uint16) spatialChatType);
		insertShort((uint16) moodType);
		insertByte(chatFlags);
		insertByte(languageID);

		insertLong(0);
		insertInt(0);
		insertInt(0);

		setCompression(true);
	}

	SpatialChat(uint64 senderID, uint64 targetID, uint64 chatTargetID, StringIdChatParameter& stringid, uint16 volume, uint16 spatialChatType, uint16 moodType, uint32 chatFlags, uint8 languageID) :
		ObjectControllerMessage(targetID, 0x0B, 0xF4) {

		insertLong(senderID);
		insertLong(chatTargetID);
		insertInt(0);
		insertShort(volume);
		insertShort(spatialChatType);
		insertShort(moodType);
		insertByte(chatFlags);
		insertByte(languageID);

		int offset = getOffset();

		insertInt(0);

		stringid.insertToMessage(this);

		int size = (getOffset() - offset - 4) / 2;

		insertInt(offset, size);

		insertInt(0);
		setCompression(true);
	}
};

#endif /*SPATIALCHAT_H_*/
