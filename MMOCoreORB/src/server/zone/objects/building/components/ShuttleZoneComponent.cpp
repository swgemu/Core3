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

void ShuttleZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

	if (sceneObject == NULL || !sceneObject->isCreatureObject())
		return;

	CreatureObject* shuttle = cast<CreatureObject*>( sceneObject);

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	Reference<PlanetTravelPoint*> ptp = planetManager->getNearestPlanetTravelPoint(shuttle, 128.f);

	if (ptp != NULL) {
		planetManager->scheduleShuttle(shuttle);
		ptp->setShuttle(shuttle);
	}
}

void ShuttleZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) {
	ZoneComponent::notifyRemoveFromZone(sceneObject);
}
