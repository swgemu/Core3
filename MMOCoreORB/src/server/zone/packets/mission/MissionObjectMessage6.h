/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MISSIONOBJECTMESSAGE6_H_
#define MISSIONOBJECTMESSAGE6_H_

#include "server/zone/packets/BaseLineMessage.h"

class MissionObjectMessage6 : public BaseLineMessage {
public:
	MissionObjectMessage6(MissionObject* mi)
			: BaseLineMessage(mi->getObjectID(), 0x4D49534F, 6, 0x02) {

		insertInt(0x79);
		/*insertLong(0);
		insertLong(0);
		insertLong(0);
		insertLong(0);
		insertLong(0);
		insertLong(0);*/


		setSize();
	}
};

#endif /*MISSIONOBJECTMESSAGE6_H_*/
