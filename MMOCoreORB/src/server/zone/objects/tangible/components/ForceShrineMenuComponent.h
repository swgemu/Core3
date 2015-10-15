/*
 * ForceShrineMenuComponent.h
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#ifndef FORCESHRINEMENUCOMPONENT_H_
#define FORCESHRINEMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

namespace server {
namespace zone {
namespace objects {
namespace player {
	class PlayerObject;
}
}
}
}

using namespace server::zone::objects::player;

class ForceShrineMenuComponent : public TangibleObjectMenuComponent {

public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	// This finds a trainer for jedi unlocks.
	virtual void findTrainerObject(CreatureObject* player, PlayerObject* ghost);

};


#endif /* FORCESHRINEMENUCOMPONENT_H_ */
