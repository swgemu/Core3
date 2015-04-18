/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STATICOBJECTMESSAGE3_H_
#define STATICOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/staticobject/StaticObject.h"

class StaticObjectMessage3 : public BaseLineMessage {
public:
	StaticObjectMessage3(StaticObject* stao) 
			: BaseLineMessage(stao->getObjectID(), 0x4F415453, 3, 4) {

		insertInt(0);
		insertStringId(stao->getObjectName());
		insertCustomName(stao->getCustomObjectName());
		insertInt(0xFF);

		setSize();
	}
	
};

#endif /*STATICOBJECTMESSAGE3_H_*/

