/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE8_H_
#define TANGIBLEOBJECTMESSAGE8_H_

#include "server/zone/packets/BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class TangibleObjectMessage8 : public BaseLineMessage {
public:
	TangibleObjectMessage8(TangibleObject* tano) 
			: BaseLineMessage(tano->getObjectID(), 0x54414E4F, 8, 0x00) {

		setSize();
	}
	
};
#endif /*TANGIBLEOBJECTMESSAGE*_H_*/
