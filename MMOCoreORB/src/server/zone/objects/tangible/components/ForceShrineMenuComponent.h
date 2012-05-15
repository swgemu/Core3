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

class ForceShrineMenuComponent : public TangibleObjectMenuComponent {
public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

};


#endif /* FORCESHRINEMENUCOMPONENT_H_ */
