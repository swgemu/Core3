/*
 * ShuttleInstallationZoneComponent.cpp
 *
 * Created on: Apr 7, 2012
 *      Author: TragD
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "server/zone/objects/structure/components/StructureZoneComponent.h"
#include "server/zone/objects/installation/components/ShuttleInstallationZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/tasks/ShuttleDepartureTask.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/region/CityRegion.h"

void ShuttleInstallationZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) {
	StructureZoneComponent::notifyInsertToZone(sceneObject, zone);

}

void ShuttleInstallationZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) {
	StructureZoneComponent::notifyRemoveFromZone(sceneObject);

	if (sceneObject->isStructureObject()){

		StructureObject* structureObject = cast<StructureObject*>(sceneObject);
		ManagedReference<Zone*> zone = sceneObject->getZone();

		if (zone != NULL && structureObject->isInstallationObject()){

			ManagedReference<InstallationObject*> installationObject = cast<InstallationObject*>(structureObject);

			if (installationObject->isShuttleInstallation()){

				ManagedReference<CityRegion*> cityRegion = structureObject->getCityRegion();
				ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

				if (cityRegion != NULL){

					planetManager->removePlayerCityTravelPoint(cityRegion->getRegionName());
					cityRegion->removeShuttleInstallation();
				}

				SortedVector < ManagedReference<SceneObject*> > *childObjects
											= structureObject->getChildObjects();

				ManagedReference<CreatureObject*> shuttle = NULL;

				for (int i = 0; i < childObjects->size(); ++i) {

					if (!childObjects->get(i)->isTerminal()) {
						shuttle = cast<CreatureObject*>(childObjects->get(i).get());
						break;
					}
				}

				if (shuttle != NULL)
					planetManager->removeShuttle(shuttle);

			}
		}
	}
}

