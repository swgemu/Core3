/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef RESOURCEHARVESTERACTIVATEPAGEMESSAGE_H_
#define RESOURCEHARVESTERACTIVATEPAGEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ResourceHarvesterActivatePageMessage : public BaseMessage {
public:
	ResourceHarvesterActivatePageMessage(uint64 oid) : BaseMessage() {
    	insertShort(0x02);
    	insertInt(0xBD18C679);  // CRC
    	insertLong(oid);
	}

};

#endif /* RESOURCEHARVESTERACTIVATEPAGEMESSAGE_H_ */
