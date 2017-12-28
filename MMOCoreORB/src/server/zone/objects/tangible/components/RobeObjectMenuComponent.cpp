/*
 * RobeObjectMenuComponent.cpp
 *
 *  Created on: Apr 5, 2012
 *      Author: katherine
 */

#include "RobeObjectMenuComponent.h"

#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
}  // namespace packets
}  // namespace zone
}  // namespace server

void RobeObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}


int RobeObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
