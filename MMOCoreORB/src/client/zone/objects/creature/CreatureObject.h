#ifndef CREATUREOBJECT_H_
#define CREATUREOBJECT_H_

#include "../tangible/TangibleObject.h"

class CreatureObject : public TangibleObject {
protected:

public:
	CreatureObject(LuaObject* templateData);

	void parseBaseline3(Message* message);

};

#endif /*CREATUREOBJECT_H_*/
