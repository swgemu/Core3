/*
 * PlaceCityHallComponent.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef PLACECITYHALLCOMPONENT_H_
#define PLACECITYHALLCOMPONENT_H_

#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"

class PlaceCityHallComponent : public PlaceStructureComponent {
public:
	int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle);
	int notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure);
};


#endif /* PLACECITYHALLCOMPONENT_H_ */
