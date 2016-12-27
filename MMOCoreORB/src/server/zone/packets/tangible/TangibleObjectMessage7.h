/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE7_H_
#define TANGIBLEOBJECTMESSAGE7_H_

#include "server/zone/packets/BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class TangibleObjectMessage7 : public BaseLineMessage {
public:
	TangibleObjectMessage7(TangibleObject* tano) 
			: BaseLineMessage(tano->getObjectID(), 0x54414E4F, 7, 0x02) {
		insertLong(0);
		insertLong(0);

		setSize();
	}
	
};
#endif /*TANGIBLEOBJECTMESSAGE7_H_*/
