#ifndef PLAYERCREATURE_H_
#define PLAYERCREATURE_H_

#include "client/zone/objects/creature/CreatureObject.h"
#include "system/lang/ref/Reference.h"
#include "zone/objects/scene/SceneObject.h"

class Zone;
namespace engine {
namespace lua {
class LuaObject;
}  // namespace lua
}  // namespace engine

class PlayerCreature : public CreatureObject {
protected:
	Reference<SceneObject*> follow;

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
