/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "events/ActiveAreaEvent.h"
#include "server/zone/Zone.h"
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

		EXECUTE_TASK_2(scene, sceno, {
			for (int i = 0; i < scene_p.size(); i++) {
				SceneObject* scenery = scene_p.get(i);
				Locker locker(scenery);

				scenery->sendTo(sceno_p, true);
			}
		});
	}
}

void ActiveAreaImplementation::notifyExit(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID != obj->getParentID())
		notifyObservers(ObserverEventType::EXITEDAREA, obj);

	if (obj->isPlayerCreature() && attachedScenery.size() > 0) {
		ManagedReference<SceneObject*> sceno = obj;
		Vector<ManagedReference<SceneObject* > > scene = attachedScenery;

		EXECUTE_TASK_2(scene, sceno, {
			for (int i = 0; i < scene_p.size(); i++) {
				SceneObject* scenery = scene_p.get(i);
				Locker locker(scenery);

				scenery->sendDestroyTo(sceno_p);
			}
		});
	}
}

bool ActiveAreaImplementation::intersectsWith(ActiveArea* area) {
	if (areaShape == NULL) {
		return false;
	}

	return areaShape->intersectsWith(area->getAreaShape());
}

void ActiveAreaImplementation::initializeChildObject(SceneObject* controllerObject) {
	ManagedReference<SceneObject*> objectParent = controllerObject->getParent();

	if (objectParent != NULL && objectParent->isCellObject()) {
		setCellObjectID(objectParent->getObjectID());
	}
}
