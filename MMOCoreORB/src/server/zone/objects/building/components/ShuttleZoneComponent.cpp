/*
 * ShuttleZoneComponent.cpp
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#include "ShuttleZoneComponent.h"

#include <stddef.h>

#include "server/zone/objects/building/tasks/ScheduleShuttleTask.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

void ShuttleZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

	if (sceneObject == NULL || !sceneObject->isCreatureObject())
		return;

	CreatureObject* shuttle = cast<CreatureObject*>( sceneObject);

	Reference<ScheduleShuttleTask*> task = new ScheduleShuttleTask(shuttle, zone);
	task->schedule(1000);
}

void ShuttleZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
	ZoneComponent::notifyRemoveFromZone(sceneObject);
}
