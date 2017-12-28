/*
 * StructureZoneComponent.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: TragD
 */

#include "StructureZoneComponent.h"

#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "system/platform.h"

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
