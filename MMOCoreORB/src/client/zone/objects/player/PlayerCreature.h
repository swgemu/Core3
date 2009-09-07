#ifndef PLAYERCREATURE_H_
#define PLAYERCREATURE_H_

#include "../creature/CreatureObject.h"

class Zone;

class PlayerCreature : public CreatureObject {
protected:
	ReferenceSlot<SceneObject*> follow;

public:
	PlayerCreature(LuaObject* templateData);

	void insertToZone(Zone* zone);
	void updatePosition(float x, float z, float y);

	void activatePositionUpdate();

	void setFollow(SceneObject* object) {
		follow = object;
	}

	SceneObject* getFollowObject() {
		return follow;
	}

};

#endif /* PLAYER_H_ */
