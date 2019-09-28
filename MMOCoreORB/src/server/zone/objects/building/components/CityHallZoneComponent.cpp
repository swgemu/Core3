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

void CityHallZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) const {
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
		ZoneComponent::destroyObjectFromWorld(sceneObject, sendSelfDestroy);
		return;
	}

	ManagedReference<CityRegion*> cityRegion = sceneObject->getCityRegion().get();

	if (cityRegion != nullptr ) {
		Locker clocker(cityRegion, sceneObject);

		if (cityRegion->getCityHall() == sceneObject) {
			cityRegion->setCityHall(nullptr);
		}

		clocker.release();

		CityManager* cityManager = zoneServer->getCityManager();

		cityManager->destroyCity(cityRegion);
	}

	ZoneComponent::destroyObjectFromWorld(sceneObject, sendSelfDestroy);
}
