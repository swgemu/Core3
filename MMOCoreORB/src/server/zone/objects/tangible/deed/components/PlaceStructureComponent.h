/*
 * PlaceStructureComponent.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef PLACESTRUCTURECOMPONENT_H_
#define PLACESTRUCTURECOMPONENT_H_

#include "server/zone/objects/scene/components/SceneObjectComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
namespace tangible {
namespace deed {
	class Deed;
}
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::tangible::deed;


class PlaceStructureComponent : public SceneObjectComponent {
public:
	virtual int placeStructure(CreatureObject* creature, Deed* deed, float x, float y, int angle);
};


#endif /* PLACESTRUCTURECOMPONENT_H_ */
