/*
 * StructureZoneComponent.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: TragD
 */

#include "server/zone/objects/scene/components/ZoneComponent.h"
#include "StructureZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/building/BuildingObject.h"
void StructureZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

	if (sceneObject->isBuildingObject()) {
		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject);
		if (building->hasTemplateChildCreatures())
			building->spawnChildCreaturesFromTemplate();
	}
}

void StructureZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
	ZoneComponent::notifyRemoveFromZone(sceneObject);

	//moved to StructureManager::destroyStructure
}
