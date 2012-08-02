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
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/CityRegion.h"

int PlaceStructureComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) {
	Zone* zone = creature->getZone();

	if (zone != NULL)
		StructureManager::instance()->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}

int PlaceStructureComponent::notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structureObject) {
	structureObject->setSurplusMaintenance(deed->getSurplusMaintenance());
	structureObject->setSurplusPower(deed->getSurplusPower());

	if (structureObject->isInstallationObject()) {
		InstallationObject* installationObject = cast<InstallationObject*>(structureObject);
		installationObject->setExtractionRate(deed->getExtractionRate());
		installationObject->setHopperSizeMax(deed->getHopperSize());
	}

	return 0;
}
