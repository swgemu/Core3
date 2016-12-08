#ifndef CREATUREOBJECT_H_
#define CREATUREOBJECT_H_

#include "client/zone/objects/tangible/TangibleObject.h"

class CreatureObject : public TangibleObject {
protected:
	uint32 actionCount;

public:
	CreatureObject(LuaObject* templateData);

	void parseBaseline3(Message* message);

	uint32 getNewActionCount() {
		return ++actionCount;
	}

};

#endif /*CREATUREOBJECT_H_*/
