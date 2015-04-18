/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTCONTROLLERMESSAGE_H_
#define OBJECTCONTROLLERMESSAGE_H_

#include "engine/engine.h"

class ObjectControllerMessage : public BaseMessage {
public:
	ObjectControllerMessage(uint64 objid, uint32 header1, uint32 header2, bool comp = true) {

		insertShort(0x05);
		insertInt(0x80CE5E46); // CRC
		insertInt(header1);
		insertInt(header2);
		insertLong(objid);
		insertInt(0x00);

		setCompression(comp);

	}

};


#endif /*OBJECTCONTROLLERMESSAGE_H_*/

