/*
 * PlaceDecorationComponent.h
 *
 *  Created on: Apr 8, 2013
 *      Author: root
 */

#ifndef PLACEDECORATIONCOMPONENT_H_
#define PLACEDECORATIONCOMPONENT_H_

#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
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

class PlaceDecorationComponent : public PlaceStructureComponent {
public:
	int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const;

};

#endif /* PLACEDECORATIONCOMPONENT_H_ */
