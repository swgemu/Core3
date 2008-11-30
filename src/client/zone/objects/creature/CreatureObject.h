#ifndef CREATUREOBJECT_H_
#define CREATUREOBJECT_H_

#include "../scene/SceneObject.h"

class CreatureObject : public SceneObject {
protected:
	String name;

public:
	CreatureObject(sys::uint64 oid);
};

#endif /*CREATUREOBJECT_H_*/
