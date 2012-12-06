/*
 * PlaceGCWBaseComponent.h
 *
 *  Created on: Dec 2, 2012
 *      Author: root
 */

#ifndef PLACEGCWBASECOMPONENT_H_
#define PLACEGCWBASECOMPONENT_H_

#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"

class PlaceGCWBaseComponent : public PlaceStructureComponent {
public:
	int placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle);
	int notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure);
};




#endif /* PLACEGCWBASECOMPONENT_H_ */
