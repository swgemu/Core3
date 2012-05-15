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
namespace structure {
	class StructureDeed;
}
}
}
namespace structure {
	class StructureObject;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::tangible::deed::structure;
using namespace server::zone::objects::structure;

class PlaceStructureComponent : public SceneObjectComponent {
public:
	virtual int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle);
	virtual int notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure);
};


#endif /* PLACESTRUCTURECOMPONENT_H_ */
