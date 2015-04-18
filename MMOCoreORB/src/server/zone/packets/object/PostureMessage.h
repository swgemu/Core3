/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POSTUREMESSAGE_H_
#define POSTUREMESSAGE_H_

#include "ObjectControllerMessage.h"

class PostureMessage : public ObjectControllerMessage {
public:
	PostureMessage(CreatureObject* creo) 
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x131) {
		insertByte(creo->getPosture());
		insertByte(1);
	}

};

#endif /*POSTUREMESSAGE_H_*/
