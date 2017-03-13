/*
 * PlaceDecorationComponent.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: root
 */

#include "PlaceDecorationComponent.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/structure/StructureManager.h"

int PlaceDecorationComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const {
	if(creature == NULL || creature->getZoneServer() == NULL)
		return 1;

	ManagedReference<CityRegion*> city = creature->getCityRegion().get();

	if (city == NULL)
		return 1;

	CityManager* cityManager = creature->getZoneServer()->getCityManager();
	if(cityManager == NULL)
		return 1;

	if(!cityManager->canSupportMoreDecorations(city)) {
		StringIdChatParameter param("city/city", "no_more_decos");
		creature->sendSystemMessage(param);
		return 1;
	}

	StructureManager::instance()->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}
