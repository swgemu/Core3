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

		GroupList* list = group->getGroupList();
		const DeltaVectorMap<uint64, uint64>* shipList = group->getGroupShips();

		if (list == nullptr || shipList == nullptr)
			return;

		// Members
		startUpdate(0x01);

		int listSize = list->size();

		insertInt(listSize);
		insertInt(list->getUpdateCounter());

		for (int i = 0; i < listSize; ++i) {
			insertByte(0x1); // Initial
			insertShort(i); // Location on list

			CreatureObject* member = list->get(i).get().get();

			if (member == nullptr)
				continue;

			insertLong(member->getObjectID());
			insertAscii(member->getDisplayedName());
		}

		// Members Ships
		startUpdate(0x02);

		// Insert players ships
		insertInt(listSize); // Size
		insertInt(shipList->getUpdateCounter()); // counter

		for (int j = 0; j < listSize; ++j) {
			insertByte(0x1); // Update
			insertShort(j); // Location on list

			CreatureObject* member = group->getGroupMember(j);

			uint64 memberShipID = 0;

			if (member != nullptr && member->isPlayerCreature()) {
				memberShipID = shipList->get(member->getObjectID());
			}

			insertLong(memberShipID); // Ship ID
			insertInt(j); // List location
		}

		// Group Name?
		startUpdate(0x03);
		insertAscii("");

		// Group Level
		startUpdate(0x04);
		insertShort((uint16)group->getGroupLevel());

		// Unknown
		//startUpdate(0x05);
		//insertInt(0);

		// Master Looter ID
		startUpdate(0x06);
		insertLong(group->getMasterLooterID());

		// Loot Rule
		startUpdate(0x07);
		insertInt(group->getLootRule());
	}

	void updateMembers() {
		//info(true) << "GroupObjectDeltaMessage6 -- updateMembers";

		GroupList* list = group->getGroupList();
		const DeltaVectorMap<uint64, uint64>* shipList = group->getGroupShips();

		if (list == nullptr || shipList == nullptr)
			return;

		// Members
		startUpdate(0x01);

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

		int listSize = shipList->size();

		// Insert players ships
		insertInt(listSize); // Size
		insertInt(shipList->getUpdateCounter()); // counter

		for (int j = 0; j < listSize; ++j) {
			insertByte(0x2); // Update
			insertShort(j); // Location on list

			CreatureObject* member = group->getGroupMember(j);

			uint64 memberShipID = 0;

			if (member != nullptr && member->isPlayerCreature()) {
				memberShipID = shipList->get(member->getObjectID());
			}

			insertLong(memberShipID); // Ship ID
			insertInt(j); // List location
		}

		// Group Name?
		startUpdate(0x03);
		insertAscii("");

		// Group Level
		startUpdate(0x04);
		insertShort((uint16)group->getGroupLevel());

		// Unknown
		//startUpdate(0x05);
		//insertInt(0);

		// Master Looter ID
		startUpdate(0x06);
		insertLong(group->getMasterLooterID());

		// Loot Rule
		startUpdate(0x07);
		insertInt(group->getLootRule());
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
