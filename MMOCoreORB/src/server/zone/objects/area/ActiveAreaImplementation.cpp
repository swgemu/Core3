/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "events/ActiveAreaEvent.h"
#include "server/zone/Zone.h"

bool ActiveAreaImplementation::containsPoint(float px, float py) {
	return (((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY())) <= radius2 );
}

void ActiveAreaImplementation::enqueueEnterEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyEnter(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.get(), obj, ActiveAreaEvent::ENTEREVENT);

	Core::getTaskManager()->executeTask(task);
#endif
}

void ActiveAreaImplementation::enqueueExitEvent(SceneObject* obj) {
#ifdef WITH_STM
	notifyExit(obj);
#else
	Reference<Task*> task = new ActiveAreaEvent(_this.get(), obj, ActiveAreaEvent::EXITEVENT);

	Core::getTaskManager()->executeTask(task);
#endif
}

void ActiveAreaImplementation::notifyEnter(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID == obj->getParentID())
		notifyObservers(ObserverEventType::ENTEREDAREA, obj);
}

void ActiveAreaImplementation::notifyExit(SceneObject* obj) {
	if (cellObjectID == 0 || cellObjectID == obj->getParentID())
		notifyObservers(ObserverEventType::EXITEDAREA, obj);
}
