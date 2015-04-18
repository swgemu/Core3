/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TANGIBLEOBJECTDELTAMESSAGE6_H_
#define TANGIBLEOBJECTDELTAMESSAGE6_H_

#include "../../packets/DeltaMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class TangibleObjectDeltaMessage6 : public DeltaMessage {
	TangibleObject* tano;

public:
	TangibleObjectDeltaMessage6(TangibleObject* ta, uint32 objType = 0x54414E4F)
		: DeltaMessage(ta->getObjectID(), objType, 6) {
		tano = ta;
	}

};


#endif /* TANGIBLEOBJECTDELTAMESSAGE6_H_ */
