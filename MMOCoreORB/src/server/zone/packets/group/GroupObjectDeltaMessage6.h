/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTDELTAMESSAGE6_H_
#define GROUPOBJECTDELTAMESSAGE6_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/group/GroupObject.h"

class GroupObjectDeltaMessage6 : public DeltaMessage, public Logger {
	GroupObject* group;

public:
	GroupObjectDeltaMessage6(GroupObject* gr) : DeltaMessage(gr->getObjectID(), 'GRUP', 0x06) {
		//info(true) << "GroupObjectDeltaMessage6 called";

		group = gr;
	}

	void updateMembers() {
		GroupList* list = group->getGroupList();

		if (list == nullptr)
			return;

		// Update Member List
		startUpdate(0x01);

		int memberListSize = list->size();

		insertInt(memberListSize);
		insertInt(memberListSize);

		for (int i = 0; i < memberListSize; ++i) {
			insertByte(0x01); // Add to list?
			insertShort((uint8)i); // Location on list

			GroupMember* member = list->get(i);

			insertLong(list->getMemberID(i));
			insertAscii(list->getMemberName(i));
		}

		// Update Ship List
		startUpdate(0x02);

		insertInt(memberListSize);
		insertInt(memberListSize);

		for (int j = 0; j < memberListSize; j++) {
			insertByte(0x01); // Add to list?
			insertShort((uint8)j); // Location on list

			insertLong(list->getMemberShipID(j));
			insertInt(j);
		}

		startUpdate(0x04);
		insertShort((uint16)group->getGroupLevel());

		startUpdate(0x06);
		insertLong(group->getMasterLooterID());
	}

	void updateLevel(uint16 value) {
		startUpdate(0x04);
		insertShort(value);
	}

	void updateLootRules(uint64 looter, int rule) {
		startUpdate(0x06);
		insertLong(looter);
		startUpdate(0x07);
		insertInt(rule);
	}
};

#endif /*GROUPOBJECTDELTAMESSAGE6_H_*/
