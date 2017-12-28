/*
 * PlaceGCWBaseComponent.h
 *
 *  Created on: Dec 2, 2012
 *      Author: root
 */

#ifndef PLACEGCWBASECOMPONENT_H_
#define PLACEGCWBASECOMPONENT_H_

#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace structure {
class StructureObject;
}  // namespace structure
namespace tangible {
namespace deed {
namespace structure {
class StructureDeed;
}  // namespace structure
}  // namespace deed
}  // namespace tangible
}  // namespace objects
}  // namespace zone
}  // namespace server

class PlaceGCWBaseComponent : public PlaceStructureComponent {
public:
	int placeStructure(server::zone::objects::tangible::deed::structure::StructureDeed* deed, server::zone::objects::creature::CreatureObject* creature, float x, float y, int angle) const;
	int notifyStructurePlaced(server::zone::objects::tangible::deed::structure::StructureDeed* deed, server::zone::objects::creature::CreatureObject* creature, server::zone::objects::structure::StructureObject* structure) const;
};




#endif /* PLACEGCWBASECOMPONENT_H_ */
