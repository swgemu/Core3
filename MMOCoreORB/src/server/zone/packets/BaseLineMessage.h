/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BASELINEMESSAGE_H_
#define BASELINEMESSAGE_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/StringId.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"

class BaseLineMessage: public BaseMessage {
public:
	BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt) {
		insertShort(0x05);
		insertInt(0x68A75F0C);
		insertLong(oid);
		insertInt(name);
		//insertInt(generateRandomObjectCRC());
		insertByte(type);
		insertInt(0);

		insertShort(opcnt);

		setCompression(true);
	}

	uint32 generateRandomObjectCRC() {
		int idx = System::random(4);

		if (idx == 0)
			return 0x4352454F; // CREO;
		else if (idx == 1)
			return 0x504C4159; // PLAY
		else if (idx == 2)
			return 0x54414E4F; // TANO
		/*else if (idx == 3)
		 return 0x45525550;	// GRUP*/
		else
			return System::random(0xFFFFFFFF);
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

	//

};

#endif /*BASELINEMESSAGE_H_*/
