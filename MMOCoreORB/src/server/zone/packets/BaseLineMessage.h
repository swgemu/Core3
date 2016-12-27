/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BASELINEMESSAGE_H_
#define BASELINEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/scene/variables/StringId.h"

class BaseLineMessage: public BaseMessage {
public:
	BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt) {
		insertShort(0x05);
		insertInt(0x68A75F0C);
		insertLong(oid);
		insertInt(name);
		insertByte(type);
		insertInt(0);

		insertShort(opcnt);

		setCompression(true);
	}

	inline void setSize() {
		insertInt(23, size() - 27);
	}

	inline void insertStringId(StringId* id) {
		insertAscii(id->getFile());
		insertInt(0);
		insertAscii(id->getStringID());
	}

	inline void insertCustomName(const UnicodeString& name) {
		insertUnicode(name);
	}

};

#endif /*BASELINEMESSAGE_H_*/
