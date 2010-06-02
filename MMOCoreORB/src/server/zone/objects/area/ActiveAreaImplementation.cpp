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

	if (!scno->isPlayerCreature())
		return;

	PlayerCreature* player = (PlayerCreature*) scno;

	if (player->getActiveArea() != _this && containsPoint(player->getPositionX(), player->getPositionY())) {
		player->setActiveArea(_this);
		notifyEnter(player);

	} else if (player->getActiveArea() == _this && !containsPoint(player->getPositionX(), player->getPositionY())) {
		player->setActiveArea(NULL);
		notifyExit(player);
	}
}
