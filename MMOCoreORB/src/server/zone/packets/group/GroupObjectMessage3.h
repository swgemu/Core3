/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTMESSAGE3_H_
#define GROUPOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/group/GroupObject.h"

class GroupObjectMessage3 : public BaseLineMessage {
public:
	GroupObjectMessage3(GroupObject* grup)
			: BaseLineMessage(grup->getObjectID(), 0x4352454F, 3, 0x04) {
		insertFloat(1);

		insertAscii("String_id_table");
		insertInt(0);
		insertShort(0);
		insertInt(0);
		insertInt(0);

		setSize();
	}
	
};

#endif /*GROUPOBJECTMESSAGE3_H_*/
