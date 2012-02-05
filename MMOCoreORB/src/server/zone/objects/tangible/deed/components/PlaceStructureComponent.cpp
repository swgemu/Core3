/*
 * PlaceStructureComponent.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#include "PlaceStructureComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/Zone.h"

int PlaceStructureComponent::placeStructure(CreatureObject* creature, Deed* deed, float x, float y, int angle) {
	StructureManager* structureManager = creature->getZone()->getStructureManager();
	structureManager->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}
