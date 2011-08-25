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

void ShuttleZoneComponent::insertToZone(SceneObject* sceneObject, Zone* zone) {
	if (sceneObject->isInQuadTree())
			return;

	ZoneComponent::insertToZone(sceneObject, zone);

	if (sceneObject == NULL || !sceneObject->isCreatureObject())
		return;

	CreatureObject* shuttle = (CreatureObject*) sceneObject;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Reference<PlanetTravelPoint*> ptp = planetManager->getNearestPlanetTravelPoint(shuttle, 128.f);

	if (ptp != NULL) {
		planetManager->scheduleShuttle(shuttle);
		ptp->setShuttle(shuttle);
	}
}

void ShuttleZoneComponent::removeFromZone(SceneObject* sceneObject) {
	ZoneComponent::removeFromZone(sceneObject);
}
