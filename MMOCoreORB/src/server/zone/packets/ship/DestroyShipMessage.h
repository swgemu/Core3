//
// Created by g on 1/1/18.
//

#ifndef DESTROYSHIPMESSAGE_H
#define DESTROYSHIPMESSAGE_H

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
#endif //DESTROYSHIPMESSAGE_H
