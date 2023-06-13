/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BASELINEMESSAGE_H_
#define BASELINEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/scene/variables/StringId.h"
#include "server/zone/objects/scene/SceneObject.h"

class BaseLineMessage: public BaseMessage {
public:
	BaseLineMessage(const SceneObject* obj, uint32 name, uint8 type, uint16 opcnt) {
		insertShort(0x05);
		insertInt(0x68A75F0C);
		insertLong(const_cast<SceneObject*>(obj)->getObjectID());
		insertInt(name);
		insertByte(type);
		insertInt(0);

		insertShort(opcnt);

		setCompression(true);
	}

	BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt) {
		insertShort(0x05);
		insertInt(0x68A75F0C);
		insertLong(oid); // Object ID
		insertInt(name); // Packet Name
		insertByte(type); // Packet Number
		insertInt(0); // Message Size - modified by setSize()

		insertShort(opcnt);

		setCompression(true);
	}

	inline void setSize() {
		insertInt(23, size() - 27);
	}

	inline void insertStringId(const StringId* id) {
		insertAscii(id->getFile());
		insertInt(0);
		insertAscii(id->getStringID());
	}

	inline void insertCustomName(const UnicodeString& name) {
		insertUnicode(name);
	}

};

#endif /*BASELINEMESSAGE_H_*/
