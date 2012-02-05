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
	int placeStructure(CreatureObject* creature, Deed* deed, float x, float y, int angle);
};


#endif /* PLACECITYHALLCOMPONENT_H_ */
