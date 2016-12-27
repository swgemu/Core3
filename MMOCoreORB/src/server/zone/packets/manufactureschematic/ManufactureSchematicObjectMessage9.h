/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE9_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE9_H_

#include "server/zone/packets/BaseLineMessage.h"

class ManufactureSchematicObjectMessage9 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage9(uint64 oid) 
			: BaseLineMessage(oid, 0x4D53434F, 9, 0x00) {

		setSize();
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE9_H_*/
