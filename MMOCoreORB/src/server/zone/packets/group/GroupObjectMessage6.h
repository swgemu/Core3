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

class GroupObjectMessage6 : public BaseLineMessage {
	GroupObject* grup;

public:
	GroupObjectMessage6(GroupObject* gr)
			: BaseLineMessage(gr->getObjectID(), 0x4352454F, 6, 0x08) {

		grup = gr;

		insertInt(0); // wtf is this
		groupLists(); //Group Members
		groupShips(); //Group Member Ships
		insertInt(0); // Group Name Length?
		insertAscii(""); //Group Name
		insertShort((uint16)gr->getGroupLevel()); //Group Level
		insertInt(0); // Formation Name CRC
		insertLong(gr->getMasterLooterID()); //Master Looter objectID
		insertInt(gr->getLootRule()); //Loot Rule: 0=Free4All, 1=Master Looter, 2=Lottery, 3=Random //7
		setSize();
	}

	void groupShips() {
		GroupShipList* gslist = grup->getGroupShipList();

		if (gslist->size() < 1)
			insertInt(0);
		else
			gslist->insertToMessage(this);
	}

	void groupLists() {
		GroupList* list = grup->getGroupList();
		list->insertToMessage(this);
	}

};

#endif /*GROUPOBJECTMESSAGE6_H_*/
