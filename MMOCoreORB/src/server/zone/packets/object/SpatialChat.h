/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SPATIALCHAT_H_
#define SPATIALCHAT_H_

#include "ObjectControllerMessage.h"

#include "server/chat/StringIdChatParameter.h"

class SpatialChat: public ObjectControllerMessage {
public:
	SpatialChat(uint64 senderid, uint64 recvid, const UnicodeString& message, uint64 target, uint32 moodid,
			uint32 mood2, uint8 langID) :
		ObjectControllerMessage(recvid, 0x0B, 0xF4) {
		insertLong(senderid);
		insertLong(target);
		insertUnicode(message);

		insertShort(0x32);
		insertShort((uint16) mood2);
		insertShort((uint16) moodid);
		insertByte(0);
		insertByte(langID);

		insertLong(0);
		insertInt(0);
		insertInt(0);

		setCompression(true);
	}

	SpatialChat(uint64 senderid, uint64 recvid, const String& file, const String& stringid, uint64 target, uint32 moodid,
			uint32 mood2, uint8 langID) :
		ObjectControllerMessage(recvid, 0x0B, 0xF4) {
		insertLong(senderid);
		insertLong(target);
		insertUnicode(UnicodeString("@" + file + ":" + stringid));

		insertShort(0x32);
		insertShort((uint16) mood2);
		insertShort((uint16) moodid);
		insertByte(0);
		insertByte(langID);

		insertLong(0);
		insertInt(0);
		insertInt(0);

		setCompression(true);
	}

	SpatialChat(uint64 senderid, uint64 recvid, StringIdChatParameter& stringid, uint64 target, uint16 moodid, uint16 mood2) :
		ObjectControllerMessage(recvid, 0x0B, 0xF4) {

		insertLong(senderid);
		insertLong(target);
		insertInt(0);
		insertShort(0x32);
		insertShort(mood2);
		insertShort(moodid);
		insertByte(0);
		insertByte(0);

		int offset = getOffset();

		insertInt(0);

		stringid.insertToMessage(this);

		int size = (getOffset() - offset - 4) / 2;

		//System::out << "size: " << size << endl;

		insertInt(offset, size);

		insertInt(0);
		/*insertInt(0);
		insertInt(0);
		insertLong(0);
		insertLong(0);*/

		setCompression(true);
	}
};

#endif /*SPATIALCHAT_H_*/
