/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLOURISH_H_
#define FLOURISH_H_

#include "ObjectControllerMessage.h"

class Flourish : public ObjectControllerMessage {
public:
	Flourish(CreatureObject* creo, int flourishid) 
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x166) {
		insertInt(flourishid);
	}

};

#endif /*FLOURISH_H_*/
