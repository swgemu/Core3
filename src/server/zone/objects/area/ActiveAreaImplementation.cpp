/*
 * ActiveAreaImplementation.cpp
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#include "ActiveArea.h"
#include "server/zone/objects/player/PlayerCreature.h"

bool ActiveAreaImplementation::containsPoint(float px, float py) {
	return (((px - positionX) * (px - positionX)) + ((py - positionY) * (py - positionY)) <= radius2 );
}

void ActiveAreaImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	if (obj == NULL || obj == this)
		return;

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	if (scno->getActiveArea() != _this && containsPoint(scno->getPositionX(), scno->getPositionY())) {
		scno->setActiveArea(_this);
		notifyEnter(scno);

	} else if (scno->getActiveArea() == _this && !containsPoint(scno->getPositionX(), scno->getPositionY())) {
		scno->setActiveArea(NULL);
		notifyExit(scno);
	}
}

void ActiveAreaImplementation::notifyDissapear(QuadTreeEntry* obj) {
	if (obj == NULL || obj == this)
		return;

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	if (scno->getActiveArea() == _this) {
		scno->setActiveArea(NULL);
		notifyExit(scno);
	}
}
