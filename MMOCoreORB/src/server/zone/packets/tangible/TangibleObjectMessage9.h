/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTMESSAGE9_H_
#define TANGIBLEOBJECTMESSAGE9_H_

#include "server/zone/packets/BaseLineMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class TangibleObjectMessage9 : public BaseLineMessage {
public:
	TangibleObjectMessage9(const TangibleObject* tano)
			: BaseLineMessage(tano, 0x54414E4F, 9, 0x00) {

		setSize();
	}

};
#endif /*TANGIBLEOBJECTMESSAGE9_H_*/
