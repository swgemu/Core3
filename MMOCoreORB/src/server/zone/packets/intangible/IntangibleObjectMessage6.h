/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTANGIBLEOBJECTMESSAGE6_H_
#define INTANGIBLEOBJECTMESSAGE6_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/intangible/IntangibleObject.h"

class IntangibleObjectMessage6 : public BaseLineMessage {
public:
	IntangibleObjectMessage6(IntangibleObject* itno)
			: BaseLineMessage(itno->getObjectID(), 0x4F4E5449, 6, 2) {

		insertInt(0x6E);
		// should be "monster_detail" for creature mounts (Although it seems to have no effect) and other itno's use
		// the _n or _name files here.
		StringId stringId;
		insertStringId(&stringId);
		insertCustomName(itno->getDetailedDescription());

		setSize();
	}

};

#endif /*INTANGIBLEOBJECTMESSAGE6_H_*/
