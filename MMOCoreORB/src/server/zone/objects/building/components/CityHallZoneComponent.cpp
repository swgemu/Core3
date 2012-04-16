/*
 * CityHallZoneComponent.cpp
 *
 *  Created on: 31/03/2012
 *      Author: victor
 */

#include "CityHallZoneComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/ZoneServer.h"

void CityHallZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) {
	CityRegion* cityRegion = sceneObject->getCityRegion();

	int i;
	for ( i = cityRegion->getCityRank(); i > 0; i--)
		cityRegion->destroyAllStructuresForRank(uint8(i));

	if (cityRegion == NULL) {
		//sceneObject->error("null city region for guild hall in destroyObjectFromWorld");

		ZoneComponent::destroyObjectFromWorld(sceneObject, sendSelfDestroy);

		return;
	} else if (cityRegion->getCityHall() == sceneObject) {
		cityRegion->setCityHall(NULL);
	}

	CityManager* cityManager = sceneObject->getZoneServer()->getCityManager();

	cityManager->destroyCity(cityRegion);

	ZoneComponent::destroyObjectFromWorld(sceneObject, sendSelfDestroy);
}
