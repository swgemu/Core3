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

	void initialUpdate() {
		//info(true) << "GroupObjectDeltaMessage6 -- initialUpdate";

		// Members
		startUpdate(0x01);

		GroupList* list = group->getGroupList();

		if (list == nullptr)
			return;

		int size = list->size();
		int updCounter = list->getUpdateCounter();

		insertInt(size);
		insertInt(updCounter);

		for (int i = 0; i < size; ++i) {
			insertByte(0x1); // Initial
			insertShort(i); // Location on list

			CreatureObject* member = list->get(i).get().get();

			insertLong(member->getObjectID());
			insertAscii(member->getDisplayedName());
		}

		// Members Ships
		startUpdate(0x02);

		// Insert players ships
		insertInt(size); // Size
		insertInt(updCounter); // counter

		for (int j = 0; j < size; ++j) {
			insertByte(0x1); // Initial
			insertShort(j); // Location on list

			insertLong(0);// Ship ID
			insertInt(j); // Vector location
		}

		startUpdate(0x04);
		insertShort((uint16)group->getGroupLevel());

		startUpdate(0x06);
		insertLong(group->getMasterLooterID());
	}

	void updateMembers() {
		//info(true) << "GroupObjectDeltaMessage6 -- updateMembers";

		// Members
		startUpdate(0x01);

		GroupList* list = group->getGroupList();

		if (list == nullptr)
			return;

		int size = list->size();
		int updCounter = list->getUpdateCounter();

		insertInt(size);
		insertInt(updCounter);

		for (int i = 0; i < size; ++i) {
			insertByte(0x2); // Update
			insertShort((uint8)i); // Location on list

			CreatureObject* member = list->get(i).get().get();

			insertLong(member->getObjectID());
			insertAscii(member->getDisplayedName());
		}

		// Members Ships
		startUpdate(0x02);

		// Insert players ships
		insertInt(size); // Size
		insertInt(updCounter); // counter

		for (int j = 0; j < size; ++j) {
			insertByte(0x2); // Update
			insertShort(j); // Location on list

			insertLong(0);// Ship ID
			insertInt(j); // Vector location
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
