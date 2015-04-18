/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTDELTAMESSAGE6_H_
#define GROUPOBJECTDELTAMESSAGE6_H_

#include "../DeltaMessage.h"

#include "server/zone/objects/group/GroupObject.h"

class GroupObjectDeltaMessage6 : public DeltaMessage {
	GroupObject* grup;
	
public:
	GroupObjectDeltaMessage6(GroupObject* gr)
			: DeltaMessage(gr->getObjectID(), 0x4352454F, 6) {
		grup = gr;
	}


	/*void addMember(SceneObject* player, int idx) {
		startUpdate(0x01);

		startList(1, grup->getNewListCount(1));
		
		insertByte(1);
		insertShort(idx);
		insertLong(player->getObjectID());
		insertAscii(player->getgetObjectName()->getCustomString().toString());
	}
	
	void removeMember(int idx) {
		startUpdate(0x01);
		
		startList(1, grup->getNewListCount(1));
		insertByte(0);
		insertShort(idx);
	}
	
	void updateLeader(SceneObject* newLeader, SceneObject* oldLeader, int oldLeaderIdx) {
		startUpdate(0x01);
		
		startList(2, grup->getNewListCount(2));
		
		insertByte(2);
		insertShort(oldLeaderIdx);
		insertLong(oldLeader->getObjectID());
		insertAscii(oldLeader->getObjectName()->getCustomString().toString());
		
		insertByte(2);
		insertShort(0);
		insertLong(newLeader->getObjectID());
		insertAscii(newLeader->getObjectName()->getCustomString().toString());
	}*/
	
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
