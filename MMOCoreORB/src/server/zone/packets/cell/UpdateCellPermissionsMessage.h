/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATECELLPERMISSIONSMESSAGE_H_
#define UPDATECELLPERMISSIONSMESSAGE_H_

#include "engine/engine.h"

class UpdateCellPermissionsMessage : public BaseMessage {
public:
    UpdateCellPermissionsMessage(uint64 coId, bool allowEntry = true) : BaseMessage() {
		insertShort(0x03); // insertShort(0x04);
		insertInt(0xF612499C);  // CRC

        insertByte((byte) allowEntry); //0 denies, 1 allows.
        insertLong(coId);
	}
};
#endif /*UPDATECELLPERMISSIONSMESSAGE_H_*/
