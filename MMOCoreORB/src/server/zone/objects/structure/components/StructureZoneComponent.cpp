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
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"

void StructureZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

}

void StructureZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) {
	ZoneComponent::notifyRemoveFromZone(sceneObject);

	//moved to StructureManager::destroyStructure
}
