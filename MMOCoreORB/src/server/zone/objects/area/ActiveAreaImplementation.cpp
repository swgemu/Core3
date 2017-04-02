/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "server/zone/objects/area/ActiveArea.h"
#include "events/ActiveAreaEvent.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"

bool ActiveAreaImplementation::containsPoint(float px, float py, uint64 cellid) {
	if (cellObjectID != 0 && cellObjectID != cellid)
		return false;

	return containsPoint(px, py);
}

bool ActiveAreaImplementation::containsPoint(float px, float py) {
	if (areaShape == NULL) {
		return QuadTreeEntryImplementation::containsPoint(px, py);
	}

	return areaShape->containsPoint(px, py);
}

void ActiveAreaImplementation::enqueueEnterEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyEnter(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.getReferenceUnsafeStaticCast(), obj, ActiveAreaEvent::ENTEREVENT);
	obj->executeOrderedTask(task);

#endif
}

void ActiveAreaImplementation::enqueueExitEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyExit(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.getReferenceUnsafeStaticCast(), obj, ActiveAreaEvent::EXITEVENT);
	obj->executeOrderedTask(task);

#endif
}

void ActiveAreaImplementation::notifyEnter(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID == obj->getParentID())
		notifyObservers(ObserverEventType::ENTEREDAREA, obj);

	if (obj->isPlayerCreature() && attachedScenery.size() > 0) {
		ManagedReference<SceneObject*> sceno = obj;
		Vector<ManagedReference<SceneObject* > > scene = attachedScenery;

		Core::getTaskManager()->executeTask([=] () {
			for (int i = 0; i < scene.size(); i++) {
				SceneObject* scenery = scene.get(i);
				Locker locker(scenery);

				scenery->sendTo(sceno, true);
			}
		}, "SendSceneryLambda");
	}
}

void ActiveAreaImplementation::notifyExit(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID != obj->getParentID())
		notifyObservers(ObserverEventType::EXITEDAREA, obj);

	if (obj->isPlayerCreature() && attachedScenery.size() > 0) {
		ManagedReference<SceneObject*> sceno = obj;
		Vector<ManagedReference<SceneObject* > > scene = attachedScenery;

		Core::getTaskManager()->executeTask([=] () {
			for (int i = 0; i < scene.size(); i++) {
				SceneObject* scenery = scene.get(i);
				Locker locker(scenery);

				scenery->sendDestroyTo(sceno);
			}
		}, "SendDestroySceneryLambda");
	}
}

void ActiveAreaImplementation::setZone(Zone* zone) {
	this->zone = zone;
}

bool ActiveAreaImplementation::intersectsWith(ActiveArea* area) {
	if (areaShape == NULL) {
		return false;
	}

	return areaShape->intersectsWith(area->getAreaShape());
}

void ActiveAreaImplementation::initializeChildObject(SceneObject* controllerObject) {
	ManagedReference<SceneObject*> objectParent = controllerObject->getParent().get();

	if (objectParent != NULL && objectParent->isCellObject()) {
		setCellObjectID(objectParent->getObjectID());
	}
}
