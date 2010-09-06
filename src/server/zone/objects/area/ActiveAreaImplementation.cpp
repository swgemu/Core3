/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "ActiveArea.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "ActiveAreaEvent.h"

bool ActiveAreaImplementation::containsPoint(float px, float py) {
	return (((px - positionX) * (px - positionX)) + ((py - positionY) * (py - positionY)) <= radius2 );
}

void ActiveAreaImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	if (obj == NULL || obj == this)
		return;

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	if (!scno->hasActiveArea(_this) && containsPoint(scno->getPositionX(), scno->getPositionY())) {
		scno->addActiveArea(_this);
		enqueueEnterEvent(scno);

	} else if (scno->hasActiveArea(_this) && !containsPoint(scno->getPositionX(), scno->getPositionY())) {
		scno->dropActiveArea(_this);
		enqueueExitEvent(scno);
	}
}

void ActiveAreaImplementation::enqueueEnterEvent(SceneObject* obj) {
	Reference<Task*> task = new ActiveAreaEvent(_this, obj, ActiveAreaEvent::ENTEREVENT);
	task->schedule(100);
}

void ActiveAreaImplementation::enqueueExitEvent(SceneObject* obj) {
	Reference<Task*> task = new ActiveAreaEvent(_this, obj, ActiveAreaEvent::EXITEVENT);
	task->schedule(100);
}

void ActiveAreaImplementation::notifyDissapear(QuadTreeEntry* obj) {
	if (obj == NULL || obj == this)
		return;

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	if (scno->hasActiveArea(_this)) {
		scno->dropActiveArea(_this);
		enqueueExitEvent(scno);
	}
}
