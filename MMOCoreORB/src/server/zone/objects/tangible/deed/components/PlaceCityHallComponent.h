/*
 * PlaceCityHallComponent.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef PLACECITYHALLCOMPONENT_H_
#define PLACECITYHALLCOMPONENT_H_

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

class PlaceCityHallComponent : public PlaceStructureComponent {
public:
	int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const;
	int notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure) const;
};


#endif /* PLACECITYHALLCOMPONENT_H_ */
