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

	if (cityRegion != NULL ) {
		int i;
		for ( i = cityRegion->getCityRank(); i > 0; i--)
			cityRegion->destroyAllStructuresForRank(uint8(i));

		cityRegion->removeAllTerminals();
		cityRegion->removeAllSkillTrainers();

		if (cityRegion->getCityHall() == sceneObject) {
			cityRegion->setCityHall(NULL);
		}

		CityManager* cityManager = sceneObject->getZoneServer()->getCityManager();

		cityManager->destroyCity(cityRegion);
	}

	ZoneComponent::destroyObjectFromWorld(sceneObject, sendSelfDestroy);
}
