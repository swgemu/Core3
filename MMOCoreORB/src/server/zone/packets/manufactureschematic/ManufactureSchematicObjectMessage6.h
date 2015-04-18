/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE6_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

class ManufactureSchematicObjectMessage6 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage6(uint64 oid, uint32 schematicCRC) 
			: BaseLineMessage(oid, 0x4D53434F, 6, 0x07) {

		insertInt(0x76); // THIS IS UNKNOWN BUT THIS NUMBER IS FOUND IN TANO6 PACKET
		insertInt(0);

		insertInt(schematicCRC);
		insertShort(1);
		
		setSize();
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE6_H_*/
