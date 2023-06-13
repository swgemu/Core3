/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTMESSAGE6_H_
#define GROUPOBJECTMESSAGE6_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/Zone.h"

class GroupObjectMessage6 : public BaseLineMessage, public Logger {
	GroupObject* group;

public:
	GroupObjectMessage6(GroupObject* gr) : BaseLineMessage(gr->getObjectID(), 'GRUP', 0x06, 0x08) {
		//info(true) << "GroupObjectMessage6 called";

		group = gr;

		insertInt(0x00); // ??

		// op count 0x08 works without these 4
		//insertAscii("string_id_table");
		//insertInt(0x0); // Unkncown Int
		//insertShort(0x0); // Unkncown Short
		// End test

		insertMembers(); // Group Members + Group Ships

		insertAscii(""); // Group Name
		insertShort(group->getGroupLevel()); // Group Level

		insertInt(0x0); // Formation Name CRC
		insertLong((uint64)group->getMasterLooterID()); //Master Looter objectID
		insertInt(group->getLootRule()); //Loot Rule: 0=Free4All, 1=Master Looter, 2=Lottery, 3=Random

		setSize();
	}


	void insertMembers() {
		GroupList* list = group->getGroupList();
		list->insertToMessage(this);
	}
};

#endif /*GROUPOBJECTMESSAGE6_H_*/
