/*
 * ShuttleZoneComponent.cpp
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#include "ShuttleZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/tasks/ScheduleShuttleTask.h"

void ShuttleZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const {
	ZoneComponent::notifyInsertToZone(sceneObject, zone);

	if (sceneObject == nullptr) {
		error() << "ShuttleZoneComponent::notifyInsertToZone -- inserted object is null";
		return;
	}

	if (!sceneObject->isCreatureObject()) {
		error() << "ShuttleZoneComponent::notifyInsertToZone -- inserted object is not a Creature Object";
		return;
	}

	CreatureObject* shuttle = cast<CreatureObject*>( sceneObject);

	Reference<ScheduleShuttleTask*> task = new ScheduleShuttleTask(shuttle, zone);

	int delay = 60; //(System::random(10) + 1) * 60;

#ifdef SHUTTLE_TIMER_DEBUG
	info(true) << "ScheduleShuttleTask for " << zone->getZoneName() << " scheduled due to server loading in " << delay << " seconds.";
#endif

	task->schedule(delay * 1000);
}

void ShuttleZoneComponent::notifyRemoveFromZone(SceneObject* sceneObject) const {
	ZoneComponent::notifyRemoveFromZone(sceneObject);
}
