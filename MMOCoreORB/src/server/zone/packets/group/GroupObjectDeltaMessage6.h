/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTDELTAMESSAGE6_H_
#define GROUPOBJECTDELTAMESSAGE6_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/group/GroupObject.h"

class GroupObjectDeltaMessage6 : public DeltaMessage {
	GroupObject* grup;

public:
	GroupObjectDeltaMessage6(GroupObject* gr)
			: DeltaMessage(gr->getObjectID(), 0x4352454F, 6) {
		grup = gr;
	}

	void updateLevel(uint16 value) {
		startUpdate(0x04);
		insertShort(value);
	}

	void updateMemberShips(GroupShipList* gsl) {
		startUpdate(0x03);
		gsl->insertToMessage(this);
	}

	void updateLootRules(uint64 looter, int rule) {
		startUpdate(0x06);
		insertLong(looter);
		startUpdate(0x07);
		insertInt(rule);
	}

};

#endif /*GROUPOBJECTDELTAMESSAGE6_H_*/
