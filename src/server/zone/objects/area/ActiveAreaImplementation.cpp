/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "ActiveArea.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "events/ActiveAreaEvent.h"
#include "server/zone/Zone.h"

bool ActiveAreaImplementation::containsPoint(float px, float py) {
	return (((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY())) <= radius2 );
}

void ActiveAreaImplementation::insertToZone(Zone* newZone) {
	if (newZone == NULL)
		return;

	ManagedReference<SceneObject*> thisLocker = _this;

	Locker zoneLocker(newZone);

	if (isInQuadTree() && newZone != zone) {
		error("trying to insert to zone an object that is already in a different quadtree");

		removeFromZone();

		//StackTrace::printStackTrace();
	}

	SceneObjectImplementation::zone = newZone;

	QuadTree* regionTree = zone->getRegionTree();

	regionTree->insert(_this);

	regionTree->inRange(_this, 512);

	// lets update area to the in range players
	SortedVector<ManagedReference<SceneObject*> > objects;

	zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &objects);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = objects.get(i);

		Vector3 worldPos = object->getWorldPosition();

		if (!object->hasActiveArea(_this) && containsPoint(worldPos.getX(), worldPos.getY())) {
			object->addActiveArea(_this);
			enqueueEnterEvent(object);
		}
	}

	zone->addSceneObject(_this);
}

void ActiveAreaImplementation::removeFromZone() {
	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> thisLocker = _this;

	Locker zoneLocker(zone);

	QuadTree* regionTree = zone->getRegionTree();

	regionTree->remove(_this);

	while (inRangeObjectCount() > 0) {
		QuadTreeEntry* obj = getInRangeObject(0);

		if (obj != _this)
			obj->removeInRangeObject(_this);

		QuadTreeEntryImplementation::removeInRangeObject((int)0);
	}

	// lets remove the in range active areas of players
	SortedVector<ManagedReference<SceneObject*> > objects;

	zone->getInRangeObjects(getPositionX(), getPositionY(), 512, &objects);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* object = objects.get(i);

		if (object->hasActiveArea(_this)) {
			object->dropActiveArea(_this);
			enqueueExitEvent(object);
		}
	}

	Zone* oldZone = zone;
	zone = NULL;

	oldZone->dropSceneObject(_this);
}

void ActiveAreaImplementation::enqueueEnterEvent(SceneObject* obj) {
	Reference<Task*> task = new ActiveAreaEvent(_this, obj, ActiveAreaEvent::ENTEREVENT);

	Core::getTaskManager()->executeTask(task);
}

void ActiveAreaImplementation::enqueueExitEvent(SceneObject* obj) {
	Reference<Task*> task = new ActiveAreaEvent(_this, obj, ActiveAreaEvent::EXITEVENT);

	Core::getTaskManager()->executeTask(task);
}
