/*
 * RobeObjectMenuComponent.cpp
 *
 *  Created on: Apr 5, 2012
 *      Author: katherine
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "RobeObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void RobeObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}


int RobeObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

		// TODO: Add visibility increase.

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

}
