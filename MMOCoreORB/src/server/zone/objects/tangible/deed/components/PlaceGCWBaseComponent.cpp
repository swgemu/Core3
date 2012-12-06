/*
 * PlaceGCWBaseComponent.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: root
 */
#include "server/zone/Zone.h"
#include "PlaceGCWBaseComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/structure/StructureManager.h"
int PlaceGCWBaseComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) {

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return 1;

	Zone* zone = creature->getZone();

	if (zone == NULL)
		return 1;

	//Check the gcwmanager to make sure more are allowed on this planet
	GCWManager* gcwMan = zone->getGCWManager();


	if(gcwMan->isPlanetCapped()){
		creature->sendSystemMessage("Planet is capped for player bases");
		return 1;
	}

	int result = StructureManager::instance()->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}

int PlaceGCWBaseComponent::notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure) {
	PlaceStructureComponent::notifyStructurePlaced(deed, creature, structure);

	Zone* zone = creature->getZone();

	if (zone == NULL)
		return 1;

	BuildingObject* buildingObject = cast<BuildingObject*>(structure);
	if (buildingObject != NULL && buildingObject->isGCWBase()) {
		GCWManager* gcwManager = zone->getGCWManager();
		if (gcwManager != NULL)
			gcwManager->registerGCWBase(buildingObject, true);

	}
	return 0;
}






