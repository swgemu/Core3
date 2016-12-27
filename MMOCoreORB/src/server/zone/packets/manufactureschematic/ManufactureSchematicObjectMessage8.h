/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE8_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE8_H_

#include "server/zone/packets/BaseLineMessage.h"

class ManufactureSchematicObjectMessage8 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage8(uint64 oid) 
			: BaseLineMessage(oid, 0x4D53434F, 8, 0x00) {

		setSize();
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE8_H_*/
