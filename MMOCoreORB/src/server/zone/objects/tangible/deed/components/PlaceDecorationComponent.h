/*
 * PlaceDecorationComponent.h
 *
 *  Created on: Apr 8, 2013
 *      Author: root
 */

#ifndef PLACEDECORATIONCOMPONENT_H_
#define PLACEDECORATIONCOMPONENT_H_

#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"

class PlaceDecorationComponent : public PlaceStructureComponent {
public:
	int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const;

};

#endif /* PLACEDECORATIONCOMPONENT_H_ */
