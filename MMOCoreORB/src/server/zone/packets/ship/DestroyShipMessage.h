//
// Created by g on 1/1/18.
//

#ifndef CORE3_DESTROYSHIPMESSAGE_H
#define CORE3_DESTROYSHIPMESSAGE_H

#include "engine/service/proto/BaseMessage.h"

class DestroyShipMessage : public BaseMessage {
public:
	DestroyShipMessage(uint64 objectID, float scale) : BaseMessage() {
		insertShort(0x12);
		insertInt(0x5C680884);  // CRC
		insertLong(objectID);
		insertFloat(scale);
	}

};
#endif //CORE3_DESTROYSHIPMESSAGE_H
