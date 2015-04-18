/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SITONOBJECT_H_
#define SITONOBJECT_H_

#include "ObjectControllerMessage.h"

class SitOnObject : public ObjectControllerMessage {
public:
	SitOnObject(CreatureObject* creo, float x, float y, float z) 
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x13B) {
		
		insertLong(creo->getParentID()); // Cell Object ID
		insertFloat(x);
		insertFloat(y);
		insertFloat(z);
	}
	
};

#endif /*SITONOBJECT_H_*/
