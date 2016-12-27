/*
 * RobeObjectMenuComponent.cpp
 *
 *  Created on: Apr 5, 2012
 *      Author: katherine
 */

#include "RobeObjectMenuComponent.h"

void RobeObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}


int RobeObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
