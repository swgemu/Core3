/*
 * PlaceStructureComponent.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#include "PlaceStructureComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/Zone.h"

int PlaceStructureComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const {
	Zone* zone = creature->getZone();

	if (zone != nullptr)
		StructureManager::instance()->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}

int PlaceStructureComponent::notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structureObject) const {
	structureObject->setSurplusMaintenance(deed->getSurplusMaintenance());
	structureObject->setSurplusPower(deed->getSurplusPower());

	if (structureObject->isHarvesterObject()) {
		HarvesterObject* harvester = cast<HarvesterObject*>(structureObject);
		harvester->setMaxExtractionRate(deed->getExtractionRate());
		harvester->setMaxHopperSize(deed->getHopperSize());
	}

	return 0;
}
