/*
 * ShuttleZoneComponent.cpp
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "ShuttleZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/tasks/ShuttleDepartureTask.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/ActiveArea.h"

void ShuttleZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

	if (sceneObject == NULL || !sceneObject->isCreatureObject())
		return;

	CreatureObject* shuttle = cast<CreatureObject*>( sceneObject);

	ManagedReference<CityRegion*> cityRegion = shuttle->getCityRegion();

	if ((cityRegion != NULL) && (cityRegion->getMayorID() != 0)){
		//cityRegion->setShuttleInstallation(structureObject);
		float x = shuttle->getWorldPositionX();
		float y = shuttle->getWorldPositionY();
		float z = shuttle->getWorldPositionZ();

		Vector3 arrivalVector(x, y, z);

		String zoneName = zone->getZoneName();

		if (shuttle != NULL){
			//System::out << cityRegion->getRegionName() << "\n";
			PlanetTravelPoint* planetTravelPoint = new PlanetTravelPoint(zoneName, cityRegion->getRegionName(), arrivalVector, arrivalVector, shuttle);
			zone->getPlanetManager()->addPlayerCityTravelPoint(planetTravelPoint);
			cityRegion->setShuttleID(shuttle->getObjectID());
			zone->getPlanetManager()->scheduleShuttle(shuttle);
		}
	}

	else{

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		Reference<PlanetTravelPoint*> ptp = planetManager->getNearestPlanetTravelPoint(shuttle, 128.f);

		if (ptp != NULL) {
			planetManager->scheduleShuttle(shuttle);
			ptp->setShuttle(shuttle);
		} else {
			sceneObject->error("PlanetTravelPoint not found in zone " + zone->getZoneName());
		}
	}
}

void ShuttleZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) {
	ZoneComponent::notifyRemoveFromZone(sceneObject);
}
