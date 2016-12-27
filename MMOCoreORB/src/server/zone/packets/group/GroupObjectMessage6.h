/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPOBJECTMESSAGE6_H_
#define GROUPOBJECTMESSAGE6_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/group/GroupObject.h"

class GroupObjectMessage6 : public BaseLineMessage {
	GroupObject* grup;
	
public:
	GroupObjectMessage6(GroupObject* gr)
			: BaseLineMessage(gr->getObjectID(), 0x4352454F, 6, 0x06) {
		
		grup = gr;
		insertFloat(128.f);
		
		groupLists();
		
		insertAscii("");
		insertShort((uint16)gr->getGroupLevel());
		insertInt(0);
		insertLong(gr->getMasterLooterID()); //Master Looter objectID
		insertInt(gr->getLootRule()); //Loot Rule: 0=Free4All, 1=Master Looter, 2=Lottery, 3=Random
		
		setSize();
	}
	
	void groupLists() {
		GroupList* list = grup->getGroupList();
		list->insertToMessage(this);
		
		insertInt(0); // uses the same method as above to parse this
		insertInt(0);
	}
	
};

#endif /*GROUPOBJECTMESSAGE6_H_*/
